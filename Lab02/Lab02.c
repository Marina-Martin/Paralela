#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MATRIX_SIZE 1000
#define NUM_THREADS 4

int matrix[MATRIX_SIZE][MATRIX_SIZE];
int vector[MATRIX_SIZE];
int result[MATRIX_SIZE];

struct ThreadArgs {
    int thread_id;
};

void *MatrixVectorMultiply(void *args) {
    struct ThreadArgs *my_args = (struct ThreadArgs *) args;
    int start_row = my_args->thread_id * (MATRIX_SIZE / NUM_THREADS);
    int end_row = (my_args->thread_id + 1) * (MATRIX_SIZE / NUM_THREADS);

    for (int i = start_row; i < end_row; ++i) {
        result[i] = 0;
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    struct ThreadArgs thread_args[NUM_THREADS];

    // Inicialização da matriz e do vetor
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            matrix[i][j] = rand() % 10; // valores aleatórios de 0 a 9
        }
        vector[i] = rand() % 10;
    }

    // Criação das threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_args[i].thread_id = i;
        pthread_create(&threads[i], NULL, MatrixVectorMultiply, (void *) &thread_args[i]);
    }

    // Aguarda a conclusão das threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Impressão do resultado
    printf("Resultado:\n");
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}
