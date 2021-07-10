#include<cstdio>
#define maxn (10000+100)
using namespace std;

int a[maxn];

void init()
{
  freopen("hdu1231.in","r",stdin);
  freopen("hdu1231.out","w",stdout);
}

void work()
{
  int i,j,k,l,r,sum,ans,ansl,ansr;
  while(scanf("%d",&a[0])==1,a[0])
    {
      for(i=1;i<=a[0];i++)scanf("%d",&a[i]);
      
	  for(j=1,i=1;i<=a[0];i++)if(a[i]>=0){j=0;break;}
      if(j){printf("%d %d %d\n",0,a[1],a[a[0]]);continue;}
      
      ans=a[1],ansl=ansr=1;
      sum=a[1],l=r=1;
      for(i=2;i<=a[0];i++)
        {
          if(sum<=0)sum=a[i],l=r=i;
          else  sum+=a[i],r++;
          if(sum>ans)ans=sum,ansl=l,ansr=r;
        }
      printf("%d %d %d\n",ans,a[ansl],a[ansr]);  
    }
}

int main()
{
  init();
  work();
  return 0;
}
