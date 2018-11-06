INCLUDE := -I. \
		   -I../../List/List \
		   -I../../Queue/Queue \
		   -I../../Stack \
		   -I../BinTree

all: main

main: $(DEPEND)
	g++ -std=c++11 $(INCLUDE) -g main.cpp -o main

run: main
	main.exe

gdb: main
	gdb -q --interpreter=mi --args main.exe