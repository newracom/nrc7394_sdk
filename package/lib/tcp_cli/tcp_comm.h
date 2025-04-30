#ifndef TCP_COMM_H
#define TCP_COMM_H

#ifdef __cplusplus
extern "C" {
#endif

#define TCP_PRINTF_BUFFER_SIZE 256
#define tcp_printf(fmt, ...)					  \
	do {							  \
		char _tcp_buf[TCP_PRINTF_BUFFER_SIZE];			  \
		snprintf(_tcp_buf, sizeof(_tcp_buf), fmt, ##__VA_ARGS__); \
		tcp_comm_write(_tcp_buf);				  \
	} while (0)

extern volatile bool input_from_tcp;

/**
 * @brief Global pointer to the CLI output callback.
 *
 * This callback is used by net_printf to forward CLI output to the TCP client.
 */
extern void (*cli_output_callback)(const char *data);

/**
 * @brief Initializes the TCP communication module.
 *
 * Starts a TCP server task that listens on port 4000. When data is received from a TCP client,
 * each character is sent to the CLI input handler (as if it were arriving via UART).
 */
void tcp_comm_init(void);

/**
 * @brief Sets the CLI output callback.
 *
 * When a TCP client is connected, CLI commands can output their results via this callback.
 *
 * @param enable whether to enable output to tcp or not.
 */
void tcp_comm_set_output_callback(bool enable);

/**
 * @brief Gets the CLI output callback.
 *
 * Get output callback. I
 *
 * @return return pointer to output callback, NULL if not set.
 */
void *tcp_comm_get_output_callback();
#ifdef __cplusplus
}
#endif

#endif // TCP_COMM_H
