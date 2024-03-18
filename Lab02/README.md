
## Comandos

cat /proc/cpuinfo → mostra informações, incluindo o processador

time ./nomeDOExe → roda o programa e passa o tempo de execução

taskset -c 0,1,2(enumeraçãoDosProcessadores) ./nomeDoExe → seta um número especifico de processadores para ser utilizado

## 1. Qual o tempo de execução serial e paralelo para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico contendo todos os tempos de execução
<img width="663" alt="Untitled" src="https://github.com/Marina-Martin/Paralela/assets/47898516/f6e797ba-9373-4884-9f39-a4e51e065a97">

### 1 Processador

processador AWS: Intel(R) Xeon(R) CPU E5-2676 v3 @ 2.40GHz

tempo de processamento real: 0.030 segundos

### 2 Processadores

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
```

Processador: Apple M1

tempo de processamento total: 0,006 seg

### 3 Processadores

Processador: Apple M1

tempo de processamento total: 0,005 seg

### 4 Processadores

Processador: Apple M1

tempo de processamento total: 0,005 seg

![Grafico](https://github.com/Marina-Martin/Paralela/assets/47898516/9c1bfa97-9fea-4026-8fb6-2fb23cc9387f)

## 3. Como você acha que poderia melhorar o seu algoritmo para obter maior benefício com o paralelismo? Para provar seu ponto, refaça a solução com essa abordagem e construa um novo gráfico de speedup para 1, 2, 4, 6 e 8 processadores.

Durante o desenvolvimento eu tive que mudar emu código e o fiz, dividindo as linhas da matriz com o número de threads disponíveis para o processo. O outro código não tinha mudanças para cada número de processadores.
