/*
  用单调队列求解最长上升子序列、最长下降子序列。。。
  以求最长上升子序列为例（这道题的第二问）：
  首先，维护一个队列，这个队列是严格递增的，用p来记录队列的长度；
  然后，遇到一个新的高度h，若h比队列的最高点f[p]还要大，就将高度
h加入队尾，p加1；否则，找到队列中从左到右第一个<=h的位置j，将f[j]
的值更换为h。
（具体原理，这里就不赘述，自己模拟一下，就理解其中道理了。）

  优化：时间   空间
       时间优化，可用二分查找来代替直接遍历。
	   空间优化，我没任何思路。
 （二分优化，见missile2.cpp）

  评测链接：http://www.rqnoj.cn/problem/217	    
*/
#include<cstdio>
#define maxn (1000+10)
using namespace std;

int n,h[maxn],f[maxn];

void init()
{
  freopen("missile.in","r",stdin);
  freopen("missile.out","w",stdout);
}

void work()
{
  int i,j,p;   scanf("%d",&n);
  for(i=1;i<=n;i++)scanf("%d",&h[i]);
  
  p=1,f[1]=h[1];
  for(i=2;i<=n;i++)
    {
      if(h[i]<=f[p]){f[++p]=h[i];continue;}
      for(j=1;j<=p;j++)if(f[j]<=h[i]){f[j]=h[i];break;}    
    }
  printf("%d ",p);
  
  p=1,f[1]=h[1];
  for(i=2;i<=n;i++)
    {
      if(h[i]>f[p]){f[++p]=h[i];continue;}
      for(j=1;j<=p;j++)if(h[i]<=f[j]){f[j]=h[i];break;}    
    }
  printf("%d\n",p);
}

int main()
{
  init();
  work();
  return 0;
}
