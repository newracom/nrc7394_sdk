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

#include "nrc_sdk.h"
#include "e_paper.h"
#include "standalone.h"
#include "nrc_lwip.h"
#include "nrc_ps_api.h"
#include "drv_pmc.h"

#include "nvs.h"
#include "multi_role_config.h"
#include "wifi_config.h"
#include "sample_smart_conn_version.h"
#include "app_debug.h"

#include "build_ver.h"
#include "nrc_ps_api.h"
#if defined(SUPPORT_EPAPER)
/* ePaper Pin */
#ifdef NRC7394
#define NRC_EPD_BUSY_PIN	12
#define NRC_EPD_RST_PIN		13
#define NRC_EPD_DC_PIN		14
#define NRC_EPD_CS_PIN		20
#define NRC_EPD_SCL_PIN		11
#define NRC_EPD_SDA_PIN		10
#define NRC_EPD_PWR_PIN		30
#else
#define NRC_EPD_BUSY_PIN    0
#define NRC_EPD_RST_PIN     1
#define NRC_EPD_DC_PIN      2
#define NRC_EPD_CS_PIN      3
#define NRC_EPD_SCL_PIN     4
#define NRC_EPD_SDA_PIN     5
#define NRC_EPD_PWR_PIN     8
#endif
#endif

struct EPD_IO_PINS IO_Pins;

static UBYTE BlackImage[EPD_2IN66B_HEIGHT * EPD_2IN66B_WIDTH / 8];
static UBYTE RedImage[EPD_2IN66B_HEIGHT * EPD_2IN66B_WIDTH / 8];

#if defined(NRC7292)
#define HARDWARE_PLATFORM_NAME    "NRC7292"
#elif defined(NRC7394)
#define HARDWARE_PLATFORM_NAME    "NRC7394"
#else
#define HARDWARE_PLATFORM_NAME    "Unknown"
#endif

extern void get_standalone_macaddr(int vif_id, uint8_t *mac);

static bool epd_init = false;

static bool nrc_epd_update_full_screen(bool black_color, char* input1, char* input2, char* input3, char* input4) {
	uint8_t addr[6];
	char buf[128] = {0};
	const char date[] = __DATE__;
	const char time[] = __TIME__;
	int text_color = black_color ? BLACK : WHITE;
	int bg_color = black_color ? WHITE : BLACK;
	UBYTE* image = black_color ? BlackImage : RedImage;

	if (!epd_init) {
		return false;
	}

	uint16_t etag_id = nrc_sf_get_etag_id();
	get_standalone_macaddr(0, addr);

	if (NRC_EPD_IO_Enable(&IO_Pins) != 0) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "DEV_Module_Init() failed\n");
		return false;
	}

	EPD_2IN66B_Wakeup();
	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);
	Paint_SelectImage(RedImage);
	Paint_Clear(WHITE);
	Paint_SelectImage(image);
	Paint_Clear(text_color);

	snprintf(buf, sizeof(buf), "[E-%d] %s", etag_id, input1 ? input1 : "");
	Paint_DrawString_EN(2, 5, buf, &Font20, text_color, bg_color);

	if (input2) {
		Paint_DrawString_EN(7, 30, input2, &Font20, text_color, bg_color);
	}
	if (input3) {
		Paint_DrawString_EN(7, 55, input3, &Font20, text_color, bg_color);
	}

	char *country_code = RF_CAL_DATA.header.country_code;
	snprintf(buf, sizeof(buf), "(%c%c%d) HW:%d %s", country_code[0], country_code[1],
		RF_CAL_DATA.header.id, SYSCONFIG.hw_version, input4 ? input4 : " ");
	Paint_DrawString_EN(7, 80, buf, &Font20, WHITE, BLACK);

	snprintf(buf, sizeof(buf), "%02X:%02X:%02X:%02X:%02X:%02X",
			 addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
	Paint_DrawString_EN(7, 105, buf, &Font20, text_color, bg_color);

	snprintf(buf, sizeof(buf), "%s %s", date, time);
	Paint_DrawString_EN(2, 130, buf, &Font20, text_color, bg_color);

	EPD_2IN66B_Display(BlackImage, RedImage);
	EPD_2IN66B_Sleep();
	DEV_Delay_ms(1000);
	NRC_EPD_IO_Disable();

	return true;
}

static void nrc_epd_update_black_full_screen(char* input1, char* input2, char* input3, char* input4)
{
	nrc_epd_update_full_screen(true, input1, input2, input3, input4);
}

static void nrc_epd_update_white_full_screen(char* input1, char* input2, char* input3, char* input4)
{
	nrc_epd_update_full_screen(false, input1, input2, input3, input4);
}

static void nrc_epd_update_boot_screen(void)
{
	if (drv_get_boot_reason()&BR_POR) {
		nrc_epd_update_black_full_screen(NULL, NULL, NULL, NULL);
	}
}

