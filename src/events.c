#include "events.h"

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