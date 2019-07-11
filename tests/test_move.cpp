#include "../ThreadSafeQueue.h"
#include <vector>
#include <stdio.h>
#include <assert.h>

using namespace codepi;
using namespace std;

int main(){
  vector<int> vec(1000000);
  int* p1 = vec.data();
  printf("Before: %p\n", p1);
  
  ThreadSafeQueue <vector<int>> q;
  q.enqueue(move(vec));
  vector<int> vec2 = q.dequeue();
  int* p2 = vec2.data();
  printf("After:  %p\n", p2);

  assert(p1==p2);
  printf("Test Passed\n");
}
