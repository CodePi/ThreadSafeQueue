FLAGS=-std=c++11 -pthread
TARGETS := testThreadSafeQueue testThreadSafeQueue2 testThreadSafeStack test_move

all : $(TARGETS)

% : %.cpp ../ThreadSafeQueue.h
	$(CXX) $< -o $@ $(FLAGS)

clean:
	rm -f $(TARGETS)
