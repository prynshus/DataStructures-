#include <iostream>
#include <climits>
#include <cstring>
#include <queue>
using namespace std;

class heap{
    public:
      int* arr;
      int size;
      int capacity;
      int heap_type;
      heap(int capacity){
        this->capacity=capacity;
        arr=new int[capacity];
        size=0;
      }
      int Parent(int);
      int leftChild(int);
      int rightChild(int);
      int getMax();
      void percolateDown(int);
      void percolateUp();
      int deleteMax();
      void insert(int);
      void resizeHeap();
      void destroyHeap();
      void print();
      void buildHeap(int*,int);
      int findMin();
      int deleteKth(int);
      void RlargerElements(int,int);
};

int heap::Parent(int i){
    if(i<=0 || i>=size){throw out_of_range("index out of range.");}
    return (i-1)/2;
}

int heap::leftChild(int i){
    int left=2*i +1;
    if(left>=size){return -1;}
    return left;
}

int heap::rightChild(int i){
    int right=2*i +2;
    if(right>=size){return -1;}
    return right;
}

int heap::getMax(){
    if(size==0){throw out_of_range("The heap is empty.");}
    return arr[0];
}

void heap::percolateDown(int i){
    int max,l,r;
    l=leftChild(i);
    r=rightChild(i);
    if(l!=-1 && arr[l]>arr[i]){max=l;}
    else{max=i;}
    if(r!=-1 && arr[r]>arr[max]){max=r;}
    if(max!=i){
        int temp=arr[i];
        arr[i]=arr[max];
        arr[max]=temp;
        percolateDown(max);
    }
}

int heap::deleteMax(){
    if(size==0){throw out_of_range("Heap is empty.");}
    int result=arr[0];
    arr[0]=arr[size-1];
    size--;
    percolateDown(0);
    return result;
}

void heap::percolateUp(){
    int data=arr[size-1];
    int i=size-1;
    while(i>0 && data>arr[Parent(i)]){
        arr[i]=arr[Parent(i)];
        i=Parent(i);
    }
    arr[i]=data;
}

void heap::insert(int data){
    if(size==capacity){resizeHeap();}
    size++;
    arr[size-1]= data;
    percolateUp();
}

void heap::resizeHeap(){
    int* old_arr = new int[capacity];
    memcpy(old_arr, arr, capacity*sizeof(int));
    arr= new int[capacity*2];
    for(int i=0;i<capacity;i++){arr[i]=old_arr[i];}
    capacity*=2;
    delete[] old_arr;
}

void heap::destroyHeap(){
    size=0;
    delete[] arr;
}

void heap::print(){
    if(size==0){return;}
    queue<int> q;
    q.push(0);
    int temp;
    while(!q.empty()){
        int size=q.size();
        for(int i=0;i<size;i++){
            temp=q.front();
            q.pop();
            if(temp!=-1){
                cout<<arr[temp]<<" ";
                if(leftChild(temp)!=-1){q.push(leftChild(temp));}
                if(rightChild(temp)!=-1){q.push(rightChild(temp));}
            }
        }
        cout<<endl;
    } 
}

void heap::buildHeap(int* list, int n){
    while(n>capacity){resizeHeap();}
    for(int i=0;i<n;i++){arr[i]=list[i];}
    size=n;
    for(int i=(n-1)/2;i>=0;i--){percolateDown(i);}
}

int heap::findMin(){
    int min=1000;
    for(int i=(size+1)/2;i<size;i++){
        if(arr[i]<min){min=arr[i];}
    }
    return min;
}

int heap::deleteKth(int k){
    if(k>=size){throw out_of_range("The index is out of range.");}
    int key= arr[k];
    arr[k]= arr[size-1];
    size--;
    percolateDown(k);
    return key;
}

void heap::RlargerElements(int i,int k){
    if(arr[i]==-1){return;}
    if(arr[i]<=k){return;}
    else if(arr[i]>k){cout<<arr[i]<<" ";}
    RlargerElements(leftChild(i),k);
    RlargerElements(rightChild(i),k);
}

class heapOperation{
    public:
       void heapsort(int*,int);
};

void heapOperation::heapsort(int* list, int n){
    if(n==0){return;}
    heap h(3);
    h.buildHeap(list,n);
    for(int i=n-1;i>=0;i--){list[i]=h.deleteMax();}
}