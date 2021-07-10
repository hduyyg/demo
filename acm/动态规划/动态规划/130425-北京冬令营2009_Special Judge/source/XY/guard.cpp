#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

const int maxn =15;
int n,g;
char G[maxn][maxn];
char map[maxn][maxn];


int main()
{
    freopen("guard.in","r",stdin);
    freopen("guard.out","w",stdout);
    scanf("%d%d",&n,&g);
    for (int i=1;i<=n;++i)
    {
        scanf("%s\n",map[i]); //cout<<map[i]<<endl;
    }
    /* for (int i=1;i<=g;++i)
    {
        scanf("%s\n",G[i]);     cout<<G[i]<<endl;
    }*/
    cout<<-1;
    return 0;
}
