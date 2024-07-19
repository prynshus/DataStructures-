
#include "circularLL.h"

//single linked list
void LinkedList::remove(int pos){
    Node* temp1=head;
    Node* temp2=NULL;
    if(head==NULL){
        cout<<"List is already empty"<<endl;
        return;
    }
    if(pos<0)
       pos=0;
    if(pos>=length)
       pos=length-1;

    if(pos==0){
       head=head->next;
       return;
    }

    for(int i=0; i<=pos-1; i++){
        temp1=temp1->next;
        if(temp2==NULL){
            temp2=head;
            continue;
        }
        temp2=temp2->next;

    } 
    temp2->next=temp1->next;
    delete temp1;
    length--;
}

void LinkedList::removeData(int data){
    Node* temp=head;
    int pos=0;
    while(temp){
        if(temp->data==data){break;}
        temp=temp->next;
        pos++;
    }
    if(!temp){return;}
    remove(pos);
}

void LinkedList::insert(int data, int pos){

    if(pos<0)
       pos=0;
    if(pos>length)
        pos=length;
    if(head==NULL)
        head= new Node(data);

    else if(pos==0){
        Node* temp= new Node(data);
        temp->next=head;
        head=temp;
    }
    else{
        Node* temp=head;
        for(int i=0; i<pos-1; i++)
            temp=temp->next;
        Node* newNode=new Node(data);
        newNode->next=temp->next;
        temp->next=newNode; 
    }
    length++;
}

int LinkedList::getPostion(int value){
    Node* temp=head;
    int pos=-1;
    while(temp!=NULL){
        if(temp->data == value)
           return pos;    
        temp=temp->next;
        ++pos;  
    }
    return pos;
}

void LinkedList::printList(){
    Node* temp=head;
    if(head==NULL){
        cout<<"List is empty"<<endl;
        return;
    }

    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp=temp->next;
    }
}

//Doubly Linked List
int DLinkedList::getPostion(int data){
    DNode* temp=head;
    int pos=-1;
    while(temp!=NULL){
        pos++;
        if(temp->data==data)
           return pos;
        temp=temp->next;
    }
    return -1;
}

void DLinkedList::insert(int data, int pos){
    if(pos<0)
        pos=0;
    if(pos>length)
        pos=length;
    if(head==NULL){
        DNode* newNode=new DNode(data);
        head=newNode;
        tail=newNode;
        length++;
        return;
    }
    if(pos==0){
        DNode* newNode=new DNode(data);
        newNode->next=head;
        head->prev=newNode;
        head=newNode;
    }

    else if(pos==length){
        DNode* newNode=new DNode(data);
        newNode->prev=tail;
        tail->next=newNode;
        tail=newNode;
    }
    else{
        int mid=int(pos/2);
        DNode* temp;
        if (mid<=pos){
            temp=head;
            for(int i=0;i<pos-1;i++)
                temp=temp->next;
        }
        else{
            temp=tail;
            for(int i=0;i<pos;i++)
                temp=temp->prev;
        }
        DNode* newNode= new DNode(data);
        newNode->next=temp->next;
        newNode->prev=temp;
        newNode->next->prev=newNode;
        temp->next=newNode;
    }
    length++;
}

void DLinkedList::printList(bool reverse){
    DNode* temp=head;
    DNode* temp1=tail;
    if(!reverse){
        if(head==NULL){
            cout<<"The list is empty" << endl;
            return;
        }

        while(temp!=NULL){
            cout<<temp->data<<" ";
            temp=temp->next;
        } 
    
    }
    else{
        if(tail==NULL){ 
            cout<<"The list is empty"<<endl;
            return;
        }  

        while(tail!=NULL){
            cout<<temp1->data<<" ";
            temp1=temp1->prev;
        }
    }
}    

//operations
Node* operations::insertSorted(Node* head, Node* newNode){
    Node* current=head;
    Node* temp;
    if(head==NULL)
        return newNode;
    while(current!=NULL && current->data<newNode->data){
        temp=current;
        current=current->next;
    }
    newNode->next=current;
    temp->next=newNode;
    return head;
}

