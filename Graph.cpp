#include <iostream>
#include "Graph/MGraph.cpp"

int main(){
    MGraph g;
    cout << initGraph(g) << endl;
    cout << adjacent(g, 4, 5) << endl;
    neighbors(g, 4);
    cout << insertVertex(g, 'f') << endl;
    cout << deleteVertex(g, 'c') << endl;
    cout << addEdge(g, 5, 6) << endl;
    cout << removeEdge(g, 4, 5) << endl;
    cout << firstNeighbor(g, 1) << endl;
}