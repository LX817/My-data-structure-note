//source from GeeksforGeeks Min Heap
#include <iostream>
#include <vector>
#include <math.h>
#include <climits>
using namespace std;

//最小堆的实现1
//min heap
//a complete tree
//key at root must be minimum among all keys in binary heap
//typically represented as an array
//可以把堆看成是一个完全二叉树


//implementations of basic heap operations

//Protoytype of a utility function to swap two integers
void swap(int *x, int*y);

//class for min heap
class MinHeap {
  int *harr; //pointer to array of elements in heap
  int capacity; //maximum possible size of min heap
  int heap_size; //current number of elements in min heap

  public:
  //constructor
  MinHeap(int capacity);

  //to heapify a subtree with the root at given index
  void MinHeapify(int);

  int parent(int i) { return (i-1)/2; }

  //to get index of left child of node at index i
  int left(int i) { return (2*i + 1); }

  //to get index of reight child of node at index i
  int right(int i) { return (2*i + 2); };

  //to extract the root which is the minumum element
  //提取作为最小元素的根
  int extractMin();

  //decrease key value of key at index i to new_val
  void decreaseKey(int i, int new_val);

  //returns the minimum key(key at root) from min heap
  int getMin() { return harr[0]; };

  //delete a key sorted at index i
  void deleteKey(int i);

  //insert a new key
  void insertKey(int k);
};

//constructor
//builds a heap from a given array a[] of given size
//cap 是给定的堆的大小
MinHeap :: MinHeap(int cap) {
  heap_size = 0;
  capacity = cap;
  //harr 是新的数组， 数组大小是cap
  harr = new int[cap];
}

//insert a new key 'k'
void MinHeap :: insertKey(int k) {
  //如果堆是满的，则无法插入更多的元素
  if (heap_size == capacity ) {
    cout << "\nOverflow: Could not insert key\n";
    return;
  }

  //First insert the new key at the end
  //假如新的元素，堆元素个数+1
  //i 是原来的heap_size
  //原来堆的第一位变成k
  heap_size++;
  int i = heap_size - 1;
  harr[i] = k;

  //Fix the min heap property if it is violated
  //如果不符合最小堆的规律，修复
  while (i != 0 && harr[parent(i)] > harr[i]) {
    swap(&harr[i], &harr[parent(i)]);
    i = parent(i);
  }
}

//Ddecrease value of key at index 'i' to new_val.
//assumed that new_val is smaller than harr[i]
//将i处的值减少到new_val
//假设new_val 小于 harr[i] (?)
void MinHeap::decreaseKey(int i, int new_val) {
  harr[i] = new_val;
  while ( i != 0 && harr[parent(i)] > harr[i] ) {
    swap(&harr[i], &harr[parent(i)]);
    i = parent(i);
  }
}

//Method to remove minimum element(or root) from min heap
int MinHeap::extractMin () {
  //如果堆里面没有元素，返回最小整数值
  if (heap_size <= 0) {
    return INT_MAX;
  }
  //如果堆里面只剩一个元素，堆的大小变为0，移除元素
  //返回堆的第一个元素
  if (heap_size == 1) {
    heap_size--;
    return harr[0];
  }
  //Store the minimum value
  //and remove it from heap
  int root = harr[0];
  harr[0] = harr[heap_size-1];
  heap_size--;
  MinHeapify(0);

  return root;
}

//delete key at index i
//先将值减少到负无限，然后调用 extractMin()
void MinHeap::deleteKey(int i) {
  decreaseKey (i, INT_MIN);
  extractMin();
}

//递归方法，用于在给定索引处堆化具有根的子树
//该方法假设子树已经堆化
void MinHeap::MinHeapify(int i) {
  int l = left(i);
  int r = right(i);
  int smallest = i;
  if (l < heap_size && harr[l] < harr[i]) {
    smallest = l;
  }
  if (r < heap_size && harr[r] < harr[smallest]) {
    smallest = r;
  }
  if (smallest != i) {
    swap(&harr[i], &harr[smallest]);
    MinHeapify(smallest);
  }
}

//交换两元素的方法
void swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

int main() {

  MinHeap h(11);
  h.insertKey(3);
  h.insertKey(2);
  h.deleteKey(1);
  h.insertKey(15);
  h.insertKey(5);
  h.insertKey(4);
  h.insertKey(45);
  cout << h.extractMin() << " ";
  cout << h.getMin() << " ";
  h.decreaseKey(2,1);
  cout << h.getMin();
  return 0;
} 