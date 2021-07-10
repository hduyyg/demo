#include<cstdio>
#include<algorithm>
#define maxn (100+10)
using namespace std;

int r,c;
int a[maxn][maxn],f[maxn][maxn];

void init()
{
  freopen("tyvj1004.in","r",stdin);
  freopen("tyvj1004.out","w",stdout);
}

inline int get(int i,int j)
{
  if(f[i][j]!=1)return f[i][j];  
  if(i-1>=1 && a[i-1][j]>a[i][j])f[i][j]=max(f[i][j],get(i-1,j)+1);
  if(i+1<=r && a[i+1][j]>a[i][j])f[i][j]=max(f[i][j],get(i+1,j)+1);
  if(j-1>=1 && a[i][j-1]>a[i][j])f[i][j]=max(f[i][j],get(i,j-1)+1);
  if(j+1<=c && a[i][j+1]>a[i][j])f[i][j]=max(f[i][j],get(i,j+1)+1);
  return f[i][j];
}

void work()
{
  scanf("%d%d",&r,&c);
  int i,j,k=0;
  for(i=1;i<=r;i++)
    for(j=1;j<=c;j++)
      scanf("%d",&a[i][j]),f[i][j]=1;
      
  for(i=1;i<=r;i++)
    for(j=1;j<=c;j++)
      f[i][j]=get(i,j),k=max(k,f[i][j]);
  printf("%d\n",k);    
}

int main()
{
  init();
  work();
  return 0;
}
