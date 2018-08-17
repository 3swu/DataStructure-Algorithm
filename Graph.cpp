#include <iostream>
#include <queue>
// #include "Graph/MGraph.cpp"
#include "Graph/ALGraph.cpp"

void BFSTraverse(ALGraph &);
void BFS(ALGraph, bool*, int);
void DFSTraverse(ALGraph &);
void DFS(ALGraph, bool*, int);

void BFSTraverse(ALGraph &G){
    bool visited[G.VexNum + 1];
    for(int i = 1; i <= G.VexNum; i++)
        visited[i] = false;
    for(int i = 1; i <= G.VexNum; i++)
        if(!visited[i])
            BFS(G, visited, i);
}

void BFS(ALGraph G, bool* visited, int v){
    cout << G.vertices[v].data << endl;
    visited[v] = true;
    queue<int> q;
    q.push(v);
    while(!q.empty()){
        v = q.front();
        q.pop();
        for(int w = firstNeighbor(G, v); w >= 0; w = nextNeighbor(G, v, w))
            if(!visited[w]){
                cout << G.vertices[w].data << endl;
                visited[w] = true;
                q.push(w);
            }
    }
}

void DFSTraverse(ALGraph &G){
    bool visited[G.VexNum + 1];
    for(int i = 1; i <= G.VexNum; i++)
        visited[i] = false;
    for(int i = 1; i <= G.VexNum; i++){
        if(!visited[i])
            DFS(G, visited, i);
    }
}

void DFS(ALGraph G, bool* visited, int v){
    cout << G.vertices[v].data << endl;
    visited[v] = true;
    queue<int> q;
    q.push(v);
    while(!q.empty()){
        v = q.front();
        q.pop();
        for(int w = firstNeighbor(G, v); w >= 0; w = nextNeighbor(G, v, w))
            if(!visited[w])
                DFS(G, visited, w);
    }
}

int main(){
    ALGraph g;
    cout << initGraphByFile(g) << endl;
    BFSTraverse(g);
    DFSTraverse(g);
    cout << adjacent(g, 4, 5) << endl;
    neighbors(g, 4);
    cout << insertVertex(g, 'f') << endl;
    cout << deleteVertex(g, 'c') << endl;
    cout << addEdge(g, 5, 6) << endl;
    cout << removeEdge(g, 4, 5) << endl;
    cout << firstNeighbor(g, 1) << endl;
}