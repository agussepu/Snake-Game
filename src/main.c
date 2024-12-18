#include "graphics.h"
#include "game_logic.h"
#include "ranking.h"

// Librerias Generales
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // TOMI
    srand(time(NULL));

    const char *archive_ranking = "data/ranking.txt";
    Player ranking[MAX_JUGADORES] = {0};

    // Cargar el ranking y obtener el número de jugadores cargados
    int num_players = load_ranking(ranking, archive_ranking, MAX_JUGADORES);

    //Bienvenida y obtengo el nombre
    char actual_player[NOMBRE_LARGO];
    welcome(actual_player);

    // AGUS
    //Bucle Principal para jugar varias veces
    int again = 1; // Indicardor para continuar jugando
    while(again)
    {
        //Espera antes de empezar;
        printf("El juego ya esta por comenzar preparate...\n");
        SDL_Delay(2000); // Pausa de 2000 ms (2 segundos)
        
        // Variables para gráficos
        SDL_Window *window = NULL;
        SDL_Renderer *renderer = NULL;
        TTF_Font *font = NULL;

        // Inicializar gráficos (ventana, renderizador y fuente)
        if (!init_graphics(&window, &renderer, &font)) {
            return 1; // Si algo falla, termina el programa
        }

        // Calculamos el desplazamiento (centrado del tablero)
        int offset_x = (WINDOW_WIDTH - WINDOW_GRID_WIDTH) / 2;
        int offset_y = (WINDOW_HEIGHT - WINDOW_GRID_HEIGHT) / 2;

        // TOMI
        // Variables del juego
        Point snake[100]; //posicion (x,y) de cada segemento de la serpiente
        int snake_length;
        Point food;
        int dir_x, dir_y;
        int score;

        // Reiniciar las variables del juego para volver a jugar
        reset_game_state(snake, &snake_length, &food, &dir_x, &dir_y, &score);

        // AGUS
        // Bucle de la partida actual
        int running = 1;    
        while (running) {
            
            //Indica la direccion de la serpiente dada por el usuario
            input(&running, &dir_x, &dir_y);

            // Calcular la nueva posición de la cabeza
            Point new_head = {snake[0].x + dir_x, snake[0].y + dir_y};

            // Mover la serpiente
            move_snake(snake, snake_length, new_head);

            // Verificar colisiones 
            int collision_type = check_collision(
                snake,
                snake_length,
                WINDOW_GRID_WIDTH / CELL_SIZE,
                WINDOW_GRID_HEIGHT / CELL_SIZE
            );
            
            // Si colision_type devuelve verdadero entonces la serpiente chocho 
            if (collision_type) {
                
                // Indica con que superficie chocaste
                collision_message(collision_type, score);
               
                // Actualiza el ranking con el jugador actual
                update_ranking(ranking, &num_players, actual_player, score);
                
                //Liberar los recursos del sistema (al chocar no necesitamos mas el juego)
                cleanup_graphics(window, renderer, font);

                running = 0; // termina el bucle de la partida actual
                break;
            }

            // Comprobar si se comió la comida FUNCION
            (check_food(snake, &snake_length, &food, &score));

            // Renderizado general del juego
            render_game(renderer, snake, snake_length, food, offset_x, offset_y);
            
            // Renderizado del puntaje
            render_score(renderer, font, score, WINDOW_WIDTH);
            
            // Actualiza la pantalla
            SDL_RenderPresent(renderer); 

            // Pausa para regular la velocidad del juego
            SDL_Delay(SNAKE_SPEED);
        }
        
        //Si checkFinish es falso el jugador no desea seguir jugando
        if(!checkFinish()){
            // Guardar y mostrar el ranking actualizado
            save_ranking(ranking, archive_ranking, num_players);
            // Mostrar el ranking
            show_ranking(ranking, 0, num_players);
            
            //Finaliza el bucle principal del juego
            again = 0;
        }
    }
}