#include<cstdio>
#include<algorithm>
#define maxn (100+10)
using namespace std;

int n;
double a[maxn],f[maxn][3];

void init()
{
  freopen("dollars.in","r",stdin);
  freopen("dollars.out","w",stdout);
}

void work()
{
  int i,j,k;
  scanf("%d",&n);
  for(i=1;i<=n;i++)scanf("%lf",&a[i]);
  f[0][0]=100,f[0][1]=0;
  for(i=1;i<=n;i++)
    {
      f[i][0]=max(f[i-1][0],f[i-1][1]*100/a[i]);
      f[i][1]=max(f[i-1][1],f[i-1][0]*a[i]/100);
	}
  printf("%.2lf\n",f[n][0]);	
}

int main()
{
  init();
  work();
  return 0;
}
