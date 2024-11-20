#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "graphics.h"

//Funciones
void draw_food(SDL_Renderer *renderer, Point food, int offset_x, int offset_y);
Point generate_food(Point *snake, int length);
int check_collision(Point *snake, int length);

#endif // GAME_LOGIC_H