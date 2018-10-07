INCLUDE := -I.
DEPEND := main.cpp dbllist.h dbllist.cpp

all: main

main: $(DEPEND)
	g++ -Wall -std=c++11 -g $(INCLUDE) main.cpp -o main

run: main
	main

gdb: main
	gdb -q main.exe

clean:
	del main.exe