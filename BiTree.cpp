#include <iostream>
#include <stack>
#include <fstream>
#include <queue>

using namespace std;

//定义二叉树类型
typedef struct BitNode{
    char data;
    struct BitNode * lchild, * rchild;
}BitNode, * BiTree;

//使用前序递归建立二叉树，空链域使用‘#’代替
BiTree createBiTree(){
    char c;
    BiTree tree;
    cin >> c;
    if(c != '#'){
        tree = (BitNode*) malloc (sizeof(BitNode));
        tree->data = c;
        tree->lchild = createBiTree();
        tree->rchild = createBiTree();
        return tree;
    }
    return NULL;
}

//手动输入前序序列建立二叉树
BiTree createBiTreeMain(){
    cout << "input node value:(\'#\' for NULL)" << endl;
    BiTree T = createBiTree();
    cout << "create success" << endl;
    return T;
}

//从文件中输入前序序列建立二叉树
BiTree createBiTreeMainByFile(){
    cout << "reading BiTreeInput.txt" << endl;
    ifstream fin("BiTreeInput.txt");
    streambuf* cinbackup = cin.rdbuf(fin.rdbuf());
    BiTree T = createBiTree();
    cout << "create success" << endl;
    cin.rdbuf(cinbackup);
    return T;
}


//递归的中序遍历
void inOrderTraverse(BiTree T){
    if(T != NULL){
        inOrderTraverse(T->lchild);
        cout << T->data;
        inOrderTraverse(T->rchild);
    }
}

//递归的前序遍历
void preOrderTraverse(BiTree T){
    if(T != NULL){
        cout << T->data;
        preOrderTraverse(T->lchild);
        preOrderTraverse(T->rchild);
    }
}

//递归的后序遍历
void postOrderTraverse(BiTree T){
    if(T != NULL){
        postOrderTraverse(T->lchild);
        postOrderTraverse(T->rchild);
        cout << T->data;
    }
}

//非递归的前序遍历
void preOrderTraverse2(BiTree T){
    stack<BitNode *> s;
    BitNode* p = T;
    while(p || !s.empty()){
        if(p){
            s.push(p);
            cout << p->data;
            p = p->lchild;
        }
        else{
            p = s.top();
            s.pop();
            p = p->rchild;
        }
    }
}

//非递归的中序遍历
void inOrderTraverse2(BiTree T){
    stack<BitNode *> s;
    BitNode* p = T;
    while(p || !s.empty()){
        if(p){
            s.push(p);
            p = p->lchild;
        }
        else{
            p = s.top();
            s.pop();
            cout << p->data;
            p = p->rchild;
        }
    }
}

//非递归的后序遍历
void postOrderTraverse2(BiTree T){
    stack<BitNode *> s;
    BitNode* p = T, * r = NULL;
    while(p || !s.empty()){
        if(p){
            s.push(p);
            p = p->lchild;
        }
        else{
            p = s.top();
            if(p->rchild && p->rchild != r){
                p = p->rchild;
                s.push(p);
                p = p->lchild;
            }
            else {
                p = s.top();
                s.pop();
                cout << p->data;
                r = p;
                p = NULL;
            }
        }
    }
}

//层序遍历
void levelOrderTraverse(BiTree T){
    BitNode* p = T;
    queue<BitNode *> q;
    q.push(p);
    while(!q.empty()){
        p = q.front();
        q.pop();
        cout << p->data;
        if(p->lchild)
            q.push(p->lchild);
        if(p->rchild)
            q.push(p->rchild);
    }
}


int main(){
    BiTree T = createBiTreeMainByFile();
    preOrderTraverse(T);
    cout << endl;
    preOrderTraverse2(T);
    cout << endl;
    inOrderTraverse(T);
    cout << endl;
    inOrderTraverse2(T);
    cout << endl;
    postOrderTraverse(T);
    cout << endl;
    postOrderTraverse2(T);
    cout << endl;
    levelOrderTraverse(T);
}