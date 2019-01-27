#include<iostream>
#include<thread>
#include<stack>

#include "../ThreadSafeQueue.h"

using namespace std;
using namespace chrono;
using namespace codepi;

void populate(ThreadSafeQueue<int>& q){
  for(int i=0;i<3;i++){
    q.enqueue(i);
    this_thread::sleep_for(milliseconds(100));
  }
}

int main(){

  // threaded stack
  bool useStack = true;
  ThreadSafeQueue<int> q(useStack);

  // kick off generator thread
  thread t(populate,ref(q));

  // receive loop
  bool testWithTimeout = false;
  while(1){
    int i;
    if(!testWithTimeout){
      // simple dequeue
      i = q.dequeue();
      cout << i << endl;
    }else{
      // dequeue with timeout
      if(q.dequeue(0.3,i)) cout << i << endl;
      else                 cout << "timeout\n";
    }
    if(i==2) break;
  }
  t.join();
}
