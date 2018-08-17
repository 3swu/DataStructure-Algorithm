/*
 * 图的邻接矩阵表示及其基本操作的实现
 * created by wulei on 17-08-2018
 * 
 */ 
#include <iostream>
#include <fstream>

using namespace std;

#define MaxVertexNum 100
typedef struct {
    char Vex[MaxVertexNum];
    int Edge[MaxVertexNum][MaxVertexNum];
    int VexNum, EdgeNum;
}MGraph;

//创建一个图
bool initGraph(MGraph &graph){
    int verNum, edgeNum;
    cout << "input vertex num:" << endl;
    cin >> verNum;
    cout << "input edge num:" << endl;
    cin >> edgeNum;
    if(verNum < 1 || verNum > 100 || edgeNum < 0){
        cout << "error" << endl;
        return false;
    }
    cout << "input vertex:" << endl;
    for(int i = 1; i <= verNum; i++)
        cin >> graph.Vex[i];
    for(int i = 1; i <= verNum; i++)
        for(int j = 1; j <= verNum; j++)
            graph.Edge[i][j] = 0;
    cout << "input edge:" << endl;
    for(int i = 0, x, y; i < edgeNum; i++){
        cin >> x >> y;
        if(x <= verNum && y <= verNum)
            graph.Edge[x][y] = 1;
        else{
            cout << "error" << endl;
            return false;
        }
    }
    graph.VexNum = verNum;
    graph.EdgeNum = edgeNum;
    return true;
}

//从文件读取图
bool initGraphByFile(MGraph &graph){
    cout << "reading MGraph.txt" << endl;
    ifstream fin("/home/wulei/桌面/ds/Graph/MGraph.txt");
    streambuf* cinbackup = cin.rdbuf(fin.rdbuf());
    bool result = initGraph(graph);
    cin.rdbuf(cinbackup);
    if(result){
        cout << "create success" << endl;
        return true;
    }
    return false;
}

//判断图G是否存在边<x, y>或(x, y)
bool adjacent(MGraph &G, int x, int y){
    if(G.Edge[x][y] == 1)
        return true;
    else
        return false;
}

//列出图G中与节点x邻接的边
void neighbors(MGraph &G, int x){
    for(int i = 1; i <= G.VexNum; i++){
        if(G.Edge[x][i] == 1)
            cout << x << " " << i << endl;
        if(G.Edge[i][x] == 1)
            cout << i << " " << x << endl;
    }
}

//在图G中插入顶点x
bool insertVertex(MGraph &G, char x){
    if(G.VexNum + 1 >= MaxVertexNum)
        return false;
    G.Vex[++G.VexNum] = x;
    return true;
}

//从图G中删除点x
bool deleteVertex(MGraph &G, char x){
    int i;
    for(i = 1; i <= G.VexNum; i++){
        if(G.Vex[i] == x)
            break;
    }
    if(i == G.VexNum + 1)
        return false;
    G.Vex[i] = '#';
    for(int j = 1; j < G.VexNum; j++){
        G.Edge[i][j] == 0;
        G.Edge[j][i] == 0;
    }
    return true;
}

//如果边(x, y)不存在，则向图G中添加(x, y)
bool addEdge(MGraph &G, int x, int y){
    G.Edge[x][y] = 1;
    return true;
}

//如果边(x, y)存在，则从图G中删除边(x, y)
bool removeEdge(MGraph &G, int x, int y){
    G.Edge[x][y] = 0;
    return true;
}

//求图G中顶点x的第一个邻接点，若有则返回的顶点好，如果没有则返回-1
int firstNeighbor(MGraph &G, int x){
    int i;
    for(i = 1; i < G.VexNum; i++){
        if(G.Edge[x][i] == 1)
            break;
    }
    if(i == G.VexNum + 1)
        return -1;
    return i;
}

//假设图G中顶点y是顶点x的第一个临界点，返回除y之外顶点的下一个邻接点的顶点号，若y是x的最后一个邻接点，返回-1
int nextNeighbor(MGraph &G, int x, int y){
    int i;
    for(i = y + 1; i <= G.VexNum; i++){
        if(G.Edge[x][i] == 1)
            break;
    }
    if(i == G.VexNum + 1)
        return -1;
    return i;
}

//获取图G中边(x, y)的权值
int getEdgeValue(MGraph &G, int x, int y){
    return G.Edge[x][y];
}

//设置图G中边(x, y)的权值
void setEdgeValue(MGraph &G, int x, int y, int v){
    G.Edge[x][y] = v;
}
