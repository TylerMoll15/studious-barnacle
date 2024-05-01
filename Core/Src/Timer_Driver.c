/*
 * Timer_Driver.c
 *
 *  Created on: Feb 29, 2024
 *      Author: tyler
 */
#include "Timer_Driver.h"


void TIMER_init(Timer_Handle_t* timer_handle){
	uint32_t temp;

//	clock div
	temp = timer_handle->timer_configuration.clock_division << CLOCK_DIVISION_OFFSET;
	timer_handle->gp_timer->TIMx_CR1 &= ~(0x3 << CLOCK_DIVISION_OFFSET);
	timer_handle->gp_timer->TIMx_CR1 |= temp;

//	auto reload value
	temp = timer_handle->timer_configuration.auto_reload_value;
	timer_handle->gp_timer->TIMx_ARR = 0; // clear reg
	timer_handle->gp_timer->TIMx_ARR = temp;

// master mode
	temp = timer_handle->timer_configuration.master_mode << MASTER_MODE_OFFSET;
	timer_handle->gp_timer->TIMx_CR2 &= ~(0x3 << MASTER_MODE_OFFSET);
	timer_handle->gp_timer->TIMx_CR2 |= temp << MASTER_MODE_OFFSET;

// prescaler
	temp = timer_handle->timer_configuration.prescaler;
	timer_handle->gp_timer->TIMx_PSC = 0;
	timer_handle->gp_timer->TIMx_PSC = temp;

// center aligned mode
	temp = timer_handle->timer_configuration.center_aligned_mode << CENTER_ALIGNED_MODE_SELECTION_OFFSET;
	timer_handle->gp_timer->TIMx_CR1 &= ~(0x3 << CENTER_ALIGNED_MODE_SELECTION_OFFSET);
	timer_handle->gp_timer->TIMx_CR1 |= temp;

// auto reload buffer enable
	temp = timer_handle->timer_configuration.auto_reload_buffer_enable << AUTORELOAD_PRELOAD_ENABLE_OFFSET;
	timer_handle->gp_timer->TIMx_CR1 &= ~(0x1 << AUTORELOAD_PRELOAD_ENABLE_OFFSET);
	timer_handle->gp_timer->TIMx_CR1 |= temp;

// timer count down mode enable
	temp = timer_handle->timer_configuration.timer_count_down_mode_enable << DIRECTION_MODE_OFFSET;
	timer_handle->gp_timer->TIMx_CR1 &= ~(0x1 << DIRECTION_MODE_OFFSET);
	timer_handle->gp_timer->TIMx_CR1 |= temp;

// interrupt update mode
	temp = timer_handle->timer_configuration.interrupt_update_enable << UPDATE_INTERRUPT_ENABLE;
	timer_handle->gp_timer->TIMx_DIER &= ~(0x1 << UPDATE_INTERRUPT_ENABLE);
	timer_handle->gp_timer->TIMx_DIER |= temp;

// Update Disable
	temp = timer_handle->timer_configuration.update_event_disable << UPDATE_DISABLE_OFFSET;
	timer_handle->gp_timer->TIMx_CR1 &= ~(0x1 << UPDATE_DISABLE_OFFSET);
	timer_handle->gp_timer->TIMx_CR1 |= temp;

// One Pulse Mode
	temp = timer_handle->timer_configuration.one_pulse_mode_enable << ONE_PULSE_MODE_OFFSET;
	timer_handle->gp_timer->TIMx_CR1 &= ~(0x1 << ONE_PULSE_MODE_OFFSET);
	timer_handle->gp_timer->TIMx_CR1 |= temp;
}

void TIMER_clock_control(GPTIMR_RegDef_t* gp_timer, uint8_t enable_or_disable){
	if (gp_timer == TIM5_){
		if (enable_or_disable == ENABLE) __HAL_RCC_TIM5_CLK_ENABLE();
		else if (enable_or_disable == DISABLE) __HAL_RCC_TIM5_CLK_DISABLE();
	}
}

void TIMER_start(GPTIMR_RegDef_t* gp_timer){
	uint32_t temp;

	temp = ENABLE << ENABLE_TIMER_OFFSET;
	gp_timer->TIMx_CR1 &= ~(0x1 << ENABLE_TIMER_OFFSET);
	gp_timer->TIMx_CR1 |= temp;
}

void TIMER_stop(GPTIMR_RegDef_t* gp_timer){
	uint32_t temp;
	
	temp = DISABLE << ENABLE_TIMER_OFFSET;
	gp_timer->TIMx_CR1 &= ~(0x1 << ENABLE_TIMER_OFFSET);
	gp_timer->TIMx_CR1 |= temp;
}

void TIMER_reset(GPTIMR_RegDef_t* gp_timer){
	gp_timer->TIMx_CNT = 0;
}

uint32_t TIMER_get_timer_value(GPTIMR_RegDef_t* gp_timer){
	return gp_timer->TIMx_CNT;
}

void TIMER_interrupt_control(GPTIMR_RegDef_t* gp_timer, uint8_t enable_or_disable){
	if (gp_timer == TIM5_){
		if (enable_or_disable == ENABLE) HAL_NVIC_EnableIRQ(TIM5_IRQn);
		else if(enable_or_disable == DISABLE) HAL_NVIC_DisableIRQ(TIM5_IRQn);
	}
}


// TIMER 5
void LED_TIMER5_init(){
    Timer_Handle_t TIM5_handle;
    TIM5_handle.gp_timer = TIM5_;
    GPTimer_Config_t TIM5_config;

    TIM5_config.auto_reload_value = MAX_32INT;
    TIM5_config.master_mode = RESET; // ???
    TIM5_config.clock_division = DIVIDE_BY_ONE; // ???
    TIM5_config.prescaler = 0; // ???
    TIM5_config.center_aligned_mode = EDGE_ALIGNED_MODE; // default
    // TIM2_config.auto_reload_buffer_enable default
    TIM5_config.timer_count_down_mode_enable = DISABLE;
    TIM5_config.interrupt_update_enable = ENABLE; // update request source ???
    TIM5_config.update_event_disable = DISABLE; // update disable
    TIM5_config.one_pulse_mode_enable = DISABLE; //counter stops counting at next update event

    TIM5_handle.timer_configuration = TIM5_config;
    TIMER_clock_control(TIM5_, ENABLE);
    TIMER_init(&TIM5_handle);
    TIMER_interrupt_control(TIM5_, ENABLE);
}

void LED_TIMER5_start(){
    TIMER_interrupt_control(TIM5_, ENABLE);
    TIMER_start(TIM5_);
}

void LED_TIMER5_stop(){
    TIMER_interrupt_control(TIM5_, DISABLE);
    TIMER_stop(TIM5_);
}

void LED_TIMER5_reset(){
    TIMER_reset(TIM5_);
}

uint32_t LED_TIMER5_get_ARR_value(){
    return TIM5_->TIMx_ARR;
}

uint32_t LED_TIMER5_get_count_value(){
    return TIM5_->TIMx_CNT;
}

void LED_TIMER5_configure_ARR(uint32_t ARR_value){
    TIM5_->TIMx_ARR = ARR_value;
}

void LED_TIMER5_specific_start(uint32_t new_start_val){
    TIM5_->TIMx_CNT = new_start_val;
}

void IRQ_TIMx_clear_pending(uint8_t pinNumber, GPTIMR_RegDef_t* gp_timer){
    gp_timer->TIMx_SR &= ~(0x1 << pinNumber);
}
