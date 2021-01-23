#include<iostream>
#include<cstring>
using namespace std;

const int MAXN = 500; //最大顶点数
const int INF = 1000000000;//无穷大
//访问数组
bool vis[MAXN] = {false};
//领接矩阵
int G[MAXN][MAXN];
// m为 顶点数，n为边数，st为起点，ed为终点
int m, n, st, ed;
//物资
int weight[MAXN] = {0};
//d[u]记录起点到u的距离
//w[u]记录起点到u所携带的物资
//num记录最短路径数量
int d[MAXN], w[MAXN], num[MAXN];


void Dijkstra(int s){
    fill(d, d + m, INF);
    memset(w, 0, sizeof(w));
    memset(num, 0, sizeof(num));
    d[s] = 0;
    w[s] = weight[s];
    num[s] = 1;
    for (int i = 0; i < m; i++)
    {
        //u使d[u]最小，min存放该最小的d[u]
        int u = -1,min = INF;
        //找到未访问顶点中d[u]最小的
        for (int j = 0; j < m;j++){
            if( vis[j]==false && d[j]<min){
                u = j;
                min = d[j];
            }
        }
        //找不到小于INF的d[u],说明剩下的顶点和起点s
        if(u==-1)
            return;
        vis[u] = true;//标记u为已访问
        for (int v = 0; v < m;v++){
            if(vis[v]==false && G[u][v]!=INF){
                if(d[u]+G[u][v] < d[v]){
                    d[v] = d[u] + G[u][v];//覆盖d[v]
                    w[v] = w[u] + weight[v];//覆盖w[v]
                    num[v] = num[u];//覆盖num[v]
                }
                //找到一条相同长度的路径
                else if(d[u]+G[u][v] ==d[v]){
                    if(w[u]+weight[v] > w[v]){
                        w[v] = w[u] + weight[v];
                    }
                    num[v] += num[u];
                }
            }
        }
    }
}


int main(){
    scanf("%d%d%d%d", &m, &n, &st, &ed);
    for (int i = 0; i < m;i++){
        scanf("%d", &weight[i]);
    }
    fill(G[0], G[0] + MAXN*MAXN , INF);//初始化
    int x, y, z;
    for (int i = 0; i < n;i++){
        scanf("%d%d%d", &x, &y, &z);
        G[x][y] = z;//读入边权
        G[y][x] = z;//无向边
    }
    Dijkstra(st);//算法入口
    printf("%d %d", num[ed], w[ed]);
    return 0;
}