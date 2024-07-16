#include "LinkedLists.h"
#include <cstring>
#include <vector>
#include <cmath>

// stack array implementation 
class stack{
    int top;
    int capacity;
    public:
        int* num;
        stack(int capacity){
            this->capacity=capacity;
            num=new int[capacity];
            top=-1; 
        }
        void push(int);
        int pop();
        void printStack();
        int peek();
        bool isempty();
        bool isfull();
        bool isAtCapacity();
        int size();
        void printStackReverse();
};

bool stack::isfull(){
    if(top==capacity-1)
        return true;
    return false;
}

bool stack::isempty(){
    if(top==-1)
        return true;
    return false;
}

void stack::push(int data){
    if(isfull()){
        cout<<"Overflow"<<endl;
        return;
    }
    num[++top]=data;  
}

int stack::pop(){
    if(isempty()){
        cout<<"Underflow"<<endl;
        abort();
    }
    return num[top--];
}

int stack::peek(){
    if(isempty()){
        cout<<"Stack is empty"<<endl;
        return 0;
    }
    return num[top];
}

void stack::printStack(){
    if(isempty()){
        cout<<"Stack is empty "<<endl;
        return;
    }
    for(int i=0;i<=top;i++)
        cout<<num[i] << " ";
    cout<<endl;
}

void stack::printStackReverse(){
    if(isempty()){
        cout<<"Stack is empty"<<endl;
        return;
    }
    for(int i=top;i>=0;i--)
        cout<<num[i]<<" ";
    cout<<endl;
}

bool stack::isAtCapacity(){
    return capacity==top+1;
}

int stack::size(){
    return top+1;
}

//stack linked list implementation 
class stackLL{
    LinkedList ll;
    Node* top;
    public:
        void push(int);
        int pop();
        int peek();
        bool isempty();
        void printStack();

};

void stackLL::printStack(){
    if(!ll.head) { cout<<"Stack is empty"<<endl;}
    else{ll.printList();}
}

bool stackLL::isempty(){
    if(!ll.head) {return true;}
    return false;
}

void stackLL::push(int data){
    ll.insert(data,0);
}

int stackLL::pop(){
    if(ll.head==NULL){ 
        cout<<"Stack is empty"<<endl;
        return -1;
    }
    else{
       int value= ll.head->data;
       ll.remove(0);
       return value;
    }
}

int stackLL::peek(){
    if(!ll.head) { 
        cout<<"Stack is empty"<<endl; 
        return -1; 
    }
    else{ return ll.head->data; }
}

//Dynamic Stack
template <class X>
class DynamicStack{
    int currSize;
    int tailptr;
    X* stack;
    public:
        DynamicStack(){
            currSize=1;
            stack = new X[currSize] {0};
            tailptr=-1;
        }
        ~DynamicStack(){
            delete[]stack;
        }
        void push(X);
        X pop();
        void printStack();
        X peek();
        void resize();
        bool isempty();
        int sizeValue();
};
template <class X>
int DynamicStack<X>::sizeValue(){
    return tailptr+1;
}
template <class X>
void DynamicStack<X>::push(X data){
    if(tailptr==currSize-1){
        resize();
    }
    stack[++tailptr]=data;
}
template <class X>
X DynamicStack<X>::pop(){
    if(isempty()){
        cout<<"Dynamic stack is empty"<<endl;
        abort();
    }
    else{return stack[tailptr--];}
}
template <class X>
X DynamicStack<X>::peek(){
    if(isempty()){
        cout<<"Dynamic stack is empty"<<endl;
        abort();
    }
    else{  return stack[tailptr]; }
}
template <class X>
void DynamicStack<X>::resize(){
    int newSize = currSize*2;
    X* newStack = new X[newSize];
    if(newStack==nullptr){
        cout<<"Memory allocation failed"<<endl;
        return;
    }
    memcpy(newStack,stack,currSize*sizeof(X));
    currSize=newSize;
    delete[]stack;
    stack=newStack;
}
template <class X>
void DynamicStack<X>::printStack(){
    for(int i=0;i<=tailptr; i++)
        cout<<stack[i]<< " ";
    cout<<endl;
}
template <class X>
bool DynamicStack<X>::isempty(){
    return (tailptr==-1);
}

