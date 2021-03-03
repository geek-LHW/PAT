#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn=52;
int n,lmt=0;
vector<int> dp[maxn];
struct work{int pro,cost,ddl;}wk[maxn];
void solve(){
	for(int i=0;i<=n;i++) dp[i].resize(lmt+1);
	//截止日期从小到大排序
    sort(wk+1,wk+n+1,[](const work& w1,const work& w2){return w1.ddl<w2.ddl;});
	//dp[i][j] 表示用j天的时间，在前i个项目中能获得的最大利润
    for(int i=1;i<=n;i++){
		for(int j=1;j<=lmt;j++){
			if(j>=wk[i].cost&&j<=wk[i].ddl)
				dp[i][j]=max(dp[i-1][j],dp[i-1][j-wk[i].cost]+wk[i].pro);
			else if(j<wk[i].cost) dp[i][j]=dp[i-1][j];
			else dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
		}
	}
	cout<<dp[n][lmt];
}
int main(){
//	freopen("Sakura.txt","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>wk[i].pro>>wk[i].cost>>wk[i].ddl;
		lmt=max(lmt,wk[i].ddl);
	}
	solve();
	return 0;
}