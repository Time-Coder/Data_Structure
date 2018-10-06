INCLUDE := -I. -I../../List -I../../Stack

all: main

main: $(DEPEND)
	g++ -std=c++11 $(INCLUDE) -g main.cpp -o main

run: main
	main.exe

gdb: main
	gdb -q main.exe