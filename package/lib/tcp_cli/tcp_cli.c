#include "nrc_sdk.h"
#include "util_cmd.h"
#include "tcp_comm.h"

#define MAX_INPUT_LENGTH      250
#define IS_ASCII(c)           ((c) > 0x1F && (c) < 0x7F)

extern void (*g_cli_callback)(char);
extern uint8_t g_binary_mode;
extern bool g_cli_typing;  // Indicates CLI typing status

// Function pointers for CLI prompt and command execution.
static char *(*cliPromptFunc)();
static int (*cliRunCommand)(char *);

// Structure representing a CLI input buffer.
typedef struct {
	char input[MAX_INPUT_LENGTH];
	int currentIndex;
	bool isQueued;
} CliBuffer;

// CLI buffers for UART and TCP input.
static CliBuffer uartCliBuffer;
static CliBuffer tcpCliBuffer;

static inline CliBuffer *getActiveBuffer()
{
	return (input_from_tcp) ? &tcpCliBuffer : &uartCliBuffer;
}

/**
 * @brief Prints the CLI prompt if a prompt function is registered.
 */
static void printCliPrompt(void)
{
	if (cliPromptFunc) {
		CPA("%s", cliPromptFunc());
	}
}

/**
 * @brief Processes a queued CLI command.
 *
 * This function is scheduled from an ISR once a complete command line is received.
 *
 * @param arg Pointer to the CLI buffer containing the command.
 * @return int32_t Always returns 0.
 */
static int32_t cliHandler(void *arg)
{
	CliBuffer *buffer = (CliBuffer *)arg;

	if (tcp_comm_get_output_callback() && !input_from_tcp) {
		return 0;
	}
	if (cliRunCommand) {
		cliRunCommand(buffer->input);
	}
	memset(buffer->input, 0, MAX_INPUT_LENGTH);
	buffer->currentIndex = 0;
	buffer->isQueued = false;

	if (!input_from_tcp) {
		// For UART mode, print the prompt after processing the command.
		printCliPrompt();
	}

	return 0;
}

/**
 * @brief Handles binary mode input.
 *
 * Processes input characters when the CLI is in binary mode.
 *
 * @param buffer Pointer to the current CLI buffer.
 * @param c The input character.
 */
static void handleBinaryMode(CliBuffer *buffer, char c)
{
	if (g_binary_mode == 0xff) {
		g_binary_mode = 4 + c * 4;  // Set expected length.
		buffer->currentIndex = 0;
	} else {
		buffer->input[buffer->currentIndex++] = c;
		g_binary_mode--;
		if (g_binary_mode == 0) {
			uint32_t baseAddress = *((uint32_t *)buffer->input);
			for (uint32_t offset = 4; offset < buffer->currentIndex; offset += 4) {
				WRITE_REG(baseAddress + offset - 4,
				*((uint32_t *)(&buffer->input[offset])));
			}
			CPA("OK\n");
			buffer->currentIndex = 0;
		}
	}
}

/**
 * @brief Processes a backspace character.
 *
 * @param buffer Pointer to the current CLI buffer.
 */
static void processBackspace(CliBuffer *buffer)
{
	if (buffer->currentIndex > 0) {
		if (!input_from_tcp) {
			CPA("\b \b");
		}
		buffer->currentIndex--;
	}
}

/**
 * @brief Processes the return key character, scheduling the command for execution.
 *
 * @param buffer Pointer to the current CLI buffer.
 */
static void processReturnKey(CliBuffer *buffer)
{
	g_cli_typing = !g_cli_typing;
	if (!input_from_tcp) {
		CPA("\n");
	}
	if (buffer->currentIndex > 0) {
		buffer->input[buffer->currentIndex] = '\0';
		buffer->isQueued = true;
		system_schedule_work_queue_from_isr(cliHandler, buffer, NULL);
	}
}

/**
 * @brief Processes a regular character input.
 *
 * @param buffer Pointer to the current CLI buffer.
 * @param c The input character.
 */
static void processRegularChar(CliBuffer *buffer, char c)
{
	if (IS_ASCII(c) && buffer->currentIndex < MAX_INPUT_LENGTH) {
		g_cli_typing = true;
		buffer->input[buffer->currentIndex++] = c;
		if (!input_from_tcp) {
			CPA("%c", c);
		}
	}
}

/**
 * @brief Callback for each received CLI character.
 *
 * Processes character input including binary mode and normal editing.
 *
 * @param c The input character.
 */
void cliInputHandler(char c)
{
	CliBuffer *activeBuffer = getActiveBuffer();

	// Ignore line feed.
	if (c == '\n') {
		return;
	}

	if (activeBuffer->isQueued) {
		return;
	}

	if (g_binary_mode != 0) {
		handleBinaryMode(activeBuffer, c);
		return;
	}

	switch (c) {
		case BACKSP_KEY:
			processBackspace(activeBuffer);
			break;

		case RETURN_KEY:
			processReturnKey(activeBuffer);
			break;

		default:
			processRegularChar(activeBuffer, c);
			break;
	}
}

/**
 * @brief TCP CLI initialization.
 *
 * Sets up the CLI callback, command execution function, and initializes TCP communication.
 */
void tcp_cli_init(void)
{
	g_cli_callback = &cliInputHandler;
	cliRunCommand = &util_cmd_run_command;
	cliPromptFunc = system_prompt_func;

	tcp_comm_init();  // Start the TCP server task.
}
