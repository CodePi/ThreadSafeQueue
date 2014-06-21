#include <queue>
#include <mutex>
#include <condition_variable>

template <class T>
class SafeQueue{
public:

  template<class U>
  void enqueue(U&& t){
    std::lock_guard<std::mutex> lock(m);
    q.push(std::forward<U>(t));
    c.notify_one();
  }

  // simple dequeue
  T dequeue(){
    std::unique_lock<std::mutex> lock(m);
    while(q.empty()) c.wait(lock);
    T val = std::move(q.front());
    q.pop();
    return val;
  }

  // dequeue with timeout
  bool dequeue(double timeout, T& rVal){
    std::unique_lock<std::mutex> lock(m);
    auto end = std::chrono::steady_clock::now()
             + std::chrono::milliseconds(int(timeout*1000));
    bool isTimeout=false;

    // wait for timeout or value available
    if(c.wait_until(lock, end, [&](){return !q.empty();} )){
      rVal = std::move(q.front());
      q.pop();
      return true;
    } else {
      return false;
    }
  }

  size_t size() { return q.size(); }
  bool  empty() { return q.empty(); }
  void  clear() {
    std::lock_guard<std::mutex> lock(m);
    q.clear();
  }

private:
  std::queue<T> q;
  mutable std::mutex m;
  std::condition_variable c;
};

////////////////////////////////////////////////////

#include<iostream>
#include<unistd.h>
#include<thread>
using namespace std;

void populate(SafeQueue<int>& q){
  for(int i=0;;i++){
    q.enqueue(i);
    sleep(1);
  }
}

int main(){

  // thread safe queue
  SafeQueue<int> q;

  // kick off generator thread
  thread t(populate,ref(q));

  // receive loop
  while(1){
    if(0){
      // simple dequeue
      cout << q.dequeue() << endl;
    }else{
      // dequeue with timeout
      int i;
      if(q.dequeue(0.3,i)) cout << i << endl;
      else                 cout << "timeout\n";
    }
  }
}
