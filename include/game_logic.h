#include "graphics.h"
#define SNAKE_SPEED 120

//     [ Funciones ] 
void welcome(char *name);
void reset_game_state(Point *snake, int *snake_length, Point *food, int *dir_x, int *dir_y, int *score);
void input(int *running, int *dir_x, int *dir_y);
Point generate_food(Point *snake, int length);
int check_collision(Point *snake, int length, int grid_width, int grid_height);
int checkFinish();
