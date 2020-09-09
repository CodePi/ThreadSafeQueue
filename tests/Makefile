CC=g++
FLAGS=-std=c++11 -pthread
TARGETS := testThreadSafeQueue testThreadSafeQueue2 testThreadSafeStack test_move

all : $(TARGETS)

% : %.cpp ../ThreadSafeQueue.h
	$(CC) $< -o $@ $(FLAGS)

clean:
	rm -f $(TARGETS)
