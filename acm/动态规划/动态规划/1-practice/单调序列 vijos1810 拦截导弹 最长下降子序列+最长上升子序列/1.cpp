#include<cstdio>
#define maxn 10000
using namespace std;
int a[maxn+20],q[maxn+20];
int main()
{
  int i,j,k;
  while(scanf("%d",&k)!=EOF)a[++a[0]]=k;
  
  q[0]=1,q[1]=a[1];
  for(i=2;i<=a[0];i++)
    if(a[i]<=q[q[0]])q[++q[0]]=a[i];
    else
      for(j=1;j<=q[0];j++)
        if(a[i]>q[j]){q[j]=a[i];break;}
  printf("%d\n",q[0]);
  
  q[0]=1,q[1]=a[1];
  for(i=2;i<=a[0];i++)
    if(a[i]>q[q[0]])q[++q[0]]=a[i];
    else 
      for(j=1;j<=q[0];j++)
        if(a[i]<=q[j]){q[j]=a[i];break;}
  printf("%d\n",q[0]);                
  return 0;
}
