#ifndef SNAKE_H
#define SNAKE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

// Constantes de ventana
#define WINDOW_X 0
#define WINDOW_Y 0
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

// Constantes del tablero
#define GRID_SIZE 20
#define GRID_DIM 800

// Prototipos
void render_grid(SDL_Renderer *renderer, int x, int y);
bool handle_events();

#endif // SNAKE_H
