COMPILER = g++
FLAGS = -std=c++0x -Wall -g -Ofast
OUTNAME = BestFirstSearch

#all: run

#run: $(OUTNAME)
#	./$(OUTNAME) in/a.txt out/a.txt

all: $(OUTNAME)

$(OUTNAME): Knapsack.o Driver.o
	$(COMPILER) $(FLAGS) -o $(OUTNAME) Knapsack.o Driver.o

Knapsack.o: Knapsack.cpp
	$(COMPILER) $(FLAGS) -c Knapsack.cpp

Driver.o: Driver.cpp
	$(COMPILER) $(FLAGS) -c Driver.cpp

clean:
	rm -rf *.o $(OUTNAME) 
