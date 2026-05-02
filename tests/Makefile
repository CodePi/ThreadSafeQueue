FLAGS=-std=c++17 -pthread
TARGETS := testThreadSafeQueue testThreadSafeQueue2 testThreadSafeQueue3 testThreadSafeStack test_move

all : $(TARGETS)

% : %.cpp ../ThreadSafeQueue.h
	$(CXX) $< -o $@ $(FLAGS)

clean:
	rm -f $(TARGETS)
