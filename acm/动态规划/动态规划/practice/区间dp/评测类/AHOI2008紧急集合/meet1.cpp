#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cctype>
#define maxn (500000+100)
using namespace std;
 
struct tnode{int d,next;}edge[maxn<<1];
int n,m;
int d[21]={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576};
int pos[maxn],c[maxn],head[maxn],f[maxn<<1][21];
 
void init()
{
  freopen("meet.in","r",stdin);
  freopen("meet.out","w",stdout);
}
 
inline int getin()
{
  int ans=0;char tmp;
  while(!isdigit(tmp=getchar()));
  do ans=(ans<<3)+(ans<<1)+tmp-'0';
  while(isdigit(tmp=getchar()));
  return ans;
}
 
inline void add_edge(int i,int u,int v)
{
  int k=2*i-1;
  edge[k].d=v,edge[k].next=head[u],head[u]=k;
  edge[k+1].d=u,edge[k+1].next=head[v],head[v]=k+1;
}
 
void dfs(int i)
{
  int k=head[i];
  while(k!=-1)
    {
      if(pos[edge[k].d]==0)
        {
          f[++f[0][0]][0]=edge[k].d;
          c[edge[k].d]=c[i]+1;
          pos[edge[k].d]=f[0][0];
          dfs(edge[k].d);
          f[++f[0][0]][0]=i;
        }
      k=edge[k].next; 
    } 
  return; 
}

void readdata()
{
  n=getin(),m=getin();
  memset(head,-1,sizeof(int)*(n+1));
  memset(pos,0,sizeof(int)*(n+1));
   
  int i,j;
  for(i=1;i<n;i++)
    add_edge(i,getin(),getin());
     
  c[1]=pos[1]=f[0][0]=f[1][0]=1;
  dfs(1);
   
  for(j=1;d[j]<=f[0][0];j++)
    for(i=1;i+d[j]-1<=f[0][0];i++)
      f[i][j]=c[f[i][j-1]]<c[f[i+d[j-1]][j-1]]?f[i][j-1]:f[i+d[j-1]][j-1];
}
 
inline int getfa(int a,int b)
{
  int i,j;
  if(pos[a]<pos[b])i=pos[a],j=pos[b];
  else i=pos[b],j=pos[a];  
  int k=int(log((j-i+1)*(1.0))/log(2.0));
  int kk=c[f[i][k]]<c[f[j-d[k]+1][k]]?f[i][k]:f[j-d[k]+1][k];
  return kk;
}

inline int get(int d,int aa,int bb,int cc)
{
  int da=getfa(d,aa),db=getfa(d,bb),dc=getfa(d,cc);
  int ka=c[d]+c[aa]-c[da]*2;
  int kb=c[d]+c[bb]-c[db]*2;
  int kc=c[d]+c[cc]-c[dc]*2;
  return ka+kb+kc;       
} 
 
void work()
{
  int i,aa,bb,cc,ac,ab,bc;
  for(i=1;i<=m;i++)
    {
      aa=getin(),bb=getin(),cc=getin();
      if(aa==bb && aa==cc)
        {
          printf("%d %d\n",aa,0);
          continue;
        }
      ab=getfa(aa,bb),ac=getfa(aa,cc),bc=getfa(bb,cc);
      if(ab==ac)
        {
          printf("%d %d\n",bc,get(bc,aa,bb,cc));
          continue;
        }
      if(ab==bc)
        {
          printf("%d %d\n",ac,get(ac,aa,bb,cc));
          continue;
        }
      printf("%d %d\n",ab,get(ab,aa,bb,cc));
    }
}
 
int main()
{
  init();
  readdata();
  work();
  return 0;
}
