CC = clang++
PROGRAM = bfs
CFLAGS = -c
CPPFILES = main.cpp
FILE = paths.txt

all: $(PROGRAM)

$(PROGRAM): main.o 
	$(CC) main.o -o $(PROGRAM)

main.o: $(CPPFILES)
	$(CC) $(CFLAGS) $(CPPFILES)

run: 
	./$(PROGRAM) $(FILE)

clean: 
	rm -f *.o

pclean:
	rm -f $(PROGRAM)
