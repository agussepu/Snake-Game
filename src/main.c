#include "graphics.h"
#include "game.logic.h"

// Librerias Generales
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    welcome();

    //Iniciar bucle para volver a jugar
    int again = 1;
    while(again)
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            printf("Error initializing SDL: %s\n", SDL_GetError());
            return 1;
        }

        SDL_Window *window = SDL_CreateWindow(
            "Snake Game",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN
        );

        if (!window) {
            printf("Error creating window: %s\n", SDL_GetError());
            SDL_Quit();
            return 1;
        }

        SDL_Renderer *renderer = SDL_CreateRenderer(
            window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
        );

        if (!renderer) {
            printf("Error creating renderer: %s\n", SDL_GetError());
            cleanup(window, NULL);
            return 1;
        }

        // Calculamos el desplazamiento para centrar el tablero
        int offset_x = (WINDOW_WIDTH - WINDOW_GRID_WIDTH) / 2;
        int offset_y = (WINDOW_HEIGHT - WINDOW_GRID_HEIGHT) / 2;

        Point snake[100];
        int snake_length = 8;
        for (int i = 0; i < snake_length; i++) {
            snake[i].x = 10 - i;
            snake[i].y = 10;
        }

        int dir_x = 1, dir_y = 0;
        Point food = generate_food(snake, snake_length);
        int score = 0;

        int running = 1;
        SDL_Event event;

        // Bucle Principal
        while (running) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = 0;
                } else if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            running = 0;
                            break; // Exit with ESC
                        case SDLK_UP:
                            if (dir_y == 0) { dir_x = 0; dir_y = -1; }
                            break;
                        case SDLK_DOWN:
                            if (dir_y == 0) { dir_x = 0; dir_y = 1; }
                            break;
                        case SDLK_LEFT:
                            if (dir_x == 0) { dir_x = -1; dir_y = 0; }
                            break;
                        case SDLK_RIGHT:
                            if (dir_x == 0) { dir_x = 1; dir_y = 0; }
                            break;
                    }
                }
            }

            Point new_head = {snake[0].x + dir_x, snake[0].y + dir_y};

            // Detectar colisiones antes de mover la serpiente
            if (new_head.x < 0 || new_head.x >= (WINDOW_GRID_WIDTH / CELL_SIZE) ||
                new_head.y < 0 || new_head.y >= (WINDOW_GRID_HEIGHT / CELL_SIZE)) {
                cleanup(window, renderer);
                printf("Game Over! You hit the wall.\nFinal Score: %d\n", score);
                running = 0;
                break;
            }

            for (int i = 1; i < snake_length; i++) {
                if (snake[i].x == new_head.x && snake[i].y == new_head.y) {
                    cleanup(window, renderer);
                    printf("Game Over! You hit yourself.\nFinal Score: %d\n", score);
                    running = 0;
                    break;
                }
            }

            // Mover la serpiente 
            for (int i = snake_length - 1; i > 0; i--) {
                snake[i] = snake[i - 1];
            }
            snake[0] = new_head;


            if (snake[0].x == food.x && snake[0].y == food.y) {
                snake_length++;
                score++;
                food = generate_food(snake, snake_length);
                //printf("Score: %d\n", score);
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
            SDL_RenderClear(renderer);

            draw_grid(renderer, offset_x, offset_y);
            draw_snake(renderer, snake, snake_length, offset_x, offset_y);
            draw_food(renderer, food, offset_x, offset_y);

            SDL_RenderPresent(renderer);

            SDL_Delay(120);
        }
        
        if(checkFinish() == 0){
            printf("Cerrando SNAKE GAME...\n");
            again = 0;
        }
        
        cleanup(window, renderer);
    }
    // Creo que esta de mas porque ahora limpio la pantalla ni bien choco
    return 0;
}
