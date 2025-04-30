#ifndef TCP_CLI_H
#define TCP_CLI_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief TCP CLI initialization.
 *
 * Sets up the CLI callback, command execution function, and initializes TCP communication.
 */
void tcp_cli_init(void);

#ifdef __cplusplus
}
#endif

#endif // TCP_CLI_H
