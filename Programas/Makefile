testa_lista_bp: busca_em_profundidade_lista.o testa_grafo_lista_bp.o
	gcc -o testa_lista_bp.exe testa_grafo_lista_bp.o

testa_grafo_lista_bp.o: testa_grafo_lista_bp.c busca_em_profundidade_lista.o
	gcc -c testa_grafo_lista_bp.c

busca_em_profundidade_lista.o: busca_em_profundidade/busca_em_prof_lista.c busca_em_profundidade/grafo_listaadj.h
	gcc -c busca_em_profundidade/busca_em_prof_lista.c

testa_lista: grafo_listaadj.o testa_grafo_lista.o
	gcc -o testa_grafo_lista.exe grafo_listaadj.o testa_grafo_lista.o

grafo_listaadj.o: lista_adjacencia/grafo_listaadj.c lista_adjacencia/grafo_listaadj.h
	gcc -c grafo_listaadj.c

testa_lista.o: testa_grafo_lista.c lista_adacencia/grafo_listaadj.h
	gcc -c testa_grafo_lista.c

testa_matriz: grafo_matrizadj.o testa_grafo.o
	gcc -o testa_grafo_matriz.exe grafo_matrizadj.o testa_grafo_matriz.o

grafo_matrizadj.o: matriz_adjacencia/grafo_matrizadj.c matriz_adjacencia/grafo_matrizadj.h
	gcc -c matriz_adjacencia/grafo_matrizadj.c

testa_grafo_matriz.o: testa_grafo_matriz.c matriz_adjacencia/grafo_matrizadj.h
	gcc -c testa_grafo_matriz.c

testa_matriz_incomp: grafo_matrizadj_incomp.o testa_grafo_incomp.o
	gcc -o testa_grafo_matriz_incomp.exe grafo_matrizadj_incomp.o testa_grafo_incomp.o

grafo_matrizadj_incomp.o: matriz_adjacencia/grafo_matrizadj_incomp.c matriz_adjacencia/grafo_matrizadj_incomp.h
	gcc -c matriz_adjacencia/grafo_matrizadj_incomp.c

testa_grafo_incomp.o: testa_grafo_incomp.c matriz_adjacencia/grafo_matrizadj_incomp.h
	gcc -c testa_grafo_incomp.c

clean:
	rm -f *.o *.exe
