#include "Menu.h"




void drawMenu(){
    LCD_Clear(0, LCD_COLOR_WHITE);
    LCD_SetTextColor(LCD_COLOR_BLACK);
    LCD_SetFont(&Font16x24);
	LCD_DisplayChar(90,270,'T');
	LCD_DisplayChar(100,270,'i');
	LCD_DisplayChar(110,270,'c');
	LCD_DisplayChar(120,270,'-');
	LCD_DisplayChar(130,270,'T');
	LCD_DisplayChar(140,270,'a');
	LCD_DisplayChar(155,270,'c');
	LCD_DisplayChar(165,270,'T');
	LCD_DisplayChar(175,270,'o');
	LCD_DisplayChar(190,270,'e');

	LCD_DisplayChar(172,290,'0');
	LCD_DisplayChar(187,290,'_');
	LCD_DisplayChar(202,290,'O');

    writeWord("1 Player", 310, 100);
    writeWord("2 Player", 310, 150);

//    player 1 box
    struct Point boxTopLeft;
    boxTopLeft.x = 305;
    boxTopLeft.y = 95;
    drawBox(&boxTopLeft, 30, 108, LCD_COLOR_BLACK);

//    player 2 box
    boxTopLeft.x = 305;
    boxTopLeft.y = 145;
    drawBox(&boxTopLeft, 30, 108, LCD_COLOR_BLACK);

}

void writeWord(char* word, int start_x, int start_y){
    int letter_distance = 12;
    char c = word[0];
    int char_i = 0;
    while(c != '\0'){
        LCD_DisplayChar(start_x + (char_i * letter_distance), start_y, c);
        char_i++;
        c = word[char_i];
    }
}

void writeWord_(char* word, int start_x, int start_y, bool fontLarge){
    int letter_distance = 12;


    if(fontLarge) {
        LCD_SetFont(&Font16x24);
        letter_distance = 12;
    }
    else{
         LCD_SetFont(&Font12x12);
         letter_distance = 8;
    }


    char c = word[0];
    int char_i = 0;
    while(c != '\0'){
        LCD_DisplayChar(start_x + (char_i * letter_distance), start_y, c);
        char_i++;
        c = word[char_i];
    }
}

struct Box_Boundaries drawBox(struct Point* top_left, int vert_size, int horz_size, int color){
    struct Box_Boundaries bounds;
    bounds.left_x = top_left->x;
    bounds.top_y = top_left->y;
    struct Point bottom_right;
    bottom_right.x = top_left->x + horz_size;
    bottom_right.y = top_left->y + vert_size;
    bounds.bottom_y = bottom_right.y;
    bounds.right_x = bottom_right.x;

    LCD_Draw_Vertical_Line(top_left->x, top_left->y, vert_size, color);
    LCD_Draw_Vertical_Line(bottom_right.x, top_left->y, vert_size, color);
    LCD_Draw_Horizontal_Line(top_left->x, top_left->y, horz_size, color);
    LCD_Draw_Horizontal_Line(top_left->x, bottom_right.y, horz_size + 1, color);
    return bounds;
}

void LCD_Draw_Horizontal_Line(int x, int y, int len, int color){
    for(int i = 0; i < len; i++) LCD_Draw_Vertical_Line(x + i, y, 1, color);
}

void Draw_Game(){
    LCD_Draw_Horizontal_Line(0, 107, 240, LCD_COLOR_BLACK);
    LCD_Draw_Horizontal_Line(0, 214, 240, LCD_COLOR_BLACK);
    LCD_Draw_Vertical_Line(80, 0, 320, LCD_COLOR_BLACK);
    LCD_Draw_Vertical_Line(160, 0, 320, LCD_COLOR_BLACK);
}

void Draw_Move(bool player, struct Box_Boundaries box){
	LCD_SetFont(&Font16x24);
	int x_pos = box.left_x - 8 + (box.right_x - box.left_x) / 2; //8 account for font size to center
	int y_pos = box.bottom_y + (box.top_y - box.bottom_y) / 2;
	if (player == 0) LCD_DisplayChar(x_pos, TOUCH_SCREEN_HEIGHT - y_pos, 'X');
	else if (player == 1) LCD_DisplayChar(x_pos, TOUCH_SCREEN_HEIGHT - y_pos, 'O');
}

