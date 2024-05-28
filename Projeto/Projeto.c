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
    int N = 100000; // Número de termos da série de Taylor
    double soma = 0.0;

    #pragma omp parallel for reduction(+:soma)
    for (int i = 0; i < N; i++) {
        soma += 1.0 / fatorial(i);
    }

    printf("A soma da série de Taylor com %d termos é: %.10f\n", N, soma);

    return 0;
}
