#include <iostream>
#include <climits>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include "node.h"
using namespace std;

class BinaryTreeNode{
    public:
        int data;
        BinaryTreeNode* left;
        BinaryTreeNode* right;
        BinaryTreeNode(){
            data=INT_MIN;
            left=NULL;
            right=NULL;
        }
        BinaryTreeNode(int data){
            this->data=data;
            left=NULL;
            right=NULL;
        }
};

class BinaryTree{
    public:
        BinaryTreeNode* root;
        BinaryTree(){
            root=NULL;
        }
        void insert(int);
        void deleteDeep(BinaryTreeNode*);
        BinaryTreeNode* deleteData(int);
        void inorderRecursive(BinaryTreeNode*);
        void preorderRecursive(BinaryTreeNode*);
        void postorderRecursive(BinaryTreeNode*);
        void levelOrderTraversal();
        void printTree(BinaryTreeNode* root);
        void preorderTraversal();
        void inorderTraversal();
        void postorderTraversal();     
};

void BinaryTree::insert(int data){
    if(root==NULL){
        root = new BinaryTreeNode(data);
        return;
    }
    queue<BinaryTreeNode*> q;
    q.push(root);
    while(!q.empty()){
        BinaryTreeNode* temp=q.front();
        q.pop();
        if(temp->left==NULL){
            temp->left=new BinaryTreeNode(data);
            break;
        }
        q.push(temp->left);
        if(temp->right==NULL){
            temp->right=new BinaryTreeNode(data);
            break;
        }
        q.push(temp->right);
    }
}

void BinaryTree::deleteDeep(BinaryTreeNode* data){
    queue<BinaryTreeNode*> q;
    q.push(root);
    BinaryTreeNode* temp;
    while(!q.empty()){
        temp=q.front();
        q.pop();
        if(temp == data){
            temp=NULL;
            delete data;
            return;
        }
        if(temp->right){
            if(temp->right==data){
                temp->right =NULL;
                delete data;
                return;
            }
            else{q.push(temp->right);}
        }
        if(temp->left){
            if(temp->left==data){
                temp->left=NULL;
                delete data;
                return;
            }
            else{q.push(temp->left);}
        }
    }
}

BinaryTreeNode* BinaryTree::deleteData(int key){
    if(!root) {return NULL;}
    if(!root->left && !root->right){
        if(root->data==key){return NULL;}
        else{return root;}
    }
    queue<BinaryTreeNode*> q;
    q.push(root);
    BinaryTreeNode* temp;
    BinaryTreeNode* keyNode;
    while(!q.empty()){
        temp=q.front();
        q.pop();
        if(temp->data==key){keyNode=temp;}
        if(temp->left){q.push(temp->left);}
        if(temp->right){q.push(temp->right);}
    }
    if(keyNode){
        int x=temp->data;
        keyNode->data=x;
        deleteDeep(temp);
    }
    return root;
}

void BinaryTree::inorderRecursive(BinaryTreeNode* root){
    if(!root){return;}
    inorderRecursive(root->left);
    cout<<root->data<<" ";
    inorderRecursive(root->right);
}

void BinaryTree::preorderRecursive(BinaryTreeNode* root){
    if(!root){return;}
    cout<<root->data<<" ";
    preorderRecursive(root->left);
    preorderRecursive(root->right);
}

void BinaryTree::postorderRecursive(BinaryTreeNode* root){
    if(!root){return;}
    preorderRecursive(root->left);
    preorderRecursive(root->right);
    cout<<root->data<<" ";
}

void BinaryTree::levelOrderTraversal(){
    if(!root){return;}
    queue<BinaryTreeNode*> q;
    q.push(root);
    BinaryTreeNode* temp;
    while(!q.empty()){
        int size=q.size();
        for(int i=0;i<size;i++){
            temp=q.front();
            q.pop();
            cout<<temp->data<<" ";
            if(temp->left){q.push(temp->left);}
            if(temp->right){q.push(temp->right);}     
        }
        cout<<endl;
    }
}

void BinaryTree::preorderTraversal(){
    if(!root){return;}
    stack<BinaryTreeNode*> s;
    s.push(root);
    while(!s.empty()){
        BinaryTreeNode* temp = s.top();
        s.pop();
        if(temp){
            cout<<temp->data<<" ";
            if(temp->right){s.push(temp->right);}
            if(temp->left){s.push(temp->left);}
        }
    }
}

