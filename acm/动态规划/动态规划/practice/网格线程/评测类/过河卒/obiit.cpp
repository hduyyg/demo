//所有坐标+2，起点坐标（2,2） 
#include<cstdio>
#define maxn (20+10)
using namespace std;

int n,m,a,b;
int s[maxn][maxn];
bool f[maxn][maxn];

void init()
{
  freopen("obiit.in","r",stdin);
  freopen("obiit.out","w",stdout);
}

void readdata()
{
  scanf("%d%d%d%d",&n,&m,&a,&b);
  n+=2,m+=2,a+=2,b+=2;
  f[a][b]=1;     s[2][2]=1;
  f[a+2][b+1]=f[a+2][b-1]=1;
  f[a+1][b+2]=f[a+1][b-2]=1;
  f[a-2][b+1]=f[a-2][b-1]=1;
  f[a-1][b+2]=f[a-1][b-2]=1;
}

void work()
{
  int x,y;
  for(x=2;x<=n;x++)
    for(y=2;y<=m;y++)
      {
      	if(f[x][y])continue;
        if(!f[x][y+1])s[x][y+1]+=s[x][y];	
        if(!f[x+1][y])s[x+1][y]+=s[x][y];
      }
  printf("%d\n",s[n][m]);
}

int main()
{
  init();
  readdata();
  work();
  return 0;
}
