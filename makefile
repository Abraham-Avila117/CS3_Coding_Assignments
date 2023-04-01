all: bfs

bfs: main.o 
	clang++ main.o -o bfs

main.o: main.cpp
	clang++ -c main.cpp

run:
	./bfs paths.txt

clean: 
	rm -f *.o

pclean:
	rm -f bfs