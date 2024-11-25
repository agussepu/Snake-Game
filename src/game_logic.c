#include "game_logic.h"

// Bienvenida y nombre del usuario
void welcome(char *name) {
    //char name[20];
    char selection;
    int verification = 0;

    printf("\n");
    printf("*********************************************************************\n");
    printf("*********************** WELCOME TO SNAKE GAME ***********************\n");
    printf("*********************************************************************\n");
    printf("\n");
    printf("=====================================================================\n");
    printf("Ⅱ                        REGLAS DEL JUEGO                           Ⅱ\n");
    printf("=====================================================================\n");
    printf("Ⅱ  Este juego consiste en ponerte en el papel de una serpiente,     Ⅱ\n");
    printf("Ⅱ  la cual odia a las manzanas. Tu mision es deborar todas las      Ⅱ\n");
    printf("Ⅱ  manzas que encuentres en tu camino pero cuidado, evita comerte   Ⅱ\n");
    printf("Ⅱ  a ti mismo o golpearte con las paredes.                          Ⅱ\n");
    printf("=====================================================================\n");
    printf("\n");
    printf("=====================================================================\n");
    printf(" Antes de comenzar, escriba su nombre por favor: ");
    scanf("%s", name);
    printf("Ⅱ-------------------------------------------------------------------Ⅱ\n");
    printf(" Buena suerte comiendo manzanas %s. No te golpees!!               \n", name);
    printf("=====================================================================\n");

    while (verification == 0) {
        printf("Escriba [Y] para comenzar: ");
        
        while (getchar() != '\n'); // Limpiar buffer de entrada

        scanf(" %c", &selection); // Nota el espacio antes del %c
        if (selection == 'Y' || selection == 'y') { // Compara con comillas simples
            verification = 1;
        } else {
            printf("Ok... parece que aún no estás listo.\n");
        }
    }
}

// Reinicia las variables del juego
void reset_game_state(Point *snake, int *snake_length, Point *food, int *dir_x, int *dir_y, int *score) {

    // Longitud inicial de la serpiente
    *snake_length = 8;

    // Posición inicial de la serpiente
    for (int i = 0; i < *snake_length; i++) {
        snake[i].x = 10 - i;
        snake[i].y = 10;
    }

    // Dirección inicial de movimiento
    *dir_x = 1;
    *dir_y = 0;

    // Generar la posición inicial de la comida
    *food = generate_food(snake, *snake_length);

    // Puntaje inicial
    *score = 0;
}

//Teclas de movimiento de snake (flechitas y salir)
void input(int *running, int *dir_x, int *dir_y) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *running = 0;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    *running = 0;
                    break;
                case SDLK_UP:
                    if (*dir_y == 0) { *dir_x = 0; *dir_y = -1; }
                    break;
                case SDLK_DOWN:
                    if (*dir_y == 0) { *dir_x = 0; *dir_y = 1; }
                    break;
                case SDLK_LEFT:
                    if (*dir_x == 0) { *dir_x = -1; *dir_y = 0; }
                    break;
                case SDLK_RIGHT:
                    if (*dir_x == 0) { *dir_x = 1; *dir_y = 0; }
                    break;
            }
        }
    }
}

// Mueve la serpiente
void move_snake(Point *snake, int snake_length, Point new_head) {
    for (int i = snake_length - 1; i > 0; i--) {
        snake[i] = snake[i - 1]; 
    }
    snake[0] = new_head; 
}

// Colision
int check_collision(Point *snake, int length, int grid_width, int grid_height) {
    // Verificar colisión con los bordes
    if (snake[0].x < 0 || snake[0].x >= grid_width || 
        snake[0].y < 0 || snake[0].y >= grid_height) {
        return 1; // Colisión con la pared
    }


    // Verificar colisión con el cuerpo
    for (int i = 1; i < length; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            return 2; // Colisión con el cuerpo
        }
    }

    return 0; // No hay colisión
}

// Indica cual fue la colision
void collision_message(int collision_type, int score) {
    if (collision_type == 1) {
        printf("***************  ¡¡GAME OVER!! Chocaste con la pared  ***************\n");
        printf("\n");
    } else if (collision_type == 2) {
        printf("**********  ¡¡GAME OVER!! Parece que te mordiste la cola  ***********\n");
        printf("\n");
    }

    printf("=====================================================================\n");
    printf("Ⅱ                          Final Score: %d                           Ⅱ\n", score);
    printf("=====================================================================\n");
}

// Chequea si se comio la manzana
int check_food(Point *snake, int *snake_length, Point *food, int *score) {
    if (snake[0].x == food->x && snake[0].y == food->y) {
        // Incrementar longitud de la serpiente
        snake[*snake_length] = snake[*snake_length - 1]; // Nuevo segmento toma posición de la cola
        (*snake_length)++;
        (*score)++;

        // Generar nueva comida
        *food = generate_food(snake, *snake_length);

        return 1; // Indica que se comió la comida
    }
    return 0; // No se comió la comida
}

// Punto donde se generara la manzana
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

// Verifica si el usuario desea seguir jugando
int checkFinish() {
    char input;

    while(1) {
        printf("¿Desea seguir jugando? [Y/n]: ");
        scanf(" %c", &input); // Leer entrada ignorando espacios en blanco

        // Verificar la entrada
        if (input == 'n' || input == 'N') {
            printf("\n");
            printf("*********************************************************************\n");
            printf("************************ CERRANDO SNAKE GAME ************************\n");
            printf("*********************************************************************\n");
            printf("\n");
            printf("=====================================================================\n");
            printf("Ⅱ                         GRACIAS POR JUGAR                         Ⅱ\n");
            printf("=====================================================================\n");
            printf("\n");
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


