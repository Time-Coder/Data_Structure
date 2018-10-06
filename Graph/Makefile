INCLUDE := -I. -I../List

all: main
main: graph.cpp graph.h ../List/list.h
	g++ -std=c++11 -g $(INCLUDE) main.cpp -o main

clean:
	del main.exe

run: main
	main

gdb: main
	gdb -q main.exe