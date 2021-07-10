#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<stdlib.h>
#include<string.h>
#include<time.h>
using namespace std;
const double INF=1000000;
int n,L;
int a[25],b[25];
void init()
{
     freopen("compete.in","r",stdin);
     freopen("compete.out","w",stdout);
}

void readdata()
{
     scanf("%d",&n);
     for(int i=1;i<=n;i++)
     {scanf("%d",&a[i]);}
     for(int j=1;j<=n;j++)
     scanf("%d",&b[j]);
     scanf("%d",&L);
}

void work()
{
     int x,y;
     for(int u=1;u<=80000;u++)
     {
     for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
       {
              if(i==j) continue;
              x=min(i,j);
              y=max(i,j);
              if(a[y]<a[x]-L) continue;
              else if(a[x]<a[y]-L)
              {
              int c=a[i];
              a[i]=a[j];
              a[j]=c;
              continue;
              }
              if((b[y]-b[x])*(a[y]-a[x])>=0&&a[x]*a[y]>=b[y]*b[x]) continue;
              if((b[y]-b[x])*(a[y]-a[x])<=0&&a[x]*a[y]<=b[y]*b[x]) continue;
              int c=a[i];
              a[i]=a[j];
              a[j]=c;
       }
     }
}

void print()
{
     double ans=0;
     for(int i=1;i<=n;i++)
     {
             double del=(double)(b[i]-a[i])/400;
             double x=pow(10.0,del);
             ans+=INF/(1+x);
     }
     printf("%lf\n",ans/INF);
     /*for(int i=1;i<=n;i++)
     printf("%d ",a[i]);*/
}

int main()
{
    init();
    readdata();
    work();
    print();
    return 0;
} 
