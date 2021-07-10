/*
  求最长上升子序列与最长下降子序列。
  用l[i]表示以i作为最长上升子序列的终点，其左边有多少个点
  用r[i]表示以i作为最长下降子序列的起始点，其右边有多少个点
  则以i为中间点的队列最长长度为l[i]+r[i]+1,需要剔除的最少人
数为n-l[i]-r[i]-1;

  由于数据偏小，就不采用任何优化了。 
*/
#include<cstdio>
#include<algorithm>
#define maxn (100+10)
#define inf 100000000
using namespace std;

int n,a[maxn],l[maxn],r[maxn]; 

void init()
{
  freopen("chorus.in","r",stdin);
  freopen("chorus.out","w",stdout);
}

void work()
{
  int i,j,ans=inf;
  scanf("%d",&n);
  for(i=1;i<=n;i++)scanf("%d",&a[i]);
  
  for(l[1]=0,i=2;i<=n;i++)
    for(j=i-1;j>=1;j--)
	  if(a[i]>a[j])l[i]=max(l[i],l[j]+1);
	  
  for(r[n]=0,i=n-1;i>=1;i--)
    for(j=i+1;j<=n;j++)
	  if(a[i]>a[j])r[i]=max(r[i],r[j]+1);
	  
  for(i=1;i<=n;i++)ans=min(ans,n-l[i]-r[i]-1);
  printf("%d\n",ans);	  
}

int main()
{
   init();
   work();
   return 0;
}
