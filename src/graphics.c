#include "graphics.h"
#include "stdio.h"

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
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Verde
    for (int i = 0; i < length - 1 ; i++) { // Solo iterar hasta la longitud actual
        SDL_Rect rect = {
            snake[i].x * CELL_SIZE + offset_x,
            snake[i].y * CELL_SIZE + offset_y,
            CELL_SIZE,
            CELL_SIZE
        };
        SDL_RenderFillRect(renderer, &rect);
    }
}

// Manzana
void draw_food(SDL_Renderer *renderer, Point food, int offset_x, int offset_y) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
    SDL_Rect rect = {
        food.x * CELL_SIZE + offset_x,
        food.y * CELL_SIZE + offset_y,
        CELL_SIZE,
        CELL_SIZE 
    };
    SDL_RenderFillRect(renderer, &rect);
}

int init_graphics(SDL_Window **window, SDL_Renderer **renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return 0;
    }

    *window = SDL_CreateWindow("Snake Game",
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!*window) {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    *renderer = SDL_CreateRenderer(
        *window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!*renderer) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return 0;
    }

    if (TTF_Init() == -1) {
        printf("Error initializing SDL_ttf: %s\n", TTF_GetError());
        return 1;
    }

    return 1;
}

void render_game(SDL_Renderer *renderer, Point *snake, int snake_length, Point food, int offset_x, int offset_y) {
    // Limpiar el renderizador con color de fondo
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Dibujar la cuadrícula, la serpiente y la comida
    draw_grid(renderer, offset_x, offset_y);
    draw_snake(renderer, snake, snake_length, offset_x, offset_y);
    draw_food(renderer, food, offset_x, offset_y);

}

void render_score(SDL_Renderer *renderer, int score, int screen_width) {
    // Abrir la fuente (reemplaza con la ruta correcta)
    TTF_Font *font = TTF_OpenFont("data/Parkinsans-Medium.ttf", 50); 
    if (font == NULL) {
        printf("Error loading font: %s\n", TTF_GetError());
        return;
    }

    // Crear el texto
    char scoreText[50];
    sprintf(scoreText, "Score: %d", score);
    
    // Definir el color del texto (blanco)
    SDL_Color textColor = {255, 255, 255, 255};  // Blanco con opacidad máxima
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, scoreText, textColor);

    // Verificar si la superficie fue creada correctamente
    if (textSurface == NULL) {
        printf("Error creating text surface: %s\n", TTF_GetError());
        TTF_CloseFont(font);  // Cerrar la fuente
        return;
    }

    // Crear la textura a partir de la superficie
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == NULL) {
        printf("Error creating text texture: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);  // Liberar la superficie
        TTF_CloseFont(font);  // Cerrar la fuente
        return;
    }

    // Obtener las dimensiones del texto
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

    // Liberar la superficie
    SDL_FreeSurface(textSurface);

    // Calcular la posición horizontal para mover el texto a la derecha
    int textX = screen_width / 2 - textWidth / 2;  // Un margen de 20 píxeles desde el borde derecho
    
    // Calcular la posición vertical para poner el puntaje un poco más abajo
    int textY = 100;  // Un margen de 20 píxeles desde el borde superior

    // Establecer la posición del texto
    SDL_Rect textRect = {textX, textY, textWidth, textHeight};

    // Renderizar el texto en la pantalla
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    // Limpiar la textura
    SDL_DestroyTexture(textTexture);

    // Cerrar la fuente
    TTF_CloseFont(font);
}

