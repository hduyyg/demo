#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cstring>
#include<cmath>
#define maxn1 (40000+100)
#define maxn2 (200+10)
using namespace std;

int n,m,kuai,sum_kuai;
int a[maxn1],b[maxn1],c[maxn1],d[maxn1];
int best[maxn2][maxn2][2],sum[maxn1];
int z[maxn1],y[maxn1];

void init()
{
  freopen("dandelion.in","r",stdin);
  freopen("dandelion.out","w",stdout);
}

inline int getin()
{
  int ans=0;char tmp;
  while(!isdigit(tmp=getchar()));
  do ans=(ans<<3)+(ans<<1)+tmp-'0';
  while(isdigit(tmp=getchar()));
  return ans;
}

inline bool cmp(int x,int y)
{
  if(a[x]<a[y])return 1;
  if(a[x]==a[y])return x<y;
  return 0;
}

void chuli_1()
{
  n=getin(),m=getin();
  int i,j;
  for(i=1;i<=n;i++)a[i]=getin(),c[i]=i;
  sort(c+1,c+n+1,cmp);
  b[0]=1,b[c[1]]=1,d[1]=a[c[1]];
  for(i=2;i<=n;i++)
    if(a[c[i]]==a[c[i-1]])b[c[i]]=b[c[i-1]];
    else b[c[i]]=++b[0],d[b[0]]=a[c[i]];
}

inline void get(int l)
{
  memset(sum,0,sizeof(sum));
  int i,j,k=kuai*(l-1),s;
  for(i=l;i<=sum_kuai;i++)
    {
      best[l][i][1]=0;
      s=min(kuai,n-k);
      for(j=1;j<=s;j++)
        {
          sum[b[++k]]++;
          if(sum[b[k]]>best[l][i][1])
            {
              best[l][i][0]=b[k];
              best[l][i][1]=sum[b[k]];
            }
          else
            if(sum[b[k]]==best[l][i][1] && b[k]<best[l][i][0])
              best[l][i][0]=b[k];
        }
    }
}

void chuli_2()
{
  sum_kuai=(int)(sqrt(n));
  if(n%sum_kuai!=0)sum_kuai++;
  kuai=n/sum_kuai;

  for(int i=1;i<=sum_kuai;i++)get(i);
}

void chuli_3()
{
  int i,j;
  for(i=1,j=2;j<=n;j++)
    {
      if(a[c[j]]!=a[c[i]])
        z[b[c[i]]]=i,y[b[c[i]]]=j-1,i=j;
      if(j==n)z[b[c[i]]]=i,y[b[c[i]]]=j;
    }
}

void readdata()
{
  chuli_1();
  chuli_2();
  chuli_3();
}

inline int de2(int x,int l,int r)
{
  if(y[x]<l)return 0;
  if(y[x]==l)return 1;
  
  int lz,lr,ll,rr,mid;
  if(z[x]>=l)lz=z[x]-1;
  else
    {
      while(ll<=rr)
        {
          ll=z[x],rr=y[x],mid=(ll+rr)/2;
          if(c[mid]>l)
            rr=mid-1;
          else
            ll=mid+1;
        }
      lz=ll-1;
    }

  if(y[x]<=r)lr=y[x];
  else
    {
      while(ll<=rr)
        {
          ll=z[x],rr=y[x],mid=(ll+rr)/2;
          if(c[mid]>r)
            rr=mid-1;
          else
            ll=mid+1;
        }
      lr=ll-1;
    }
  return lr-lz;
}

inline int de(int l,int r)
{
  int z,s,i,j;
  i=(l/kuai)+2,j=r/kuai;
  if(i>j)s=0;
  else z=best[i][j][0],s=best[i][j][1];
  
  int stack[400+100],ss,k;
  stack[0]=0;
  
  ss=min(r,kuai*(i-1));
  for(k=1;k<=ss;k++)
    stack[++stack[0]]=b[k];
  ss=max(l,kuai*j);
  for(k=ss;k<=r;k++)
    stack[++stack[0]]=b[k];
  for(i=2,j=1;i<=stack[0];i++)
    if(stack[i]!=stack[j])stack[++j]=stack[i];
  for(i=1;i<=j;i++)
    {
       k=de2(stack[i],l,r);
       if(k>s)z=stack[i],s=k;
       if(k==s && stack[i]<z)z=stack[i];
    }
  return d[z];
}

void work()
{
  int i,x=0,l,r;
  for(i=1;i<=m;i++)
    {
      l=getin(),r=getin();
      l=(l+x-1)%n+1,r=(r+x-1)%n+1;
      x=de(l,r);
      printf("%d\n",x);
    }
}

int main()
{
  init();
  readdata();
  work();
  return 0;
}
