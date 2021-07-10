#include<cstdio>
#include<cstring>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;

int a[105];
bool f[100000+5];
int pre[100000+5];
int q[105];

int main()
{
  freopen("1.in","r",stdin);
  
  int n,m,i,j,k;
  scanf("%d%d",&m,&n);
  for(k=0,i=1;i<=n;i++)scanf("%d",&a[i]),k+=a[i];
  m=k-m;
  if(m<1 || m>k)
    {
      printf("0\n");
      return 0;
	}
  ms(pre,0),ms(f,0),f[0]=1;
  for(i=1;i<=n;i++)if(m>=a[i])
    {
      if(f[m] && f[m-a[i]])
        {
          printf("-1\n");
          return 0;
		}
      for(j=m;j>=a[i];j--)
	    if(f[j-a[i]] && !f[j])f[j]=1,pre[j]=i;
	}
  if(!f[m]){printf("0\n");return 0;}
  for(q[0]=0,j=m;pre[j];q[++q[0]]=pre[j],j-=a[pre[j]]);
  for(i=q[0];i>1;i--)printf("%d ",q[i]);
  printf("%d\n",q[1]);
  return 0;
}
