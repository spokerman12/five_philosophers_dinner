/* 
 * Universidad Simon Bolivar
 * Departamento de Computación y Tecnologı́a de la Información
 * Sistemas de Operacion I - CI3825
 * Trimestre Enero-Marzo 2018
 *
 * Simulacion del problema de la cena de los filosofos
 * 
 * 
 * Ultima modificacion: 12.04.2018
 *
 * @Autor: Daniel Francis. 12-10863
 *
 *
 * Propuesto en el Stallings - Operating Systems. Capitulo 6
 * (Originalmente descrito por Dijkstra)
 *
 *  Hay cinco filosofos en una casa donde han aprendido
 *	que lo unico que necesitan es comer o pensar. Nunca ambas a la vez.
 *	Su comida favorita es el espagueti, pero no son buenos con
 *	las manos, asi cada uno debe usar dos tenedores para comer.
 * 
 *	Su austeridad les ha demostrado que pueden compartir
 *	cubiertos (y saliva).
 *
 *	Los filosofos se sientan en una mesa redonda con un
 *	tenedor entre cada uno y sus platos al frente.
 *
 *	Se pide un algoritmo para que ningun filosofo se quede sin 
 *	comer y que no deba usar un cubierto ocupado 
 *  (evitar deadlock y "starvation").
 *
 */

/*
 *	Solucion 1: Usar semaforos
 *				Hay riesgo de deadlock
 *
 *	Solucion 2: Usar un monitor
 *				
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdbool.h>


typedef struct
{
	int num;

} thread_struct;

sem_t tenedores[5];
sem_t monitor;


void * filosofo1();
void * filosofo2();

void * filosofo1(void * args)
{
	thread_struct threadS = *(thread_struct *)args;
	int i = threadS.num;
	int q = i+1;
	printf("El filosofo %d se sienta\n", q);
	sleep(3);

	printf("El filosofo %d piensa...\n", q);
	srand(time(NULL));
	int k = rand() % 10;
	sleep(k);

	printf("Ya penso el filosofo %d!\n", q);
	sem_wait(&tenedores[i]);
	sem_wait(&tenedores[(i+1)%5]);

	printf("El filosofo %d come...\n", q);
	sleep(k);
	printf("Comio el filosofo %d \n", q);
	sem_post(&tenedores[(i+1)%5]);
	sem_post(&tenedores[i]);

}

void * filosofo2(void * args)
{
	thread_struct threadS = *(thread_struct *)args;
	int i = threadS.num;
	int q = i+1;
	printf("El filosofo %d se sienta\n", q);
	sleep(3);

	printf("El filosofo %d piensa...\n", q);
	srand(time(NULL));
	int k = rand() % 10;
	sleep(k);

	printf("Ya penso el filosofo %d!\n", q);
	sem_wait(&monitor);
	sem_wait(&tenedores[i]);
	sem_wait(&tenedores[(i+1)%5]);

	
	printf("El filosofo %d come...\n", q);
	sleep(k);

	printf("Comio el filosofo %d \n", q);
	sem_post(&tenedores[(i+1)%5]);
	sem_post(&tenedores[i]);
	sem_post(&monitor);

}


int main()
{
	pthread_t thread[5];
	sem_init(&monitor,0,1);

	for (int j = 0; j < 5; j++)
	{
		sem_init(&tenedores[j],0,1);
	}

	int j = 0;
	while(j<5)
	{
		// Es problematico hacer que empiecen al mismo tiempo.
		// Cualquier mejora en este punto es apreciada
		pthread_create(&thread[j],NULL,filosofo1,(void*)&j);

		// Segunda solucion
		//pthread_create(&thread[j],NULL,filosofo2,(void*)&j);
		sleep(1);
		j++;
	}

	sleep(60);

}





