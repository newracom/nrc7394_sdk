/*
 * MIT License
 *
 * Copyright (c) 2023 Newracom, Inc.
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

#ifndef __SAMPLE_SMART_CONN_VERSION_H__
#define __SAMPLE_SMART_CONN_VERSION_H__

#define CHIP_MODULE "NRC7394"
#define SAMPLE_SMART_CONN_APP_NAME "NEWRACOM_SCM"

#define SAMPLE_SMART_CONN_MAJOR 1
#define SAMPLE_SMART_CONN_MINOR 1
#define SAMPLE_SMART_CONN_PATCH 0

#define sample_smart_conn_set_app_version()                  \
    do {                                             \
        VERSION_T app_version;                       \
        app_version.major = SAMPLE_SMART_CONN_MAJOR;  \
        app_version.minor = SAMPLE_SMART_CONN_MINOR;  \
        app_version.patch = SAMPLE_SMART_CONN_PATCH;  \
        nrc_set_app_version(&app_version);           \
        nrc_set_app_name(SAMPLE_SMART_CONN_APP_NAME); \
    } while (0)

#endif /* __SAMPLE_SMART_CONN_VERSION_H__ */
