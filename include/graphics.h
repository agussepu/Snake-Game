#ifndef GRAPHICS_H
#define GRAPHICS_H

// sudo apt install libsdl2-dev
#include <SDL2/SDL.h>

//sudo apt install libsdl2-ttf-dev
#include <SDL2/SDL_ttf.h>

// Dimensiones de la ventana
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

// Dimensiones del grid (espacio jugable)
#define WINDOW_GRID_WIDTH 800
#define WINDOW_GRID_HEIGHT 600
#define CELL_SIZE 40

// Estructura general de eje x,y
typedef struct {
    int x, y;
} Point;

//     [ Funciones ] 

int init_graphics(SDL_Window **window, SDL_Renderer **renderer);

void draw_grid(SDL_Renderer *renderer, int offset_x, int offset_y);
void draw_snake(SDL_Renderer *renderer, Point *snake, int length, int offset_x, int offset_y);
void draw_food(SDL_Renderer *renderer, Point food, int offset_x, int offset_y);

void render_game(SDL_Renderer *renderer, Point *snake, int snake_length, Point food, int offset_x, int offset_y);
void render_score(SDL_Renderer *renderer, int score, int screen_width);

void cleanup(SDL_Window *window, SDL_Renderer *renderer);

#endif // GRAPHICS_H
