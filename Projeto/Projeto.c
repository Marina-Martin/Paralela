#include <stdio.h>
#include <omp.h>

double fatorial(int n) {
    double resultado = 1.0;
    for (int i = 1; i <= n; i++) {
        resultado *= i;
    }
    return resultado;
}

int main() {
    int N = 1000000; // Número de termos da série de Taylor
    double soma = 0.0;

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        double soma_local = 0.0;

        #pragma omp for schedule(static)
        for (int i = 0; i < N; i++) {
            soma_local += 1.0 / fatorial(i);
        }

        #pragma omp critical
        {
            soma += soma_local;
        }
    }

    printf("A soma da série de Taylor com %d termos é: %.10f\n", N, soma);

    return 0;
}
