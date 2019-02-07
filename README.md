
# Simulacion del problema de la cena de los filosofos


Ultima modificacion: 12.04.2018




Propuesto en el Stallings - Operating Systems. Capitulo 6
(Originalmente descrito por Dijkstra)

Hay cinco filosofos en una casa donde han aprendido
que lo unico que necesitan es comer o pensar. Nunca ambas a la vez.
Su comida favorita es el espagueti, pero no son buenos con
las manos, asi cada uno debe usar dos tenedores para comer.

Su austeridad les ha demostrado que pueden compartir
cubiertos (y saliva).

Los filosofos se sientan en una mesa redonda con un
tenedor entre cada uno y sus platos al frente.

Se pide un algoritmo para que ningun filosofo se quede sin 
comer y que no deba usar un cubierto ocupado 
(evitar deadlock y "starvation").


Solucion 1: Usar semaforos
			Hay riesgo de deadlock

Solucion 2: Usar un monitor
			
