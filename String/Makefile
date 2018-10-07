INCLUDE := -I.
DEPEND := main.cpp string.h string.cpp

all: main

main: $(DEPEND)
	g++ -Wall -std=c++11 $(INCLUDE) -g *.cpp -o main

run: main
	main

gdb: main
	gdb -q main.exe

clean:
	del main.exe