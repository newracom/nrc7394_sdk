#include "nrc_sdk.h"
#include "nrc_psram_impl.h"
#include "psram.h"

static SemaphoreHandle_t psram_lock;

static void psram_reset()
{
	/* Send reset enable */
	psram_spi_reset(APM_PSRAM_REG_RESET_ENABLE);

	/* send reset command */
	psram_spi_reset(APM_PSRAM_REG_RESET);
}

int psram_init()
{
	if (psram_spi_init() != 0) {
		return -1;
	}

	vTaskDelay(pdMS_TO_TICKS(1));
	psram_reset();

	psram_lock = xSemaphoreCreateMutex();
	return 0;
}

bool psram_read_id()
{
	uint8_t psram_id[12];
	uint8_t density = 0;

	xSemaphoreTake(psram_lock, portMAX_DELAY);
	psram_spi_read(APM_PSRAM_REG_READ_ID, 0, psram_id, 12);
//	print_hex(psram_id, 12);
	xSemaphoreGive(psram_lock);
	system_printf("** PSRAM MFID : 0x0%1X\n", psram_id[0]);
	if (psram_id[1] != 0x5D) {
		system_printf("** PSRAM Not good...\n");
		return false;
	}

	density = psram_id[2] >> 5;
	system_printf("** PSRAM density :");
	switch (density) {
	case 0:
		system_printf("16 Mbit\n");
		break;
	case 1:
		system_printf("32 Mbit\n");
		break;
	case 2:
		system_printf("64 Mbit\n");
		break;
	case 3:
		system_printf("128 Mbit\n");
		break;
	case 4:
		system_printf("256 Mbit\n");
		break;
	default:
		system_printf("unknown\n");
	}
	return true;
}

int psram_read(uint32_t addr, uint8_t *buffer, uint32_t size)
{
	xSemaphoreTake(psram_lock, portMAX_DELAY);
	psram_spi_read(APM_PSRAM_REG_READ, addr, buffer, size);
	xSemaphoreGive(psram_lock);
	return 0;
}

int psram_write(uint32_t addr, uint8_t *buffer, uint32_t size)
{
	xSemaphoreTake(psram_lock, portMAX_DELAY);
	psram_spi_write(APM_PSRAM_REG_WRITE, addr, buffer, size);
	xSemaphoreGive(psram_lock);
	return 0;
}
