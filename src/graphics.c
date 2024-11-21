#include "graphics.h"
#include "stdio.h"

int welcome() {
    char name[20];
    char selection;
    int verification = 0;

    printf("-------------------------[SNAKE GAME]------------------------\n");
    printf("Este juego consiste en ponerte en el papel de una serpiente la cual odia a apple... \n");
    printf("Por lo que debe aguantar lo más que pueda comiendo manzanas.\n");
    printf("-------------------------------------------------------------\n");
    printf("Antes de comenzar, escriba su nombre por favor: ");
    scanf("%s", name);

    printf("Buena suerte comiendo manzanas %s. Escriba [Y] si quiere comenzar.\n", name);

    while (verification == 0) {
        printf("Escriba [Y] para comenzar: ");
        scanf(" %c", &selection); // Nota el espacio antes del %c
        if (selection == 'Y' || selection == 'y') { // Compara con comillas simples
            verification = 1;
        } else {
            printf("Ok... parece que aún no estás listo.\n");
        }
    }

    //Espera un Segundo antes de comenzar
    return 0;
}

int checkFinish() {
    char input;

    while (1) {
        printf("¿Desea seguir jugando? [Y/n]: ");
        scanf(" %c", &input); // Leer entrada ignorando espacios en blanco

        // Verificar la entrada
        if (input == 'n' || input == 'N') {
            return 0; // Terminar juego
        } else if (input == 'y' || input == 'Y') {
            return 1; // Continuar juego
        } else {
            printf("Entrada no válida. Intenta nuevamente.\n");
        }

        // Consumir cualquier entrada sobrante para evitar errores en la siguiente iteración
        while (getchar() != '\n');
    }
}

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