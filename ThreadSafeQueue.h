// From the personal library of Paul Ilardi (http://github.com/CodePi).
// Free to use or modify.

#pragma once

#include <queue>
#include <stack>
#include <mutex>
#include <condition_variable>

namespace codepi{

template <class T, class Container=std::queue<T>>
class ThreadSafeQueue {
public:

  ThreadSafeQueue() =default;

  // enqueue - supports move, copies only if needed. e.g. q.enqueue(move(obj));
  void enqueue(T t){
    std::lock_guard<std::mutex> lock(m);
    q.push(std::move(t));
    c.notify_one();
  }

  // simple dequeue
  T dequeue(){
    std::unique_lock<std::mutex> lock(m);
    while(empty()) c.wait(lock);
    return pop();
  }

  // dequeue with timeout in seconds
  bool dequeue(double timeout_sec, T& rVal){
    std::unique_lock<std::mutex> lock(m);
    bool isTimeout=false;

    // wait for timeout or value available
    auto maxTime = std::chrono::milliseconds(int(timeout_sec*1000));
    if(c.wait_for(lock, maxTime, [&](){return !this->empty();} )){
      rVal = pop();
      return true;
    } else {
      return false;
    }
  }

  size_t size() const { return q.size(); }
  bool  empty() const { return q.empty(); }
  void  clear() {
    std::lock_guard<std::mutex> lock(m);
    // stack and queue have no clear method!! Maybe switch to deque
    while(!empty()) pop();
  }

private:
  Container q;
  mutable std::mutex m;
  std::condition_variable c;

  T& get_top(std::stack<T>& s){ return s.top(); }
  T& get_top(std::queue<T>& qu){ return qu.front(); }

  T pop(){
    T val = std::move(get_top(q));
    q.pop();
    return val;
  }
    
};

} // end namespace codepi
