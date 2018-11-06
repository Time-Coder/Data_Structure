INCLUDE := -I. \
		   -I../../List/List \
		   -I../../Stack \
		   -I../../Queue/Queue \
		   -I../Tree

DEPEND := ../../List/List/list.h		../../List/List/list.cpp \
		  ../../Stack/stack.h			../../Stack/stack.cpp \
		  ../../Queue/Queue/queue.h		../../Queue/Queue/queue.cpp \
		  ../Tree/tree.h				../Tree/tree.cpp \
		  bintree.h						bintree.cpp

all: main

main: $(DEPEND)
	g++ -g -std=c++11 $(INCLUDE) main.cpp -o main

run: main
	main

clean:
	del main.exe

gdb:
	gdb -q main.exe