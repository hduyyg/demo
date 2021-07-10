#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#define ms(a,b,c) memset(a,b,sizeof(a[0])*(c+5))
using namespace std;

const int maxn=1e5;
int v[maxn+5],h[maxn+5];
struct tnode{
	int x,y,next;
}q[maxn*3];
int sq,head[maxn+5];
int d11[maxn+5],vd11[maxn+5];
int d12[maxn+5],d2[maxn+5];
int u1[maxn+5],u2[maxn+5];
int a[maxn+5];

int read()
{
  int ans=0;char tmp;
  while(!isdigit(tmp=getchar()));
  do ans=(ans<<3)+(ans<<1)+tmp-'0';
  while(isdigit(tmp=getchar()));
  return ans;
}

void add_edge(int x,int y,int z)
{
  q[sq].x=y,q[sq].y=z;
  q[sq].next=head[x],head[x]=sq++;
}

void work_h(int rt)
{
  int p,x;
  for(p=head[rt];p+1;p=q[p].next)
    if(!h[x=q[p].x])h[x]=h[rt]+1,work_h(x);
}

bool cmp_a(int x,int y)
{
  return h[x]<h[y];
}

int main()
{
  freopen("1.in","r",stdin);
  
  int t,n,cas,i,j,k,x,y,z,p;
  for(t=read(),cas=1;cas<=t;cas++)
    {
      printf("Case #%d:\n",cas);
      for(n=read(),i=1;i<=n;i++)v[i]=read();
	  for(ms(head,-1,n),sq=0,i=1;i<n;i++)
        {
          x=read(),y=read(),z=read();
          add_edge(x,y,z),add_edge(y,x,z);
		}
	  ms(h,0,n),h[1]=1,work_h(1);
/*	  printf("h: ");
	  for(i=1;i<=n;i++)printf("%d ",h[i]);
	  printf("\n");
*/	  
	  for(i=1;i<=n;i++)a[i]=i;
	  sort(a+1,a+1+n,cmp_a);
	  
	  for(ms(d2,0,n),i=n;i>=1;i--)
	    for(p=head[i];p+1;p=q[p].next)
	      if(h[x=q[p].x]>h[i])d2[i]+=max(0,v[x]-2*q[p].y+d2[x]);
/*	  printf("d2: ");
	  for(i=1;i<=n;i++)printf("%d ",d2[i]);
	  printf("\n");
*/	  
	  ms(d11,0,n),ms(vd11,0,n),ms(d12,0,n);
	  for(i=n;i>=1;i--)
	    for(p=head[i];p+1;p=q[p].next)
	      if(h[x=q[p].x]>h[i])
		    {
		      j=max(0,v[x]-2*q[p].y+d2[x]);
		      j=d2[i]-j+v[x]-q[p].y+d11[x];
		      
		      if(j>d11[i])
		        {
		          d12[i]=d11[i],d11[i]=j,vd11[i]=x;
				  continue;
				}
			  if(j>d12[i])d12[i]=j;
			}
/*	  printf("d1: \n");
	  for(i=1;i<=n;i++)printf("%d %d %d\n",d11[i],vd11[i],d12[i]);
	  printf("\n");
*/
	  for(ms(u2,0,n),i=1;i<=n;i++)
        for(p=head[i];p+1;p=q[p].next)
		  if(h[x=q[p].x]<h[i])
		    {
		      j=max(0,v[i]-2*q[p].y+d2[i]);
		      u2[i]=u2[x]+d2[x]-j+v[x]-2*q[p].y;
		      if(u2[i]<0)u2[i]=0;
			}
/*	  printf("u2: ");
	  for(i=1;i<=n;i++)printf("%d ",u2[i]);
	  printf("\n");
*/
      for(ms(u1,0,n),i=1;i<=n;i++)
	    for(p=head[i];p+1;p=q[p].next)
		  if(h[x=q[p].x]<h[i])
		    {
		      j=max(0,v[i]-2*q[p].y+d2[i]);
		      y=((vd11[x]==i)?d12[x]:d11[x])-j;
		      u1[i]=max(u2[x]+y,d2[x]-j+u1[x])+v[x]-q[p].y;
		      if(u1[i]<0)u1[i]=0;
		 	}
/*		 	
	  printf("u1: ");
	  for(i=1;i<=n;i++)printf("%d ",u1[i]);
	  printf("\n");
*/
	  for(i=1;i<=n;i++)printf("%d\n",max(d2[i]+u1[i],u2[i]+d11[i])+v[i]);
	}
  return 0;
}
