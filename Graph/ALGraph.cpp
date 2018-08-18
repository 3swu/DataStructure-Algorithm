/*
 * 图的邻接表表示及基本操作实现
 * created by wulei on 17-08-2018
 *
 */ 
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

#define MaxVertexNum 100
typedef struct ArcNode{
    int adjvex;             //弧指向的顶点号
    struct ArcNode* next;   //指向下一个弧结点
    int info;               //权值
}ArcNode;
typedef struct VNode{
    char data;              //顶点信息
    ArcNode* first;         //指向第一条弧结点
}VNode;
typedef struct ALGraph{
    VNode vertices[MaxVertexNum];         //邻接表
    int VexNum, ArcNum;     //顶点数和弧数
}ALGraph;

//创建图
bool initGraph(ALGraph &graph){
    int vexNum, edgeNum;
    cout << "input vertex num and edge num" << endl;
    cin >> vexNum >> edgeNum;
    if(vexNum < 1 || vexNum > 100 || edgeNum < 0){
        cout << "error" << endl;
        return false;
    }
    cout << "input vertex:" << endl;
    for(int i = 1; i <= vexNum; i++){
        cin >> graph.vertices[i].data;
        graph.vertices[i].first = NULL;
    }
    cout << "input edge:" << endl;
    for(int i = 1, x, y; i <= edgeNum; i++){
        cin >> x >> y;
        if(x <= vexNum && y <= vexNum){
            ArcNode* node = (ArcNode*) malloc (sizeof(ArcNode));
            node->next = graph.vertices[x].first;
            graph.vertices[x].first =node;
            node->adjvex = y;
            node->info = 0;
        }
        else{
            cout <<  "error" << endl;
            return false;
        }
    }
    graph.VexNum = vexNum;
    graph.ArcNum = edgeNum;
    return true;
}

//从文件读取图
bool initGraphByFile(ALGraph &graph){
    cout << "reading ALGraph.txt" << endl;
    ifstream fin("/home/wulei/桌面/ds/Graph/ALGraph.txt");
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
bool adjacent(ALGraph &G, int x, int y){
    ArcNode* p;
    for(p = G.vertices[x].first; p != NULL; p = p->next)
        if(p->adjvex = y)
            return true;
    return false;
}

//列出图G中与节点x邻接的边
void neighbors(ALGraph &G, int x){
    ArcNode* p;
    for(int i = 1; i <= G.VexNum; i++)
        for(p = G.vertices[i].first; p != NULL; p = p->next)
            if(i == x)
                cout << x << " " << p->adjvex << endl;
            else if(p->adjvex == x)
                cout << i << " " << x << endl;
}

//在图G中插入顶点x
bool insertVertex(ALGraph &G, char x){
    if(G.VexNum + 1 >= MaxVertexNum)
        return false;
    G.vertices[++G.VexNum].data = x;
    G.vertices[G.VexNum].first = NULL;
    return true;
}

//从图G中删除点x
bool deleteVertex(ALGraph &G, char x){
    int i;
    for(i = 1; i <= G.VexNum; i++){
        if(G.vertices[i].data == x)
            break;
    }
    if(i == G.VexNum + 1)
        return false;
    ArcNode* p, * pr;
    for(p = G.vertices[i].first, pr = p->next; pr != NULL; p = pr, pr = pr->next, G.ArcNum--)
        free(p);
    G.vertices[i].data = '#';
    G.vertices[i].first = NULL;
    G.VexNum--;
    return true;
}

//如果边(x, y)不存在，则向图G中添加(x, y)
bool addEdge(ALGraph &G, int x, int y){
    ArcNode* p;
    for(p = G.vertices[x].first; p != NULL; p = p->next)
        if(p->adjvex == y)
            return false;
    p = (ArcNode*) malloc (sizeof(ArcNode));
    p->adjvex = y;
    p->next = G.vertices[x].first;
    G.vertices[x].first = p;
    return true;
}

//如果边(x, y)存在，则从图G中删除边(x, y)
bool removeEdge(ALGraph &G, int x, int y){
    ArcNode* p, * pl;
    for(pl = G.vertices[x].first, p = pl->next; p != NULL; pl = p, p = p->next){
        if(pl->adjvex == y){
            G.vertices[x].first = pl->next;
            free(pl);
            G.ArcNum--;
            return true;
        }
        if(p->adjvex == y){
            pl->next = p->next;
            free(p);
            G.ArcNum--;
            return true;
        }
    }
    return false;
}

//求图G中顶点x的第一个邻接点，若有则返回的顶点好，如果没有则返回-1
int firstNeighbor(ALGraph &G, int x){
    if(G.vertices[x].first == NULL)
        return -1;
    return G.vertices[x].first->adjvex;
}

//假设图G中顶点y是顶点x的第一个临界点，返回除y之外顶点的下一个邻接点的顶点号，若y是x的最后一个邻接点，返回-1
int nextNeighbor(ALGraph &G, int x, int y){
    ArcNode* p;
    for(p = G.vertices[x].first; p != NULL; p = p->next)
        if(p->adjvex == y)
            return p->next == NULL ? -1 : p->next->adjvex;
    return -1;
}

//获取图G中边(x, y)的权值
int getEdgeValue(ALGraph &G, int x, int y){
    ArcNode* p;
    for(p = G.vertices[x].first; p != NULL; p = p->next)
        if(p->adjvex == y)
            return p->info;
    return -1;
}

//设置图G中边(x, y)的权值
void setEdgeValue(ALGraph &G, int x, int y, int v){
    ArcNode* p;
    for(p = G.vertices[x].first; p != NULL; p = p->next)
        if(p->adjvex == y)
            p->info = v;
}