#if ENABLE_RESET_BUTTON

#include "nrc_sdk.h"
#include "nvs.h"
#include "button_action.h"

static TaskHandle_t reset_task_handle;
static int interrupt_vector = -1;

void reset_device()
{
	nvs_handle_t nvs_handle;
	if (nvs_open(NVS_DEFAULT_NAMESPACE, NVS_READWRITE, &nvs_handle) == NVS_OK) {
		if (nvs_erase_all(nvs_handle) != NVS_OK) {
			nrc_usr_print("nvs erase failed.\n");
		} else {
			nrc_usr_print("nvs erased all.\n");
		}
		nvs_close(nvs_handle);
	} else {
		nrc_usr_print("nvs open failed.\n");
	}

	nrc_usr_print("System Reset in 3 sec.\n", __func__);
	_delay_ms(3 * 1000);
	nrc_sw_reset();
}

void reset_task(void *param)
{
	while (1) {
		bool long_press = true;
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		nrc_usr_print("[%s] Notified, Hold button for %d sec\n", __func__, RESET_MAX);
		for (int i = 0; i < RESET_MAX; i++) {
			_delay_ms(1000);
			int value = 0;
			nrc_gpio_inputb(RESET_BUTTON, &value);
			if (value == 0) {
				nrc_usr_print("Reset Canceled.\n");
				long_press = false;
				break;
			} else {
				nrc_usr_print("Hold %d more seconds...\n", RESET_MAX - i);
			}
		}

		if (long_press) {
			reset_device();
		}

		if (interrupt_vector != -1) {
			system_irq_unmask(interrupt_vector);
		}
	}

	vTaskDelete(NULL);
}

void gpio_reset_handler(int vector)
{
	interrupt_vector = vector;
	system_irq_mask(vector);

	BaseType_t high_task_wakeup = pdFALSE;
	vTaskNotifyGiveFromISR(reset_task_handle, &high_task_wakeup);
	if (high_task_wakeup != pdFALSE) {
		portYIELD_FROM_ISR(high_task_wakeup);
	}
}

void init_reset_button()
{
	NRC_GPIO_CONFIG gpio_conf;

	gpio_conf.gpio_pin = RESET_BUTTON;
	gpio_conf.gpio_dir = GPIO_INPUT;
	gpio_conf.gpio_mode = GPIO_PULL_DOWN;
	gpio_conf.gpio_alt = GPIO_FUNC;
	nrc_gpio_config(&gpio_conf);

	// Use INT_VECTOR1 (INT_VECTOR0 is used by w5500)
	nrc_gpio_trigger_config(INT_VECTOR1, TRIGGER_EDGE, TRIGGER_HIGH, true);
	nrc_gpio_register_interrupt_handler(INT_VECTOR1, RESET_BUTTON, gpio_reset_handler);

	xTaskCreate(reset_task, "RESET TASK", 1024, NULL, uxTaskPriorityGet(NULL), &reset_task_handle);
}

#endif // ENABLE_RESET_BUTTON
