QueuePath := ..
QueueHead1 := queue.h
QueueHead2 := deque.h

MainSource1 := example_queue.cpp
MainObject1 := example_queue.o
MainExe1 := example_queue

MainSource2 := example_deque.cpp
MainObject2 := example_deque.o
MainExe2 := example_deque

INCLUDE := -I${QueuePath}

all: ${MainExe1} ${MainExe2}

${MainExe1}: ${MainObject1}
	g++ -std=gnu++11 ${MainObject1} -o ${MainExe1}

${MainExe2}: ${MainObject2}
	g++ -std=gnu++11 ${MainObject2} -o ${MainExe2}

${MainObject1}: ${MainSource1} ${QueuePath}/${QueueHead1}
	g++ -std=gnu++11 ${INCLUDE} -c ${MainSource1}

${MainObject2}: ${MainSource2} ${QueuePath}/${QueueHead2}
	g++ -std=gnu++11 ${INCLUDE} -c ${MainSource2}
 
clean:
	rm *.o