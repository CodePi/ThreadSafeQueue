# ThreadSafeQueue
Header-only thread-safe queue.  Compiles with C++11 compatible compilers.  Tested with gcc 4.6 and Visual Studio 2012.

#### Relevant methods:
```cpp
namespace codepi{

template <class T>
class ThreadSafeQueue{
public:
  // constructor - option to use stack instead of queue
  ThreadSafeQueue(bool useStack=false);

  // inserts onto back of queue  
  void enqueue(T t);       // supports move, copies if needed
  
  // retrieves from front of queue (blocks until success)
  T dequeue();
  
  // dequeue with timeout in seconds (returns true if successful)
  bool dequeue(double timeout_sec, T& returnVal);

  // basic methods  
  size_t size();
  bool  empty();
  void  clear();

  ...
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

#### Move example:

``` cpp
vector<int> vec1(1000000);      // large object that supports move
ThreadSafeQueue<vector<int>> q;
q.enqueue(move(vec));           // moves vector onto queue without copy
vector<int> vec2 = q.dequeue(); // moves vector into vec2 without copy
```

#### ThreadSafeStack:

ThreadSafeQueue can also be used as a stack (first in, last out).

```cpp
bool useStack = true;
ThreadSafeQueue<int> s(useStack);
s.enqueue(1);
s.enqueue(2);
std::cout << s.dequeue() << " " << s.dequeue() << "\n";
// prints: 2 1
```