void BinaryTree::inorderTraversal(){
    stack<BinaryTreeNode*> s;
    bool done=false;
    BinaryTreeNode* currNode = root;
    while(!done){
        if(currNode){
            s.push(currNode);
            currNode=currNode->left;
        }
        else{
            if(s.empty()){done=true;}
            else{
                currNode=s.top();
                s.pop();
                cout<<currNode->data<<" ";
                currNode=currNode->right;
            }           
        }
    }
}

void BinaryTree::postorderTraversal(){
    if(!root){return;}
    stack<BinaryTreeNode*> s;
    BinaryTreeNode* prev=NULL;
    BinaryTreeNode* curr;
    s.push(root);
    while(!s.empty()){
        curr=s.top();
        if(prev==NULL||prev->right==curr||prev->left==curr){
            if(curr->left!=NULL)
                s.push(curr->left);
            else if(curr->right!=NULL)
                s.push(curr->right);
        }
        else if(curr->left==prev){
            if(curr->right){s.push(curr->right);}
        }
        else{
            cout<<curr->data<<" ";
            s.pop();
        }
        prev=curr;
    }
}

class BinaryTreeOperations{
    void printPathsR(BinaryTreeNode*,int path[],int);
    BinaryTreeNode* BuildTreeRecursive(vector<int>,int,int,vector<int>,int,int);
    BinaryTreeNode* BuildTreeRecursivepostorder(vector<int>,int,int,vector<int>,int,int);
    public:
        int RmaxElement(BinaryTreeNode*);
        int maxElement(BinaryTreeNode*);
        bool search(BinaryTreeNode*,int);
        bool Rsearch(BinaryTreeNode*,int);
        BinaryTreeNode* insert(BinaryTreeNode*,int);
        int Rsize(BinaryTreeNode*);
        int size(BinaryTreeNode*);
        void levelOrderReverse(BinaryTreeNode*);
        int Rheight(BinaryTreeNode*);
        int heightUsingStack(BinaryTreeNode*);
        int minHeight(BinaryTreeNode*);
        BinaryTreeNode* deepestNode(BinaryTreeNode*);
        int numberOfLeaves(BinaryTreeNode*);
        int numberOfInternalLeaves(BinaryTreeNode*);
        int numberOfHalfLeaves(BinaryTreeNode*);
        bool isomerphic(BinaryTreeNode*,BinaryTreeNode*);
        int diameter(BinaryTreeNode*);
        int maxsumLevel(BinaryTreeNode*);
        void printPaths(BinaryTreeNode*);
        bool pathSumCheck(BinaryTreeNode*,int);
        int Rsum(BinaryTreeNode*);
        int sum(BinaryTreeNode*);
        BinaryTreeNode* createMirror(BinaryTreeNode*);
        bool mirrorCheck(BinaryTreeNode*,BinaryTreeNode*);
        BinaryTreeNode* buildBinaryTreeWithPreorder(vector<int>,vector<int>);
        BinaryTreeNode* buildBinaryTreeWithPostorder(vector<int>,vector<int>);
        bool printAncestors(BinaryTreeNode*,int);
        BinaryTreeNode* RLCA(BinaryTreeNode*,BinaryTreeNode*,BinaryTreeNode*);
        void zigzagTraversal(BinaryTreeNode*);
        vector<BinaryTreeNode*> constructTrees(int,int);
        BinaryTreeNode* constructTreeWithPreorder(vector<char>,int);
        BinaryTreeNode* buildExpressionTree(vector<char>);

};

int BinaryTreeOperations::RmaxElement(BinaryTreeNode* root){
    int max=INT_MIN;
    if(root){
        int leftMax = maxElement(root->left);
        int rightMax = maxElement(root->right);
        if(leftMax>rightMax){max=leftMax;}
        else{max=rightMax;}
        if(max<root->data){max=root->data;}
    }
    return max;
}

