/*
 * MIT License
 *
 * Copyright (c) 2022 Newracom, Inc.
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

#include "atcmd.h"
#include "nrc_ps_api.h"


static atcmd_retinfo_t *g_atcmd_retinfo = NULL;

/**********************************************************************************************/

#if defined(INCLUDE_LWIP_RECOVERY)
extern int lwip_get_ret_info_size (void);
#else
#define lwip_get_ret_info_size() (0)
#endif

void atcmd_retinfo_init (void)
{
	struct retention_info *ret_info = nrc_ps_get_retention_info();
	const int retinfo_user_size = sizeof(ret_info->user_data);
	const int retinfo_atcmd_size = sizeof(atcmd_retinfo_t);

	g_atcmd_retinfo = (atcmd_retinfo_t *)&ret_info->user_data;

	_atcmd_info("RETENTION_INFO: system=%d lwip=%d user=%d/%d",
			nrc_ps_get_retention_info_size() - retinfo_user_size, 
			lwip_get_ret_info_size(),
			retinfo_atcmd_size, retinfo_user_size);
	_atcmd_info(" - basic: addr=%p size=%d", &g_atcmd_retinfo->basic, sizeof(g_atcmd_retinfo->basic));

	ASSERT(retinfo_atcmd_size <= retinfo_user_size); 	
}

void *atcmd_retinfo_basic_addr (void)
{
	ASSERT(g_atcmd_retinfo);

	return &g_atcmd_retinfo->basic;
}

