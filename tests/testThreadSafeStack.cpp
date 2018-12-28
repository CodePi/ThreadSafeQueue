#include<iostream>
#include<thread>
#include<stack>

#include "../ThreadSafeQueue.h"

using namespace std;
using namespace chrono;
using namespace codepi;

void populate(ThreadSafeQueue<int, stack<int>>& q){
  for(int i=0;;i++){
    q.enqueue(i);
    this_thread::sleep_for(seconds(1));
  }
}

int main(){

  // threaded queue
  ThreadSafeQueue<int, stack<int>> q;

  // kick off generator thread
  thread t(populate,ref(q));

  // receive loop
  bool testWithTimeout = false;
  while(1){
    if(!testWithTimeout){
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
