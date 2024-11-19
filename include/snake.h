#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

// Dimensiones de la ventana
#define WINDOW_X 0
#define WINDOW_Y 0
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

// Movimiento de la serpiente
typedef enum {
    SNAKE_UP,
    SNAKE_DOWN,
    SNAKE_LEFT,
    SNAKE_RIGHT
} SnakeDirection;

// Nodo de la serpiente
typedef struct Snake {
    int x, y;                   // Posición en la cuadrícula
    SnakeDirection direction;   // Dirección actual
    struct Snake *next;         // Siguiente segmento
} Snake;

// Funciones
void init_snake();
void increase_snake();
void move_snake();
void render_snake(SDL_Renderer *renderer, int x, int y);
void free_snake(); // Para liberar la memoria al final del juego

// Declaraciones de variables globales
extern Snake *head;  // Declaración sin inicialización
extern Snake *tail;

#endif
