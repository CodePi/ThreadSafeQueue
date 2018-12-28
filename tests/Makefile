all : testThreadSafeQueue testThreadSafeQueue2 testThreadSafeStack

CC=g++
FLAGS=-std=c++0x -pthread -D_GLIBCXX_USE_NANOSLEEP

testThreadSafeQueue : testThreadSafeQueue.cpp ../ThreadSafeQueue.h
	$(CC) $< -o $@ $(FLAGS)

testThreadSafeQueue2 : testThreadSafeQueue2.cpp ../ThreadSafeQueue.h
	$(CC) $< -o $@ $(FLAGS)

testThreadSafeStack : testThreadSafeStack.cpp ../ThreadSafeQueue.h
	$(CC) $< -o $@ $(FLAGS)

clean:
	rm -f testThreadSafeQueue testThreadSafeQueue2 testThreadSafeStack