block operations::cyclicOrAcyclic(Node* head){
    Node* slowptr=head;
    Node* fastptr=head;
    block result;
    bool loop=false;
    while(fastptr!=NULL && fastptr->next!=NULL){
        fastptr=fastptr->next->next;
        slowptr=slowptr->next;
        if(slowptr==fastptr){
           loop=true;
           break;
        }    
    }
    if(loop==true){
        cout<<"Loop exits."<<endl;
        slowptr=head;
        while(slowptr!=fastptr){
            slowptr=slowptr->next;
            fastptr=fastptr->next;
        }
        fastptr=fastptr->next;
        int size=1;
        while(slowptr!=fastptr){
            fastptr=fastptr->next;
            size++;
        }
        result.size = size;
        result.ptr = slowptr;
        return result;
    }
    else{
        cout<<"Loop doesn't exist"<<endl;
        result.size=-1;
        result.ptr=NULL;
        return result;
    }

}

int operations::getDataFromEnd(Node* head, int pos, int length){
    if(pos<=0)
       pos=1;
    if(pos>length)
       pos=length;
    Node* temp1=head;
    for(int i=1;i<pos;i++){
        if(temp1!=NULL)
           temp1=temp1->next;
    }
    Node* temp2=NULL;
    while(temp1!=NULL){
        if(temp2==NULL)
            temp2=head;
        else
          temp2=temp2->next;
        temp1=temp1->next;
    }
    return temp2->data;
}

Node* operations::reverseList(Node* head){
    Node* curr = head;
    Node* prev = NULL;
    while(curr!=NULL){
        Node* next=curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }
    return prev;
}

Node* operations::intersectingNode(Node* head1, Node* head2){
    int l1=0; 
    int l2=0;
    int diff=0;
    Node* temp1=head1;
    Node*temp2=head2;
    while(temp1!=NULL){
        l1++;
        temp1=temp1->next;
    }
    while(temp2!=NULL){
        l2++;
        temp2=temp2->next;
    }
    if(l1<l2){
        temp1=head2;
        temp2=head1;
        diff=l2-l1;
    }
    else{
        temp1=head1;
        temp2=head2;
        diff=l1-l2;
    }
    for(int i=0;i<diff;i++)
        temp1=temp1->next;
    while(temp1!=NULL && temp2!=NULL){
        if(temp1==temp2)
            return temp1;
        temp1=temp1->next;
        temp2=temp2->next;
    }
    return NULL;
}

Node* operations::midElement(Node* head){
    Node* slowptr=head;
    Node* fastptr=head;
    int i=0;
    while(fastptr->next!=NULL){
        if(i==0){
            fastptr=fastptr->next;
            i=1;
        }
        else{
            slowptr=slowptr->next;
            fastptr=fastptr->next;
            i=0;
        }
    }
    return slowptr;
}

bool operations::listIsOdd(Node* head){
    Node* temp=head;
    while(temp!=NULL && temp->next!=NULL)
        temp=temp->next->next;
    if(temp==NULL) return false;
    return true;
}

Node* operations::merge2SortedList(Node* head1, Node* head2){
    Node* head= new Node(0);
    Node* curr=head;
    while(head1 && head2){
        if(head1->data<=head2->data){
            curr->next=head1;
            head1=head1->next;
            
        }
        else{
            curr->next=head2;
            head2=head2->next;
        }
        curr=curr->next;
    }
    curr->next = head1 ? head1 : head2;
    Node* result=head->next;
    delete head;
    return result;
}

Node* operations::reverseListPairwise(Node* head){
    Node* temp1=NULL;
    Node* temp2=NULL;
    while(head&&head->next){
        if(temp1!=NULL)
            temp1->next->next=head->next;
        temp1=head->next;
        head->next=head->next->next;
        temp1->next=head;
        if(temp2==NULL)
            temp2=temp1;
        head=head->next;
    }
    
    return temp2;
}

