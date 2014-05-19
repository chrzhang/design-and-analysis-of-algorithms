COMPILER = g++
FLAGS = -std=c++0x -Wall -pedantic-errors -g
EXECUTABLE1 = program1
EXECUTABLE2 = program2
EXECUTABLE3 = program3

all: $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3)

$(EXECUTABLE1): Program1Driver.o Program1.o
	$(COMPILER) $(FLAGS) -o $(EXECUTABLE1) Program1Driver.o Program1.o

Program1Driver.o: Program1Driver.cpp
	$(COMPILER) $(FLAGS) -c Program1Driver.cpp

Program1.o: Program1.cpp
	$(COMPILER) $(FLAGS) -c Program1.cpp

$(EXECUTABLE2): Program2Driver.o Program2.o
	$(COMPILER) $(FLAGS) -o $(EXECUTABLE2) Program2Driver.o Program2.o

Program2Driver.o: Program2Driver.cpp
	$(COMPILER) $(FLAGS) -c Program2Driver.cpp

Program2.o: Program2.cpp
	$(COMPILER) $(FLAGS) -c Program2.cpp

$(EXECUTABLE3): Program3Driver.o Program3.o
	$(COMPILER) $(FLAGS) -o $(EXECUTABLE3) Program3Driver.o Program3.o

Program3Driver.o: Program3Driver.cpp
	$(COMPILER) $(FLAGS) -c Program3Driver.cpp
    
Program3.o: Program3.cpp
	$(COMPILER) $(FLAGS) -c Program3.cpp 

clean:
	rm -rf *.o $(EXECUTABLE1) $(EXECUTABLE2) $(EXECUTABLE3)
