#include<cstdio>
#include<algorithm>
#define maxn (100+10)
using namespace std;

int n,f[maxn];

void init()
{
  freopen("p1.in","r",stdin);
  freopen("p1.out","w",stdout);
}

void work()
{
  scanf("%d",&n);
  int i,j=0;  f[0]=0;
  for(i=1;i<=n;i++)scanf("%d",&f[i]);
  sort(f+1,f+n+1);
  for(i=1;i<=n;i++)
    if(f[i]!=f[i-1])++j,f[j]=f[i];
  printf("%d\n",j);  
  for(i=1;i<=j;i++)printf("%d ",f[i]);  
}

int main()
{
  init();
  work();
  return 0;	
}
