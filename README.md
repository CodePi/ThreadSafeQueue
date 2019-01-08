# ThreadSafeQueue
Header-only thread-safe queue.  Compiles with C++11 compatible compilers.  Tested with gcc 4.4 and Visual Studio 2012.

#### Relevant methods:
```cpp
namespace codepi{

template <class T>
class ThreadSafeQueue{
public:
  // inserts onto back of queue  
  void enqueue(T& t);
  
  // retrieves from front of queue (blocks until success)
  T dequeue();
  
  // dequeue with timeout in seconds (returns true if successful)
  bool dequeue(double timeout_sec, T& returnVal);

	// basic methods  
  size_t size();
  bool  empty();
  void  clear();

};
}
```

#### Example usage:
```cpp
#include <thread>
#include "ThreadSafeQueue.h"

using namespace std;
using namespace codepi;

void populate(ThreadSafeQueue<int>& q){
  for(int i=0;;i++){
    q.enqueue(i);
    this_thread::sleep_for(chrono::seconds(1));
  }
}

int main(){
  // threaded queue
  ThreadSafeQueue<int> q;

  // kick off generator thread
  thread t(populate, ref(q));

  // receive loop
  while(1){
      cout << q.dequeue() << endl;
  }
}
```

#### ThreadSafeStack:

ThreadSafeQueue can also be used as a stack (first in, last out).

```cpp
ThreadSafeQueue<int, std::stack<int>> s;
s.enqueue(1);
s.enqueue(2);
std::cout << s.dequeue() << " " << s.dequeue() << "\n";
// prints: 2 1
```