void operations::splitCircularList(Node* head, Node* head1, Node* head2){
    Node* slowptr=head;
    Node* fastptr=head;
    if(head==NULL){
        cout<<"The list is empty."<<endl;
        return;
    }
    while(fastptr->next!=head && fastptr->next->next!=head){
        slowptr=slowptr->next;
        fastptr=fastptr->next->next;
    }
    if(fastptr->next->next==head)
        fastptr=fastptr->next;
    head1=head;
    if(head->next!=head)
        head2=slowptr->next;
    fastptr->next=slowptr->next;
    slowptr->next=head;
}

Node* operations::reverseKnodes(Node* head,int k){
    Node* prevCurr=head;
    Node* tail=NULL;
    Node* curr=head;
    while(curr&&k>0){
        Node* next=curr->next;
        curr->next=tail;
        tail=curr;
        curr=next;
        k--;
    }
    prevCurr->next=curr;
    return tail;
}

Node* operations::KreverseBlocks(Node* head, int k){
    Node* prevCurr=head;
    Node* prevTail=NULL;
    Node* curr=head;
    while(curr){
        int count=k;
        Node* tail=NULL;
        while(curr&&count>0){
            Node* next=curr->next;
            curr->next=tail;
            tail=curr;
            curr=next;
            count--;
        }

        if(prevTail)
            prevTail->next=tail;
        else
            head=tail;
        prevTail=prevCurr;
        prevCurr=curr;
    }
    return head;
}

void operations::getJosephusPosition(int M, int N){
    CircularLL cl;
    int j=1;
    Node* temp=cl.head;
    for(int i=0;i<N;i++)
        cl.insert(j++,i);

    for(int count=N; count>1;--count){
        for(int k=0;k<M-1;++k)
            temp=temp->next;

        temp->next=temp->next->next;
    }
    cout<<"The last player of Josephus circle is: "<<temp->data;
    
}

Node* operations::modularNode(Node* head, int k){
    Node* modularNode=head;
    int i=0;
    if(k<=0)
        return NULL;
    for(;head!=NULL;head=head->next){
        if(i%k==0)
            modularNode=head;
        i++;
    }
    return modularNode;
}

Node* operations::reorderingList(Node* head){
    operations op;
    if(head==NULL) { return NULL; }
    Node* mid=op.midElement(head);
    Node* head2=mid->next;
    mid->next=NULL;
    head2=op.reverseList(head2);
    Node* ptr=head;
    Node* result=head;
    head=head->next;
    bool flag=false;
    while(head||head2){
        if((head2!=NULL&&!flag)||(head==NULL)){
            ptr->next=head2;
            head2=head2->next;
            flag=true;
            ptr=ptr->next;
        }
        else{
            ptr->next=head;
            head=head->next;
            flag=false;
            ptr=ptr->next;
        }
    }
    delete head;
    return result;
}   

Node* operations::add2Numbers(Node* head1, Node* head2){
    if(!head1) { return head2;}
    if(!head2) { return head1;}
    Node* head=new Node(0);
    Node* curr=head;
    int carry=0;
    while(head1||head2){
        int sum=carry;
        if(head1){
           sum+=head1->data;
           head1=head1->next;
        }
        if(head2){
           sum+=head2->data;
           head2=head2->next;
        }
        curr->next=new Node(sum%10);
        carry=sum/10;
    }
    if (carry)
        curr->next=new Node(carry);
    return head; 
}

Node* operations::rotateRight(Node* head, int k){
    if(!head||!head->next) {return head;}
    Node* rotateStart=head;
    Node* rotateEnd=head;
    while(k-->0){
        rotateEnd=rotateEnd->next;
        if(!rotateEnd)
            rotateEnd=head;
    }
    if(rotateStart==rotateEnd)
        return head;
    while(rotateEnd->next){
        rotateEnd=rotateEnd->next;
        rotateStart=rotateStart->next;
    }
    Node* result = rotateStart->next;
    rotateEnd->next=head;
    rotateStart->next=NULL;
    return result;
}