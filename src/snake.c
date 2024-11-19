#include "snake.h"

// Definición de las variables globales
Snake *head = NULL;
Snake *tail = NULL;

void init_snake() {
    Snake *new = malloc(sizeof(Snake));
    if (!new) {
        fprintf(stderr, "Error: No se pudo asignar memoria para la serpiente.\n");
        exit(EXIT_FAILURE);
    }
    new->x = GRID_SIZE / 2;
    new->y = GRID_SIZE / 2;
    new->direction = SNAKE_UP;
    new->next = NULL;

    head = new;
    tail = new;
}

void increase_snake() {
    Snake *new = malloc(sizeof(Snake));
    if (!new) {
        fprintf(stderr, "Error: No se pudo asignar memoria para la serpiente.\n");
        exit(EXIT_FAILURE);
    }
    new->x = tail->x;
    new->y = tail->y;
    new->direction = tail->direction;
    new->next = NULL;

    tail->next = new;
    tail = new;
}

void move_snake() {
    int prev_x = head->x;
    int prev_y = head->y;

    // Actualiza la posición de la cabeza
    switch (head->direction) {
        case SNAKE_UP:    head->y--; break;
        case SNAKE_DOWN:  head->y++; break;
        case SNAKE_LEFT:  head->x--; break;
        case SNAKE_RIGHT: head->x++; break;
    }

    // Actualiza los segmentos restantes
    Snake *track = head->next;
    while (track) {
        int save_x = track->x;
        int save_y = track->y;

        track->x = prev_x;
        track->y = prev_y;

        prev_x = save_x;
        prev_y = save_y;

        track = track->next;
    }
}

void render_snake(SDL_Renderer *renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 255);

    int seg_size = GRID_DIM / GRID_SIZE;
    SDL_Rect seg = {0, 0, seg_size, seg_size};

    Snake *track = head;
    while (track) {
        seg.x = x + track->x * seg_size;
        seg.y = y + track->y * seg_size;

        SDL_RenderFillRect(renderer, &seg);
        track = track->next;
    }
}

void free_snake() {
    while (head) {
        Snake *temp = head;
        head = head->next;
        free(temp);
    }
    tail = NULL;
}
