#include<iostream>
#include<thread>
#include<stack>
#include<cassert>

#include "../ThreadSafeQueue.h"

using namespace std;
using namespace chrono;
using namespace codepi;

static const int N=3;

void populate(ThreadSafeQueue<int, stack<int>>& s){
  for(int i=0;i<N;i++){
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
  s.enqueue(3);
  assert(s.size()==3);
  assert(s.dequeue()==3);
  assert(s.dequeue()==2);
  assert(s.dequeue()==1);
  assert(s.empty());

  // kick off generator thread
  thread t(populate,ref(s));

  // receive loop
  bool testWithTimeout = false;
  for(int i=0; i<N; i++){
    if(!testWithTimeout){
      // simple dequeue
      int val = s.dequeue();
      cout << val << endl;
    }else{
      // dequeue with timeout
      if(s.dequeue(0.3,i)) cout << i << endl;
      else                 cout << "timeout\n";
    }
  }
  t.join();
}
