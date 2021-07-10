#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
#define maxn 11111
#define maxm 22222

int n,x,y,e,ot[maxm],len[maxm],ne[maxm],g[maxn],f[maxn][2],p[maxn][2];
bool v[maxn];

void AddEdge(int x, int y, int l){              //建边
    ot[++e]=y; len[e]=l; ne[e]=g[x]; g[x]=e;
    ot[++e]=x; len[e]=l; ne[e]=g[y]; g[y]=e;
}

void dfs(int x){                               
    v[x]=1;
    for (int yy=g[x]; yy; yy=ne[yy]){         //枚举x的每个孩子
        int y=ot[yy];
        if (!v[y]){
            dfs(y);                           //先算出孩子y的答案
            int tmp=f[y][0]+len[yy];          //计算经过y的最长路
            if (f[x][0]<tmp){                 //更新x的答案
                f[x][1]=f[x][0];
                p[x][1]=p[x][0];
                f[x][0]=tmp;
                p[x][0]=y;
            }else
            if (f[x][1]<tmp){
                f[x][1]=tmp;
                p[x][1]=y;
            }
        }
    }
}

void solve(int x){                             
    v[x]=1;
    for (int yy=g[x]; yy; yy=ne[yy]){
        int y=ot[yy];
        if (!v[y]){
            int tmp=f[x][0]+len[yy];             
            if (p[x][0]==y) tmp=f[x][1]+len[yy];  //tmp即为x为起点经过其父亲的最长路
            if (f[y][0]<tmp){                     //用tmp来更新x的最终答案
                f[y][1]=f[y][0];
                p[y][1]=p[y][0];
                f[y][0]=tmp;
                p[y][0]=y;
            }else
            if (f[y][1]<tmp){
                f[y][1]=tmp;
                p[y][1]=y;
            }
            solve(y);
        }
    }
}

int main(){
    freopen("computer.in","r",stdin);
    freopen("computer.out","w",stdout);
    while (scanf("%d",&n)!=EOF){
        e=0;
        memset(g,0,sizeof(g));
        for (int i=2; i<=n; i++){
            scanf("%d%d",&x,&y);
            AddEdge(i,x,y);
        }
        memset(v,0,sizeof(v));
        memset(f,0,sizeof(f));
        memset(p,0,sizeof(p));
        dfs(1);                        //第一遍DFS，求出x这棵子树中以x为起点的的最长路，次长路以及分别经过的孩子
        memset(v,0,sizeof(v));
        solve(1);                      //第二遍DFS，计算每个点的最终答案
        for (int i=1; i<=n; i++) printf("%d\n",f[i][0]);
    }
    return 0;
}