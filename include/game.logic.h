#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "graphics.h"

//Funciones
Point generate_food(Point *snake, int length);
int check_collision(Point *snake, int length, int grid_width, int grid_height);
void input(int *running, int *dir_x, int *dir_y);
void reset_game_state(Point *snake, int *snake_length, Point *food, int *dir_x, int *dir_y, int *score);
int checkFinish();
void welcome(char *name);


#endif // GAME_LOGIC_H