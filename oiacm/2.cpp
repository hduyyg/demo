#include<cstdio>
#include<algorithm>
#define maxn 200
using namespace std;
 
int n,c[maxn+20],r[maxn+20],ans[maxn+20];
int a[maxn+20][maxn+20],w[maxn+20][maxn+20];
bool used[maxn+20];
 
void readdata()
{  
  int i,j,k,x,y,z;
  scanf("%d%d",&n,&k);
  for(i=1;i<=n;i++)
    {
      scanf("%d%d",&x,&y);
      c[i]=(x==0)?-y:x;
    }
  for(i=1;i<=k;i++)
    {
      scanf("%d%d%d",&x,&y,&z);
      a[x][++a[x][0]]=y;
      w[x][y]=z,r[y]++;
    }  
}
void work()
{
  int i,j,k,x,y;
  for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
      if(r[j]==0 && !used[j])
        {
          used[j]=1;
          if(a[j][0]==0 && c[j]>0)
            {
              ans[++ans[0]]=j;
              break;
            }
          for(k=1;k<=a[j][0];k++)
            {
              x=a[j][k];
              if(c[j]>0)c[x]+=c[j]*w[j][x];
              r[x]--;
            }
          break;  
        }
  if(ans[0]==0)printf("NULL\n");
  else
    {
      sort(ans+1,ans+ans[0]+1);
      for(i=1;i<=ans[0];i++)
        printf("%d %d\n",ans[i],c[ans[i]]);
    }        
}
 
int main()
{
  //freopen("1.in","r",stdin);
  readdata();
  work();
  return 0;
}
