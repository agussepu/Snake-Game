#include "grid.h"

void render_grid(SDL_Renderer *renderer, int x, int y) {
    // Establece el color para las líneas del grid
    SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0x55, 255);

    const int cell_size = GRID_DIM / GRID_SIZE; // Tamaño de cada celda
    SDL_Rect cell = {0, 0, cell_size, cell_size}; // Rectángulo base

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            cell.x = x + (i * cell_size);
            cell.y = y + (j * cell_size);
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
}