bool nrc_display_state(bool success,char* role, int fota_done, char* input1, char* input2)
{
	char buf[128];
	uint8_t hwaddr[6];
	uint16_t etag_id = nrc_sf_get_etag_id();
	char* ip_addr = NULL;
	bool boot_reason_sw_reset = system_modem_api_is_boot_reason_sw_reset();
	uint64_t rtc_time = 0;
	nrc_get_rtc(&rtc_time);
	int vif_id = 0;
	int netif_idx = 0;
	char date[] = __DATE__;
	char time[] = __TIME__;

	if(epd_init == false )
		return false;

	if (!strcmp(role, "relay")) {
		vif_id = 1;
		netif_idx = BRIDGE_INTERFACE;
	} else {
		vif_id = 0;
		netif_idx = WLAN0_INTERFACE;
	}

	get_standalone_macaddr(vif_id, hwaddr);
	struct netif *interface = nrc_netif_get_by_idx(netif_idx);

	if (!ip4_addr_isany(netif_ip4_addr(interface))) {
		app_log(DEBUG_LEVEL_ALWAYS, NULL, "[%s] IP Address: %s\n", __func__, ip4addr_ntoa(netif_ip4_addr(interface)));
	}

	if (NRC_EPD_IO_Enable(&IO_Pins) != 0) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "DEV_Module_Init() failed\n");
		return false;
	}
	EPD_2IN66B_Wakeup();
	Paint_SelectImage(RedImage);
	Paint_Clear(WHITE);
	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);

	sprintf(buf, "[E-%d]%s(%llus)", etag_id, role, rtc_time/ 1000);
	Paint_DrawString_EN(2, 5, buf, &Font20, WHITE, BLACK);
	if(input1){
		Paint_DrawString_EN(2, 30, input1, &Font20, WHITE, BLACK);
	}
	if(input2){
		Paint_DrawString_EN(2, 55, input2, &Font20, WHITE, BLACK);
	}

	char *country_code = RF_CAL_DATA.header.country_code;
	sprintf(buf, "%s(%c%c%d)", ip4addr_ntoa(netif_ip4_addr(interface)),
		country_code[0], country_code[1], RF_CAL_DATA.header.id);
	Paint_DrawString_EN(7, 80, buf, &Font20, WHITE, BLACK);

	sprintf(buf, "%02X:%02X:%02X:%02X:%02X:%02X",
		hwaddr[0], hwaddr[1], hwaddr[2], hwaddr[3], hwaddr[4], hwaddr[5]);
	Paint_DrawString_EN(7, 105, buf, &Font20, WHITE, BLACK);

	sprintf(buf, "%s %s", date, time);
	Paint_DrawString_EN(7, 130, buf, &Font20, WHITE, BLACK);

	if(fota_done) {
		Paint_SelectImage(BlackImage);
		Paint_DrawCircle(270, 25, 20, RED, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
	} else {
		if (!strcmp(role, "softap")) {
			Paint_SelectImage(BlackImage);
			Paint_DrawRectangle(250, 35, 290, 75, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
		} else if (!strcmp(role, "station")) {
			Paint_SelectImage(RedImage);
			Paint_DrawCircle(270, 50, 20, RED, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
		} else if (!strcmp(role, "relay")) {
			Paint_SelectImage(RedImage);
			Paint_DrawRectangle(250, 35, 290, 75, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
		}
	}
	EPD_2IN66B_Display(BlackImage, RedImage);
	EPD_2IN66B_Sleep();
	DEV_Delay_ms(2000);
	NRC_EPD_IO_Disable();

	return true;
}

static int nrc_epd_init(void)
{
	UWORD ImageSize = 0;
	int i;

	IO_Pins.BUSY = NRC_EPD_BUSY_PIN;
	IO_Pins.RST = NRC_EPD_RST_PIN;
	IO_Pins.DC = NRC_EPD_DC_PIN;
	IO_Pins.CS = NRC_EPD_CS_PIN;
	IO_Pins.SCL = NRC_EPD_SCL_PIN;
	IO_Pins.SDA = NRC_EPD_SDA_PIN;
	IO_Pins.PWR = NRC_EPD_PWR_PIN;

	Paint_NewImage(BlackImage, EPD_2IN66B_WIDTH, EPD_2IN66B_HEIGHT, 270, WHITE);
	Paint_Clear(WHITE);

	Paint_NewImage(RedImage, EPD_2IN66B_WIDTH, EPD_2IN66B_HEIGHT, 270, WHITE);
	Paint_Clear(WHITE);

	if (NRC_EPD_IO_Enable(&IO_Pins) != 0) {
		app_log(DEBUG_LEVEL_ERROR, NULL, "DEV_Module_Init() failed\n");
		return -1;
	}

	if (EPD_2IN66B_Init() != 0) {
		return -1;
	}

	EPD_2IN66B_Sleep();
	NRC_EPD_IO_Disable();

	epd_init = true;

	return 0;
}

#if defined(MODE_TEST_SETTING)
static void update_ssid_and_system_role(nvs_handle_t nvs_handle)
{
	size_t length = 32;
	uint8_t ssid[32 + 1] = {0};
	char system_role[16] = {0};
	uint16_t etag_id = nrc_sf_get_etag_id();
	WIFI_CONFIG *config = get_system_config();
	const int start_etag_id_num = 3;
	const int gourp_num = 5;
	uint16_t section = 0;
	bool is_ap = 0;

	app_log(DEBUG_LEVEL_ALWAYS, NULL, "Current SSID: %s\n", config->ssid);

#if defined(MULTI_STA_TEST_SETTING)
	const char date[] = __DATE__;
	const char time[] = __TIME__;
	int day, year, hour, min, sec;
	sscanf(date, "%*s %d %d", &day, &year);
	sscanf(time, "%d:%d:%d", &hour, &min, &sec);
	section = (day + year + hour + min + sec) % 1000;
	is_ap = (etag_id == 3) ? true : false;
#elif defined(GROUPING_TEST_SETTING)
	section = (etag_id - start_etag_id_num) / gourp_num;
	is_ap = ((etag_id - start_etag_id_num) % gourp_num == 0);
#endif

	char new_ssid[64] = {0}; // Increased size to handle the length of the original SSID + section
	memcpy(config->ssid,  STR_SSID, sizeof(STR_SSID));
	snprintf(new_ssid, sizeof(new_ssid), "%s_%d", config->ssid, section);
	nvs_set_str(nvs_handle, NVS_SSID, (char*)new_ssid);
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "Updated SSID: %s\n", new_ssid);

	if (is_ap) {
		char new_system_role[16] = {0};
		snprintf(new_system_role, sizeof(new_system_role), "softap");
		app_log(DEBUG_LEVEL_ALWAYS, NULL, "Updated system_role: %s\n", new_system_role);
		nvs_set_str(nvs_handle, "system_role", (char*)new_system_role);
	} else {
		snprintf(system_role, sizeof(system_role), "station");
		nvs_set_str(nvs_handle, "system_role", system_role);
	}

	length = sizeof(system_role);
	nvs_get_str(nvs_handle, "system_role", system_role, &length);
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "Current system_role: %s\n", system_role);
}

static int check_home_mode(nvs_handle_t nvs_handle)
{
	const int home_mode_reset_count = 2;
	uint8_t home_mode = 0;
	uint8_t current_home_mode = 0;
	char system_role[16] = {0};
	WIFI_CONFIG *config = get_system_config();
	nvs_get_u8(nvs_handle, "home_mode", (uint8_t *) &home_mode);

	current_home_mode = home_mode;
	if (home_mode == 0) {
		update_ssid_and_system_role(nvs_handle);
		nvs_set_u8(nvs_handle, "home_mode", 1);
		nvs_set_u8(nvs_handle, "test_on", 1);
		nvs_set_u8(nvs_handle, "report_on", 1);
		nvs_set_i32(nvs_handle, "test_delay", TEST_DELAY);
	} else if (home_mode >= home_mode_reset_count) {
		nvs_set_u8(nvs_handle, "home_mode", 0);
		nvs_set_u8(nvs_handle, "test_on", 0);
		nvs_set_u8(nvs_handle, "report_on", 0);
		snprintf(system_role, sizeof(system_role), "station");
		nvs_set_str(nvs_handle, "system_role", system_role);
		snprintf((char*)config->ssid, sizeof(config->ssid), "%s", STR_SSID);
		nvs_set_str(nvs_handle, NVS_SSID, (char*)config->ssid);
		app_log(DEBUG_LEVEL_ALWAYS, NULL, "Updated system_role: %s, SSID: %s\n", system_role, config->ssid);
	} else {
		home_mode++;
		nvs_set_u8(nvs_handle, "home_mode", home_mode);
	}
	app_log(DEBUG_LEVEL_ALWAYS, NULL, "current_home_mode: %d\n", current_home_mode);

	return current_home_mode;
}
#endif /* MODE_TEST_SETTING */

void update_home_mode_display(nvs_handle_t nvs_handle)
{
	int fota_done = (int)(nrc_ps_get_retention_info()->fota_done);
	char* home_mode_str = NULL;

#if defined(MODE_TEST_SETTING)
	char current_mode_str[16] = {0};
	snprintf(current_mode_str, sizeof(current_mode_str), "[C]%d", check_home_mode(nvs_handle));
	home_mode_str = current_mode_str;
#endif /* MODE_TEST_SETTING */
	system_role_t role = get_system_role(nvs_handle);

	if (nrc_epd_init() == 0) {
		app_log(DEBUG_LEVEL_ALWAYS, NULL, "nrc_epd_init() success\n");
		WIFI_CONFIG *config = get_system_config();

		switch (role) {
			case ROLE_SOFTAP:
				nrc_epd_update_full_screen(fota_done, "softap", (char*)config->ssid, NULL, home_mode_str);
				break;
			case ROLE_STATION:
				nrc_epd_update_full_screen(fota_done, "station", (char*)config->ssid, NULL, home_mode_str);
				break;
			case ROLE_RELAY: {
				char relay_ssid[64] = {0};
				get_relay_ssid(nvs_handle, relay_ssid, sizeof(relay_ssid));
				nrc_epd_update_full_screen(fota_done, "relay", (char*)config->ssid, relay_ssid, home_mode_str);
				break;
			}
			default:
				nrc_epd_update_full_screen(fota_done, "setting", NULL, NULL, home_mode_str);
				break;
		}
	}
}
