#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define ms(a,b,c) memset(a,b,sizeof(a[0])*(c+5))
using namespace std;

typedef long long LL;
const int maxn=5e4;

template <class T>
T read(T &ans)
{
  ans=0;char tmp;bool sign=0;
  while((tmp=getchar())+1 && !isdigit(tmp) && tmp!='-');
  if(tmp==-1)return -1;
  if(tmp=='-')sign=1,tmp=getchar();
  do ans=(ans<<3)+(ans<<1)+tmp-'0';
  while(isdigit(tmp=getchar()));
  if(sign)ans=-ans;
  return ans;
}

LL dpL[maxn+5],dpR[maxn+5];
LL work(LL a[],int n)
{
  int i;LL mx,ans=0;
  ms(dpL,0,n),ms(dpR,0,n);
  for(mx=dpL[1]=a[1],i=2;i<=n;i++)
    {
      mx=max(mx,a[i]);
      dpL[i]=max(dpL[i-1]+a[i],mx);
	}
  for(i=n;i>=1;i--)
    {
	  dpR[i]=max(dpR[i+1],(LL)0)+a[i];
      ans=max(ans,dpR[i]);
	}
  for(i=2;i<n;i++)ans=max(ans,dpL[i-1]+dpR[i]-a[i]);
  return ans;
}

LL a[maxn+5];
int main()
{
 // freopen("1.in","r",stdin);
  
  int n,i;LL ans;
  while(read(n)+1)
    {
      for(i=1;i<=n;i++)read(a[i]);
      ans=work(a,n);
      for(i=1;i*2<=n;i++)swap(a[i],a[n+1-i]);
      ans=max(ans,work(a,n));
      printf("%I64d\n",ans);
	}
  return 0;
}
