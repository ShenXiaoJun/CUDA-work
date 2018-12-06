UNAME_S := $(shell uname)

CC = gcc

all: main.exe

main.exe: main.o
	$(CC) $^ -o $@
	
main.o: main.cpp
	$(CC) -c $< -o $@
	
clean:
	rm -f *.o *.exe