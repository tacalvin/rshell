CC = g++
CCFLAGS = -Wall  -std=c++11
debug: CCFLAGS += -g
debug: all
all:main Shell Command
	mkdir -p bin
	$(CC) $(CCFLAGS) main.o Shell.o Command.o -o ./bin/rshell
main:
	$(CC) $(CCFLAGS) -c ./src/main.cpp
Shell:
	$(CC) $(CCFLAGS) -c ./src/Shell.cpp
Command:
	$(CC) $(CCFLAGS) -c ./src/Command.cpp
clean:
	rm -r *.o
