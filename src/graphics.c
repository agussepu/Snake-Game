#include "graphics.h"

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
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green
    for (int i = 0; i < length; i++) {
        SDL_Rect rect = {
            snake[i].x * CELL_SIZE + offset_x,
            snake[i].y * CELL_SIZE + offset_y,
            CELL_SIZE,
            CELL_SIZE
        };
        SDL_RenderFillRect(renderer, &rect);
    }
}