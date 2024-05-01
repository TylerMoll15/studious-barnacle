/*
 * Definitions.h
 *
 *  Created on: Apr 25, 2024
 *      Author: tyler
 */

#ifndef INC_DEFINITIONS_H_
#define INC_DEFINITIONS_H_
#include <stdint.h>

struct Point{
    int x;
    int y;
};

struct Box_Boundaries{
	int left_x;
	int top_y;
	int right_x;
	int bottom_y;
};

// screen states
#define SCREEN_MENU 0
#define SCREEN_1P 1
#define SCREEN_2P 3
#define SCREEN_END 4

#define UIF_INTERRUPT_FLAG 0

//screen dimensions
#define TOUCH_SCREEN_WIDTH 240
#define TOUCH_SCREEN_HEIGHT 320

// tic tac toe players
#define PLAYER_X 1
#define PLAYER_O 2
#define TIE 3
#define NO_WINNER -1

// tic tac toe bool
#define PLAYER_X_BOOL false
#define PLAYER_O_BOOL true

#define BOARD_DIMENSION 3
#define FULL_BOARD BOARD_DIMENSION * BOARD_DIMENSION

typedef struct {
    volatile uint32_t TIMx_CR1;
    volatile uint32_t TIMx_CR2;
    volatile uint32_t TIMx_SMCR;
    volatile uint32_t TIMx_DIER;
    volatile uint32_t TIMx_SR;
    volatile uint32_t TIMx_EGR;
    volatile uint32_t TIMx_CCMR1;
    volatile uint32_t TIMx_CCMR2;
    volatile uint32_t TIMx_CCER;
    volatile uint32_t TIMx_CNT;
    volatile uint32_t TIMx_PSC;
    volatile uint32_t TIMx_ARR;
    volatile uint32_t RESERVED_A;
    volatile uint32_t TIMx_CCR1;
    volatile uint32_t TIMx_CCR2;
    volatile uint32_t TIMx_CCR3;
    volatile uint32_t TIMx_CCR4;
    volatile uint32_t RESERVED_B;
    volatile uint32_t TIMx_DCR;
    volatile uint32_t TIMx_DMAR;
    volatile uint32_t TIM2_TIM5_OR;
} GPTIMR_RegDef_t;


#define TIM5_ ((GPTIMR_RegDef_t*) TIM5_BASE)



#endif /* INC_DEFINITIONS_H_ */