//stack operations
class stackOperations{
    public:
        bool balancedParanthesis(string);
        int postfixEvaluation(string);
        bool pairwiseConsecutive(stack);
};

bool stackOperations::balancedParanthesis(string s){
    DynamicStack<int> st;
    for(int i=0;i<s.length();i++){
        // ( -> 3 | { -> 2 | [ -> 1
        if(s[i]==')'){
            if(!st.isempty() && st.peek()==3)
               st.pop();
            else
               return false;
        }
        else if(s[i]=='}'){
            if(!st.isempty()&&st.peek()==2)
                st.pop();
            else
               return false;
        }
        else if(s[i]==']'){
            if(!st.isempty()&&st.peek()==1)
                st.pop();
            else
                return false;
        }
        else if(s[i]=='[')
            st.push(1);
        else if(s[i]=='{')
            st.push(2);
        else if(s[i]=='(')
            st.push(3);
        else {continue; }
    }
    //st.printStack() remove the comment to see the stack
    if(!st.isempty()) {return false;}
    return true;
}

int stackOperations::postfixEvaluation(string s){
    DynamicStack<int> st;
    for(int i=0; i<s.length();i++){
        if(s[i]=='+'){
            int value1=st.pop();
            int value2=st.pop();
            st.push(value1+value2);
        }
        else if(s[i]=='-'){
            int value1=st.pop();
            int value2=st.pop();
            st.push(value2-value1);
        }
        else if(s[i]=='*'){
            int value1=st.pop();
            int value2=st.pop();
            st.push(value2*value1);
        }
        else if(s[i]=='/'){
            int value1=st.pop();
            int value2=st.pop();
            st.push(value2/value1);
        }
        else {st.push(int(s[i] - '0')); }
    }
    return st.pop();
}

//Dual stack in one array
class doubleStack{
    int* arr;
    int size;
    
    
    public:
        int top1;
        int top2;
        doubleStack(int n){
            size=n;
            arr=new int[n];
            top1=n/2+1;
            top2=n/2;
        }
        void push1(int);
        void push2(int);
        int pop1();
        int pop2();
        int peek1();
        int peek2();
        void printStack1();
        void printStack2();
        bool isempty1();
        bool isempty2();
        bool isfull1();
        bool isfull2();
};;

void doubleStack::push1(int data){
    if(isfull1()) {cout<< "stack1 is full"<<endl;}
    else{arr[--top1]=data;}
}

void doubleStack::push2(int data){
    if(isfull2()) {cout<<"stack2 is full"<<endl;}
    else{arr[++top2]=data;}
}

int doubleStack::pop1(){
    if(isempty1()) {
        cout<<"Stack1 is empty"<<endl;
        return -1;
    }
    int data=arr[top1++];
    return data;
}

int doubleStack::pop2(){
    if(isempty2()){
        cout<<"Stack2 is empty"<<endl;
        return -1;
    }
    int data=arr[top2--];
    return data;
}

int doubleStack::peek1(){
    return arr[top1];
}

int doubleStack::peek2(){
    return arr[top2];
}

void doubleStack::printStack1(){
    if(isempty1()){
        cout<<"stack1 is empty"<<endl;
        return;
    }
    for(int i=size/2;i>=top1;i--)
        cout<<arr[i]<<" ";
    cout<<endl;
}

