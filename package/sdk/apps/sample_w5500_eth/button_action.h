#ifndef __BUTTON_ACTION_H__
#define __BUTTON_ACTION_H__
#include "api_gpio.h"

#define RESET_BUTTON GPIO_25
#define RESET_MAX 5 // sec

void init_reset_button();

#endif //  __BUTTON_ACTION_H__
