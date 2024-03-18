
### Comandos

cat /proc/cpuinfo → mostra informações, incluindo o processador

time ./nomeDOExe → roda o programa e passa o tempo de execução

taskset -c 0,1,2(enumeraçãoDosProcessadores) ./nomeDoExe → seta um número especifico de processadores para ser utilizado

## 1. Qual o tempo de execução serial e paralelo para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico contendo todos os tempos de execução
![Result](https://prod-files-secure.s3.us-west-2.amazonaws.com/ae478dc5-da13-4a90-b2fe-e60944889681/791f568a-26f0-4477-af66-bd90b7918d1f/Untitled.png)

# 1 Processador

processador AWS: Intel(R) Xeon(R) CPU E5-2676 v3 @ 2.40GHz

tempo de processamento real: 0.030 segundos

# 2 Processadores

fiz testes com taskset, mas ele não parece funcionar dentro do MacOs. 

recriei o código a partir do helloWorld de threads do pdf.
```
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count;

void *Hello(void* rank);

void *Hello(void* rank){
		long my_rank = (long) rank;
		
		printf("Hello from thread %ld of %d", my_rank, thread_count);
		
		return NULL;
}

int main(int argc, char* argv[]){
	long thread;
	pthread_t* thread_handles;

	thread_count = strtol(argv[1], NULL, 10);
	thread_handles = malloc(thread_count * sizeof(pthread_t));
	
	for(thread = 0; thread < thread_count; thread++){
		pthread_create(thread_handles[thread], NULL, Hello, (void*) thread);
	}
	
	printf("Hello from main\n");
	
	for(thread = 0; thread < thread_count; thread++){
		pthread_join(thread_handles[thread], NULL);
	}
	
	free(thread_handles);
	
	return 0;
}
```

aqui o código recriado
```
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
	
	//for pra dividir as linhas entre as threads disponíveis

	thread_count = strtol(argv[1], NULL, 10);
	thread_handles = malloc(thread_count * sizeof(pthread_t));
	
	//esse código supostamente vai divir as linhas da matriz entre as threads	
	while(num >= 0){
	    if(i > 3){
	        i = 0;
	    }
	    vet[num] += 1;
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
```
