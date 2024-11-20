#include "graphics.h"
#include "game.logic.h"

// Librerias Generales
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

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
    int snake_length = 5;
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

        for (int i = snake_length - 1; i > 0; i--) {
            snake[i] = snake[i - 1];
        }
        snake[0].x += dir_x;
        snake[0].y += dir_y;

        if (snake[0].x < 0 || snake[0].x >= (WINDOW_GRID_WIDTH / CELL_SIZE) ||
            snake[0].y < 0 || snake[0].y >= (WINDOW_GRID_HEIGHT / CELL_SIZE)) {
            printf("Game Over! You hit the wall.\nFinal Score: %d\n", score);
            break;
        }

        if (check_collision(snake, snake_length)) {
            printf("Game Over! You hit yourself.\nFinal Score: %d\n", score);
            break;
        }

        if (snake[0].x == food.x && snake[0].y == food.y) {
            snake_length++;
            score++;
            food = generate_food(snake, snake_length);
            printf("Score: %d\n", score);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
        SDL_RenderClear(renderer);

        draw_grid(renderer, offset_x, offset_y);
        draw_snake(renderer, snake, snake_length, offset_x, offset_y);
        draw_food(renderer, food, offset_x, offset_y);

        SDL_RenderPresent(renderer);

        SDL_Delay(120);
    }

    cleanup(window, renderer);
    return 0;
}
