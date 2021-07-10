#include<cstdio>
#include<algorithm>
#define maxn (500+20)
using namespace std;

int m,n,f[maxn][maxn],l[maxn];

void init()
{
  freopen("book.in","r",stdin);
  freopen("book.out","w",stdout);
}

void readdata()
{
  scanf("%d%d",&m,&n);    
  for(int i=1;i<=m;i++)scanf("%d",&f[i][0]),f[i][1]=f[i-1][1]+f[i][0];
}

void work()
{
  int i,j,k,sum;
  for(j=2;j<=n;j++)
    for(i=j;i<=m;i++)
      {
        f[i][j]=max(f[i-1][j-1],f[i][0]);
        for(k=i-2;k>=j-1;k--)f[i][j]=min(f[i][j],max(f[k][j-1],f[i][1]-f[k][1]));
      }

  sum=0,j=n,l[n+1]=m+1;
  for(i=m;i>=1;i--)
    if(sum+f[i][0]>f[m][n])l[j--]=i+1,sum=f[i][0];
	else sum+=f[i][0];
  l[j]=1;	
  for(i=1;i<j;i++)printf("%d %d\n",0,0);
  for(i=j;i<=n;i++)printf("%d %d\n",l[i],l[i+1]-1);
}

int main()
{
  init();
  readdata();
  work();
  return 0;
}
