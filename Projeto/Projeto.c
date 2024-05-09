#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

void Taylor(int n, double* global_result_p);

int main(int argc, char* argv[]){
    double global_result = 0.0;
    int n;
    int thread_count;
    
    thread_count = strtol(argv[1], NULL, 10);
    printf("Enter n\n");
    scanf("%d", &n);
    #pragma omp parallel num_threads(thread_count)
    Trap(a, b, n, &global_result);
    
    printf("With n = %d\n", n);
    printf("our estimate for S is: %e\n", global_result);
    return 0;
}

void Fat(int n){
    fat[n] = 0;
    
    fat[0] = 0;
    if(n => 1){
        fat[1] = 1;
    }
    if(n > 1){
        for(int i = 2; i < n; n++){
            fat[n] += fat[n-1]
        }
    }
}

void Taylor(int n, double* global_result_p){
    double my_result;
    int i, local_n;
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();
    
    for (i = 1; i <= local_n-1; i++){
        my_result += 1 / Fat(local_n);
    }
    
    #pragma omp critical
    *global_result_p += my_result;

}
