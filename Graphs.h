#include <iostream>
#include <stdexcept>
#include <random>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include "LinkedLists.h"
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
typedef pair<int,int> ipair;

class adjMatrixGraph{
    int V;
    int E;
    int choice;
    bool* visited;
    pair<bool,int>** adjMatrix;
    public:
        adjMatrixGraph(int V,int choice){
            if(V<0){throw invalid_argument("Too few Vertices.");}
            this->V=V;
            this->choice=choice;
            E=0;
            visited=new bool[V];
            adjMatrix= new pair<bool,int>*[V];
            for(int i=0;i<V;i++){adjMatrix[i]=new pair<bool,int>[V];}
        }

        void clearVisited(){for(int i=0;i<V;i++){visited[i]=false;}}

        int Vertices(){return V;}
        int Edges(){return E;}
        
        void addEdge(int u,int v){
            if(!adjMatrix[u][v].first){
                E++;
                adjMatrix[u][v].first=true;
                if(choice){adjMatrix[v][u].first=true;}
            }
        }

        void addEdge(int u,int v, int weight){
            if(!adjMatrix[u][v].first){
                E++;
                adjMatrix[u][v].first=true;
                adjMatrix[u][v].second=weight;
                if(choice){
                    adjMatrix[v][u].first=true;
                    adjMatrix[v][u].second=weight;
                }
            }
        }

        void removeEdge(int u,int v){
            if(adjMatrix[u][v].first){
                E--;
                adjMatrix[u][v].first=false;
                if(choice){adjMatrix[v][u].first=false;}
            }
        }

        bool checkEdge(int u,int v){return adjMatrix[u][v].first;}
        void DFS();
        void BFS();
        void print(bool);
        void Dijkstra(int);
        void printReachSet(bool*,int*);
        void DijkstraPQ(int);
};

void adjMatrixGraph::Dijkstra(int s){
    int* dist=new int[V];
    int* path= new int[V];
    path[s]=s;
    clearVisited();
    visited[s]=true;
    for(int i=0;i<V;i++){
        if(adjMatrix[s][i].first){dist[i]=adjMatrix[s][i].second;}
        else{dist[i]=INT_MAX;}
    }
    printReachSet(visited,dist);
    for(int k=0;k<V-1;k++){
        int minIndex;
        int minDist=INT_MAX;
        for(int n=0;n<V;n++){
            if(!visited[n] && dist[n]<minDist){
               minDist=dist[n];
               minIndex=n;
            }
        }
        visited[minIndex]=true;
        for(int n=0;n<V;n++){
            if(!visited[n] && adjMatrix[minIndex][n].first){
                if(dist[minIndex] + adjMatrix[minIndex][n].second < dist[n]){
                    dist[n]=dist[minIndex] + adjMatrix[minIndex][n].second;
                    path[n]=minIndex;
                }
            }
        }
        printReachSet(visited,dist);
    }
    cout<<"Previous path of "<<s<<": "<<endl;
    for(int i=0;i<V;i++){cout<<path[i]<<" ";}
    delete[] dist;
    delete[] path;
}

void adjMatrixGraph::printReachSet(bool* visited, int* dist){
    cout<<"Visited set: ";
    for(int i=0;i<V;i++){
        if(visited[i]){cout<<i<<" ";}
    }
    cout<<endl;
    cout<<"Distances:   ";
    for(int i=0;i<V;i++){
        if(dist[i]==INT_MAX){cout<<"- ";}
        else{cout<<dist[i]<<" ";}
    }
    cout<<endl;
}

void adjMatrixGraph::DijkstraPQ(int s){
    priority_queue<ipair,vector<ipair>,greater<ipair>> pq; //creates min heap
    vector<int> dist(V,INF);
    vector<int> path(V);
    pq.push(make_pair(0,s));
    dist[s]=0;
    while(!pq.empty()){
        int u=pq.top().second;
        pq.pop();
        for(int i=0;i<V;i++){
            if(adjMatrix[u][i].first){
                int weight=adjMatrix[u][i].second;
                if(dist[i]>dist[u]+weight){dist[i]=dist[u] + weight;}
                pq.push(make_pair(dist[i],i));
                path[i]=u;
            }
        }
    }
    cout<<"Distances: "<<endl;
    for(int i=0;i<V;i++){cout<<dist[i]<<" ";}
    cout<<endl;
    cout<<"Previous path: "<<endl;
    for(int i=0;i<V;i++){cout<<path[i]<<" ";}
}

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
                if(adjMatrix[temp][i].first && !visited[i]){s.push(i);}
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
                if(adjMatrix[temp][i].first && !visited[i]){q.push(i);}
            }
        }
    }
}

void adjMatrixGraph::print(bool choice){
    cout<<"  ";
    for(int i=0;i<V;i++){cout<<i<<" ";}
    cout<<endl;
    for(int i=0;i<V;i++){
        for(int j=0; j<V;j++){
            if(j==0){cout<<i<<" ";}
            if(!choice){cout<<adjMatrix[i][j].first<<" ";}
            else{
                if(adjMatrix[i][j].first){cout<<adjMatrix[i][j].second<<" ";}
                else{cout<<"-"<<" ";}
            }
        }
        cout<<endl;
    }
}

class adjListGraph{
    int V;
    int E;
    int choice;
    int* visited;
    public:
        vector<LinkedList*> adjList;
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

class graphOperations{
    public:
       void unweightedShortestPath(adjListGraph, int);
};

void graphOperations::unweightedShortestPath(adjListGraph g,int data){
    int* dist= new int[g.Vertices()];
    int* path= new int[g.Vertices()];
    queue<int> q;
    q.push(data);
    for(int i=0;i<g.Vertices();i++){ path[i]=dist[i]=-1; }
    dist[data]=0;
    while(!q.empty()){
        int v=q.front();
        q.pop();
        for(int w=0;w<g.Vertices();w++){
            if(g.adjList[v]->find(w)){
                if(dist[w]==-1){
                    dist[w]=dist[v] + 1;
                    path[w]=v;
                    q.push(w);
                }
            }
        }
    }
    cout<<"Distance of "<<data<<": "<<endl;
    for(int i=0;i<g.Vertices();i++){cout<<dist[i]<<" ";}
    cout<<endl;
    cout<<"Previous vertex of "<<data<<": "<<endl;
    for(int i=0;i<g.Vertices();i++){cout<<path[i]<<" ";}
    cout<<endl;
    delete[] path;
    delete[] dist;
}