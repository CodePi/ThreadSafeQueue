all : testThreadSafeQueue testThreadSafeQueue2

CC=g++

testThreadSafeQueue : testThreadSafeQueue.cpp ../ThreadSafeQueue.h
	$(CC) testThreadSafeQueue.cpp -o testThreadSafeQueue -std=c++0x -pthread -D_GLIBCXX_USE_NANOSLEEP
testThreadSafeQueue2 : testThreadSafeQueue2.cpp ../ThreadSafeQueue.h
	$(CC) testThreadSafeQueue2.cpp -o testThreadSafeQueue2 -std=c++0x -pthread -D_GLIBCXX_USE_NANOSLEEP



clean:
	rm testThreadSafeQueue
