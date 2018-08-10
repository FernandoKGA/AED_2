all: dijkstra

dijkstra:  dijkstra.o grafo_listaadj.o heap_binario.o grafo_listaadj.h heap_binario.h
	gcc -o dijkstra grafo_listaadj.o heap_binario.o dijkstra.o

dijkstra.o: dijkstra.c
	gcc -c dijkstra.c

grafo_listaadj.o: grafo_listaadj.c grafo_listaadj.h
	gcc -c grafo_listaadj.c

heap_binario.o: heap_binario.c heap_binario.h
	gcc -c heap_binario.c


clean:
	rm *.o dijkstra