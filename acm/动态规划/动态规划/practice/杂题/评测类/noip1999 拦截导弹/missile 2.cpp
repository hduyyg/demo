#include<cstdio>
#include<cstdlib>
#define maxn 1000+100
using  namespace std;

int q[maxn],h[maxn],len=1;

void init()
{
  freopen("daodan.in","r",stdin);
  freopen("daodan.out","w",stdout);
}

int find1(int x)//求最长下降子序列中，从左数第一个小于x的数的位置
{
  int l=1,r=len,mid;
  while(l<=r)
    {
      mid=(l+r)>>1;
      if(x>q[mid])
        r=mid-1;
      else
        l=mid+1;
    }
  return l;
}

int find2(int x)// 求最长上升子序列中，从左数第一个大于等于x的数的位置
{
  int l=1,r=len,mid;
  while(l<=r)
    {
      mid=(l+r)>>1;
      if(x>q[mid])
        l=mid+1;
      else
        r=mid-1;
    }
  return l;
}

void work()
{
  int n,i;
  scanf("%d",&n);
  if(n<=0){printf("%d %d\n",0,0);exit(0);}
  for(i=1;i<=n;i++)scanf("%d",&h[i]);
  
  q[1]=h[1];
  for(i=2;i<=n;i++)//求最长下降子序列
    {
      if(h[i]<=q[len])q[++len]=h[i];
      else q[find1(h[i])]=h[i];
    }
  printf("%d ",len);
  
  len=1;q[1]=h[1];//求最长上升子序列
  for(i=2;i<=n;i++)
    {
      if(h[i]>q[len])q[++len]=h[i];
      else if(h[i]<q[len])q[find2(h[i])]=h[i];
    }
  printf("%d\n",len);
}

int main()
{
  init();
  work();
  return 0;
}

