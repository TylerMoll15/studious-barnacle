#include "LCD_Driver.h"
#include <stdio.h>
#include "touchLogic.h"
#include "Definitions.h"

void drawMenu();
void writeWord(char* word, int start_y, int start_x);
void writeWord_(char* word, int start_x, int start_y, bool fontLarge);
struct Box_Boundaries drawBox(struct Point* top_left, int vert_size, int horz_size, int color); // color as defined in LCD_Driver
void LCD_Draw_Horizontal_Line(int x, int y, int len, int color);
void Draw_Game();
void Draw_Move(bool player, struct Box_Boundaries box);

