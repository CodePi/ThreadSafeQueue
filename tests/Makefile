CC=g++
FLAGS=-std=c++0x -pthread -D_GLIBCXX_USE_NANOSLEEP
TARGETS=testThreadSafeQueue testThreadSafeQueue2 testThreadSafeStack test_move

all : $(TARGETS)

% : %.cpp ../ThreadSafeQueue.h
	$(CC) $< -o $@ $(FLAGS)

clean:
	rm -f $(TARGETS)
