/*
 * ApplicationCode.c
 *
 *  Created on: Dec 30, 2023
 *      Author: Xavion
 */

#include "ApplicationCode.h"

/* Static variables */
static int x_win_history = 0;
static int o_win_history = 0;
static int tie_history = 0;

extern void initialise_monitor_handles(void); 


#if COMPILE_TOUCH_FUNCTIONS == 1
static STMPE811_TouchData StaticTouchData;
static EXTI_HandleTypeDef hexti;
#if TOUCH_INTERRUPT_ENABLED == 1
static EXTI_HandleTypeDef LCDTouchIRQ;
void LCDTouchScreenInterruptGPIOInit(void);
#endif // TOUCH_INTERRUPT_ENABLED
#endif // COMPILE_TOUCH_FUNCTIONS

void ApplicationInit(void)
{
	initialise_monitor_handles(); // Allows printf functionality
    LTCD__Init();
    LTCD_Layer_Init(0);
    LCD_Clear(0,LCD_COLOR_WHITE);
	RNG_Init();
	init_button_application();
	init_button_interrupt_application();
	LED_TIMER5_init();

	hexti.Line = 0;

   #if COMPILE_TOUCH_FUNCTIONS == 1
	InitializeLCDTouch();

	// This is the orientation for the board to be direclty up where the buttons are vertically above the screen
	// Top left would be low x value, high y value. Bottom right would be low x value, low y value.
	StaticTouchData.orientation = STMPE811_Orientation_Portrait_2;

	#if TOUCH_INTERRUPT_ENABLED == 1
	LCDTouchScreenInterruptGPIOInit();
	#endif // TOUCH_INTERRUPT_ENABLED

	#endif // COMPILE_TOUCH_FUNCTIONS
}

void LCD_Visual_Demo(void)
{
	visualDemo();
}

