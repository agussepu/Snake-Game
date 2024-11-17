#include "snake.h"
#include "grid.h"
#include "events.h"

int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;

    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Error al inicializar SDL: %s\n", SDL_GetError());
        return -1;
    }

    // Crear la ventana
    window = SDL_CreateWindow(
        "SnakeTable",
        WINDOW_X,
        WINDOW_Y,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );

    if (!window) {
        fprintf(stderr, "Error al crear la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Crear el renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Error al crear el renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Centramos el grid en la pantalla
    int grid_x = (WINDOW_WIDTH / 2) - (GRID_DIM / 2);
    int grid_y = (WINDOW_HEIGHT / 2) - (GRID_DIM / 2);

    // Bucle principal
    bool quit = false;
    while (!quit) {
        quit = !handle_events(); // Manejo de eventos
        SDL_RenderClear(renderer);

        // Dibujar el tablero
        render_grid(renderer, grid_x, grid_y);

        // Actualizar pantalla
        SDL_SetRenderDrawColor(renderer, 0x11, 0x11, 0x11, 255); // Color de fondo
        SDL_RenderPresent(renderer);
    }

    // Liberar recursos
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