int BinaryTreeOperations::maxElement(BinaryTreeNode* root){
    int max=INT_MIN;
    if(!root){return max;}
    queue<BinaryTreeNode*> q;
    q.push(root);
    while(!q.empty()){
        BinaryTreeNode* temp = q.front();
        q.pop();
        if(temp->data>max){max=temp->data;}
        if(temp){
           if(temp->left){q.push(temp->left);}
           if(temp->right){q.push(temp->right);}
        }
    }
    return max;
}

bool BinaryTreeOperations::Rsearch(BinaryTreeNode* root,int value){
    if(!root){return false;}
    if(root->data==value){return true;}
    return search(root->left,value) || search(root->right,value);
}

bool BinaryTreeOperations::search(BinaryTreeNode* root,int value){
    if(!root){return false;}
    queue<BinaryTreeNode*> q;
    q.push(root);
    while(!q.empty()){
        BinaryTreeNode* temp=q.front();
        q.pop();
        if(temp->data==value){return true;}
        if(temp){
            if(temp->left){q.push(temp->left);}
            if(temp->right){q.push(temp->right);}
        }
    }
    return false;
}

int BinaryTreeOperations::Rsize(BinaryTreeNode* root){
    int leftSize = root->left ==NULL?0:Rsize(root->left);
    int rightSize = root->right ==NULL?0:Rsize(root->right);
    return 1+leftSize+rightSize;
}

int BinaryTreeOperations::size(BinaryTreeNode* root){
    if(!root){return 0;}
    queue<BinaryTreeNode*> q;
    q.push(root);
    int treeSize=0;
    while(!q.empty()){
        BinaryTreeNode* temp=q.front();
        q.pop();
        if(temp){
            treeSize++;
            if(temp->left){q.push(temp->left);}
            if(temp->right){q.push(temp->right);}
        }
    }
    return treeSize;
}

void BinaryTreeOperations::levelOrderReverse(BinaryTreeNode* root){
    if(!root){return;}
    queue<BinaryTreeNode*> q;
    stack<BinaryTreeNode*> s;
    q.push(root);
    while(!q.empty()){
        BinaryTreeNode* temp=q.front();
        q.pop();
        if(temp){
            if(temp->left){q.push(temp->left);}
            if(temp->right){q.push(temp->right);}
        }
        s.push(temp);
    }
    while(!s.empty()){
        cout<<s.top()->data<<" ";
        s.pop();
    }
    cout<<endl;
}

int BinaryTreeOperations::Rheight(BinaryTreeNode* root){
    if(!root){return 0;}
    int leftHeight= Rheight(root->left);
    int rightHeight= Rheight(root->right);
    return leftHeight > rightHeight ? leftHeight +1 : rightHeight +1;
}

int BinaryTreeOperations::heightUsingStack(BinaryTreeNode* root){
    if(!root){return 0;}
    stack<BinaryTreeNode*> s;
    s.push(root);
    BinaryTreeNode* prev=NULL;
    int max=0;
    while(!s.empty()){
        BinaryTreeNode* curr = s.top();
        if(!prev || prev->left==curr || prev->right==curr){
            if(curr->left){s.push(curr->left);}
            if(curr->right){s.push(curr->right);}
        }
        else if(curr->left==prev){
            if(curr->right){s.push(curr->right);}
        }
        else{s.pop();}
        prev=curr;
        if(s.size()>max){max=s.size();}
    }
    return max;
}

int BinaryTreeOperations::minHeight(BinaryTreeNode* root){
    if(!root){return 0;}
    queue<BinaryTreeNode*> q;
    q.push(root);
    q.push(NULL);
    int count=1;
    while(!q.empty()){
        BinaryTreeNode* temp= q.front();
        q.pop();
        if(temp){
            if(!temp->left&&!temp->right){return count;}
            if(temp->left){q.push(temp->left);}
            if(temp->right){q.push(temp->right);}
        }
        else{
            if(!q.empty()){
                count++;
                q.push(NULL);
            }
        }
    }
    return count;
}

BinaryTreeNode* BinaryTreeOperations::deepestNode(BinaryTreeNode* root){
    if(!root){return NULL;}
    queue<BinaryTreeNode*> q;
    q.push(root);
    BinaryTreeNode* temp;
    while(!q.empty()){
        temp=q.front();
        q.pop();
        if(temp){
            if(temp->left){q.push(temp->left);}
            if(temp->right){q.push(temp->right);}
        }
    }
    return temp;
}

