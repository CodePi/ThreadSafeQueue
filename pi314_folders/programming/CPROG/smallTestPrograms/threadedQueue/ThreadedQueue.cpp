#include <queue>
#include <mutex>
#include <condition_variable>

template <class T>
class SafeQueue{
public:

  void enqueue(T t){
    std::lock_guard<std::mutex> lock(m);
    q.push(t);
    c.notify_one();
  }

  T dequeue(void){
    std::unique_lock<std::mutex> lock(m);
    while(q.empty()) c.wait(lock);
    T val = q.front();
    q.pop();
    return val;
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
  SafeQueue<int> q;
  thread t(populate,ref(q));
  while(1){
    cout << q.dequeue() << endl;
  }
}
