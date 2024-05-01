#include <stdio.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

#define BUTTON_PIN_NUMBER 0

// button states
#define BUTTON_PRESSED GPIO_PIN_SET
#define BUTTON_NOT_PRESSED GPIO_PIN_RESET


void init_button();
void interrupt_init_button();
void enable_clock();
bool is_button_pressed(); // return button state
