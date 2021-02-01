#include<iostream>
#include<vector>
using namespace std;
const int MAXN = 1010;//顾客量最大值
struct job{
    int id;//编号
    int start_time=100000000;//开始时间
    int end_time;//结束时间
    int run_time;//运行时间
} customers[MAXN];

vector<job> Que[22];//20个窗口队列加一个等待队列
//N是窗口数，M是每个窗口队列最大容纳数，
//K是顾客数量，Q是顾客查询数量
int N, M, K, Q;

void fun(){
    //首先计算黄线内顾客的开始时间和结束时间
    for (int i = 1; i <=N;i++){
        Que[i][0].start_time = 480;//每个窗口一开始都是从480分开始
        Que[i][0].end_time = 480+Que[i][0].run_time;
        int id = Que[i][0].id;
        customers[id].start_time = Que[i][0].start_time;
        customers[id].end_time = Que[i][0].end_time;
        for (int j = 1; j < Que[i].size();j++){
            Que[i][j].start_time = Que[i][j - 1].end_time;
            Que[i][j].end_time = Que[i][j].start_time + Que[i][j].run_time;
            int id = Que[i][j].id;
            customers[id].start_time = Que[i][j].start_time;
            customers[id].end_time = Que[i][j].end_time;
        }
    }
    //模拟时间的流转
    for (int current_time = 480; current_time <= 1020;current_time++){
        int flag = false;//标志
        int num = 0;//空位

        for (int i = 1; i <= N;i++){
                if(Que[i][0].end_time == current_time){
                    Que[i].erase(Que[i].begin());//移出队列
                    flag = true;
                    num++;
                }
        }
        //如果有空位
        if(flag){
            for (int i = 0; i < num;i++){
                //如果黄线外没人等待
                if(Que[21].size()==0)
                    break;
                int minsize = 1000000000;//最小的窗口队列
                int index = -1;//初始下标为一号窗口
                for (int j = 1; j <= N;j++){
                    if(Que[j].size()<minsize){
                    minsize = Que[j].size();
                    index = j;
                    }
                }
                Que[index].push_back(Que[21][0]);   
                Que[21].erase(Que[21].begin());
                if(Que[index].size()==1)
                    Que[index][minsize].start_time = current_time;
                else{
                    Que[index][minsize].start_time = Que[index][minsize - 1].end_time;
                }
                Que[index][minsize].end_time = Que[index][minsize].start_time + Que[index][minsize].run_time;
                int id = Que[index][minsize].id;
                customers[id].start_time = Que[index][minsize].start_time;
                customers[id].end_time = Que[index][minsize].end_time;
            }
        }
    }
}


int main(){
    scanf("%d%d%d%d", &N, &M, &K, &Q);
    for (int i = 1; i <= K;i++){
        customers[i].id = i;
        scanf("%d", &customers[i].run_time);
    }
    int limit = N * M;//限制数
    for (int i = 1; i <=N;i++){
        for (int j = i; j <= limit;){
            Que[i].push_back(customers[j]);
            j +=N;
        }
    }
    for (int i = limit + 1; i <= K;i++){
        Que[21].push_back(customers[i]);
    }
    fun();//进行调度
    for (int i = 1; i <= Q;i++){
        int index;
        scanf("%d", &index);
        if(customers[index].start_time<1020){
            int hour = customers[index].end_time / 60;
            int min = customers[index].end_time % 60;
            printf("%02d:%02d\n", hour, min);
        }
        else{
            printf("Sorry\n");
        }
    }
    return 0;
}