INCLUDE := -I.
DEPEND := main.cpp stack.h stack.cpp

all: main

main: $(DEPEND)
	g++ -Wall -std=c++11 $(INCLUDE) -g main.cpp -o main

run: main
	main

gdb: main
	gdb -q main.exe

clean:
	del main.exe