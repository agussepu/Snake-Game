#include "snake.h"

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

bool handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false; // Salir del juego
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
            return false; // Salir con tecla ESC
        }
    }
    return true; // Continuar
}

int main(){

    SDL_Window *window;
    SDL_Renderer *renderer;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Error al inicializar SDL: %s\n", SDL_GetError());
        return -1;
    }  

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

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    if (!renderer) {
        fprintf(stderr, "Error al crear el renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    int grid_x = (WINDOW_WIDTH / 2) - (GRID_DIM / 2);
    int grid_y = (WINDOW_HEIGHT / 2) - (GRID_DIM / 2);

    //Mantenemos el juego funcionando hasta que quiera el ususario
    bool quit = false;
    SDL_Event event;

    while (!quit) {
        quit = !handle_events();

        SDL_RenderClear(renderer);

        // Dibujar el tablero
        render_grid(renderer, grid_x, grid_y);

        // Actualizar pantalla
        SDL_SetRenderDrawColor(renderer, 0x11, 0x11, 0x11, 255); // Color de fondo
        SDL_RenderPresent(renderer);
    }


    //cierro la ventana y todo SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}