void doubleStack::printStack2(){
    if(isempty2()){
        cout<<"stack2 is empty"<<endl;
        return;
    }
    for(int i=(size/2)+1;i<=top2;i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}

bool doubleStack::isempty1(){
    if(top1==(size/2)+1) {return true;}
    return false;
}

bool doubleStack::isempty2(){
    if(top2==(size/2)) {return true;}
    return false;
}

bool doubleStack::isfull1(){
    if(top1==0) {return true;}
    return false;
}

bool doubleStack::isfull2(){
    if(top2==size-1) {return true;}
    return false;
}

//multiple stack in single array
class multipleStack{
    int* arr;
    int* top;
    int* next;
    int n;
    int k;
    int free;
    public:
        multipleStack(int n,int k){
            this->n=n;
            this->k=k;
            arr=new int[n];
            top=new int[k];
            next=new int[n];
            free=0;
            for(int i=0;i<k;i++)
                top[i] = -1;
            for(int i=0;i<n;i++)
                next[i]=i+1;
            next[n-1]=-1;
        }
        bool isfull();
        void push(int,int);
        int pop(int);
        bool isempty(int);
        void printStack(int);
};

void multipleStack::push(int data, int k){
    if(isfull()){
        cout<<"Stack "<<k<<" is full."<<endl;
        return;
    }
    int i=free;
    free=next[i];
    next[i]=top[k];
    top[k]=i;
    arr[i]=data;
}

int multipleStack::pop(int k){
    if(isempty(k)){
        cout<<"Stack "<<k<<" is empty."<<endl;
        return -1;
    }
    int i = top[k];
    top[k]=next[i];
    next[i]=free;
    free=i;
    return arr[i];  
}

bool multipleStack::isempty(int k){
    return top[k]==-1;
}

bool multipleStack::isfull(){
    return free == -1;
}

void multipleStack::printStack(int k){
    if(isempty(k)){
        cout<<"Stack "<< k <<" is empty" <<endl;
        return;
    }
    int j = top[k];
    while(j!=-1){
        cout<<arr[j]<<" ";
        j=next[j];
    }
    cout<<endl;
}

//List of stacks
class StackSets{
    int threshold;
    vector<stack*> listOfStacks;
    public:
        StackSets(int threshold){
            this->threshold=threshold;
        }
        void push(int);
        int pop();
        int pop(int);
        stack* getLastStack();
        stack* getNthStack(int);
};

void StackSets::push(int data){
    stack* laststack=this->getLastStack();
    if(laststack==NULL){
        stack* s = new stack(threshold);
        laststack= s;
        s->push(data);
        listOfStacks.push_back(laststack);
    }
    else{
        if(!laststack->isAtCapacity())
            laststack->push(data);
        else{
            stack* s = new stack(threshold);
            s->push(data);
            listOfStacks.push_back(s);
        }
    }
}

int StackSets::pop(){
    stack* laststack=this->getLastStack();
    if(laststack==NULL) {
        cout<<"There is no list of stacks"<<endl;
        return -1;
    }
    int value=laststack->pop();
    if(laststack->size()==0){listOfStacks.pop_back();}
    return value;
}

int StackSets::pop(int n){
    stack* Nthstack = this->getNthStack(n);
    if(Nthstack==NULL){
        cout<<"The list of stacks are empty"<<endl;
        return -1;
    }
    int value= Nthstack->pop();
    if(Nthstack->size()==0){listOfStacks.pop_back();}
    return value;
}

stack* StackSets::getLastStack(){
    if(listOfStacks.empty()) {return NULL;}
    int size = listOfStacks.size();
    return listOfStacks[size-1];
}

stack* StackSets::getNthStack(int n){
    if(listOfStacks.empty()) {return NULL;}
    return listOfStacks[n-1];
    
}


//Get minimum from stack
class AdvancedStack{
    public:
        stackLL elementStack;
        stackLL minStack;
        void push(int);
        int pop();
        int getMinimum();
        int peek();
        bool isempty();
};    

void AdvancedStack::push(int data){
    elementStack.push(data);
    if(minStack.isempty() || (minStack.peek()>=data))
        minStack.push(data);
}

int AdvancedStack::pop(){
    if(elementStack.isempty()){
        cout<<"Stack is empty "<<endl;
        return -1;
    }
    int value=elementStack.pop();
    if(value==minStack.peek())
        minStack.pop();
    return value;
}

int AdvancedStack::getMinimum(){
    return minStack.peek();
}

int AdvancedStack::peek(){
    return elementStack.peek();
}

bool AdvancedStack::isempty(){
    return elementStack.isempty();
}

//circular queue array implication
class Queue{
    int front;
    int rear;
    int* arr;
    public:
        int size;
        Queue(int size){
            this->size = size;
            front=-1;
            rear=-1;
            arr= new int[size];
        }
        void enqueue(int);
        int dequeue();
        void printQueue();
        bool isempty();
        bool isfull();
};

void Queue::enqueue(int data){
    if(isfull()){
        cout<<"OVERFLOW"<<endl;
        return;
    }
    else if(isempty()){ 
        arr[++front]=data;
        rear++;
        
    }
    else{arr[++rear]=data;}
    size++;
}

int Queue::dequeue(){
    if(isempty()){
        cout<<"UNDERFLOW"<<endl;
        return -1;
    }
    int value= arr[front];
    if(rear==front){
        rear=-1;
        front=-1;
    }
    else{front=(front+1)%size;}
    size--;
    return value;
}

void Queue::printQueue(){
    if(isempty()){
        cout<<"Queue is empty"<<endl;
        return;
    }
    for(int i=front;i!=rear;i=(i+1)%size)
        cout<<arr[i]<<" ";
    cout<<arr[rear]<<endl;
}

bool Queue::isfull(){
    if((front==0&&rear==size-1) || (rear+1)%size==front){return true;}
    return false;
}

bool Queue::isempty(){
    return front==-1;
}

//circular queue linked list implementation
class QueueLL{
    CircularLL cl;
    public:
        void enqueue(int);
        int dequeue();
        void printQueue();
        bool isempty();
        int size();
};

int QueueLL::size(){
    return cl.length;
}

bool QueueLL::isempty(){
    return cl.head==NULL;
}

void QueueLL::enqueue(int data){
    cl.insert(data,cl.length);
}

int QueueLL::dequeue(){
    if(cl.head==NULL){
        cout<<"UNDERFLOW"<<endl;
        return -1;
    }
    int value=cl.head->data;
    cl.remove(0);
    return value;
}

void QueueLL::printQueue(){
    cl.printList();
}

//Dynamic circular queue implication
template <class X>
class DynamicQueue{
    int front;
    int rear;
    int size;
    int capacity = 4;
    X* arr;
    public:
        DynamicQueue(){
            front =-1;
            rear =-1;
            size=0;
            arr = new X[capacity];
        }
        void enqueue(X x);
        X dequeue();
        bool isempty();
        bool isfull();
        X frontValue();
        X rearValue();
        int sizeValue();
        int capacityValue();
        void printQueue();
};

template <class X>
bool DynamicQueue<X>::isempty(){
    if(front==-1&&rear==-1){return true;}
    return false;
}

template <class X>
bool DynamicQueue<X>::isfull(){
    return size==capacity;
}

template <class X>
int DynamicQueue<X>::sizeValue(){
    return size;
}

template <class X>
int DynamicQueue<X>::capacityValue(){
    return capacity;
}

template <class X>
X DynamicQueue<X>::frontValue(){
    if(isempty()) {
        cout<<"Queue underflow"<<endl;
        abort();
    }
    return arr[front];
}

template <class X>
X DynamicQueue<X>::rearValue(){
    if(isempty()){
        cout<<"Queue underflow"<<endl;
        abort();
    }
    return arr[rear];
}

template <class X>
void DynamicQueue<X>::enqueue(X data){
    if(isfull()){
        capacity=capacity*2;
        X* temp = new X[capacity];
        for(int i=0,j=front;i<size;i++){
            temp[i] = arr[j];
            j=(j+1)%capacity;
        }
        front=0;
        rear=size-1;
        delete[] arr;
        arr=temp;
    }
    if(isempty()){
        front = rear=0;
    }
    else{rear=(rear+1)%capacity;}
    arr[rear]=data;
    size++; 
}

template <class X>
X DynamicQueue<X>::dequeue(){
    if(isempty()){
        cout<<"Queue underflow"<<endl;
        abort();
    }
    X value = arr[front];
    if(front==rear){
        front=rear=-1;
        size--;
        return value;
    }
    front=(front+1)%capacity;
    size--;
    return value; 
}

template <class X>
void DynamicQueue<X>::printQueue(){
    if(isempty()){
        cout<<"The queue is empty"<<endl;
        return;
    }
    for(int i=front;i!=rear;i=(i+1)%capacity)
        cout<<arr[i]<<" ";
    cout<<arr[rear]<<endl;
}

class queueOperations{
    public:
        Queue* reverse(Queue*);
        void interLeavingQueue(QueueLL &q);
        void reverseFirstK(QueueLL &q,int k);
};

void queueOperations::reverseFirstK(QueueLL &q, int k){
    if(k>q.size()){return;}
    stack s(k);
    for(int i=0;i<k;i++) {s.push(q.dequeue());}
    while(!s.isempty()) {q.enqueue(s.pop());}
    for(int i=0;i<q.size()-k;i++) {q.enqueue(q.dequeue());}
}

void queueOperations::interLeavingQueue(QueueLL &q){
    if(q.size()%2!=0) {return;}
    stack s(q.size()/2);
    int halfsize=q.size()/2;
    for(int i=0;i<halfsize;i++) {s.push(q.dequeue());}
    while(!s.isempty()) {q.enqueue(s.pop());}
    for(int i=0;i<halfsize;i++) {q.enqueue(q.dequeue());}
    for(int i=0;i<halfsize;i++) {s.push(q.dequeue());}
    while(!s.isempty()){
        q.enqueue(s.pop());
        q.enqueue(q.dequeue());
    }
}

Queue* queueOperations::reverse(Queue* q){
    stack* s = new stack(q->size);
    while(!q->isempty())
        s->push(q->dequeue());
    while(!s->isempty())
        q->enqueue(s->pop());
    return q; 
}

class queueWith2Stacks{
    int size;
    stack* s1;
    stack* s2;
    public:
        queueWith2Stacks(int size){
            this->size=size;
            s1= new stack(size/2);
            s2= new stack(size-(size/2));
        }
        void enqueue(int);
        int dequeue();
        void printQueue();
};

void queueWith2Stacks::enqueue(int data){
    if(s1->isfull()&&s2->isfull()){
        cout<<"Queue OVERFLOW"<<endl;
        return;
    }
    if(!s1->isfull()){
        s1->push(data);
        return;
    }
    while(!s2->isfull())
        s2->push(s1->pop());
    s1->push(data);
}

int queueWith2Stacks::dequeue(){
    if(!s2->isempty()) {return s2->pop();}
    while(!s1->isempty()){
        s2->push(s1->pop());
    }
    return s2->pop();
}

void queueWith2Stacks::printQueue(){
    if(s1->isempty())
        s2->printStack();
    else if(s2->isempty())
        s1->printStackReverse();
    else{
        s1->printStackReverse();
        s2->printStack();
    }
}

class stackWith2Queues{
    QueueLL* q1;
    QueueLL* q2;
    public:
        stackWith2Queues(){
            q1= new QueueLL();
            q2= new QueueLL();
        }
        void push(int);
        int pop();
        void printStack();
};

void stackWith2Queues::push(int data){
    q2->enqueue(data);
    while(!q1->isempty()){
        q2->enqueue(q1->dequeue());
    }
    QueueLL* q=q1;
    q1=q2;
    q2=q;
}

int stackWith2Queues::pop(){
    if(q1->isempty()) {
        cout<<"Stack is empty"<<endl;
        return -1;
    }
    return q1->dequeue();
}

void stackWith2Queues::printStack(){
    q1->printQueue();
}

bool stackOperations::pairwiseConsecutive(stack s){
    Queue* q= new Queue(s.size());
    while(!s.isempty()){q->enqueue(s.pop());}
    while(!q->isempty()){s.push(q->dequeue());}
    bool result = true;
    while(!s.isempty()){
        int n=s.pop();
        q->enqueue(n);
        if(!s.isempty()){
            int m=s.pop();
            q->enqueue(m);
            if(abs(n-m)!=1)
               result = false;
        }
    }
    while(!q->isempty()){s.push(q->dequeue());}
    return result;
}
