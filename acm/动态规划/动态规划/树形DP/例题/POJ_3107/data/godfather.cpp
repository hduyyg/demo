#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;
#define maxn 55555
#define maxm 111111

int e,ans,x,y,n,f[maxn],g[maxn],ne[maxm],ot[maxm],cnt[maxn];
bool v[maxn];

void AddEdge(int x, int y){                  //建边
    ot[++e]=y; ne[e]=g[x]; g[x]=e;
    ot[++e]=x; ne[e]=g[y]; g[y]=e;
}

void dfs(int x){                            
    v[x]=1; cnt[x]=1;                       //cnt[x]记录以x为根的子树的大小
    for (int yy=g[x]; yy; yy=ne[yy]){       //枚举x的每一个孩子y
        int y=ot[yy];
        if (!v[y]){
            dfs(y);                         //先计算y的答案
            cnt[x]+=cnt[y];                 
            f[x]=max(f[x],cnt[y]);          //更新最大的连通块 
        }
    }
    f[x]=max(f[x],n-cnt[x]);                //删除x后x的父亲所在的联通块的大小为n-cnt[x]，并用其更新x的答案
    ans=min(ans,f[x]);                      //统计所有f[x]的最小值
}

int main(){
    freopen("godfather.in","r",stdin);
    freopen("godfather.out","w",stdout);
    scanf("%d",&n);
    for (int i=1; i<n; i++){
        scanf("%d%d",&x,&y);
        AddEdge(x,y);
    }
    ans=n;
    dfs(1);                       //按照DFS的顺序计算每个点删除后，最大的连通块大小f[i]
    for (int i=1; i<=n; i++)
        if (f[i]==ans) printf("%d ",i);
    printf("\n");
    return 0;
}