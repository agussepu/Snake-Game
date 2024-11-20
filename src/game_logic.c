#include "game.logic.h"

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

// Lugar donde se generara la manzana
Point generate_food(Point *snake, int length) {
    Point food;
    int valid;
    do {
        valid = 1;
        food.x = rand() % (WINDOW_GRID_WIDTH / CELL_SIZE);
        food.y = rand() % (WINDOW_GRID_HEIGHT / CELL_SIZE);

        //Chequea que no se genere sobre la serpiente
        for (int i = 0; i < length; i++) {
            if (snake[i].x == food.x && snake[i].y == food.y) {
                valid = 0;
                break;
            }
        }
    } while (!valid);
    return food;
}

// Colision
int check_collision(Point *snake, int length) {
    for (int i = 1; i < length; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            return 1; // Collision detected
        }
    }
    return 0;
}