INCLUDE := -I. \
		   -I../Tree/BinTree \
		   -I../Tree/Tree \
		   -I../List/List \
		   -I../Stack \
		   -I../Queue/Queue

DEPEND := main.cpp	graph.h		graph.cpp \
		  ../Tree/BinTree/bintree.h		../Tree/BinTree/bintree.cpp \
		  ../Tree/Tree/tree.h			../Tree/Tree/tree.cpp \
		  ../List/List/list.h			../List/List/list.cpp \
		  ../Stack/stack.h				../Stack/stack.cpp \
		  ../Queue/Queue/queue.h		../Queue/Queue/queue.cpp

all: main
main: $(DEPEND)
	g++ -std=c++11 -g $(INCLUDE) main.cpp -o main

clean:
	del main.exe

run: main
	main

gdb: main
	gdb -q main.exe