#include <bits/stdc++.h>
using namespace std;

// EK算法的邻接矩阵版本
class EdmondsKarp {
public:
    vector<vector<int>> G; // 邻接矩阵
    vector<int> pre; // 前驱记录
    int vertices_num;

    EdmondsKarp(int n) {
        this->vertices_num = n;
        G.resize(n, vector<int>(n, 0));
        pre.resize(n);
    }

    void addEdge(int x, int y, int c) {
        G[x][y] += c;
    }

    int computeMaxFlow(int src, int dst) {
        int flow = 0, d;
        while (bfs(src, dst)) {
            d = INT_MAX;
            for (int i = dst; i != src; i = pre[i])
                d = min(d, G[pre[i]][i]);
            for (int i = dst; i != src; i = pre[i]) {
                G[pre[i]][i] -= d;
                G[i][pre[i]] += d;
            }
            flow += d;
        }
        return flow;
    }

private:
    bool bfs(int src, int dst) {
        fill(pre.begin(), pre.end(), -1);
        queue<int> q;
        q.push(src);
        while (!q.empty()) {
            int t = q.front(); q.pop();
            for (int i = 0; i < this->vertices_num; i++) {
                if (G[t][i] != 0 && pre[i] == -1) { // pre也充当vis来用
                    pre[i] = t;
                    if (i == dst) return true;
                    q.push(i);
                }
            }
        }
        return false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    unordered_map<string, int> nameDict;
    string src, dst, x, y;
    int m, c, num = 0;
    EdmondsKarp ek(1005);
    cin >> src >> dst >> m;
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> c;
        if (nameDict.find(x) == nameDict.end()) nameDict[x] = num++;
        if (nameDict.find(y) == nameDict.end()) nameDict[y] = num++;
        ek.addEdge(nameDict[x], nameDict[y], c);
    }
    cout << ek.computeMaxFlow(nameDict[src], nameDict[dst]);
    return 0;
}