#if COMPILE_TOUCH_FUNCTIONS == 1
void LCD_Touch_Polling_Demo()
{
	struct Box_Boundaries p1_bounds;
	struct Box_Boundaries p2_bounds;
	struct Box_Boundaries player_select[2];
	uint16_t move_count = 0;
	uint32_t game_board[BOARD_DIMENSION][BOARD_DIMENSION]; //player x
	int screen_state = SCREEN_MENU;
	int player_turn = false;
	int winning_numb = NO_WINNER; //init to none
	bool needs_to_increment = true;

	p1_bounds.left_x = 63;
	p1_bounds.top_y = 224;
	p1_bounds.right_x = 190;
	p1_bounds.bottom_y = 180;

	p2_bounds.left_x = 63;
	p2_bounds.top_y = 155;
	p2_bounds.right_x = 190;
	p2_bounds.bottom_y = 111;

	player_select[0] = p1_bounds;
	player_select[1] = p2_bounds;

	struct Box_Boundaries game_grid[3][3];
//	calc all box boundaries
	for(int x = 1; x < 4; x++){
		for(int y = 1; y < 4; y++){
			struct Box_Boundaries curr_grid;
			curr_grid.right_x = x * TOUCH_SCREEN_WIDTH/3;
			curr_grid.left_x = (x - 1) * TOUCH_SCREEN_WIDTH/3;
			curr_grid.top_y = y * TOUCH_SCREEN_HEIGHT/3;
			curr_grid.bottom_y = (y - 1) * TOUCH_SCREEN_HEIGHT/3;

			game_grid[x - 1][y - 1] = curr_grid;
		}
	}

//	clear game_board
	for(int x = 0; x < BOARD_DIMENSION; x++){
		for(int y = 0; y < BOARD_DIMENSION; y++){
			game_board[x][y] = 0;
		}
	}


	while (1) {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);


			struct Point touch_loc;
			touch_loc.x = StaticTouchData.x;
			touch_loc.y = StaticTouchData.y;

//			bool for if the player should switch
			bool changePlayer = false;

			if(screen_state == SCREEN_MENU){
				needs_to_increment = true;
				for(int i = 0; i < 2; i++){
					if(checkTouchBounds(&touch_loc, player_select[i])){
						printf("Player %d box pressed!", i+1);
						LCD_Clear(0, LCD_COLOR_WHITE);
						Draw_Game();

						if(i == 0){ //1P
							screen_state = SCREEN_1P;
						}
						else if(i == 1){ //2P
							screen_state = SCREEN_2P;
						}
						TIMER_start(TIM5_);
					}
				}
			}
			else if(screen_state == SCREEN_2P || screen_state == SCREEN_1P){
				for(int x = 0; x < 3; x++){
					for(int y = 0; y < 3; y++){
						if(checkTouchBounds(&touch_loc, game_grid[x][y])){

							printf("Grid Square x = %d y = %d pressed\n", x, y);

							if(!game_board[x][y]){
								if(player_turn == PLAYER_O_BOOL){ //player O
									game_board[x][y] = PLAYER_O;

								}
								else{ //player X
									game_board[x][y] = PLAYER_X;
								}
								move_count++;
								Draw_Move(player_turn, game_grid[x][y]);
								changePlayer = true;
							}

						    if(move_count == FULL_BOARD){
						    	winning_numb = TIE;
						    }



//							check win state
						    uint8_t num_win_states = 8;

							uint16_t winning_states[num_win_states];
						    uint8_t board_width = BOARD_DIMENSION;

						//    set winning states to 0
						    for(int i = 0; i < num_win_states; i++){
						    	winning_states[i] = 0;
						    }

						    uint16_t players[2] = {PLAYER_X, PLAYER_O};
						    for(int j = 0; j < 2; j++){
						        for(int i = 0; i < BOARD_DIMENSION; i++){
						            if (game_board[0][i] == players[j]) winning_states[0]++;
						            if (game_board[1][i] == players[j]) winning_states[1]++;
						            if (game_board[2][i] == players[j]) winning_states[2]++;
						            if (game_board[i][0] == players[j]) winning_states[3]++;
						            if (game_board[i][1] == players[j]) winning_states[4]++;
						            if (game_board[i][2] == players[j]) winning_states[5]++;
						            if (game_board[i][i] == players[j]) winning_states[6]++;
						            if (game_board[board_width - i - 1][i] == players[j]) winning_states[7]++;
						        }

						        for(int k = 0; k < num_win_states; k++){
						            if(winning_states[k] == BOARD_DIMENSION) {
						                winning_numb = players[j];
						            }
						            winning_states[k] = 0;
						        }
						    }

														// if 1 player, automatically place 'O'
							int rand_x;
							int rand_y;
							if(screen_state == SCREEN_1P){
								int ran_sel_placement = 1;

								// while rand indices already have placement, re-call rand-int
								while(ran_sel_placement && move_count != FULL_BOARD && winning_numb == NO_WINNER){
									HAL_Delay(100);
									rand_x = Get_Random_Number() % BOARD_DIMENSION;
									HAL_Delay(100);
									rand_y = Get_Random_Number() % BOARD_DIMENSION;

									ran_sel_placement = game_board[rand_x][rand_y];
								}
							}

//							drawing move logic

							if(screen_state == SCREEN_1P && changePlayer){
								Draw_Move(PLAYER_O_BOOL, game_grid[rand_x][rand_y]);
								game_board[rand_x][rand_y] = PLAYER_O;
								move_count++;
								changePlayer = false;
							}

						    if(move_count == FULL_BOARD){
						    	winning_numb = TIE;
						    }

						    if(winning_numb != NO_WINNER) {
								TIMER_stop(TIM5_);
								screen_state = SCREEN_END;
							}
								break;

						    }


						}
					}
				}
				if(changePlayer) player_turn = !player_turn;
			}
		else if(screen_state == SCREEN_END){
			// change screen
			if(winning_numb != NO_WINNER){

//				end check win state
			if (needs_to_increment){
				LCD_Clear(0, LCD_COLOR_MAGENTA);
				switch(winning_numb){
					case PLAYER_X:
						writeWord_("X Wins!", 310, 100, true);
						x_win_history++;
						break;
					case PLAYER_O:
						writeWord_("O Wins!", 310, 100, true);
						o_win_history++;
						break;
					case TIE:
						writeWord_("Tie!", 310, 100, true);
						tie_history++;
						break;
				}
				needs_to_increment = false;
				}

				writeWord_("Game Record:", 280, 130, false);
				char history_string[100];
				sprintf(history_string, "X: %d O: %d Tie: %d", x_win_history, o_win_history, tie_history);
				writeWord_(history_string, 280, 150, false);
				
				char timing_string[100];
				TIMER_stop(TIM5_);
				uint32_t game_length = TIMER_get_timer_value(TIM5_);
				sprintf(timing_string, "Length: %ld seconds", TIMER_convert_to_seconds(game_length));

				writeWord_(timing_string, 280, 170, false);
		}

		} else {
			/* Touch not pressed */
			printf("Not Pressed\n\n");
		}

