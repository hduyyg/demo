#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn=1e3;
int f[maxn+5];

int main()
{
  freopen("1.in","r",stdin);
  int n,m,i,v,w;
  scanf("%d%d",&n,&m);
  while(m--)
    {
      scanf("%d%d",&v,&w);
      for(i=n;i>=v;i--)f[i]=max(f[i],f[i-v]+w);
	}
  printf("%d\n",f[n]);
  return 0;
}
