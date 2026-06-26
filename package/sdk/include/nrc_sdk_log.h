/*
 * MIT License
 *
 * Copyright (c) 2024 Newracom, Inc.
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
 */

#ifndef __NRC_SDK_LOG_H__
#define __NRC_SDK_LOG_H__

/**
 * SDK Log Level definitions
 *
 * Usage in standalone.c (user configures this):
 *   nrc_sdk_log_init(SDK_LOG_INFO);
 *
 * Usage in SDK/API code:
 *   static const char *TAG = "WIFI";
 *   SDK_LOGE(TAG, "connect failed: %d\n", ret);
 *   SDK_LOGI(TAG, "scan done, n=%d\n", n);
 *   SDK_LOGD(TAG, "freq=%u\n", freq);
 *
 * Output format:
 *   [E][WIFI] connect failed: -1
 *   [I][WIFI] scan done, n=3
 */

#define SDK_LOG_NONE    0
#define SDK_LOG_ERROR   1
#define SDK_LOG_WARN    2
#define SDK_LOG_INFO    3
#define SDK_LOG_DEBUG   4

/**
 * Compile-time maximum log level.
 * Logs above this level are removed entirely from the binary (zero code size).
 * Override via Makefile: -DSDK_LOG_MAX_LEVEL=SDK_LOG_INFO
 */
#ifndef SDK_LOG_MAX_LEVEL
#define SDK_LOG_MAX_LEVEL  SDK_LOG_DEBUG
#endif

/**
 * Runtime log level initialization.
 * Call once at startup (e.g. in standalone.c before nrc_user_app_main()).
 * Default level if not called: SDK_LOG_INFO
 */
void nrc_sdk_log_init(int level);

/**
 * Internal log write function — do not call directly, use macros below.
 */
void nrc_sdk_log_write(int level, const char *tag, const char *fmt, ...);

/* --- Log macros ---------------------------------------------------------- */

#if SDK_LOG_MAX_LEVEL >= SDK_LOG_ERROR
#define SDK_LOGE(tag, fmt, ...) \
	nrc_sdk_log_write(SDK_LOG_ERROR, tag, "[E][%s] " fmt, tag, ##__VA_ARGS__)
#else
#define SDK_LOGE(tag, fmt, ...)  do {} while (0)
#endif

#if SDK_LOG_MAX_LEVEL >= SDK_LOG_WARN
#define SDK_LOGW(tag, fmt, ...) \
	nrc_sdk_log_write(SDK_LOG_WARN,  tag, "[W][%s] " fmt, tag, ##__VA_ARGS__)
#else
#define SDK_LOGW(tag, fmt, ...)  do {} while (0)
#endif

#if SDK_LOG_MAX_LEVEL >= SDK_LOG_INFO
#define SDK_LOGI(tag, fmt, ...) \
	nrc_sdk_log_write(SDK_LOG_INFO,  tag, "[I][%s] " fmt, tag, ##__VA_ARGS__)
#else
#define SDK_LOGI(tag, fmt, ...)  do {} while (0)
#endif

#if SDK_LOG_MAX_LEVEL >= SDK_LOG_DEBUG
#define SDK_LOGD(tag, fmt, ...) \
	nrc_sdk_log_write(SDK_LOG_DEBUG, tag, "[D][%s] " fmt, tag, ##__VA_ARGS__)
#else
#define SDK_LOGD(tag, fmt, ...)  do {} while (0)
#endif

#endif /* __NRC_SDK_LOG_H__ */
