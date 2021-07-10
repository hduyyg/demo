#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cmath>
#define maxn (50000+10)
using namespace std;

int d[17]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536};
int dmin[maxn][17],dmax[maxn][17];

void init()
{
  freopen("poj3264.in","r",stdin);
  freopen("poj3264.out","w",stdout);
}

inline int getin()
{
  int ans=0;char tmp;
  do tmp=getchar();
  while(!isdigit(tmp));
  do ans=(ans<<3)+(ans<<1)+tmp-'0';
  while(isdigit(tmp=getchar()));
  return ans;
}

void work()
{
  int n=getin(),q=getin(),i,j;
  for(i=1;i<=n;i++)dmin[i][0]=dmax[i][0]=getin();

  for(j=1;d[j]<=n;j++)
    for(i=1;i+d[j]-1<=n;i++)  
      {
        dmax[i][j]=max(dmax[i][j-1],dmax[i+d[j-1]][j-1]);
        dmin[i][j]=min(dmin[i][j-1],dmin[i+d[j-1]][j-1]);
      }    
  
  int a,b,kmax,kmin;
  for(i=1;i<=q;i++)
    {
      a=getin(),b=getin();
      j=(int)(log((b-a+1)*1.0)/log(2.0));
      kmax=max(dmax[a][j],dmax[b-d[j]+1][j]);
      kmin=min(dmin[a][j],dmin[b-d[j]+1][j]);
      printf("%d\n",kmax-kmin);
    }  
}

int main()
{
  init();
  work();
  return 0;
} 
