// From the personal library of Paul Ilardi (http://github.com/CodePi).
// Free to use or modify.

#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

namespace codepi{

template <class T>
class ThreadSafeQueue {
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

  // dequeue with timeout in seconds
  bool dequeue(double timeout_sec, T& rVal){
    std::unique_lock<std::mutex> lock(m);
    bool isTimeout=false;

    // wait for timeout or value available
    auto maxTime = std::chrono::milliseconds(int(timeout_sec*1000));
    if(c.wait_for(lock, maxTime, [&](){return !q.empty();} )){
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

} // end namespace codepi
