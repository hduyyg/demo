#include<cstdio>
#include<algorithm>
#define maxn (8+5)
using namespace std;

int n,a[maxn][maxn],f[maxn][maxn];

void init()
{
  freopen("grid.in","r",stdin);
  freopen("grid.out","w",stdout);
}

void readdata()
{
  int i,j,k;
  scanf("%d%d%d%d",&n,&i,&j,&k);
  while(i!=0)a[i][j]=k,scanf("%d%d%d",&i,&j,&k);
}

void work()
{
  int i,j,k,k1,k2;    f[1][1]=a[1][1];
  for(k=3;k<=n*2;k++)
    for(i=k-1;i>=1;i--)
      {
	      k1=max(f[i][i],f[i][i-1]);
	      k2=max(f[i-1][i],f[i-1][i-1]);
	      f[i][i]=max(k1,k2)+a[i][k-i];

	  for(j=i-1;j>=1;j--)
	    {
	      k1=max(f[i][j],f[i][j-1]);
	      k2=max(f[i-1][j],f[i-1][j-1]);
	      f[i][j]=max(k1,k2)+a[i][k-i]+a[j][k-j];
	      f[j][i]=f[i][j];
	    }
	  }
  printf("%d\n",f[n][n]);	    
}

int main()
{
  init();
  readdata();
  work();
  return 0;
}
