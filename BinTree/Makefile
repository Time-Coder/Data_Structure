INCLUDE := -I../Stack -I../Queue
DEPEND := ../Stack/stack.h ../Queue/queue.h

all: main

main: $(DEPEND)
	g++ -std=c++11 $(INCLUDE) main.cpp -o main

run: main
	main

clean:
	del main.exe