#include "touchLogic.h"

bool checkTouchBounds(struct Point* touch_loc, struct Box_Boundaries bounds){
    // checks to see if Point input is in the given box boundaries
    return ((bounds.left_x <= touch_loc->x && bounds.right_x > touch_loc->x) &&
            (bounds.top_y >= touch_loc->y && bounds.bottom_y < touch_loc->y));
}


uint16_t Check_Win(int (*game_board)[BOARD_DIMENSION]){ //check if win or tie
	uint8_t num_win_states = 8;
	uint8_t winning_numb = PLAYER_X;
	uint16_t winning_states[num_win_states];
	uint8_t board_width = BOARD_DIMENSION;

//    set winning states to 0
	for(int i = 0; i < num_win_states; i++){
		winning_states[i] = 0;
	}

	for(int j = 0; j < 2; j++){
		for(int i = 0; i < BOARD_DIMENSION; i++){
			if (game_board[0][i] == winning_numb) winning_states[0]++;
			if (game_board[1][i] == winning_numb) winning_states[1]++;
			if (game_board[2][i] == winning_numb) winning_states[2]++;
			if (game_board[i][0] == winning_numb) winning_states[3]++;
			if (game_board[i][1] == winning_numb) winning_states[4]++;
			if (game_board[i][2] == winning_numb) winning_states[5]++;
			if (game_board[i][i] == winning_numb) winning_states[6]++;
			if (game_board[board_width - i][board_width - i] == winning_numb) winning_states[7]++;
		}

		for(int k = 0; k < num_win_states; k++){
			if(winning_states[k] == BOARD_DIMENSION) {
				return winning_numb;
			}
			winning_states[k] = 0;
		}
		winning_numb = PLAYER_O;
	}
	return TIE;
}

