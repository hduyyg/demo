#include<cstdio>
#define maxv (5000+100)
#define maxk (50+10)
using namespace std;

int k,v,n;
int f[maxv][maxk],sum[maxv][maxk];
int ps[maxk],pw[maxk];

void init()
{
  freopen("bags.in","r",stdin);
  freopen("bags.out","w",stdout);
}

inline void merge(int j,int x,int w)
{
  int p1,p2,p=0;    p1=p2=1;
  while(p<k && p1<=sum[j][0] && p2<=sum[x][0])
    {
      if(f[j][p1]==f[x][p2]+w)
        {
          pw[++p]=f[j][p1],ps[p]=sum[j][p1]+sum[x][p2];
          ++p1,++p2;
          continue;
        }
      if(f[j][p1]>f[x][p2]+w)
	    {
	      pw[++p]=f[j][p1],ps[p]=sum[j][p1];
	      ++p1;    continue;
	    }  
	  pw[++p]=f[x][p2]+w,ps[p]=sum[x][p2];
	  ++p2;  
    }
  
  int i;
  for(i=p1;i<=sum[j][0] && p<k;i++)ps[++p]=sum[j][i],pw[p]=f[j][i];
  for(i=p2;i<=sum[x][0] && p<k;i++)ps[++p]=sum[x][i],pw[p]=f[x][i]+w;
  sum[j][0]=p;  
  for(i=1;i<=p;i++)f[j][i]=pw[i],sum[j][i]=ps[i];
}

void work()
{
  scanf("%d%d%d",&k,&v,&n);
  int i,j,b,w,ans=0;
  sum[0][1]=sum[0][0]=1;
  for(i=1;i<=n;i++)
    {
      scanf("%d%d",&b,&w);
      for(j=v;j>=b;j--)if(sum[j-b][0]>0)merge(j,j-b,w);
    }
  for(i=1;k>0;i++)
    if(k>=sum[v][i])ans+=(f[v][i]*sum[v][i]),k-=sum[v][i];
    else ans+=(f[v][i]*k),k=0;
  printf("%d\n",ans);		  
}

int main()
{
  init();
  work();
  return 0;
}
