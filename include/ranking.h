#include <string.h>
#include <stdio.h>

#define NOMBRE_LARGO 50
#define MAX_JUGADORES 20

// Estructura para almacenar información del jugador
typedef struct {
    char nombre[NOMBRE_LARGO];
    int puntuacion;
} Jugador;

//     [ Funciones ] 
void guardarRanking(Jugador ranking[], const char *archivo, int numJugadores);
void mostrarRanking(Jugador ranking[], int numJugadores);
void actualizarRanking(Jugador ranking[], int *numJugadores, const char *nombre, int puntuacion);
int cargarRanking(Jugador ranking[], const char *archivo, int maxJugadores);
void ordenarRanking(Jugador ranking[], int numJugadores);