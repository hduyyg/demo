#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;
#define maxn 22222

int n,e,x,y,a[maxn],ot[maxn],ne[maxn],g[maxn],f[maxn][2];
bool v[maxn];

void dfs(int x){
    int y;
    f[x][0]=0; f[x][1]=a[x]; v[x]=1;    //初始化
    for (int yy=g[x]; yy; yy=ne[yy]){   //枚举当前节点x的所有孩子
        if (v[y=ot[yy]]) continue;      
        dfs(y);                         //先计算孩子y的答案 
        f[x][0]+=max(f[y][0],f[y][1]);  //如果x不参加，x的孩子可以参加也可以不参加（取最大值）
        f[x][1]+=f[y][0];               //如果x参加，x的孩子就一定都不能参加
    }
}

int main(){
    while (scanf("%d",&n)!=EOF) {
        e=0;
        memset(v,0,sizeof(v));
        memset(g,0,sizeof(g));
        for (int i=1; i<=n; i++) scanf("%d",a+i);
        while (scanf("%d%d",&x,&y),x+y){       //建边
            ot[++e]=x; ne[e]=g[y]; g[y]=e;
            ot[++e]=y; ne[e]=g[x]; g[x]=e;
        }
        dfs(1);                                //按DFS的顺序DP                          
        printf("%d\n",max(f[1][0],f[1][1]));   //答案为1号点参加和不参加的最大值
    }
    return 0;
}
