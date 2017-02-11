all : testThreadSafeQueue testThreadSafeQueue2

testThreadSafeQueue : testThreadSafeQueue.cpp ../ThreadSafeQueue.h
	g++ testThreadSafeQueue.cpp -o testThreadSafeQueue -std=c++0x -pthread -D_GLIBCXX_USE_NANOSLEEP
testThreadSafeQueue2 : testThreadSafeQueue2.cpp ../ThreadSafeQueue.h
	g++ testThreadSafeQueue2.cpp -o testThreadSafeQueue2 -std=c++0x -pthread -D_GLIBCXX_USE_NANOSLEEP



clean:
	rm testThreadSafeQueue
