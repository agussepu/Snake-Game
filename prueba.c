#include <stdio.h>
#include <string.h>

#define MAX_JUGADORES 5
#define NOMBRE_LARGO 50

// Estructura para almacenar información del jugador
typedef struct {
    char nombre[NOMBRE_LARGO];
    int puntuacion;
} Jugador;

// Función para cargar el ranking desde el archivo
void cargarRanking(Jugador ranking[], const char *archivo)
{
    FILE *fp = fopen(archivo, "r");
    if (fp == NULL) {
        // Si no existe el archivo, inicializamos el ranking vacío
        for (int i = 0; i < MAX_JUGADORES; i++) {
            strcpy(ranking[i].nombre, "Vacío");
            ranking[i].puntuacion = 0;
        }
        return;
    }


    for (int i = 0; i < MAX_JUGADORES; i++) {
            if (fscanf(fp, "%s %d", ranking[i].nombre, &ranking[i].puntuacion) != 2) {
                strcpy(ranking[i].nombre, "Vacío");
                ranking[i].puntuacion = 0;
            }
        }
        fclose(fp);
}

// Función para guardar el ranking en el archivo
void guardarRanking(Jugador ranking[], const char *archivo) {
    FILE *fp = fopen(archivo, "w");
    if (fp == NULL) {
        perror("Error al guardar el archivo");
        return;
    }

    for (int i = 0; i < MAX_JUGADORES; i++) {
        fprintf(fp, "%s %d\n", ranking[i].nombre, ranking[i].puntuacion);
    }
    fclose(fp);
}

// Función para actualizar el ranking con un nuevo jugador
void actualizarRanking(Jugador ranking[], const char *nombre, int puntuacion) {
    // Inserta el nuevo jugador si corresponde
    for (int i = 0; i < MAX_JUGADORES; i++) {
        if (puntuacion > ranking[i].puntuacion) {
            // Mover los jugadores inferiores una posición hacia abajo
            for (int j = MAX_JUGADORES - 1; j > i; j--) {
                ranking[j] = ranking[j - 1];
            }
            // Insertar el nuevo jugador
            strcpy(ranking[i].nombre, nombre);
            ranking[i].puntuacion = puntuacion;
            break;
        }
    }
}

// Función para mostrar el ranking
void mostrarRanking(Jugador ranking[]) {
    printf("Ranking de jugadores:\n");
    for (int i = 0; i < MAX_JUGADORES; i++) {
        printf("%d. %s - %d puntos\n", i + 1, ranking[i].nombre, ranking[i].puntuacion);
    }
}

// Función para procesar un nuevo jugador
void procesarNuevoJugador(Jugador ranking[], const char *nombre, int puntuacion, const char *archivo) {
    actualizarRanking(ranking, nombre, puntuacion);  
    guardarRanking(ranking, archivo);               
}

int main() {
    Jugador ranking[MAX_JUGADORES];
    const char *archivoRanking = "ranking.txt";

    cargarRanking(ranking, archivoRanking);
    mostrarRanking(ranking);

    char nuevoNombre[NOMBRE_LARGO];
    int nuevaPuntuacion;

    printf("\nIngresar nuevo jugador:\n");
    printf("Nombre: ");
    scanf("%s", nuevoNombre);
    printf("Puntuación: ");
    scanf("%d", &nuevaPuntuacion);

    procesarNuevoJugador(ranking, nuevoNombre, nuevaPuntuacion, archivoRanking);

    printf("\nRanking actualizado:\n");
    mostrarRanking(ranking);

    return 0;
}