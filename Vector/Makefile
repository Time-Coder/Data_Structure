INCLUDE := -I.
DEPEND := main.cpp vector.h vector.cpp

all: main

main.exe: $(DEPEND)
	g++ -Wall -std=c++11 $(INCLUDE) main.cpp -o main

run: main.exe
	main

clean:
	del main.exe