//		deal with button reset
		int scheduledEvents = getScheduledEvents();
		if(scheduledEvents && RESET_GAME_SCREEN_EVENT){
			LCD_Clear(0, LCD_COLOR_CYAN);
			writeWord("Resetting Game", 260, 100);
			HAL_Delay(500);
			writeWord(".", 425, 100);
			HAL_Delay(500);
			writeWord(".", 435, 100);
			HAL_Delay(500);
			writeWord(".", 445, 100);
			HAL_Delay(500);
			drawMenu();
			removeSchedulerEvent(RESET_GAME_SCREEN_EVENT);
			screen_state = SCREEN_MENU;
			winning_numb = NO_WINNER;
			move_count = 0;
			player_turn = PLAYER_X_BOOL;
			TIMER_reset(TIM5_);


			//	clear game_board
			for(int x = 0; x < BOARD_DIMENSION; x++){
				for(int y = 0; y < BOARD_DIMENSION; y++){
					game_board[x][y] = 0;
				}
			}
		}

	}
}

void init_button_application(){
	init_button();
}

void init_RNG_application(){
	RNG_Init();
}

void init_button_interrupt_application(){
	interrupt_init_button();
}

void EXTI0_IRQHandler(){
    HAL_NVIC_DisableIRQ(EXTI0_IRQn);
    addSchedulerEvent(RESET_GAME_SCREEN_EVENT);
    printf("Resetting Screen!");
    HAL_EXTI_ClearPending(&hexti, GPIO_MODE_IT_RISING);
    __HAL_GPIO_EXTI_CLEAR_FLAG(EXTI_LINE_0); // ??? or __HAL_GPIO_EXTI_CLEAR_IT()
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void TIM5_IRQHandler(){ //??? should this be enabled or no
    HAL_NVIC_DisableIRQ(TIM5_IRQn);
    HAL_NVIC_ClearPendingIRQ(TIM5_IRQn);
    IRQ_TIMx_clear_pending(UIF_INTERRUPT_FLAG, TIM5_);
    HAL_NVIC_EnableIRQ(TIM5_IRQn);
}

// TouchScreen Interrupt
#if TOUCH_INTERRUPT_ENABLED == 1

void LCDTouchScreenInterruptGPIOInit(void)
{
	GPIO_InitTypeDef LCDConfig = {0};
    LCDConfig.Pin = GPIO_PIN_15;
    LCDConfig.Mode = GPIO_MODE_IT_RISING_FALLING;
    LCDConfig.Pull = GPIO_NOPULL;
    LCDConfig.Speed = GPIO_SPEED_FREQ_HIGH;
    
    // Clock enable
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // GPIO Init      
    HAL_GPIO_Init(GPIOA, &LCDConfig);

    // Interrupt Configuration
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	LCDTouchIRQ.Line = EXTI_LINE_15;

}

#define TOUCH_DETECTED_IRQ_STATUS_BIT   (1 << 0)  // Touchscreen detected bitmask

static uint8_t statusFlag;

void EXTI15_10_IRQHandler()
{
	HAL_NVIC_DisableIRQ(EXTI15_10_IRQn); // May consider making this a universial interrupt guard
	bool isTouchDetected = false;

	// Disable touch interrupt bit on the STMPE811
	uint8_t currentIRQEnables = ReadRegisterFromTouchModule(STMPE811_INT_EN);
	WriteDataToTouchModule(STMPE811_INT_EN, 0x00);

	// Clear the interrupt bit in the STMPE811
	statusFlag = ReadRegisterFromTouchModule(STMPE811_INT_STA);
	uint8_t clearIRQData = (statusFlag | TOUCH_DETECTED_IRQ_STATUS_BIT); // Write one to clear bit
	WriteDataToTouchModule(STMPE811_INT_STA, clearIRQData);
	
	uint8_t ctrlReg = ReadRegisterFromTouchModule(STMPE811_TSC_CTRL);
	if (ctrlReg & 0x80)
	{
		isTouchDetected = true;
	}

	// Determine if it is pressed or unpressed
	if(isTouchDetected) // Touch has been detected
	{
		printf("\nPressed");
		// May need to do numerous retries? 
		DetermineTouchPosition(&StaticTouchData);
		/* Touch valid */
		printf("\nX: %03d\nY: %03d \n", StaticTouchData.x, StaticTouchData.y);
		LCD_Clear(0, LCD_COLOR_RED);

	}else{

		/* Touch not pressed */
		printf("\nNot pressed \n");
		LCD_Clear(0, LCD_COLOR_GREEN);
	}

	// Re-enable IRQs
    WriteDataToTouchModule(STMPE811_INT_EN, currentIRQEnables);
	HAL_EXTI_ClearPending(&LCDTouchIRQ, EXTI_TRIGGER_RISING_FALLING);

	HAL_NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	//Potential ERRATA? Clearing IRQ bit again due to an IRQ being triggered DURING the handling of this IRQ..
	WriteDataToTouchModule(STMPE811_INT_STA, clearIRQData);

}
#endif // TOUCH_INTERRUPT_ENABLED
#endif // COMPILE_TOUCH_FUNCTIONS

