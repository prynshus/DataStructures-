#include <iostream>
using namespace std;

class disjointSet{
    public:
        int* arr;
        int size;
        int choice;
        disjointSet(int size,int choice){
            this->size=size;
            arr=new int[size];
            this->choice=choice;
            if(!choice){
                for(int i=0;i<size;i++){arr[i]=i;}
            }
            else{
                for(int i=0;i<size;i++){arr[i]=-1;}
            }
        }
        int FIND(int);
        void UNION(int,int);
        void print();
        void printUtil(int);
        void UNIONbyRANK(int,int);
        void printarray();
};

int disjointSet::FIND(int data){
    if(data<0 || data>=size){return -1;}
    if(!choice){
      if(data==arr[data]){return data;}
    }
    else{
        if(arr[data]==-1){return data;}
    }
    return FIND(arr[data]);
}

void disjointSet::UNION(int root1,int root2){
    if(!choice){
      if(FIND(root1)==FIND(root2)){return;}
      if((root1<0 || root1>=size) || (root2<0 || root2>=size)){return;}
      arr[root1]=root2;
    }
    else{
        if(FIND(root1)==FIND(root2) && FIND(root1)!=-1){return;}
        if(arr[root2]<arr[root1]){
            arr[root1]=root2;
            arr[root2]+=arr[root1];
        }
        else{
            arr[root2]=root1;
            arr[root1]+=arr[root2];
        }
    }
}

void disjointSet::printarray(){
    for(int i=0;i<size;i++){cout<<arr[i]<<" ";}
    cout<<endl;
    for(int i=0;i<size;i++){cout<<i<<" ";}
}

void disjointSet::printUtil(int data){
    cout<<data<<" -> ";
    if(data==arr[data]){cout<<data;}
    else{ printUtil(arr[data]);}
}

void disjointSet::print(){
    for(int i=0;i<size;i++){
        printUtil(i);
        cout<<endl;
    }
}

void disjointSet::UNIONbyRANK(int root1,int root2){
    if(FIND(root1)==FIND(root2) && FIND(root1)!=-1){return;}
    if(arr[root2]<arr[root1]){arr[root1]=root2;}
    else{
        if(arr[root1]==arr[root2]){arr[root1]--;}
        arr[root2]=root1;
    }
}