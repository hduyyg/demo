#include<cstdio>
#include<algorithm>
#define maxn (100+10)
using namespace std;

int n,a[maxn*2];
long long f[maxn*2][maxn];

void init()
{
  freopen("energy.in","r",stdin);
  freopen("energy.out","w",stdout);
}

void work()
{
  scanf("%d",&n);     int i,j,k,x=2*n;
  for(i=1;i<=n;i++)scanf("%d",&a[i]),a[i+n]=a[i];

  for(j=2;j<=n;j++)
    for(i=1;i+j<=x;i++)
	  for(k=1;k<j;k++)
	    f[i][j]=max(f[i][j],f[i][k]+f[i+k][j-k]+a[i]*a[i+k]*a[i+j]);  
  	    
  long long ans=0;
  for(i=1;i<=n;i++)ans=max(ans,f[i][n]);	
  printf("%I64d\n",ans);   
}

int main()
{
  init();
  work();
  return 0;
}
