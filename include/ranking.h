#include <string.h>
#include <stdio.h>
#include <graphics.h>

#define NOMBRE_LARGO 50
#define MAX_JUGADORES 20

// Estructura para almacenar información del jugador
typedef struct {
    char name[NOMBRE_LARGO];
    int points;
} Player;

//Funciones
void save_ranking(Player ranking[], const char *archive, int num_players);
void show_ranking(Player ranking[], int num_players);
void update_ranking(Player ranking[], int *num_players, const char *name, int points);
int load_ranking(Player ranking[], const char *archive, int max_players);
void order_ranking(Player ranking[], int num_players);