int BinaryTreeOperations::numberOfLeaves(BinaryTreeNode* root){
    if(!root){return 0;}
    queue<BinaryTreeNode*> q;
    q.push(root);
    int count=0;
    while(!q.empty()){
        BinaryTreeNode* temp=q.front();
        q.pop();
        if(temp){
            if(!temp->left && !temp->right){count++;}
            if(temp->left){q.push(temp->left);}
            if(temp->right){q.push(temp->right);}
        }
    }
    return count;
}

int BinaryTreeOperations::numberOfInternalLeaves(BinaryTreeNode* root){
    if(!root){return 0;}
    queue<BinaryTreeNode*> q;
    q.push(root);
    int count=0;
    while(!q.empty()){
        BinaryTreeNode* temp=q.front();
        q.pop();
        if(temp){
            if(temp->left && temp->right){count++;}
            if(temp->left){q.push(temp->left);}
            if(temp->right){q.push(temp->right);}
        }
    }
    return count;
}

int BinaryTreeOperations::numberOfHalfLeaves(BinaryTreeNode* root){
    if(!root){return 0;}
    queue<BinaryTreeNode*> q;
    q.push(root);
    int count=0;
    while(!q.empty()){
        BinaryTreeNode* temp=q.front();
        q.pop();
        if(temp){
            if((temp->left && !temp->right) || (!temp->left && temp->right)){count++;}
            if(temp->left){q.push(temp->left);}
            if(temp->right){q.push(temp->right);}
        }
    }
    return count;
}

bool BinaryTreeOperations::isomerphic(BinaryTreeNode* root1 ,BinaryTreeNode* root2){
    if(!root1 && !root2){return true;}
    if(!root1 || !root2){return false;}
    return isomerphic(root1->left ,root2->right) && isomerphic(root1->right, root2->left);
}

int BinaryTreeOperations::maxsumLevel(BinaryTreeNode* root){
    if(!root){return INT_MIN;}
    int max=0;
    queue<BinaryTreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int sum=0;
        int size=q.size();
        for(int i=0;i<size;i++){
            BinaryTreeNode* temp=q.front();
            q.pop();
            sum+=temp->data;
            if(temp){
                if(temp->left){q.push(temp->left);}
                if(temp->right){q.push(temp->right);}
            }
            if(sum>max){max=sum;}
        }
    }
    return max;
}

void BinaryTreeOperations::printPaths(BinaryTreeNode* root){
    int arr[1000];
    printPathsR(root,arr,0);
}

void BinaryTreeOperations::printPathsR(BinaryTreeNode* root, int arr[], int pathLen){
    if(!root){return;}
    arr[pathLen]=root->data;
    pathLen++;
    if(!root->left && !root->right){
        for(int i=0;i<pathLen;i++){cout<<arr[i]<<" ";}
        cout<<endl;
    }
    else{
        printPathsR(root->left,arr,pathLen);
        printPathsR(root->right,arr,pathLen);
    }
}

bool BinaryTreeOperations::pathSumCheck(BinaryTreeNode* root, int sum){
    if(!root){return false;}
    if(!root->left && !root->right && root->data==sum){return true;}
    return pathSumCheck(root->left,sum- root->data) || pathSumCheck(root->right, sum- root->data);
}

int BinaryTreeOperations::Rsum(BinaryTreeNode* root){
    if(!root){return 0;}
    return Rsum(root->left) + Rsum(root->right) + root->data;
}

int BinaryTreeOperations::sum(BinaryTreeNode* root){
    if(!root){return INT_MIN;}
    queue<BinaryTreeNode*> q;
    q.push(root);
    int sum=0;
    while(!q.empty()){
        BinaryTreeNode* temp= q.front();
        q.pop();
        if(temp){
            sum+=temp->data;
            if(temp->left){q.push(temp->left);}
            if(temp->right){q.push(temp->right);}
        }
    }
    return sum;
}

BinaryTreeNode* BinaryTreeOperations::createMirror(BinaryTreeNode* root){
    BinaryTreeNode* temp;
    if(root){
        createMirror(root->left);
        createMirror(root->right);
        temp=root->left;
        root->left=root->right;
        root->right=temp;
    }
    return root;
}

