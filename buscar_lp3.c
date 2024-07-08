/*buscar_lp3.c*/
/*
	Nombre y Apellido: Fabrizio Calderoli
	Primer examen final de LP3
	Tema 2
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX 20  // Tamaño máximo del vector

int vector[MAX];  // Vector de números aleatorios
int buscado;  // Número a buscar en el vector
int encontrado = 0;  // Variable para indicar si se encontró el número
pthread_mutex_t lock;  // Mutex para sincronización

// Estructura para los argumentos de cada hilo
typedef struct {
    int thread_id;
    int start_index;
    int end_index;
} ThreadArgs;

// Función que realiza la búsqueda en un fragmento del vector
void *buscar_numero(void *args) {
    ThreadArgs *my_args = (ThreadArgs *)args;
    int thread_id = my_args->thread_id;
    int start = my_args->start_index;
    int end = my_args->end_index;
    
    for (int i = start; i <= end; ++i) {
        if (vector[i] == buscado && encontrado != 1) {
            pthread_mutex_lock(&lock);
            encontrado = 1;
            printf("El número %d ha sido encontrado en la posición de indice [%d] por el hilo %d.\n", buscado, i, thread_id);
            pthread_mutex_unlock(&lock);
            pthread_exit(NULL);
        }
    }
    
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <número_a_buscar> <número_de_hilos>\n", argv[0]);
        return 1;
    }

    buscado = atoi(argv[1]);  // Convertir primer argumento a entero
    int num_threads = atoi(argv[2]);  // Convertir segundo argumento a entero

    if (num_threads > MAX || num_threads <= 0) {
        fprintf(stderr, "Número de hilos debe estar entre 1 y %d.\n", MAX);
        return 1;
    }

    // Inicializar el vector con números aleatorios entre 0 y 9
    printf("Vector generado:\n");
    for (int a = 0; a < MAX; ++a)
    {
    	printf("[%d]", a);
    }
    printf("\n");
    printf("----------------------------------------------------------------------");
    printf("\n");

    srand(time(NULL));
    
    for (int i = 0; i < MAX; ++i) {
        vector[i] = rand() % 10;
        if (i <= 9)
        {
        	printf(" %d ", vector[i]);
        }else{
        	printf(" %d  ", vector[i]);
        }
    }
    printf("\n");
    printf("----------------------------------------------------------------------");
    printf("\n");

    pthread_t threads[num_threads];
    ThreadArgs thread_args[num_threads];
    int elems_por_thread = MAX / num_threads;

    pthread_mutex_init(&lock, NULL);

    // Crear y ejecutar los hilos
    for (int i = 0; i < num_threads; ++i) {
        thread_args[i].thread_id = i + 1;
        thread_args[i].start_index = i * elems_por_thread;
        thread_args[i].end_index = (i == num_threads - 1) ? MAX - 1 : (i + 1) * elems_por_thread - 1;
        
        pthread_create(&threads[i], NULL, buscar_numero, (void *)&thread_args[i]);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Si no se encontró el número, mostrar mensaje
    if (!encontrado) {
        printf("El número %d no está presente en el vector.\n", buscado);
    }

    pthread_mutex_destroy(&lock);
    return 0;
}