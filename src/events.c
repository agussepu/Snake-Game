#include "events.h"
#include "snake.h"

bool handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false; // Salir del juego
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE: return false; // Salir con ESC
                case SDLK_UP:    if (head->direction != SNAKE_DOWN)  head->direction = SNAKE_UP;    break;
                case SDLK_DOWN:  if (head->direction != SNAKE_UP)    head->direction = SNAKE_DOWN;  break;
                case SDLK_LEFT:  if (head->direction != SNAKE_RIGHT) head->direction = SNAKE_LEFT;  break;
                case SDLK_RIGHT: if (head->direction != SNAKE_LEFT)  head->direction = SNAKE_RIGHT; break;
            }
        }
    }
    return true; // Continuar
}
