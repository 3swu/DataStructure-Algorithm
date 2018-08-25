#include <iostream>
#include <queue>
// #include "Graph/MGraph.cpp"
#include "Graph/ALGraph.cpp"
#include <stack>
#include <vector>

#define INFINITY 65535

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

void dijkstra(ALGraph &G, int v, int w){
    bool collected[G.VexNum + 1];
    for(int i = 1; i <= G.VexNum; i++)
        if(i == v)
            collected[i] = true;
        else
            collected[i] = false;
    cout << 1 << endl;

    int dist[G.VexNum + 1] = {0};
    for(int i = 1; i <= G.VexNum; i++)
        if(adjacent(G, v, i))
            dist[i] = getEdgeValue(G, v, i);
        else
            dist[i] = INFINITY;

    int path[G.VexNum + 1] = {v};
    for(int i = 1; i <= G.VexNum; i++)
        path[i] = v;

    while(true){
        int min_dist, min_dist_vex;
        vector<int> not_collected;
        for(int i = 1; i <= G.VexNum; i++)
            if(collected[i] == false)
                not_collected.push_back(i);
        if(not_collected.empty())
            break;
        min_dist = dist[not_collected.at(0)];
        min_dist_vex = not_collected.at(0);
        for(auto i : not_collected)
            if(dist[i] < min_dist){
                min_dist = dist[i];
                min_dist_vex = i;
            }

        collected[min_dist_vex] = true;
        cout << min_dist_vex << endl;
        for(int s = firstNeighbor(G, min_dist_vex); s != -1; s = nextNeighbor(G, min_dist_vex, s)){
            int edge_value = getEdgeValue(G, min_dist_vex, s);
            if(dist[min_dist_vex] + edge_value < dist[s]){
                dist[s] = dist[min_dist_vex] + edge_value;
                path[s] = min_dist_vex;
            }
        }
    }

    int i = w;
    stack<int> s;
    while(i != v){
        s.push(i);
        i = path[i];
    }
    cout << v << " ";
    while(!s.empty()){
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}

int main(){
    ALGraph g;
    cout << initGraphByFile(g) << endl;
    setEdgeValue(g, 1, 2, 5);
    setEdgeValue(g, 1, 5, 4);
    setEdgeValue(g, 2 ,3, 2);
    setEdgeValue(g, 2, 4, 9);
    setEdgeValue(g, 3, 5, 6);
    setEdgeValue(g, 4, 1, 2);
    setEdgeValue(g, 5, 4, 7);
    setEdgeValue(g, 5, 2, 6);
    setEdgeValue(g, 5, 6, 5);
    setEdgeValue(g, 6, 3, 2);
    BFSTraverse(g);
    DFSTraverse(g);
    // cout << adjacent(g, 4, 5) << endl;
    // neighbors(g, 4);
    // cout << insertVertex(g, 'f') << endl;
    // cout << deleteVertex(g, 'c') << endl;
    // cout << addEdge(g, 5, 6) << endl;
    // cout << removeEdge(g, 4, 5) << endl;
    // cout << firstNeighbor(g, 1) << endl;
    dijkstra(g, 1, 6);
}