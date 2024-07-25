#include <iostream>
#include <algorithm>
#include <climits>
#ifndef NODE_H
#define NODE_H
using namespace std;

class Node{
    public:
        int data;
        int weight = INT_MIN;
        Node* next;
        Node(){
            data=0;
            next=NULL;
        }
        Node(int data){
            this->data=data;
            this->next=NULL;
        }

};

class DNode{
    public:
        int data;
        DNode* next;
        DNode* prev;
        DNode(){
            data=0;
            next=NULL;
            prev=NULL;
        }
        DNode(int data){
            this->data=data;
            this->next=NULL;
            this->prev=NULL;
        }

};

class LinkedList{
    public:
        int length;
        Node* head;
        LinkedList(){
            head=NULL;
            length=0;
        }
        void printList();
        int getPostion(int);
        void insert(int,int);
        void remove(int);
        void removeData(int);
        bool find(int);

};

class DLinkedList{
    public:
        int length;
        DNode* head;
        DNode* tail;
        DLinkedList(){
            head=NULL;
            tail=NULL;
            length=0;
        }
        void insert(int,int);
        int getPostion(int);
        void remove(int);
        void printList(bool);
};

class CircularLL{
    public:
        int length;
        Node* head;
        Node* tail;
        CircularLL(){
            head=NULL;
            tail=NULL;
            length=0;
        }
        void remove(int);
        void insert(int,int);
        void printList();
};

struct block{
    int size;
    Node* ptr;
};

class operations{
    public:
        int getDataFromEnd(Node*,int,int);
        block cyclicOrAcyclic(Node*);
        Node* insertSorted(Node*,Node*);
        Node* reverseList(Node*);
        Node* intersectingNode(Node*,Node*);
        Node* midElement(Node*);
        bool listIsOdd(Node*);
        Node* merge2SortedList(Node*,Node*);
        Node* reverseListPairwise(Node*);
        void splitCircularList(Node*,Node*,Node*);
        Node* reverseKnodes(Node*, int);
        Node* KreverseBlocks(Node*, int);
        void getJosephusPosition(int,int);
        Node* modularNode(Node*,int);
        Node* reorderingList(Node*);
        Node* add2Numbers(Node*, Node*);
        Node* rotateRight(Node*,int);
};

#endif // NODE_H