#include <iostream>
#include <math.h>
using namespace std;
#define maxn 25
#define maxs 4000100
const double base=log(10.0);
double rec[maxs],mat[maxn][maxn];
int dat1[maxn],dat2[maxn],rel[maxn],n,l,p[maxn];
bool used[maxs];
void change(int *a)
{
  int i,j;
  for(i=1,j=n;i<j;i++,j--)
    swap(a[i],a[j]);     
}
void sort(int *a)
{
  int i,j;
  for(i=1;i<=n;i++)
    p[i]=i;  
  for(i=1;i<=n;i++)
    for(j=i+1;j<=n;j++)     
      if(a[j]<a[i])
        {
          swap(a[j],a[i]);
          swap(p[i],p[j]);
        }
}
double cal(int a,int b)
{return 1.0/(1+exp(double(dat2[b]-dat1[a])/400*base));}
void init()
{
  freopen("compete.in","r",stdin);
  freopen("compete.out","w",stdout);
  scanf("%d",&n);
  int i,j;
  for(i=1;i<=n;i++) 
    scanf("%d",&dat1[i]);
  for(i=1;i<=n;i++)
    scanf("%d",&dat2[i]);
  scanf("%d",&l);
  change(dat2);  
  sort(dat1);
  for(i=1;i<=n;i++)
    for(j=1;j<i;j++)
      if(dat1[j]<dat1[i]-l)
        rel[i]|=1<<j;   
  for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
      mat[i][j]=cal(i,j);
}
double s(int a,int b)
{
  if(a>n)
    return 0;
  if(used[b])
    return rec[b];
  int i;
  double ans=0,t;
  for(i=1;i<=n;i++)
     if((b&rel[i])==rel[i]&&((1<<i)&b)==0)
       ans>?=s(a+1,b|(1<<i))+mat[i][a];
  used[b]=1;
  rec[b]=ans;
  return ans;               
}
int main()
{
  init();
  printf("%.6lf",s(1,0));
  return 0;     
}
