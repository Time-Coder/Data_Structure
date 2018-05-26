HeadPath := ..
Head := circlist.h

MainSource := example.cpp
MainHead := example.h
MainObject := example.o
MainExe := example

INCLUDE := -I${HeadPath}

${MainExe}: ${MainObject}
	g++ *.o -o ${MainExe}

${MainObject}: ${MainSource} ${HeadPath}/${Head}
	g++ ${INCLUDE} -c ${MainSource}
 
clean:
	rm *.o