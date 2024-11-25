#include "ranking.h"

// Función para cargar el ranking desde el archivo
int cargarRanking(Jugador ranking[], const char *archivo, int maxJugadores) {
    FILE *fp = fopen(archivo, "r");
    if (fp == NULL) {
        perror("Error al abrir el archivo de ranking");
        return 0; // No se pudo cargar ningún jugador
    }

    int count = 0; // Contador de jugadores cargados
    while (count < maxJugadores && fscanf(fp, "%19s %d", ranking[count].nombre, &ranking[count].puntuacion) == 2) {
        // Verifica si el nombre tiene una longitud válida y si la puntuación es un número válido
        if (strlen(ranking[count].nombre) == 0 || ranking[count].puntuacion < 0) {
            break;  // Si los datos no son válidos, interrumpir la carga
        }
        count++;
    }
    fclose(fp);
    return count; // Retorna la cantidad de jugadores cargados
}

// Función para mostrar el ranking
void mostrarRanking(Jugador ranking[], int numJugadores) {
    printf("=====================================================================\n");
    printf("Ⅱ                        Ranking de Jugadores                       Ⅱ\n");
    printf("=====================================================================\n");
    printf("Ⅱ Posición           | Nombre                  | Puntos             Ⅱ\n");
    printf("---------------------------------------------------------------------\n");
    for (int i = 0; i < numJugadores; i++) {
        printf("Ⅱ N°%8d              | %-15s                   | %6d                Ⅱ\n", i + 1, ranking[i].nombre, ranking[i].puntuacion);
    }
    printf("=====================================================================\n");
}

void ordenarRanking(Jugador ranking[], int numJugadores) {
    for (int i = 0; i < numJugadores - 1; i++) {
        for (int j = 0; j < numJugadores - i - 1; j++) {
            if (ranking[j].puntuacion < ranking[j + 1].puntuacion) {
                // Intercambiar jugadores
                Jugador temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }
}

void guardarRanking(Jugador ranking[], const char *archivo, int numJugadores) {
    // Ordenar el ranking antes de guardarlo
    ordenarRanking(ranking, numJugadores);

    FILE *fp = fopen(archivo, "w");
    if (fp == NULL) {
        perror("Error al guardar el archivo");
        return;
    }

    for (int i = 0; i < numJugadores; i++) {
        if (strlen(ranking[i].nombre) > 0 && ranking[i].puntuacion >= 0) {
            fprintf(fp, "%s %d\n", ranking[i].nombre, ranking[i].puntuacion);
        }
    }
    fclose(fp);
}

void actualizarRanking(Jugador ranking[], int *numJugadores, const char *nombre, int puntuacion) {
    // Verificar si el jugador ya existe
    for (int i = 0; i < *numJugadores; i++) {
        if (strcmp(ranking[i].nombre, nombre) == 0) {
            if (puntuacion > ranking[i].puntuacion) {
                ranking[i].puntuacion = puntuacion; // Actualizar puntuación si es mayor
            }
            return; // Ya se actualizó, salir
        }
    }

    // Si no existe y hay espacio, agregar al final
    if (*numJugadores < MAX_JUGADORES) {
        strncpy(ranking[*numJugadores].nombre, nombre, NOMBRE_LARGO - 1);
        ranking[*numJugadores].nombre[NOMBRE_LARGO - 1] = '\0'; // Asegurar terminación
        ranking[*numJugadores].puntuacion = puntuacion;
        (*numJugadores)++;
    }
}