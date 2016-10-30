CC = g++
CCFLAGS = -Wall -Werror
debug: CCFLAGS += -g
debug: all
all:main Shell
	$(CC) $(CCFLAGS) main.o Shell.o -o ./bin/rshell
main:
	$(CC) $(CCFLAGS) -c ./src/main.cpp
Shell:
	$(CC) $(CCFLAGS) -c ./src/Shell.cpp
clean:
	rm *.o ./src/
