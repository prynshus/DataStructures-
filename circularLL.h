
#include "node.h"

void CircularLL::insert(int data, int pos){
    if(pos<0)
       pos=0;
    if(pos>length)
       pos=length;
    if(head==NULL){
        Node* newNode= new Node(data);
        head=newNode;
        tail=newNode;
        length++;
        return;

    }

    if(pos==0){
        Node* newNode=new Node(data);
        newNode->next=head;
        head=newNode;
        tail->next = head;
    }
    else if(pos==length){
        Node* newNode=new Node(data);
        newNode->next=head;
        tail->next=newNode;
        tail=newNode;
    }
    else{
        Node* temp=head;
        for(int i=0;i<pos-1;i++)
            temp=temp->next;
        Node* newNode= new Node(data);
        newNode->next=temp->next;
        temp->next=newNode;
    }
    length++;
}

void CircularLL::printList(){
    if(head==NULL){
       cout<<"The list is empty"<<endl;
       return;
    }
    if(!head->next){
        cout<<head->data;
        return;
    }
    cout<<head->data<< " ";
    Node* temp=head->next;
    while(temp!=head){
        cout<<temp->data<< " ";
        temp=temp->next;
    }
    
}

void CircularLL::remove(int pos){
    if(pos<0)
       pos=0;
    if(pos>=length)
       pos=length-1;
    if(head==NULL){
        cout<<"The list is empty "<<endl;
        return;
    }
    if(pos==0){
        Node* temp=head;
        if(head->next==head){
            head=NULL;
            tail=NULL;
        }
        else{
            head=head->next;
            tail->next=head;
        }
        delete temp;
        length--;
        return;  
    }
    else{
        Node* temp1=head;
        Node* temp2=NULL;
        for(int i=0; i<pos;i++){
           temp1=temp1->next;
           if(temp2==NULL){
               temp2=head;
               continue;
           }
           temp2=temp2->next;
        }
        
        if (temp1==tail){
            tail=temp2;
            tail->next=head;
            delete temp1;
        }
        else{
            temp2->next=temp1->next;
            delete temp1;
        }
        length--;
    }
}
