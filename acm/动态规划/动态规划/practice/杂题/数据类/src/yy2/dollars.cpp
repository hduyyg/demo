#include<cstdio>
#include<algorithm>
using namespace std;

void init()
{
  freopen("dollars.in","r",stdin);
  freopen("dollars.out","w",stdout);
}

void work()
{
  int n,k,l;  double i,j,me=100.0,ma=0.0;
  scanf("%d",&n);
  for(l=1;l<=n;l++)
    {
      scanf("%d",&k);
      i=max(me,ma*100/k);
      j=max(ma,me*k/100);
      me=i,ma=j;
    }
  printf("%.2lf\n",me);  
}

int main()
{
  init();
  work();
  return 0;
}
