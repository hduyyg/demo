#include<cstdio>
#include<algorithm>
#define maxn (3200+10)
using namespace std;

int n,m;
int f[maxn],a[60+10][3],v[60+10],w[60+10];

void init()
{
  freopen("budget.in","r",stdin);
  freopen("budget.out","w",stdout);
}

void  read()
{
  scanf("%d%d",&n,&m);n/=10;
  int i,j;
  for(i=1;i<=m;i++)
    {
     scanf("%d%d%d",&v[i],&w[i],&j);
	 v[i]/=10,w[i]*=v[i];
	  
	 if(j==0)a[i][0]=1;
	 else if(a[j][1])a[j][2]=i;
	 else a[j][1]=i;     
   }
}

void work()
{
  int i,j,k1,k2,t;
  for(i=1;i<=m;i++)if(a[i][0])
    for(j=n;j>=v[i];j--)
      {
        f[j]=max(f[j],f[j-v[i]]+w[i]);
        
        k1=a[i][1],t=j-v[k1]-v[i];
        if(k1 && t>=0)f[j]=max(f[j],f[t]+w[i]+w[k1]);
        
        k2=a[i][2],t=j-v[i]-v[k2];
        if(k2 && t>=0)f[j]=max(f[j],f[t]+w[i]+w[k2]);

        t=j-v[i]-v[k1]-v[k2];
        if(k1 && k2 && t>=0)f[j]=max(f[j],f[t]+w[i]+w[k1]+w[k2]);        
      }
    
  printf("%d\n",f[n]*10);
}

int main()
{
  init();
  read();
  work();
  return 0;
}
