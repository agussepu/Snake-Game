#include "graphics.h"
#include "stdio.h"

// Inicia los recursos graficos del juego y cheque que no hayan errores
int init_graphics(SDL_Window **window, SDL_Renderer **renderer, TTF_Font **font) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error al inicializar SDL: %s\n", SDL_GetError());
        return 0;
    }

    *window = SDL_CreateWindow("Snake Game",
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!*window) {
        printf("Error al crear window: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    *renderer = SDL_CreateRenderer(
        *window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!*renderer) {
        printf("Error al crear renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return 0;
    }

    if (TTF_Init() == -1) {
        printf("Error al inicializar SDL_ttf: %s\n", TTF_GetError());
        SDL_DestroyRenderer(*renderer);
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return 0;
    }

    // Inicializar la fuente
    *font = TTF_OpenFont("fonts/Parkinsans-Medium.ttf", 50);
    if (!*font) {
        printf("Error al cargar fuente: %s\n", TTF_GetError());
        SDL_DestroyRenderer(*renderer);
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return 0;
    }

    return 1;
}

// Dibuja el tablero
void draw_grid(SDL_Renderer *renderer, int offset_x, int offset_y) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); // Colo de las lineas del tablero
    for (int x = 0; x <= WINDOW_GRID_WIDTH; x += CELL_SIZE) {
        SDL_RenderDrawLine(renderer, x + offset_x, offset_y, x + offset_x, WINDOW_GRID_HEIGHT + offset_y);
    }
    for (int y = 0; y <= WINDOW_GRID_HEIGHT; y += CELL_SIZE) {
        SDL_RenderDrawLine(renderer, offset_x, y + offset_y, WINDOW_GRID_WIDTH + offset_x, y + offset_y);
    }
}

// Dibuja la serpiente
void draw_snake(SDL_Renderer *renderer, Point *snake, int length, int offset_x, int offset_y) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Colo de la serpient (Verde)
    for (int i = 0; i < length - 1 ; i++) { 
        SDL_Rect rect = {
            snake[i].x * CELL_SIZE + offset_x,
            snake[i].y * CELL_SIZE + offset_y,
            CELL_SIZE,
            CELL_SIZE
        };
        SDL_RenderFillRect(renderer, &rect);
    }
}

// Dibuja la manzana
void draw_food(SDL_Renderer *renderer, Point food, int offset_x, int offset_y) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Color de la manzana (rojo)
    SDL_Rect rect = {
        food.x * CELL_SIZE + offset_x,
        food.y * CELL_SIZE + offset_y,
        CELL_SIZE,
        CELL_SIZE 
    };
    SDL_RenderFillRect(renderer, &rect);
}

// Dibuja los elementos principales del jeugo 
void render_game(SDL_Renderer *renderer, Point *snake, int snake_length, Point food, int offset_x, int offset_y) {
    // Limpia el renderizador con un color negro (fondo del juego)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Dibuja el tablero, la serpiente y la manzana
    draw_grid(renderer, offset_x, offset_y);
    draw_snake(renderer, snake, snake_length, offset_x, offset_y);
    draw_food(renderer, food, offset_x, offset_y);

}

// Dibuja el puntaje de la partida en juego
void render_score(SDL_Renderer *renderer, TTF_Font *font, int score, int screen_width) {
    char scoreText[50];
    sprintf(scoreText, "Score: %d", score);

    SDL_Color textColor = {255, 255, 255, 255}; // Blanco
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, scoreText, textColor);

    if (!textSurface) {
        printf("Error al crear superficie de texto: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        printf("Error al crear textura de texto: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    int textWidth = textSurface->w;
    int textHeight = textSurface->h;
    SDL_FreeSurface(textSurface);

    SDL_Rect textRect = {screen_width / 2 - textWidth / 2, 100, textWidth, textHeight};
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_DestroyTexture(textTexture); // Liberar textura después de renderizar
}

// Limpie las ventanas
void cleanup_graphics(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font) {
    if (font) TTF_CloseFont(font);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
