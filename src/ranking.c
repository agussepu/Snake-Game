#include "ranking.h"

// Función para cargar el ranking desde el archivo
int load_ranking(Player ranking[], const char *archive, int max_players) {
    FILE *fp = fopen(archive, "r");
    if (fp == NULL) {
        perror("Error al abrir el archivo de ranking");
        return 0; // No se pudo cargar ningún jugador
    }

    int count = 0; // Contador de jugadores cargados
    while (count < max_players && fscanf(fp, "%19s %d", ranking[count].name, &ranking[count].points) == 2) {
        // Verifica si el nombre tiene una longitud válida y si la puntuación es un número válido
        if (strlen(ranking[count].name) == 0 || ranking[count].points < 0) {
            break;  // Si los datos no son válidos, interrumpir la carga
        }
        count++;
    }
    fclose(fp);
    return count; // Retorna la cantidad de jugadores cargados
}

// Agrega jugador y su score o solo actuliza el score del jugador existente
void update_ranking(Player ranking[], int *num_players, const char *name, int points) {
    // Verificar si el jugador ya existe
    for (int i = 0; i < *num_players; i++) {
        if (strcmp(ranking[i].name, name) == 0) {
            if (points > ranking[i].points) {
                ranking[i].points = points; // Actualizar puntuación si es mayor
            }
            return; // Ya se actualizó, salir
        }
    }

    // Si no existe y hay espacio, agregar al final
    if (*num_players < MAX_JUGADORES) {
        strncpy(ranking[*num_players].name, name, NOMBRE_LARGO - 1);
        ranking[*num_players].name[NOMBRE_LARGO - 1] = '\0'; // Asegurar terminación
        ranking[*num_players].points = points;
        (*num_players)++;
    }
}

// Guarda para guadar el ranking en el archivo
void save_ranking(Player ranking[], const char *archive, int num_players) {
    // Ordenar el ranking antes de guardarlo
    order_ranking(ranking, num_players);

    FILE *fp = fopen(archive, "w");
    if (fp == NULL) {
        perror("Error al guardar el archivo");
        return;
    }

    for (int i = 0; i < num_players; i++) {
        if (strlen(ranking[i].name) > 0 && ranking[i].points >= 0) {
            fprintf(fp, "%s %d\n", ranking[i].name, ranking[i].points);
        }
    }
    fclose(fp);
}

// Ordena mediante burbujeo a los jugadores
void order_ranking(Player ranking[], int num_players) {
    for (int i = 0; i < num_players - 1; i++) {
        for (int j = 0; j < num_players - i - 1; j++) {
            if (ranking[j].points < ranking[j + 1].points) {
                Player temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }
}

// Función para mostrar el ranking
// Función para mostrar el ranking
void show_ranking(Player ranking[], int index, int num_players) {
    if (index >= num_players) {
        printf("=====================================================================\n");
        return; // Caso base
    }

    if (index == 0) {
        printf("=====================================================================\n");
        printf("Ⅱ                        Ranking de Jugadores                       Ⅱ\n");
        printf("=====================================================================\n");
        printf("Ⅱ Posición           | Nombre                  | Puntos             Ⅱ\n");
        printf("---------------------------------------------------------------------\n");
    }

    // Mostrar un jugador
    printf("Ⅱ N°%8d         | %-15s         | %6d             Ⅱ\n", index + 1, ranking[index].name, ranking[index].points);

    // Llamada recursiva
    show_ranking(ranking, index + 1, num_players);
}
