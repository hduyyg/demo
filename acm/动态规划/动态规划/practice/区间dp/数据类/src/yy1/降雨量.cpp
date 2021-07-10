#include<cstdio>
#include<cctype>
#include<algorithm>
#define maxn (50000+100)
#define false {printf("false\n");continue;}
#define true {printf("true\n");continue;}
#define maybe {printf("maybe\n");continue;}
/*
  true：两个端点确定，且中间所有年份已知并满足条件
  maybe：即不确定
         端点不确定：左端点不确定，右端点不确定，两个端点都不确定
		 中间不确定：两端点确定，中间存在未知年份，且中间已知年份满足条件， 
*/
using namespace std;

int n,m,y[maxn],ma[maxn][17];
bool flag[maxn][17];
int a[17]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536};


void init()
{
  freopen("rain.in","r",stdin);
  freopen("rain.out","w",stdout);	
}


inline int getin()
{
  int ans=0;bool sign=0; char tmp;
  do tmp=getchar();
  while(!isdigit(tmp) && tmp!='-');
  if(tmp=='-')sign=1,tmp=getchar();
  do ans=(ans<<3)+(ans<<1)+tmp-'0';
  while(isdigit(tmp=getchar())); 
  return sign?-ans:ans;
}

void chuli_flag()
{
  int i,j;
  for(i=1;i<=n;i++)if(y[i]+1!=y[i+1])flag[i][1]=1;
  for(j=2;a[j]<=n;j++)
    for(i=1;i+a[j]-1<=n;i++)
      flag[i][j]=(flag[i][j-1] || flag[i+a[j-1]][j-1]);
}

void chuli_ma()
{
  int i,j;
  for(j=1;a[j]<=n;j++)
    for(i=1;i+a[j]-1<=n;i++)
      ma[i][j]=max(ma[i][j-1],ma[i+a[j-1]][j-1]);
}

void readdata()
{
  int i,j;  n=getin();
  for(i=1;i<=n;i++)y[i]=getin(),ma[i][0]=getin();
  chuli_flag();       chuli_ma();  	
}

inline int get(int x)
{
  int l=1,r=n,mid;
  while(l<=r)
    {
      mid=(l+r)>>1;
      if(x<=y[mid])r=mid-1;
      else l=mid+1;
    }
  return l;  
}

inline int get_max(int l,int r)
{
  int i=r-l+1,j=0;
  while(a[j]<=i)j++;
  return max(ma[l][j-1],ma[r-a[j-1]+1][j-1]);  
}

inline bool get_flag(int l,int r)
{
  int i=r-l+1,j=0;
  while(a[j]<=i)j++;
  return (flag[l][j-1] || flag[r-a[j-1]+1][j-1]);  
}

void work()
{
  int i,j,k1,k2,p1,p2;
  m=getin();
  for(i=1;i<=m;i++)
    {
      k1=getin(),k2=getin();
      if(k2<=k1)false;
      p1=get(k1),p2=get(k2);
      
      if(y[p1]!=k1 && y[p2]!=k2)maybe;
      if(y[p1]==k1 && y[p2]!=k2 && get_max(p1+1,p2-1)<ma[p1][0])maybe;
      if(y[p1]!=k1 && y[p2]==k2 && get_max(p1,p2-1)<ma[p2][0])maybe;
      if(y[p1]==k1 && y[p2]==k2 && ma[p2][0]<=ma[p1][0] && get_max(p1+1,p2-1)<ma[p2][0])
        if(get_flag(p1,p2))maybe else true;
      
	  false;  
    }
}

int main()
{
  init();
  readdata();
  work();
  return 0;
}
