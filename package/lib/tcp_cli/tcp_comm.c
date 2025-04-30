#include "nrc_sdk.h"
#include "tcp_comm.h"
#include "util_cmd.h"     // For util_cmd_run_command
#include "FreeRTOS.h"
#include "task.h"
#include "lwip/sockets.h"
#include "lwip/inet.h"
#include "hal_uart.h"

#define TCP_PORT                     4000
#define BUFFER_SIZE                  512
#define TCP_SERVER_TASK_STACK_SIZE   2048
#define TCP_SERVER_TASK_PRIORITY     (tskIDLE_PRIORITY + 1)
#define TCP_SEND_QUEUE_LENGTH 10
typedef struct {
	char data[BUFFER_SIZE];
} tcp_send_item_t;

extern void (*g_cli_callback)(char);
// user_cli_output_callback is defined in hal_uart.c; declare it as extern.
extern void (*user_cli_output_callback)(const char *data);

// Global socket descriptors.
static int tcp_server_fd = -1;
static int tcp_client_fd = -1;

volatile bool input_from_tcp = false;

static QueueHandle_t tcpSendQueue = NULL;

static void tcp_send_task(void *pvParameters)
{
	tcp_send_item_t sendItem;

	for (;;) {
		if (xQueueReceive(tcpSendQueue, &sendItem, portMAX_DELAY) == pdTRUE) {
			if (tcp_client_fd != -1) {
				send(tcp_client_fd, sendItem.data, strlen(sendItem.data), 0);
			}
		}
	}
}

/**
 * @brief Queue data to the connected TCP client.
 *
 * @param data Null-terminated string to send.
 */
static void tcp_comm_write(const char *data)
{
    if (tcp_client_fd != -1 && tcpSendQueue != NULL) {
		tcp_send_item_t sendItem;
		memset(&sendItem, 0, sizeof(sendItem));
		strncpy(sendItem.data, data, BUFFER_SIZE - 1);

		if (xQueueSend(tcpSendQueue, &sendItem, portMAX_DELAY) != pdPASS) {
			CPA("Failed to queue TCP send data\n");
		}
    }
}

/**
 * @brief Sets the CLI output callback.
 *
 * Overrides default output with an output that sends data to the TCP client.
 *
 * @param enable whether the tcp output or not.
 */
void tcp_comm_set_output_callback(bool enable)
{
	if (enable) {
		user_cli_output_callback = tcp_comm_write;
	} else {
		user_cli_output_callback = NULL;
	}
}

void *tcp_comm_get_output_callback()
{
	return (void *) user_cli_output_callback;
}

/**
 * @brief TCP server task.
 *
 * This FreeRTOS task listens on port 4000 and processes received TCP data.
 * Each received character is passed to the CLI callback (converting '\n' to RETURN_KEY).
 *
 * @param pvParameters Unused.
 */
static void tcp_comm_server_task(void *pvParameters)
{
	(void)pvParameters;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
	char recv_buffer[BUFFER_SIZE];

	tcp_server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (tcp_server_fd < 0) {
		CPA("socket creation failed\n");
		vTaskDelete(NULL);
		return;
	}

	int opt = 1;
	setsockopt(tcp_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family      = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port        = htons(TCP_PORT);

	if (bind(tcp_server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		CPA("bind failed\n");
		close(tcp_server_fd);
		vTaskDelete(NULL);
		return;
	}

	if (listen(tcp_server_fd, 1) < 0) {
		CPA("listen failed\n");
		close(tcp_server_fd);
		vTaskDelete(NULL);
		return;
	}

	for (;;) {
		tcp_client_fd = accept(tcp_server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
		if (tcp_client_fd < 0) {
			CPA("accept failed\n");
			continue;
		}

		hal_uart_disable_irq();
		tcp_comm_set_output_callback(true);
		// Register TCP output function.
		tcp_comm_write("Welcome to CLI TCP Server. Type a command and press ENTER.\n> ");

		input_from_tcp = true;

		// Process incoming TCP data.
		for (;;) {
			tcp_comm_write(system_prompt_func());

			ssize_t bytes_received = recv(tcp_client_fd, recv_buffer, BUFFER_SIZE - 1, 0);
			if (bytes_received <= 0) {
				break;
			}
			recv_buffer[bytes_received] = '\0';

			// Send each received character to the CLI.
			for (int i = 0; i < bytes_received; i++) {
				char c = recv_buffer[i];
				if (c == '\n') {
					c = RETURN_KEY;  // Map LF to RETURN_KEY.
				}
				if (g_cli_callback) {
					g_cli_callback(c);
				}
			}
		}

		input_from_tcp = false;
		close(tcp_client_fd);
		tcp_client_fd = -1;
		tcp_comm_set_output_callback(false);
		hal_uart_enable_irq();
	}

	/* Unreachable code */
	close(tcp_server_fd);
	vTaskDelete(NULL);
}

/**
 * @brief Initializes the TCP communication module.
 *
 * Starts the TCP server task.
 */
void tcp_comm_init(void)
{
	BaseType_t result;

	// Create a queue to hold outgoing TCP data.
	tcpSendQueue = xQueueCreate(TCP_SEND_QUEUE_LENGTH, sizeof(tcp_send_item_t));
	if (tcpSendQueue == NULL) {
		CPA("Failed to create tcpSendQueue\n");
		return;
	}

	// Create the background task to process send requests.
	result = xTaskCreate(tcp_send_task,
					"TCP CLI Send",
					512,
					NULL,
					tskIDLE_PRIORITY + 2,
					NULL);
	if (result != pdPASS) {
		CPA("Failed to create TCP send task\n");
	}

	result = xTaskCreate(tcp_comm_server_task,
					"TCP CLI Server",
					TCP_SERVER_TASK_STACK_SIZE,
					NULL,
					TCP_SERVER_TASK_PRIORITY,
					NULL);
	if (result != pdPASS) {
		CPA("Failed to create TCP server task\n");
	}
}
