all: execute_b_tree

execute_b_tree: b_tree
	./FKGA.exe entrada2.txt minha_saida2.txt

b_tree: b_tree.o
	gcc -o FKGA.exe d-FernandoKarchiloffGouveiaDeAmorim_Original.o

b_tree.o: d-FernandoKarchiloffGouveiaDeAmorim_Original.c
	gcc -c d-FernandoKarchiloffGouveiaDeAmorim_Original.c

clean: 
	rm *.o b_tree