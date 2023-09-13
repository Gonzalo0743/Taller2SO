#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>

#define MAX_LINE_LEN 1000

// Estructura para pasar argumentos a los hilos
struct ThreadArgs {
    char *filename;
    char *target_word;
    int *count;
};

// Función que realiza la búsqueda de la palabra en el archivo
void *searchWord(void *args) {
    struct ThreadArgs *threadArgs = (struct ThreadArgs *)args;
    FILE *file = fopen(threadArgs->filename, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LEN];
    char *lowercase_target = strdup(threadArgs->target_word);
    for (int i = 0; lowercase_target[i]; i++) {
        lowercase_target[i] = tolower(lowercase_target[i]);
    }

    int count = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        // Buscar la palabra en esta línea
        char *word = strtok(line, " \t\n");
        while (word != NULL) {
            // Convertir cada palabra a minúsculas antes de comparar
            char *lowercase_word = strdup(word);
            for (int i = 0; lowercase_word[i]; i++) {
                lowercase_word[i] = tolower(lowercase_word[i]);
            }

            if (strcmp(lowercase_word, lowercase_target) == 0) {
                count++;
            }

            free(lowercase_word);
            word = strtok(NULL, " \t\n");
        }
    }

    fclose(file);
    free(lowercase_target);
    *(threadArgs->count) = count;
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <archivo.txt> <palabra> <num_hilos>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *filename = argv[1];
    char *target_word = argv[2];
    int num_threads = atoi(argv[3]);

    pthread_t threads[num_threads];
    struct ThreadArgs threadArgs[num_threads];
    int counts[num_threads];
    int total_count = 0;

    for (int i = 0; i < num_threads; i++) {
        counts[i] = 0;
        threadArgs[i].filename = filename;
        threadArgs[i].target_word = target_word;
        threadArgs[i].count = &counts[i];
        pthread_create(&threads[i], NULL, searchWord, &threadArgs[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        total_count += counts[i];
    }

    printf("La palabra '%s' aparece %d veces en el archivo.\n", target_word, total_count);

    return 0;
}