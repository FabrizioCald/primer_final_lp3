/*factorial.c*/
/*
	Nombre y Apellido: Fabrizio Calderoli
	Primer examen final de LP3
	Tema 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void *funcion_hilo(void *dato);
unsigned long long calcular_factorial(int n);
//--------------------------------------------------------

void *funcion_hilo(void *dato){
	int valor = *((int*)dato);
	unsigned long long resultado;

	resultado = calcular_factorial(valor);

	printf("Factorial de %d: %llu\n", valor, resultado);
	return NULL;
}

// Función para calcular el factorial de un número
unsigned long long calcular_factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    unsigned long long fact = 1;
    for (unsigned long long i = 2; i <= n; ++i)
        fact *= i;
    return fact;
}

//--------------------------------------------------------

int main(int argc, char *argv[])
{
	//---------------------------------------------------------
	pthread_t hilo;
	char *input_list = argv[1];
	int arr[100];
    int n = 0;
    int datos = 0;

    char *token = strtok(input_list, ",");
    while (token != NULL) {
        arr[n] = atoi(token);
        n++;
        token = strtok(NULL, ",");
    }

    int arreglo_de_n[n];
	for (int i = 0; i < n; ++i)
	{
		arreglo_de_n[i] = arr[i];//Para tener un arreglo de n elementos
	}
	//---------------------------------------------------------
	printf("\n");
	printf("Salida\n");
	for (int j = 0; j < n; ++j)
	{
		datos = arreglo_de_n[j];
		pthread_create(&hilo, NULL, funcion_hilo, &datos);
		pthread_join(hilo, NULL);
	}

	//---------------------------------------------------------

	return 0;
}