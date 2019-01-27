#include <iostream>
#include <thread>
#include <memory>

#include "../ThreadSafeQueue.h"

using namespace std;
using namespace chrono;
using namespace codepi;

void populate(ThreadSafeQueue<unique_ptr<char[]>>& q){
  for(int i=0;i<3;i++){
    unique_ptr<char[]> buf(new char[1000]);
    buf[0] = i;
    q.enqueue(move(buf));
    this_thread::sleep_for(milliseconds(100));
  }
}

int main(){

  // threaded queue
  ThreadSafeQueue<unique_ptr<char[]>> q;

  // kick off generator thread
  thread t(populate,ref(q));

  // receive loop
  while(1){
    unique_ptr<char[]> buf = q.dequeue();
    cout << (int)buf[0] << endl;
    if(buf[0]==2) break;
  }
  t.join();
}
