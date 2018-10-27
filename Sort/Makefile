DEPEND := sort.h sort.cpp \
		  ../Vector/vector.h ../Vector/vector.cpp \
		  ../List/List/list.h ../List/List/list.cpp \
		  ../Heap/Heap/heap.h ../Heap/Heap/heap.cpp \
		  main.cpp

INCLUDE := -I. -I../Vector -I../List/List -I../Heap/Heap

all: main

main: $(DEPEND)
	g++ -std=c++11 main.cpp $(INCLUDE) -g -o main

clean:
	del main.exe

run: main
	.\\main.exe

gdb: main
	gdb -q --interpreter=mi --args main.exe