bool BinaryTreeOperations::mirrorCheck(BinaryTreeNode* root1,BinaryTreeNode* root2){
    if(!root1 && !root2){return true;}
    if(!root1 || !root2){return false;}
    if(root1->data!=root2->data){return false;}
    return mirrorCheck(root1->left,root2->right) && mirrorCheck(root1->right,root2->left);
}

BinaryTreeNode* BinaryTreeOperations::buildBinaryTreeWithPreorder(vector<int> preorder ,vector<int> inorder){
    if(inorder.size()==0 || inorder.size()!=preorder.size()){return NULL;}
    return BuildTreeRecursive(preorder,0,preorder.size()-1,inorder,0,inorder.size()-1);
}

BinaryTreeNode* BinaryTreeOperations::BuildTreeRecursive(vector<int> preorder, int prestart, int preEnd, vector<int> inorder,int inStart, int inEnd){
    if(prestart>preEnd || inStart>inEnd){return NULL;}
    int data=preorder[prestart];
    BinaryTreeNode* curr= new BinaryTreeNode(data);
    int offset = inStart;
    for(;offset<inEnd;offset++){
        if(inorder[offset]==data)
           break;
    }
    curr->left = BuildTreeRecursive(preorder,prestart+1,prestart+offset-inStart,inorder,inStart,offset-1);
    curr->right= BuildTreeRecursive(preorder,prestart+offset-inStart+1,preEnd,inorder,offset+1,inEnd);
    return curr;
}

BinaryTreeNode* BinaryTreeOperations::buildBinaryTreeWithPostorder(vector<int> postorder,vector<int> inorder){
    if(inorder.size()==0 || inorder.size()!=postorder.size()){return NULL;}
    return BuildTreeRecursivepostorder(postorder,0,postorder.size()-1,inorder,0,inorder.size()-1);
}

BinaryTreeNode* BinaryTreeOperations::BuildTreeRecursivepostorder(vector<int> postorder,int postStart, int postEnd, vector<int> inorder, int inStart, int inEnd){
    if(postStart>postEnd || inStart>inEnd){return NULL;}
    int data = postorder[postEnd];
    int offset = inStart;
    BinaryTreeNode* curr=new BinaryTreeNode(data);
    for(;offset<inEnd;offset++)
        if(inorder[offset]==data){break;}
    curr->left=BuildTreeRecursivepostorder(postorder,postStart,postStart+offset-inStart-1,inorder,inStart,offset-1);
    curr->right=BuildTreeRecursivepostorder(postorder,postStart+offset-inStart,postEnd-1,inorder,offset-1,inEnd);
    return curr;
}

bool BinaryTreeOperations::printAncestors(BinaryTreeNode* root, int data){
    if(!root){return false;}
    if(root->left->data==data || root->right->data==data || printAncestors(root->left, data) || printAncestors(root->right, data)){
        cout<<root->data<<" ";
        return true;
    }
    return false;
}

BinaryTreeNode* BinaryTreeOperations::RLCA(BinaryTreeNode* root,BinaryTreeNode* a, BinaryTreeNode* b){
    if(!root){return NULL;}
    if(root->left ==a || root->right==b){return root;}
    BinaryTreeNode* left = RLCA(root->left,a,b);
    BinaryTreeNode* right = RLCA(root->right,a,b);
    if(left && right){return root;}
    else{return left!=NULL?left:right;}
}

void BinaryTreeOperations::zigzagTraversal(BinaryTreeNode* root){
    if(!root){return;}
    queue<BinaryTreeNode*> q;
    stack<BinaryTreeNode*> s;
    bool turn=1;
    q.push(root);
    while(!q.empty()){
        int size=q.size();
        for(int i=0;i<size;i++){
            BinaryTreeNode* temp=q.front();
            q.pop();
            if(turn){cout<<temp->data<<" "; }
            else{s.push(temp);}
            if(temp->left){q.push(temp->left);}
            if(temp->right){q.push(temp->right);}
        }
        if(!turn){
            while(!s.empty()){
                cout<<s.top()->data<<" ";
                s.pop();
            }
        }
        turn=!turn;
    }
}

