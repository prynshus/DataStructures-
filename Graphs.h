#include <iostream>
#include <stdexcept>
#include <random>
#include <vector>
#include <queue>
#include <stack>
#include "LinkedLists.h"
using namespace std;

class adjMatrixGraph{
    int V;
    int E;
    int choice;
    int* visited;
    bool** adjMatrix;
    public:
        adjMatrixGraph(int V,int choice){
            if(V<0){throw invalid_argument("Too few Vertices.");}
            this->V=V;
            this->choice=choice;
            E=0;
            adjMatrix= new bool*[V];
            visited=new int[V];
            for(int i=0;i<V;i++){adjMatrix[i]=new bool[V];}
        }

        void EdgeCreate(int V, int E){
            if(E>(V*(V-1)/2)+V){throw invalid_argument("Too many edges.");}
            if(E<0){throw invalid_argument("Too few edges.");}
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> dis(0,V-1);
            while(this->E!=E){
                int u=dis(gen);
                int v=dis(gen);
                addEdge(u,v);
            }
        }

        void clearVisited(){for(int i=0;i<V;i++){visited[i]=0;}}

        int Vertices(){return V;}
        int Edges(){return E;}
        void addEdge(int u,int v){
            if(!adjMatrix[u][v]){
                E++;
                adjMatrix[u][v]=true;
                if(choice){adjMatrix[v][u]=true;}
            }
        }

        void removeEdge(int u,int v){
            if(adjMatrix[u][v]){
                E--;
                adjMatrix[u][v]=false;
                if(choice){adjMatrix[v][u]=false;}
            }
        }

        bool checkEdge(int u,int v){return adjMatrix[u][v];}
        void DFS();
        void BFS();
        void print();


};

void adjMatrixGraph::DFS(){
    stack<int> s;
    clearVisited();
    s.push(0);
    while(!s.empty()){
        int temp=s.top();
        s.pop();
        if(!visited[temp]){
            cout<<temp<<" ";
            visited[temp]=true;
            for(int i=0;i<V;i++){
                if(adjMatrix[temp][i] && !visited[i]){s.push(i);}
            }
        }
    }
}

void adjMatrixGraph::BFS(){
    clearVisited();
    queue<int> q;
    q.push(0);
    while(!q.empty()){
        int temp=q.front();
        q.pop();
        if(!visited[temp]){
            cout<<temp<<" ";
            visited[temp]=true;
            for(int i=0;i<V;i++){
                if(adjMatrix[temp][i] && !visited[i]){q.push(i);}
            }
        }
    }
}

void adjMatrixGraph::print(){
    cout<<"  ";
    for(int i=0;i<V;i++){cout<<i<<" ";}
    cout<<endl;
    for(int i=0;i<V;i++){
        for(int j=0; j<V;j++){
            if(j==0){cout<<i<<" ";}
            cout<<adjMatrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

class adjListGraph{
    int V;
    int E;
    int choice;
    int* visited;
    vector<LinkedList*> adjList;
    public:
        adjListGraph(int V,int choice){
            if(V<0){throw invalid_argument("Too few vertices.");}
            this->choice=choice;
            this->V=V;
            visited=new int[V];
            for(int i=0;i<V;i++){adjList.push_back(new LinkedList());}
        }
        int Vertices(){return V;}
        int Edges(){return E;}
        
        void clearVisited(){for(int i=0;i<V;i++){visited[i]=0;}}
        void validateVertex(int u){if(u<0 || u>=V){throw invalid_argument("Vertex not in valid range.");}}

        void addEdge(int u,int v){
            validateVertex(v);
            validateVertex(u);
            adjList[u]->insert(v,adjList[u]->length);
            if(choice)adjList[v]->insert(u,adjList[v]->length);
            E++;
        }

        void removeEdge(int u,int v){
            validateVertex(v);
            validateVertex(u);
            adjList[u]->removeData(v);
            if(choice)adjList[v]->removeData(u);
            E--;
        }

        int degree(int u){
            validateVertex(u);
            return adjList[u]->length;
        }
        
        void print(){
            for(int i=0;i<V;i++){
                cout<<i<<" -> ";
                if(adjList[i]->head==NULL){
                    cout<<endl;
                    continue;
                }
                adjList[i]->printList();
                cout<<endl;
            }
        }

        void DFS();
        void BFS();
};

void adjListGraph::DFS(){
    clearVisited();
    stack<int> s;
    s.push(0);
    while(!s.empty()){
        int temp=s.top();
        s.pop();
        if(!visited[temp]){
            cout<<temp<<" ";
            visited[temp]= true;
            for(int i=0;i<V;i++){if(adjList[temp]->find(i) && !visited[i]){s.push(i);}}
        }
    }
}

void adjListGraph::BFS(){
    clearVisited();
    queue<int> q;
    q.push(0);
    while(!q.empty()){
        int temp=q.front();
        q.pop();
        if(!visited[temp]){
            cout<<temp<<" ";
            visited[temp]=true;
            for(int i=0;i<V;i++){if(adjList[temp]->find(i) && !visited[i]){q.push(i);}}
        }
    }
}

