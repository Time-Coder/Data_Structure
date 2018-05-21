StackPath := ..
StackHead := stack.h

MainSource := example.cpp
MainHead := example.h
MainObject := example.o
MainExe := example

INCLUDE := -I${StackPath}

${MainExe}: ${MainObject}
	g++ *.o -o ${MainExe}

${MainObject}: ${MainSource} ${StackPath}/${StackHead}
	g++ ${INCLUDE} -c ${MainSource}
 
clean:
	rm *.o