#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

template <class T>
class ThreadedQueue{
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

