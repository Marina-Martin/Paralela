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
int V[4] = {1, 2, 3, 4};

void *Mult(void* rank){
		long my_rank = (long) rank;
		
		printf("Hello from thread %ld of %d", my_rank, thread_count);
		
		return NULL;
}
//saber o numero de linhas
//dividir as linhas pelas threads
//for que multiplica o numero de linhas dividido

int main(int argc, char* argv[]){
	long thread;
	pthread_t* thread_handles;
	int num = 4, i = 0;
	
	thread_count = strtol(argv[1], NULL, 10);
	thread_handles = malloc(thread_count * sizeof(pthread_t));
	
	//esse código supostamente vai divir as linhas da matriz entre as threads	
	while(num >= 0){
	    if(i > 3){
	        i = 0;
	    }
	    vet[thread_count] += 1;
	    num -= 1;
	}
	
	for(int i = 0; i < 4; i++){
	    printf("%i", vet[i]);
	}
	
	for(thread = 0; thread < thread_count; thread++){
		pthread_create(&thread_handles[thread], NULL, Mult, (void*) thread);
	}
	
	printf("Hello from main\n");
	
	for(thread = 0; thread < thread_count; thread++){
		pthread_join(thread_handles[thread], NULL);
	}
	
	free(thread_handles);
	
	return 0;
}
