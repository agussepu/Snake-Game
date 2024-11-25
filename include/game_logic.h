#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "graphics.h"


//     [ Funciones ] 

void welcome(char *name);
int checkFinish();

void input(int *running, int *dir_x, int *dir_y);

Point generate_food(Point *snake, int length);

int check_collision(Point *snake, int length, int grid_width, int grid_height);
void reset_game_state(Point *snake, int *snake_length, Point *food, int *dir_x, int *dir_y, int *score);


#endif // GAME_LOGIC_H