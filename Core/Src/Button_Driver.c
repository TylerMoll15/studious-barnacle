#include "Button_Driver.h"

void init_button(){
	GPIO_InitTypeDef configure_Button = {};
	enable_clock();

	configure_Button.Pin = GPIO_PIN_0; // ??? NEW pin number is zero, but 0x1?
	configure_Button.Mode = GPIO_MODE_INPUT;
	configure_Button.Speed = GPIO_SPEED_FREQ_LOW;
	configure_Button.Pull = GPIO_NOPULL;
	// configure_Button.Alternate = GPIO_MODE_OUTPUT_PP; //??? should I not configure the alt register?

	HAL_GPIO_Init(GPIOA, &configure_Button);
}

void enable_clock(){
	__HAL_RCC_GPIOA_CLK_ENABLE();
}

bool is_button_pressed(){
	GPIO_PinState state = HAL_GPIO_ReadPin(GPIOA, BUTTON_PIN_NUMBER);

	// button pressed
	if(state == BUTTON_PRESSED){
		return true;
	}
	// button not pressed
	else if(state == BUTTON_NOT_PRESSED){
		return false;
	}

//	shouldnt get here
	return false;
}

void interrupt_init_button(){
	GPIO_InitTypeDef configure_Button = {};
	enable_clock();

	configure_Button.Pin = GPIO_PIN_0; // ??? pin can't be zero?
	configure_Button.Mode = GPIO_MODE_IT_RISING;
	configure_Button.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	configure_Button.Pull = GPIO_NOPULL;
	// configure_Button.GPIO_PinConfig.OPType = GPIO_OTYPER_PUSH_PULL;
	// configure_Button.GPIO_PinConfig.PinInterruptMode = GPIO_INTERRUPT_MODE_FALLING_AND_RISING_EDGE;

	HAL_GPIO_Init(GPIOA, &configure_Button);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

