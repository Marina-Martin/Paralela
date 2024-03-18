#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count;
int vet[4] = {0, 0, 0, 0};

int M[4][4] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
int R[4][4], iterador = 0;
int V[4] = {1, 2, 3, 4};

void *Mult(void* rank){
		long my_rank = (long) rank;
		
		for(int cont = iterador; cont < vet[my_rank]; cont++){
		    for(int i2 = 0; i2 < 4; i2++){
		        R[iterador][i2] = M[iterador][i2] * V[i2];
		    }
		    iterador = cont;
		}
		printf("Hello from thread %ld of %d\n", my_rank, thread_count);
		
		return NULL;
}
//saber o numero de linhas
//dividir as linhas pelas threads
//for que multiplica o numero de linhas dividido

int main(int argc, char* argv[]){
	long thread;
	pthread_t* thread_handles;
	int i = 0;
	
	//for pra dividir as linhas entre as threads disponíveis

	thread_count = strtol(argv[1], NULL, 10);
	thread_handles = malloc(thread_count * sizeof(pthread_t));
	
	//esse código vai divir as linhas da matriz entre as threads	
	for(int num = 0; num < 4;){
	    if(i == thread_count){
	        i = 0;
	    }
	    vet[i] += 1;
	    i += 1;
	    num += 1;
	}
	
	for(int it = 0; it < 4; it++){
	    printf("%i", vet[it]);
	}printf("\n");
	
	for(thread = 0; thread < thread_count; thread++){
		pthread_create(&thread_handles[thread], NULL, Mult, (void*) thread);
	}
	
	printf("Hello from main\n");
	
	for(thread = 0; thread < thread_count; thread++){
		pthread_join(thread_handles[thread], NULL);
	}
	
	free(thread_handles);
	
	for(int i = 0; i < 4; i++){
	    for(int i2 = 0; i2 < 4; i2++){
	        printf("%i", M[i][i2]);
	    }
	}
	
	return 0;
}