vector<BinaryTreeNode*> BinaryTreeOperations::constructTrees(int start, int end){
    vector<BinaryTreeNode*> listOfTrees;
    if(start>end){
        listOfTrees.push_back(NULL);
        return listOfTrees;
    }
    for(int i=start;i<=end;i++){
        vector<BinaryTreeNode*> leftList=constructTrees(start,i-1);
        vector<BinaryTreeNode*> rightList=constructTrees(i+1,end);
        for(BinaryTreeNode* left: leftList){
            for(BinaryTreeNode* right: rightList){
                BinaryTreeNode* root=new BinaryTreeNode(i);
                root->left=left;
                root->right=right;
                listOfTrees.push_back(root);
            }
        }
    }
    return listOfTrees;
}

BinaryTreeNode* BinaryTreeOperations::constructTreeWithPreorder(vector<char> s, int i){
    if(i>=s.size()){return NULL;}
    BinaryTreeNode* root= new BinaryTreeNode(s[i]);
    i++;
    if(s[i-1]!='L'){
        root->left= constructTreeWithPreorder(s,i);
        root->right= constructTreeWithPreorder(s,i);
    }
    return root;
}

BinaryTreeNode* BinaryTreeOperations::buildExpressionTree(vector<char> x){
    vector<char> o = {'+','-','/','*'};
    stack<BinaryTreeNode*> s;
    for(int i=0;i<x.size();i++){
        BinaryTreeNode* newNode= new BinaryTreeNode(x[i]);
        if(count(o.begin(),o.end(),x[i])){
            BinaryTreeNode* t1=s.top();
            s.pop();
            BinaryTreeNode* t2=s.top();
            s.pop();
            newNode->right=t2;
            newNode->left=t1;
            s.push(newNode);
        }
        else{
            s.push(newNode);
        }
    }
    return s.top();
}

//Binary search tree
class binarySearchTree{
    public:
      BinaryTreeNode* root;
      binarySearchTree(){
        root=NULL;
      }
      BinaryTreeNode* Rinsert(BinaryTreeNode*,int);
      void insert(int);
      BinaryTreeNode* deleteData(BinaryTreeNode*,int);
      BinaryTreeNode* findMax(BinaryTreeNode*);
};

BinaryTreeNode* binarySearchTree::Rinsert(BinaryTreeNode* root,int data){
    if(!root){root=new BinaryTreeNode(data);}
    if(data<root->data){root->left=Rinsert(root->left,data);}
    if(data>root->data){root->right=Rinsert(root->right,data);}
    return root;
}

void binarySearchTree::insert(int data){
    if(!root){
        root=new BinaryTreeNode(data);
        return;
    }
    BinaryTreeNode* temp1=root;
    BinaryTreeNode* temp2=NULL;
    BinaryTreeNode* newNode=new BinaryTreeNode(data);
    while(temp1){
        temp2=temp1;
        if(temp1->data>data){temp1=temp1->left;}
        else{temp1=temp1->right;}
    }
    if(temp2->data>data){temp2->left=newNode;}
    else{temp2->right=newNode;}
}

BinaryTreeNode* binarySearchTree::deleteData(BinaryTreeNode* root,int data){
    if(!root){return NULL;}
    BinaryTreeNode* temp;
    if(root->data>data){root->left=deleteData(root->left,data);}
    else if(root->data<data){root->right=deleteData(root->right,data);}
    else{
        if(root->left&&root->right){
            temp=findMax(root->left);
            root->data=temp->data;
            root->left=deleteData(root->left,data);
        }
        else{
            if(root->left){
                temp=root;
                delete root;
                temp=root->left;
            }
            else if(root->right){
                temp=root;
                delete root;
                temp=root->right;
            }
            else{
                delete root;
                root=NULL;
            }
        }
    }
    return root;
}

BinaryTreeNode* binarySearchTree::findMax(BinaryTreeNode* root){
    if(!root){return NULL;}
    BinaryTreeNode* temp=root;
    while(temp->right){temp=temp->right;}
    return temp;
}

