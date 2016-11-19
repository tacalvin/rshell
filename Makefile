
CC = g++
CCFLAGS = -Werror -ansi -Wall -pedantic
debug: CCFLAGS += -ggdb
debug: all
all:main Shell Command And Operator Semi Or
	mkdir -p bin
	$(CC) $(CCFLAGS) main.o Shell.o Command.o AndOperator.o Operator.o SemiOperator.o OrOperator.o -o ./bin/rshell
main:
	$(CC) $(CCFLAGS) -c ./src/main.cpp
Shell:
	$(CC) $(CCFLAGS) -c ./src/Shell.cpp
Command:
	$(CC) $(CCFLAGS) -c ./src/Command.cpp
And:
	$(CC) $(CCFLAGS) -c ./src/AndOperator.cpp
Operator:
	$(CC) $(CCFLAGS) -c ./src/Operator.cpp
Semi:
	$(CC) $(CCFLAGS) -c ./src/SemiOperator.cpp
Or:
	$(CC) $(CCFLAGS) -c ./src/OrOperator.cpp
clean:
	rm -r *.o
