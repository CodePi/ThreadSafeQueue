#include<iostream>
#include<unistd.h>
#include<thread>

#include "ThreadedQueue.h"

using namespace std;

void populate(ThreadedQueue<int>& q){
  for(int i=0;;i++){
    q.enqueue(i);
    sleep(1);
  }
}

int main(){

  // threaded queue
  ThreadedQueue<int> q;

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
