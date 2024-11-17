#ifndef GRID_H
#define GRID_H

#include <SDL2/SDL.h>

// Dimensiones del tablero
#define GRID_SIZE 20
#define GRID_DIM 800

// Función para renderizar el tablero
void render_grid(SDL_Renderer *renderer, int x, int y);

#endif
