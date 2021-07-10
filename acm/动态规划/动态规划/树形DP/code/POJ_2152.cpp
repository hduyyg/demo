#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;
#define MAX 1100
#define INF 2147483647
#define min(a,b) (a)<(b)?(a):(b)
#define max(a,b) (a)>(b)?(a):(b)

struct node {
    int v,len;
}now;
vector<node> tree[MAX];
int n,cur,best[MAX],dp[MAX][MAX];   //best[i]表示以i为根的子树的最小花费，dp[i][j]表示i依赖j的花费
int dist[MAX][MAX],limit[MAX],cost[MAX];

void Initial() {    //初始化
    int i,j;
    for (i = 0; i <= n; ++i)
        tree[i].clear(),best[i] = INF;
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j)
            dp[i][j] = INF;
}

void CountDist(int s,int pa,int dis){    //先DFS，记录每个点到其他点的距离
    dist[cur][s] = dis;
    for (int i = 0; i < tree[s].size(); ++i) {
        int v = tree[s][i].v;
        int len = tree[s][i].len;
        if (v == pa) continue;
        CountDist(v,s,dis+len);
    }
}
void Tree_DP(int s,int pa) {
    int i,j,k;
    for (i = 0; i < tree[s].size(); ++i)
        if (tree[s][i].v != pa)
            Tree_DP(tree[s][i].v,s);
    for (i = 1; i <= n; ++i)                //枚举s依赖的点i
        if (dist[s][i] <= limit[s]) {
            dp[s][i] = cost[i];
            for (j = 0; j < tree[s].size(); ++j) {      //把子树信息汇总到当前点
                int v = tree[s][j].v;
                if (v == pa) continue;
                dp[s][i] += min(dp[v][i]-cost[i],best[v]);
            }
            best[s] = min(best[s],dp[s][i]);            //状态转移方程，结果存储在best中
        }
}

int main()
{
    int i,j,k,a,b,c,t;
    scanf("%d",&t);
    while (t--) {
        scanf("%d",&n);
        Initial();
        for (i = 1; i <= n; ++i)
            scanf("%d",&cost[i]);
        for (i = 1; i <= n; ++i)
            scanf("%d",&limit[i]);
        for (i = 1; i < n; ++i) {
            scanf("%d%d%d",&a,&b,&c);
            now.v = b,now.len = c;
            tree[a].push_back(now);
            now.v = a,now.len = c;
            tree[b].push_back(now);
        }
        for (i = 1; i <= n; ++i)
            cur = i,CountDist(i,0,0);
        Tree_DP(1,0);
        printf("%d\n",best[1]);
    }
}
