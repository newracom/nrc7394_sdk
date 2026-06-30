/*
 * MIT License
 *
 * Copyright (c) 2025 Newracom, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "app_debug.h"
#include "nrc_sdk.h"
#include <stdarg.h>

uint8_t g_debug_level = DEBUG_LEVEL_ERROR;  // default level
uint8_t g_hex_mode = 0; /* to set hex print mode (0:disable, 1:hex, 2:simple hex */

SemaphoreHandle_t print_sem = NULL;

void set_debug_level(int level)
{
	g_debug_level = level;
}

int get_debug_level(void)
{
	return g_debug_level;
}

ATTR_NC void app_debug_print_hex(int level, const uint8_t *data, int len, const uint8_t *description)
{
	if(!print_sem)
		print_sem = xSemaphoreCreateMutex();

	if (g_debug_level < level || !data || len <= 0 || !g_hex_mode)
		return;

	xSemaphoreTake(print_sem, portMAX_DELAY);
	nrc_usr_print("\n"  );
	if(description) {
		nrc_usr_print("[%s] ", description);
	}
	nrc_usr_print("Size = %d\n", len);
	xSemaphoreGive(print_sem);

	if (g_hex_mode == 2) {
		xSemaphoreTake(print_sem, portMAX_DELAY);
		for (int i = 0; i < len; i++) {
			nrc_usr_print("%02X", data[i]);
		}
		nrc_usr_print("\n");
		xSemaphoreGive(print_sem);
		return;
	}

	const int BYTES_PER_LINE = 16;
	char line[96];
	int offset = 0;

	while (offset < len) {
		int line_len = snprintf(line, sizeof(line), "%03X :", offset);

		for (int i = 0; i < BYTES_PER_LINE && offset + i < len; i++) {
			if (line_len >= sizeof(line) - 4) break;
			line_len += snprintf(line + line_len, sizeof(line) - line_len, " %02X", data[offset + i]);
		}

		line[sizeof(line) - 1] = '\0';
		xSemaphoreTake(print_sem, portMAX_DELAY);
		nrc_usr_print("%s\n", line);
		xSemaphoreGive(print_sem);

		offset += BYTES_PER_LINE;
	}
}

ATTR_NC void app_log(int level, const char *tag, const char *fmt, ...)
{
	if(!print_sem)
		print_sem = xSemaphoreCreateMutex();

	if (g_debug_level < level)
		return;

	const char *level_char = (level == DEBUG_LEVEL_ERROR) ? "E" :
				(level == DEBUG_LEVEL_WARN)  ? "W" :
				(level == DEBUG_LEVEL_INFO)  ? "I" :
				(level == DEBUG_LEVEL_DEBUG) ? "D" : "";

	char buffer[256];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);

	xSemaphoreTake(print_sem, portMAX_DELAY);
	if (level == DEBUG_LEVEL_ALWAYS) {
		nrc_usr_print("%s", buffer);
	} else if (tag && tag[0] != '\0') {
		nrc_usr_print("[%s][%s] %s", level_char, tag, buffer);
	} else {
		nrc_usr_print("[%s] %s", level_char, buffer);
	}
	xSemaphoreGive(print_sem);
}

void app_print_hex_dump (char *data, size_t len, const char *desc)
{
	char buf[64];
	int i;

	memset(buf, 0, sizeof(buf));

	if (desc)
		nrc_usr_print("%s: %d\n", desc, len);

	for (i = 0 ; i < len ; i++)
	{
		sprintf(buf + (3 * (i % 16)), "%02X ", data[i]);

		if ((i % 16) == 15)
		{
			nrc_usr_print(" %05d: %s\n", i / 16, buf);
			memset(buf, 0, sizeof(buf));
		}
	}

	if (((i - 1) % 16) < 15)
	{
		for (i %= 16 ; i < 16 ; i++)
			sprintf(buf + (3 * (i % 16)), "   ");

		nrc_usr_print(" %05d: %s\n", i / 16, buf);
	}
}

