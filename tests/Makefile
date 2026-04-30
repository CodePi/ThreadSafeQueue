FLAGS=-std=c++11 -pthread -O3
TARGETS := testThreadSafeQueue testThreadSafeQueue2 testThreadSafeQueue3 testThreadSafeStack test_move

all : $(TARGETS)

% : %.cpp ../ThreadSafeQueue.h
	$(CXX) $< -o $@ $(FLAGS)

clean:
	rm -f $(TARGETS)
