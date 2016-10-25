CC = g++

all:main Shell
	$(CC) main.o Shell.o -o ./bin/rshell
main:
	$(CC) -c ./src/main.cpp
Shell:
	$(CC) -c ./src/Shell.cpp
clean:
	rm *.o ./src/

