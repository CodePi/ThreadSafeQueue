# ThreadedQueue
Header-only thread-safe queue

### Relevant methods:
```cpp
namespace codepi{

template <class T>
class ThreadedQueue{

	// inserts onto back of queue  
  void enqueue(T& t);
  
  // retrieves from front of queue (blocks until success)
  T dequeue();
  
  // dequeue with timeout (returns true if successful)
  bool dequeue(double timeout, T& returnVal);

	// basic methods  
  size_t size();
  bool  empty();
  void  clear();

};
}
```

### Example usage:
```cpp
#include <thread>
#include "ThreadedQueue.h"

using namespace std;
using namespace codepi;

void populate(ThreadedQueue<int>& q){
  for(int i=0;;i++){
    q.enqueue(i);
    this_thread::sleep_for(chrono::seconds(1));
  }
}

int main(){
  // threaded queue
  ThreadedQueue<int> q;

  // kick off generator thread
  thread t(populate, ref(q));

  // receive loop
  while(1){
      cout << q.dequeue() << endl;
  }
}
```

