#include <iostream>
#include <stdexcept>
#include <random>
#include <vector>
#include "LinkedLists.h"
using namespace std;

class adjMatrixGraph{
    int V;
    int E;
    bool** adjMatrix;
    public:
        adjMatrixGraph(int V){
            if(V<0){throw invalid_argument("Too few Vertices.");}
            this->V=V;
            E=0;
            adjMatrix= new bool*[V];
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
        int Vertices(){return V;}
        int Edges(){return E;}
        void addEdge(int u,int v){
            if(!adjMatrix[u-1][v-1]){
                E++;
                adjMatrix[u-1][v-1]=true;
                adjMatrix[v-1][u-1]=true;
            }
        }

        void removeEdge(int u,int v){
            if(adjMatrix[u-1][v-1]){
                E--;
                adjMatrix[u-1][v-1]=false;
                adjMatrix[v-1][u-1]=false;
            }
        }

        bool checkEdge(int u,int v){return adjMatrix[u][v];}
        void print();


};

void adjMatrixGraph::print(){
    cout<<"  ";
    for(int i=0;i<V;i++){cout<<i+1<<" ";}
    cout<<endl;
    for(int i=0;i<V;i++){
        for(int j=0; j<V;j++){
            if(j==0){cout<<i+1<<" ";}
            cout<<adjMatrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

class adjListGraph{
    int V;
    int E;
    vector<LinkedList*> adjList;
    public:
        adjListGraph(int V){
            if(V<0){throw invalid_argument("Too few vertices.");}
            this->V=V;
            for(int i=0;i<V;i++){adjList.push_back(new LinkedList());}
        }
        int Vertices(){return V;}
        int Edges(){return E;}
        
        void validateVertex(int u){if(u<0 || u>=V){throw invalid_argument("Vertex not in valid range.");}}

        void addEdge(int u,int v){
            validateVertex(v);
            validateVertex(u);
            adjList[u]->insert(v,adjList[u]->length);
            adjList[v]->insert(u,adjList[v]->length);
            E++;
        }

        void removeEdge(int u,int v){
            validateVertex(v);
            validateVertex(u);
            adjList[u]->removeData(v);
            adjList[v]->removeData(u);
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
};


