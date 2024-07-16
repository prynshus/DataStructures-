#include <iostream>
#include <queue>
using namespace std;

class threadedNode{
    public:
      threadedNode* left;
      bool leftThread;
      int data;
      bool rightThread;
      threadedNode* right;
      threadedNode(int data){
        left=NULL;
        leftThread=true;
        this->data=data;
        rightThread=true;
        right=NULL;
      }
      bool getLeftThread(){return leftThread;}
      bool getRightThread(){return rightThread;}
      void setLeftThread(bool tag){leftThread=tag;}
      void setRightThread(bool tag){rightThread=tag;}
};

class threadedTree{
    public:
        threadedNode* root;
        threadedTree(){root=NULL;}
        void insert(int);
        threadedNode* inorderSuccessor(threadedNode*);
        threadedNode* preorderSuccessor(threadedNode*);
        void print();
};

void threadedTree::insert(int data){
    threadedNode* newNode= new threadedNode(data);
    if(!root){
        root=newNode;
        return;
    }
    threadedNode* curr=root;
    threadedNode* parent=NULL;
    while(curr){
        parent=curr;
        if(data<parent->data){
            if(!curr->leftThread){curr=curr->left;}
            else{break;}
        }
        else{
            if(!curr->rightThread){curr=curr->right;}
            else{break;}
        }
    }
    if(data<parent->data){
        newNode->right=parent;
        parent->left=newNode;
        parent->setLeftThread(false);
        newNode->left=parent->right;
    }
    else{
        newNode->right=parent->right;
        newNode->left=parent;
        parent->setRightThread(false);
        parent->right=newNode;
    }
}

threadedNode* threadedTree::inorderSuccessor(threadedNode* p){
    if(p->rightThread){return p->right;}
    threadedNode* temp=p->right;
    while(temp->leftThread){temp=temp->left;}
    return temp;
}

void threadedTree::print(){
    if(!root){return;}
    queue<threadedNode*> q;
    q.push(root);
    while(!q.empty()){
        int size=q.size();
        for(int i=0;i<size;i++){
          threadedNode* temp=q.front();
          q.pop();
          if(temp){
             cout<<temp->data<<" ";
             if(!temp->leftThread){q.push(temp->left);}
             if(!temp->rightThread){q.push(temp->right);}
            } 
        }
        cout<<endl;
    }
}

class AVLTreeNode{
    public:
      int data;
      int height;
      AVLTreeNode* left;
      AVLTreeNode* right;
      AVLTreeNode(int data){
         this->data=data;
         left=NULL;
         right=NULL;
         height=0;
        }
       void setHeight(int val){height=val;}
};

class AVLTree{
    public:
      AVLTreeNode* root;
      AVLTree(){root=NULL;}
      int height();
      AVLTreeNode* LLrotation(AVLTreeNode*);
      AVLTreeNode* RRrotation(AVLTreeNode*);
      AVLTreeNode* LRrotation(AVLTreeNode*);
      AVLTreeNode* RLrotation(AVLTreeNode*);
      AVLTreeNode* insert(AVLTreeNode*,int);
      void print();
};

AVLTreeNode* AVLTree::LLrotation(AVLTreeNode* X){
    AVLTreeNode* W=X->left;
    X->left=W->right;
    W->right=X;
    X->setHeight(max(X->left->height,X->right->height) +1);
    W->setHeight(max(W->left->height,X->height)+1);
    return W;
}

AVLTreeNode* AVLTree::RRrotation(AVLTreeNode* X){
    AVLTreeNode* W=X->right;
    X->right=W->left;
    W->left=X;
    X->setHeight(max(X->left->height,X->right->height)+1);
    W->setHeight(max(X->height,W->right->height)+1);
    return W;
}

AVLTreeNode* AVLTree::LRrotation(AVLTreeNode* X){
    X->left=RRrotation(X->left);
    return LLrotation(X);
}

AVLTreeNode* AVLTree::RLrotation(AVLTreeNode* X){
    X->right=LLrotation(X->right);
    return RRrotation(X);
}

int AVLTree::height(){
    if(!root){return -1;}
    return root->height;
}

AVLTreeNode* AVLTree::insert(AVLTreeNode* root, int data){
    if(!root){
        root=new AVLTreeNode(data);
        return root;
    }
    else if(data<root->data){
        if(root->left){root->left=insert(root->left,data);}
        else{root->left= new AVLTreeNode(data);}
        if(root->left && root->left->height - root->right->height ==2){
            if(data<root->left->data){root=LLrotation(root);}
            else{root=LRrotation(root);}
        }
    }
    else if(data>root->data){
        if(root->right){root->right=insert(root->right,data);}
        else{root->right=new AVLTreeNode(data);}
        if(root->right && root->right->height - root->left->height ==2){
            if(data<root->right->data){root=RRrotation(root);}
            else{root=RLrotation(root);}
        }
    }
    root->setHeight(max(root->left->height,root->right->height)+1);
    return root;
}

void AVLTree::print(){
    if(!root){return;}
    queue<AVLTreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int size=q.size();
        for(int i=0;i<size;i++){
            AVLTreeNode* temp=q.front();
            q.pop();
            if(temp){
                cout<<temp->data<<" ";
                if(temp->left){q.push(temp->left);}
                if(temp->right){q.push(temp->right);}
            }
        }
        cout<<endl;
    }
}