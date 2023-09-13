# Función recursiva para calcular el factorial
def factorial(n):

    if n == 0 or n == 1:
        return 1
    else:
        return n * factorial(n - 1)

# Se le pide al usuario que ingrese un número positivo
num = int(input("Ingrese un número entero positivo: "))

# Verifica si el número es negativo
if num < 0:
    print("El factorial no está definido para números negativos.")

# Llama a la función y brinda el resultado
else:
    resultado = factorial(num)
    print(f"El factorial de {num} es {resultado}")

# Se introduce una pausa de 5 segundos para lograr ver el rendimiento
time.sleep(5)
