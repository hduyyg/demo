#include<cstdio>
#include<algorithm>
#define maxn1 (100+10)
#define maxn2 (50+3+10)
using namespace std;

int n,m,t[maxn1],f[maxn1][maxn2];

void init()
{
  freopen("chop.in","r",stdin);
  freopen("chop.out","w",stdout);
}

void readdata()
{
   scanf("%d%d",&n,&m),m+=3;
   if(n<m*2)printf("%d\n",-1),exit(0);
   
   int i;
   for(i=1;i<=n;i++)scanf("%d",&t[i]);
   sort(t+1,t+n+1);
   for(i=2;i<=n;i++)f[i][60]=(t[i]-t[i-1])*(t[i]-t[i-1]);
   for(i=1;i<=m;i++)f[2*i][i]=f[2*i-2][i-1]+f[2*i][60];
}

void work()
{
  int i,j;
  for(j=1;j<=m;j++)
    for(i=2*j+1;i<=n;i++)
      f[i][j]=min(f[i-1][j],f[i-2][j-1]+f[i][60]);
  printf("%d\n",f[n][m]);    
}

int main()
{
  init();
  readdata();
  work();
  return 0;
}
