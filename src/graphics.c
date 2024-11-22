#include "graphics.h"
#include "stdio.h"

// Limpie las ventanas
void cleanup(SDL_Window *window, SDL_Renderer *renderer) {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

// Tablero
void draw_grid(SDL_Renderer *renderer, int offset_x, int offset_y) {
    SDL_SetRenderDrawColor(renderer, 55, 55, 55, 255); // White
    for (int x = 0; x < WINDOW_GRID_WIDTH + 1; x += CELL_SIZE) {
        SDL_RenderDrawLine(renderer, x + offset_x, offset_y, x + offset_x, WINDOW_GRID_HEIGHT + offset_y);
    }
    for (int y = 0; y < WINDOW_GRID_HEIGHT + 1; y += CELL_SIZE) {
        SDL_RenderDrawLine(renderer, offset_x, y + offset_y, WINDOW_GRID_WIDTH + offset_x, y + offset_y);
    }
}

// Serpiente
void draw_snake(SDL_Renderer *renderer, Point *snake, int length, int offset_x, int offset_y) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Verde
    for (int i = 0; i < length - 1 ; i++) { // Solo iterar hasta la longitud actual
        SDL_Rect rect = {
            snake[i].x * CELL_SIZE + offset_x,
            snake[i].y * CELL_SIZE + offset_y,
            CELL_SIZE,
            CELL_SIZE
        };
        SDL_RenderFillRect(renderer, &rect);
    }
}

// Manzana
void draw_food(SDL_Renderer *renderer, Point food, int offset_x, int offset_y) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
    SDL_Rect rect = {
        food.x * CELL_SIZE + offset_x,
        food.y * CELL_SIZE + offset_y,
        CELL_SIZE,
        CELL_SIZE 
    };
    SDL_RenderFillRect(renderer, &rect);
}

int init_graphics(SDL_Window **window, SDL_Renderer **renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 0;
    }

    *window = SDL_CreateWindow("Snake Game",
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!*window) {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    *renderer = SDL_CreateRenderer(
        *window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!*renderer) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return 0;
    }
    return 1;
}

void render_game(SDL_Renderer *renderer, Point *snake, int snake_length, Point food, int offset_x, int offset_y) {
    // Limpiar el renderizador con color de fondo
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Dibujar la cuadrícula, la serpiente y la comida
    draw_grid(renderer, offset_x, offset_y);
    draw_snake(renderer, snake, snake_length, offset_x, offset_y);
    draw_food(renderer, food, offset_x, offset_y);

    // Actualizar la pantalla
    SDL_RenderPresent(renderer);
}




