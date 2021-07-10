#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
#define fi first
#define se second
#define inf 0xfffffff
#define maxn 3333
#define PII pair<int, int>
int n,m,k,x,y,e,st[maxn],ed[maxn],val[maxn],dp[maxn][maxn],sum[maxn];  //sum[i]记录i为根的子树中叶子节点的个数，dp[i][j]表示以i为根的子树中选取了j个叶子节点的最大收益
PII edge[maxn];       //用边集数组（前向星）edge来存边

bool cmp(PII a, PII b){
    return sum[a.fi]>sum[b.fi];
}

void dfs(int x){
    if (x>n-m){                 //叶子节点x
        sum[x]=1;
        dp[x][1]=val[x];
        return;
    }

    for (int i=st[x]; i<ed[x]; i++) dfs(edge[i].fi); //先计算x的所有孩子的答案

    sort(&edge[st[x]],&edge[ed[x]],cmp);             //按照孩子中叶子节点的大小降序排序

    dp[x][0]=0;
    for (int i=1; i<=sum[edge[st[x]].fi]; i++)       //排序后第一个孩子的答案-x到它的费用 就是x的初始答案
        dp[x][i]=max(dp[x][i],dp[edge[st[x]].fi][i]-edge[st[x]].se);
    
    sum[x]=sum[edge[st[x]].fi];
    for (int i=st[x]+1; i<ed[x] && (sum[x]+=sum[edge[i].fi]); i++)  //对于剩下的每个孩子，进行分组背包
        for (int j=sum[x]; j; j--)
            for (int k=1; k<=j && k<=sum[edge[i].fi]; k++)
                dp[x][j]=max(dp[x][j],dp[x][j-k]+dp[edge[i].fi][k]-edge[i].se);

}

int main(){
    freopen("tele.in","r",stdin);
    freopen("tele.out","w",stdout);
    scanf("%d%d",&n,&m);
    for (int i=1; i<=n-m; i++){
        scanf("%d",&k);
        st[i]=e;
        for (int j=0; j<k; j++){   //读入边，用前向星储存
            scanf("%d%d",&x,&y);
            edge[e].fi=x;
            edge[e++].se=y;
        }
        ed[i]=e;
    }
    for (int i=n-m+1; i<=n; i++) scanf("%d",&val[i]);
    for (int i=0; i<=n; i++)
        for (int j=0; j<=m; j++)
            dp[i][j]=-inf;
            
    dfs(1);                       //按照DFS的顺序做树上的背包
    for (int i=m; i+1; i--)
        if (dp[1][i]>=0){
            printf("%d\n",i);
            break;
        }
    return 0;
}