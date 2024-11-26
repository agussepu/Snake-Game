#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "graphics.h"

#define SNAKE_SPEED 120

//     [ Funciones ] 
void welcome(char *name);
void reset_game_state(Point *snake, int *snake_length, Point *food, int *dir_x, int *dir_y, int *score);
void input(int *running, int *dir_x, int *dir_y);
int check_food(Point *snake, int *snake_length, Point *food, int *score);
Point generate_food(Point *snake, int length);
int check_collision(Point *snake, int length, int grid_width, int grid_height);
void collision_message(int collision_type, int score);
int checkFinish();

#endif // GAME_LOGIC_H