class BSTOperation{
    bool BSTutil(BinaryTreeNode*,int,int);
    BinaryTreeNode* DLL2BSTUtil(DNode*,int,int);
    BinaryTreeNode* CeilUtil(BinaryTreeNode*,int,BinaryTreeNode*);
    BinaryTreeNode* FloorUtil(BinaryTreeNode*,int,BinaryTreeNode*);
    public:
      BinaryTreeNode* LCA(BinaryTreeNode*,BinaryTreeNode*,BinaryTreeNode*);
      bool isBST(BinaryTreeNode*);
      BinaryTreeNode* DLL2BST(DNode*);
      BinaryTreeNode* Array2BST(int arr[],int,int);
      BinaryTreeNode* KthSmallest(BinaryTreeNode*,int,int&);
      BinaryTreeNode* Ceil(BinaryTreeNode*,int);
      BinaryTreeNode* Floor(BinaryTreeNode*,int);
};

BinaryTreeNode* BSTOperation::LCA(BinaryTreeNode* root,BinaryTreeNode* a, BinaryTreeNode* b){
    if(!root){return NULL;}
    if(root==a || root==b){return root;}
    if(max(a->data,b->data)<root->data){return LCA(root->left,a,b);}
    else if(min(a->data,b->data)>root->data){return LCA(root->right,a,b);}
    else{return root;}
}

bool BSTOperation::isBST(BinaryTreeNode* root){
    return BSTutil(root,INT_MIN,INT_MAX);
}

bool BSTOperation::BSTutil(BinaryTreeNode* root,int min,int max){
    if(!root){return true;}
    return (root->data<max && root->data>min && BSTutil(root->left,min,root->data) && BSTutil(root->right,root->data,max));
}

BinaryTreeNode* BSTOperation::DLL2BST(DNode* head){
    if(!head){return NULL;}
    DNode* temp=head;
    int len=0;
    while(temp){
        len++;
        temp=temp->next;
    }
    return DLL2BSTUtil(head,0,len-1);
}

BinaryTreeNode* BSTOperation::DLL2BSTUtil(DNode* head,int start,int end){
    if(start>end){return NULL;}
    int mid=start+(end-start)/2;
    BinaryTreeNode* left=DLL2BSTUtil(head,start,mid-1);
    BinaryTreeNode* root=new BinaryTreeNode(head->data);
    root->left=left;
    if(head->next){
        head->data=head->next->data;
        head->next=head->next->next;
    }
    root->right=DLL2BSTUtil(head,mid+1,end);
    return root;
}

BinaryTreeNode* BSTOperation::Array2BST(int arr[],int start,int end){
    if(start>end){return NULL;}
    BinaryTreeNode* newNode=new BinaryTreeNode();
    if(start==end){newNode->data=arr[start];}
    else{
        int mid=start+(end-start)/2;
        newNode->data=arr[mid];
        newNode->left=Array2BST(arr,start,mid-1);
        newNode->right=Array2BST(arr,mid+1,end);
    }
    return newNode;
}

BinaryTreeNode* BSTOperation::KthSmallest(BinaryTreeNode* root,int k,int& count){
    if(!root){return NULL;}
    BinaryTreeNode* left=KthSmallest(root->left,k,count);
    if(left){return left;}
    if(++count==k){return root;}
    return KthSmallest(root->right,k,count);
}

BinaryTreeNode* BSTOperation::Floor(BinaryTreeNode* root,int key){
    BinaryTreeNode* prev=NULL;
    return FloorUtil(root,key,prev);
}

BinaryTreeNode* BSTOperation::FloorUtil(BinaryTreeNode* root, int key, BinaryTreeNode* prev){
    if(!root){return NULL;}
    if(!FloorUtil(root->left,key,prev)){return NULL;}
    if(root->data==key){return root;}
    if(root->data>key){return prev;}
    prev=root;
    return FloorUtil(root->right,key,prev);
}

BinaryTreeNode* BSTOperation::Ceil(BinaryTreeNode* root,int key){
    BinaryTreeNode* prev=NULL;
    return CeilUtil(root,key,prev);
}

BinaryTreeNode* BSTOperation::CeilUtil(BinaryTreeNode* root,int key, BinaryTreeNode* prev){
    if(!root){return prev;}
    if(!CeilUtil(root->right,key,prev)){return NULL;}
    if(root->data==key){return root;}
    if(root->data<key){return prev;}
    prev=root;
    return CeilUtil(root->left,key,prev);
}