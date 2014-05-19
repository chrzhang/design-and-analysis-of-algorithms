CC = gcc
FLAGS = -O -Wall -m32 -std=c99 -pedantic -Wextra
EXEC = p

all: $(EXEC)

$(EXEC): heap.o graph.o main.o
	$(CC) $(FLAGS) -o $(EXEC) heap.o graph.o main.o

main.o: main.c
	$(CC) $(FLAGS) -c main.c

heap.o: heap.c
	$(CC) $(FLAGS) -c heap.c

graph.o: graph.c
	$(CC) $(FLAGS) -c graph.c

clean:
	rm -f *.o $(EXEC) *~

