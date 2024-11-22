#include "graphics.h"
#include "game.logic.h"
#include "ranking.h"

// Librerias Generales
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    const char *archivoRanking = "data/ranking.txt";
    Jugador ranking[MAX_JUGADORES] = {0};

    // Cargar el ranking y obtener el número de jugadores cargados
    int numJugadores = cargarRanking(ranking, archivoRanking, MAX_JUGADORES);

    //Bienvenida y obtengo el nombre
    char jugadorActual[NOMBRE_LARGO];
    welcome(jugadorActual);

    //Bucle Principal para jugar varias veces
    int again = 1; // Indicardor para continuar jugando
    while(again)
    {
        //Espera antes de empezar;
        printf("El juego ya esta por comenzar preparate...\n");
        SDL_Delay(2000); // Pausa de 1000 ms (1 segundo)
        
        // Inicializar el juego (GRAPHICS)
        SDL_Window *window;
        SDL_Renderer *renderer;
        
        if (!init_graphics(&window, &renderer))
        {
            return 1;
        }

        // Calculamos el desplazamiento para centrar el tablero
        int offset_x = (WINDOW_WIDTH - WINDOW_GRID_WIDTH) / 2;
        int offset_y = (WINDOW_HEIGHT - WINDOW_GRID_HEIGHT) / 2;
        
        // Variables del juego
        Point snake[100];
        int snake_length;
        Point food;
        int dir_x, dir_y;
        int score;

        // Reiniciar el estado del juego
        reset_game_state(snake, &snake_length, &food, &dir_x, &dir_y, &score);

        // Bucle Juego
        int running = 1;    

        while (running) {
            //printf("Head position: (%d, %d)\n", snake[0].x, snake[0].y);
            input(&running, &dir_x, &dir_y);

            // Calcular la nueva posición de la cabeza
            Point new_head = {snake[0].x + dir_x, snake[0].y + dir_y};

           // Mover la serpiente
            for (int i = snake_length - 1; i > 0; i--) {
                snake[i] = snake[i - 1];
            }
            snake[0] = new_head;

            // Verificar colisiones
            int collision_type = check_collision(
                snake,
                snake_length,
                WINDOW_GRID_WIDTH / CELL_SIZE,
                WINDOW_GRID_HEIGHT / CELL_SIZE
            );
 
            if (collision_type) {
                cleanup(window, renderer);

                // Actualiza el ranking con el jugador actual
                actualizarRanking(ranking, &numJugadores, jugadorActual, score);

                if (collision_type == 1) {
                    printf("Game Over! Chocaste con la pared\n");
                } else {
                    printf("Game Over! Parece que te mordiste la cola.\n");
                }
                printf("====================\n");
                printf("= Final Score: %d  =\n", score);
                printf("====================\n");
                running = 0;
                break;
            }

            // Comprobar si se comió la comida
            if (snake[0].x == food.x && snake[0].y == food.y) {
                // Incrementar longitud de la serpiente correctamente
                snake[snake_length] = snake[snake_length - 1]; // Nuevo segmento toma posición de la cola
                snake_length++;
                score++;

                // Generar una nueva manzana
                food = generate_food(snake, snake_length);
            }

            // Renderizar el juego
            render_game(renderer, snake, snake_length, food, offset_x, offset_y);

            //Velocidad serpiente
            SDL_Delay(120);
        }
        
        if(!checkFinish()){

            // Guardar el ranking actualizado
            guardarRanking(ranking, archivoRanking, numJugadores);

            // Mostrar el ranking
            mostrarRanking(ranking, numJugadores);
            again = 0;
        }
        
        cleanup(window, renderer);
    }
}