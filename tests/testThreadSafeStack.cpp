#include<iostream>
#include<thread>
#include<stack>
#include<cassert>

#include "../ThreadSafeQueue.h"

using namespace std;
using namespace chrono;
using namespace codepi;

void populate(ThreadSafeQueue<int, stack<int>>& s){
  for(int i=0;i<3;i++){
    s.enqueue(i);
    this_thread::sleep_for(milliseconds(100));
  }
}

int main(){

  // threaded stack
  bool useStack = true;
  ThreadSafeQueue<int, std::stack<int>> s;

  // test basics
  s.enqueue(1);
  s.enqueue(2);
  assert(s.size()==2);
  assert(s.dequeue()==2);
  assert(s.dequeue()==1);
  assert(s.empty());

  // kick off generator thread
  thread t(populate,ref(s));

  // receive loop
  bool testWithTimeout = false;
  while(1){
    int i;
    if(!testWithTimeout){
      // simple dequeue
      i = s.dequeue();
      cout << i << endl;
    }else{
      // dequeue with timeout
      if(s.dequeue(0.3,i)) cout << i << endl;
      else                 cout << "timeout\n";
    }
    if(i==2) break;
  }
  t.join();
}
