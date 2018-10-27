DEPEND := heap.h heap.cpp \
		  ../../Vector/vector.h ../../Vector/vector.cpp \
		  main.cpp

INCLUDE := -I. -I../../Vector

all: main

main: $(DEPEND)
	g++ -std=c++11 main.cpp $(INCLUDE) -g -o main

clean:
	del main.exe

run: main
	.\\main.exe

gdb: main
	gdb -q --interpreter=mi --args main.exe