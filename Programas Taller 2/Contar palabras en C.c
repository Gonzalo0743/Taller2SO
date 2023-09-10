#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 1000  // Longitud máxima de una línea en el archivo

int main() {
    char filename[] = "C:\\Users\\Chalo\\Desktop\\Programas Taller 2\\texto.txt"; //Cambiar según el directorio específico
    char palabra[] = "hola";  // Palabra a contar

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }

    char line[MAX_LEN];
    int count = 0;
    clock_t start_time, end_time;
    double cpu_time_used;

    start_time = clock();

    while (fgets(line, sizeof(line), file) != NULL) {
        // Buscar la palabra en cada línea del archivo
        char *token = strtok(line, " \t\n");  // Dividir la línea en palabras
        while (token != NULL) {
            if (strcmp(token, palabra) == 0) {
                count++;
            }
            token = strtok(NULL, " \t\n");
        }
    }

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("La palabra '%s' aparece %d veces en el archivo.\n", palabra, count);
    printf("Tiempo de ejecución: %f segundos\n", cpu_time_used);

    fclose(file);
    return 0;
}
