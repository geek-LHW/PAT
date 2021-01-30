#include<iostream>
#include<vector>
#include<queue>
using namespace std;

const int MAXN = 110;//最大结点数
struct node{
    int layer;//记录层号
    vector<int> child;
}Node[MAXN];
int Num[MAXN] = {0};//统计叶子结点的数量

//队列实现BFS
void BFS(int root){
    queue<int> Q;
    Q.push(root);//将根节点入队
    Node[root].layer = 0;//记根结点的层号为0
    while(!Q.empty()){
        int front = Q.front();//取出队首元素
        Q.pop();//队首元素出队
        //如果是叶子结点
        if(Node[front].child.size()==0){
            int index = Node[front].layer; 
            Num[index] += 1; //累加
            continue;
        }
        for (int i = 0; i < Node[front].child.size();i++){
            int child = Node[front].child[i];//当前结点的第i个子结点的编号
            // 子结点层号为当前结点层号加1
            Node[child].layer = Node[front].layer + 1;
            Q.push(child);//将当前结点的所有子结点入队
        }
    }
}



int main(){

    int N, M;//结点数量，非叶子结点数量
    scanf("%d%d",&N,&M);
    //建树
    for (int i = 0; i < M;i++){
        int id, k, child;
        scanf("%d%d",&id,&k);//结点编号，孩子数量
        for (int j = 0; j < k;j++){
            scanf("%d", &child);
            Node[id].child.push_back(child);//child为结点id的孩子
        }
    }
    BFS(1);
    printf("%d",Num[0]);
    for (int i = 1; i <= Node[N].layer;i++){
        printf(" %d", Num[i]);
    }
    return 0;

}