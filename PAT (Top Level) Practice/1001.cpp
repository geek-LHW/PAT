#include<iostream>
using namespace std;
const int MAXV = 550; //最大顶点数
const int INF = 1000000000; //设INF为一个很大的数
int n,m, G[MAXV][MAXV];//N为顶点数，M为边数
int d[MAXV], cost[MAXV];//d为顶点与集合S的最短距离
bool vis[MAXV] = {false};//标记数组  vis[i]==true 表示已访问

//最小生成树prim算法
void prim(int v){
    fill(d, d + MAXV, INF); //fill函数将整个d数组赋值为INF
    vis[v] = true; //从剩余的顶点中寻找最小生成树
    v == n ? d[1] = 0:d[v + 1] = 0;
    for (int i = 1; i <= n-1;i++){
        int u = -1, min = INF; //u 使d[u]最小，min存放该最小的d[u]
        for (int j = 1; j <= n;j++){ // 找到未访问顶点中d[u]最小的
            if(vis[j] == false && d[j] < min ){
                u = j;
                min = d[j];
            }
        }
        if ( u  == -1){
            cost[v] = INF;
        }
        vis[u] = true;//标记u为已访问
        cost[v] += d[u]; // 将与集合s距离最小的边加入最小生成树
        for (int v = 1; v <= n;v++){
            if(vis[v]==false&&G[u][v] != INF && G[u][v] < d[v]){
                d[v] = G[u][v];
            }
        }
    }
}


int main(){
    scanf("%d%d", &n, &m);
    int c1, c2, c, status;
    fill(G[0], G[0] + MAXV*MAXV, INF);
    for (int i = 1; i <= m;i++){
        scanf("%d%d%d%d", &c1, &c2, &c, &status);
        if(status){
            G[c1][c2] = G[c2][c1] = 0;
        }
        else{
            G[c1][c2] = G[c2][c1] = c;
        }
    }
    int maxCost = 0;
    for (int i = 1; i <= n;i++){
        fill(vis, vis + MAXV, false);
        prim(i);
        if(cost[i]>maxCost){
            maxCost = cost[i];
        }
    }
    if(!maxCost){
        printf("%d", 0);
    }else{
        int flag = 0;
        for (int i = 1; i <= n;i++){
            if(cost[i]==maxCost){
                printf("%s%d", flag ? " " : "", i);
			    flag = 1;
            }
        }
    }
    return 0;
}