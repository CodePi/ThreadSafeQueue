#include <iostream>
#include <thread>
#include <memory>

#include "../ThreadSafeQueue.h"

using namespace std;
using namespace chrono;
using namespace codepi;

int main(){

  // threaded queue
  ThreadSafeQueue<int> q;
  int val;
  vector<int> rc;
  vector<duration<double>> diffs;

  auto t = steady_clock::now();

  // empty tests
  auto prev = t;
  rc.push_back(q.dequeue(0.00, val));
  t = steady_clock::now(); diffs.push_back(t-prev); prev = t;
  rc.push_back(q.dequeue(0.05, val));
  t = steady_clock::now(); diffs.push_back(t-prev); prev = t;
  rc.push_back(q.dequeue(0.10, val));
  t = steady_clock::now(); diffs.push_back(t-prev); prev = t;

  // ready tests
  q.enqueue(1);
  rc.push_back(q.dequeue(0.10, val));
  t = steady_clock::now(); diffs.push_back(t-prev); prev = t;

  // wakeup tests
  thread th([&]{ 
    std::this_thread::sleep_for(milliseconds(50));
    q.enqueue(2);    
  });
  rc.push_back(q.dequeue(0.10, val));
  t = steady_clock::now(); diffs.push_back(t-prev); prev = t;

  // results
  for(size_t i=0;i<rc.size();i++) printf("%d %.0f\n", rc[i], diffs[i].count()*1000);

  th.join();
  
}
