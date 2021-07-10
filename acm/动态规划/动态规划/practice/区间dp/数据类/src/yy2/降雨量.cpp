#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cctype>
#define maxn (50000+100)
#define inf 2000000000
#define false {printf("false\n");continue;}
#define true  {printf("true\n");continue;}
#define maybe {printf("maybe\n");continue;}
using namespace std;

int n,m,y[maxn];
int d[17]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536};
int ma[maxn][17];
bool flag[maxn][17];//1 代表区间存在不连续的部分 

void init()
{
  freopen("rain.in","r",stdin);
  freopen("rain.out","w",stdout);
}

inline int getin()
{
  int ans=0;bool sign=0;char tmp;
  do tmp=getchar();
  while(!isdigit(tmp) && tmp!='-');
  if(tmp=='-')sign=1,tmp=getchar();
  do ans=(ans<<3)+(ans<<1)+tmp-'0';
  while(isdigit(tmp=getchar()));
  return sign?-ans:ans;
}

void build()
{
  int i,j; n=getin();
  for(i=1;i<=n;i++)y[i]=getin(),ma[i][0]=getin();
  for(i=1;i<n;i++)if(y[i]+1!=y[i+1])flag[i][1]=1;
  y[n+1]=inf;
  
  for(j=1;d[j]<=n;j++)
    for(i=1;i+d[j]-1<=n;i++)
      ma[i][j]=max(ma[i][j-1],ma[i+d[j-1]][j-1]);

  for(j=2;d[j]<=n;j++)
    for(i=1;i+d[j]-1<=n;i++)
      if(flag[i][j-1] || flag[i+d[j-1]][j-1] || y[i+d[j-1]-1]+1!=y[i+d[j-1]])
        flag[i][j]=1;          
}

inline int get(int x)
{
  int l=1,r=n,m;
  while(l<=r)
    {
      m=(l+r)>>1;
      if(x<=y[m])r=m-1;
      else l=m+1;
    }
  return l;  
}

void work()
{
  build();
  
  m=getin();
  int i,a,b,k,Max,aa,bb;
  for(i=1;i<=m;i++)
    {
      aa=getin(),bb=getin();
      if(bb<=aa)false
      a=get(aa),b=get(bb);
      if(y[a]==aa && y[b]==bb)
        {
          if(ma[b][0]>ma[a][0])false
          if(b-a==1)
            {if(!flag[a][1])true}
          else
            {  
              k=int(log((b-a-1)*(1.0))/log(2.0));
              Max=max(ma[a+1][k],ma[b-d[k]][k]);
              if(Max>=ma[b][0])false
              k=int(log((b-a+1)*(1.0))/log(2.0));
              if(!flag[a][k] && !flag[b-d[k]+1][k] && !flag[a+d[k]-1][1])true
            }
        }
      if(y[a]==aa && y[b]!=bb && b-a>=2)
        {
          k=int(log((b-a-1)*(1.0))/log(2.0));
          Max=max(ma[a+1][k],ma[b-d[k]][k]);
          if(Max>=ma[a][0])false;
        }  
      if(y[a]!=aa && y[b]==bb && b-a>=1) 
        {
          k=int(log((b-a)*(1.0))/log(2.0));
          Max=max(ma[a][k],ma[b-d[k]][k]);
          if(Max>=ma[b][0])false;
        } 
      maybe;  
    }
}  


int main()
{
  init();
  work(); 
  return 0;
}

