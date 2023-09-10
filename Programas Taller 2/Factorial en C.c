#include <stdio.h>

// Función recursiva para calcular el factorial
unsigned long long factorial(int n) {

    if (n == 0 || n == 1) {
        return 1;
        
    } else {
        return n * factorial(n - 1);
    }
}

int main() {

    int num;
    printf("Ingrese un numero entero positivo: ");
    scanf("%d", &num);

    if (num < 0) {
        printf("El factorial no está definido para numeros negativos.\n");
    } else {
        unsigned long long resultado = factorial(num);
        printf("El factorial de %d es %llu\n", num, resultado);
    }

    return 0;
}
