/*
解题思路与采药几乎一样，只是决策不一样罢了。
f[i]表示高度为i时能存活的最长时间
对于每一个垃圾，有两种情况：1.吃下去，当前高度存活时间增加
                            2.垫起来，出去 或者 更新另一高度的存活时间
有个比较容易忽略的地方：提上给的垃圾并未说按照时间先后来给，所以得sort一下。							  
*/
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#define maxn (100+10)
using namespace std;

int d,g,f[maxn];
struct tnode{int t,f,h;}a[maxn];

void init()
{
  freopen("well.in","r",stdin);
  freopen("well.out","w",stdout);
}

inline bool cmp(tnode x,tnode y){return x.t<y.t;}

void readdata()
{
  scanf("%d%d",&d,&g);     int i;
  for(i=1;i<=g;i++)scanf("%d%d%d",&a[i].t,&a[i].f,&a[i].h);
  sort(a+1,a+g+1,cmp);
  
  f[0]=10;
}

void work()
{
  int i,j;
  for(i=1;i<=g;i++)
    for(j=d;j>=0;j--)
      if(f[j]>=a[i].t)
	    {
	      if(j+a[i].h>=d){printf("%d\n",a[i].t);exit(0);}
	      f[j+a[i].h]=max(f[j+a[i].h],f[j]);
	      f[j]+=a[i].f;
	    }	
  printf("%d\n",f[0]);	    
}

int main()
{
  init();
  readdata();
  work();
  return 0;
}
