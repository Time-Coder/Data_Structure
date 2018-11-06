DEPEND := splay.h							splay.cpp \
		  ../bst.h							../bst.cpp \
		  ../../bintree.h					../../bintree.cpp \
		  ../../../Tree/tree.h				../../../Tree/tree.cpp \
		  ../../../../Stack/stack.h			../../../../Stack/stack.cpp \
		  ../../../../List/List/list.h		../../../../List/List/list.cpp \
		  ../../../../Queue/Queue/queue.h	../../../../Queue/Queue/queue.cpp \
		  main.cpp

INCLUDE := -I. 						\
		   -I.. 					\
		   -I../../					\
		   -I../../../Tree 			\
		   -I../../../../Stack 		\
		   -I../../../../List/List 	\
		   -I../../../../Queue/Queue

all: main

main: $(DEPEND)
	g++ -std=c++11 -g $(INCLUDE) main.cpp -o main

run: main
	main

clean:
	del main.exe

gdb: main
	gdb -q main.exe