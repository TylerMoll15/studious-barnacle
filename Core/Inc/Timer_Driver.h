/*
 * Timer_Driver.h
 *
 *  Created on: Feb 29, 2024
 *      Author: tyler
 */

#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_
#include <stdbool.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "Definitions.h"

typedef struct {
    uint32_t auto_reload_value;
    uint32_t master_mode;
    uint32_t clock_division;
    uint16_t prescaler;
    uint32_t center_aligned_mode;
    bool auto_reload_buffer_enable;
    bool timer_count_down_mode_enable;
    bool interrupt_update_enable;
    bool update_event_disable;
    bool one_pulse_mode_enable;
} GPTimer_Config_t;

typedef struct {
	GPTIMR_RegDef_t* gp_timer;
	GPTimer_Config_t timer_configuration;
} Timer_Handle_t;

void TIMER_init(Timer_Handle_t* timer);
void TIMER_clock_control(GPTIMR_RegDef_t* gp_timer, uint8_t enable_or_disable);
void TIMER_start(GPTIMR_RegDef_t* gp_timer);
void TIMER_stop(GPTIMR_RegDef_t* gp_timer);
void TIMER_reset(GPTIMR_RegDef_t* gp_timer);

uint32_t TIMER_get_timer_value(GPTIMR_RegDef_t* gp_timer);
void TIMER_interrupt_control(GPTIMR_RegDef_t* gp_timer, uint8_t enable_or_disable);
void IRQ_TIMx_clear_pending(uint8_t pinNumber, GPTIMR_RegDef_t* gp_timer);

// TIMER 5
void LED_TIMER5_init();

void LED_TIMER5_start();

void LED_TIMER5_stop();

void LED_TIMER5_reset();

uint32_t LED_TIMER5_get_ARR_value();

uint32_t LED_TIMER5_get_count_value();

void LED_TIMER5_configure_ARR(uint32_t ARR_value);

void LED_TIMER5_specific_start(uint32_t new_start_val);




// pg 627
// GPTimer_Config_t

// clock_division
#define DIVIDE_BY_ONE 0b00
#define DIVIDE_BY_TWO 0b01
#define DIVIDE_BY_FOUR 0b10
#define CLOCK_DIVISION_RESERVED 0b11

// auto_reload_buffer_enable - true/false

// center_aligned_mode
#define EDGE_ALIGNED_MODE 0b00
#define CENTER_ALIGNED_MODE_1 0b01
#define CENTER_ALIGNED_MODE_2 0b10
#define CENTER_ALIGNED_MODE_3 0b11

// one_pulse_mode_enable - true/false

// timer_count_down_mode_enable - true/false

// master_mode
// RESET 0b000 already defined
// ENABLE 0b001 already defined
#define UPDATE 0b010
#define COMPARE_PULSE 0b011
#define COMPARE_OC1REF 0b100
#define COMPARE_OC2REF 0b101
#define COMPARE_OC3REF 0b110
#define COMPARE_OC4REF 0b111

// Timer Offsets
// TIMx CR1
#define CLOCK_DIVISION_OFFSET 8
#define AUTORELOAD_PRELOAD_ENABLE_OFFSET 7
#define CENTER_ALIGNED_MODE_SELECTION_OFFSET 5
#define DIRECTION_MODE_OFFSET 4 // timer count down mode enable
#define ONE_PULSE_MODE_OFFSET 3
#define UPDATE_DISABLE_OFFSET 1 // update_event_disable
#define ENABLE_TIMER_OFFSET 0

// TIMx CR2
#define MASTER_MODE_OFFSET 4

// TIMx DIER
#define UPDATE_INTERRUPT_ENABLE 0 // interrupt_update_enable

// max
#define MAX_32INT 0xFFFFFFFF

#endif /* TIMER_DRIVER_H_ */
