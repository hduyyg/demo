#include <iostream>
#define maxs 10010
#define maxn 15
using namespace std;
typedef struct nedge
{int fr,to;};
bool rec[maxs],used[maxs];
int n,m,goal,tot,tot1;
char s[110],rst[maxs][maxn];
nedge edge[maxs];
void ins(int a,int b)
{
  edge[tot].fr=a;
  edge[tot++].to=b;
}
void deal()
{
  int p=0,t=0,t1=0,l=strlen(s);
  while(s[p]!='-')
    t|=1<<(s[p++]-'A');
  p+=2;
  while(s[p])
    t1|=1<<(s[p++]-'A');
  ins(t,t1);         
}
void init()
{
  freopen("dependence.in","r",stdin);
  freopen("dependence.out","w",stdout);
  int i;
  scanf("%d%d\n",&n,&m);
  for(i=0;i<m;i++)
    {
      memset(s,0,strlen(s));
      gets(s);
      deal();
    }
 // for(i=0;i<tot;i++)
   // printf("%d %d\n",edge[i].fr,edge[i].to);  
  goal=(1<<n)-1;
}
bool search(int a)
{
  if(used[a])
    return rec[a];
  if(a==goal)
    return 1;
  int i;
  bool ans=0;
  for(i=0;i<tot;i++)
    if((edge[i].fr&a)==edge[i].fr&&(edge[i].to&a)!=edge[i].to)
      {
        ans|=search(a|edge[i].to);         
        if(ans) break;
      }
  rec[a]=ans;
  used[a]=1;
  return ans;
}
int cmp(const void *a,const void *b)
{
  char *ca=(char *)a;char *cb=(char *)b;
  int i,l=min(strlen(ca),strlen(cb));
  for(i=0;i<l;i++)
    if(ca[i]!=cb[i])
      return ca[i]-cb[i];
  return strlen(ca)-strlen(cb);         
}
void change(int a,char *b)
{
  int i,p=0;
  for(i=0;i<n;i++)
    if(((1<<i)|a)==a)
      b[p++]='A'+i;      
}
void calc()
{
  int j,i,lim=1<<n;
  bool ok;
  for(i=0;i<lim;i++)
    search(i);
  for(i=0;i<lim;i++)
    {
      if(!rec[i]) continue;
      ok=1;
      for(j=0;j<lim;j++)
        if(i!=j&&rec[j]&&(j&i)==j)
          {ok=0;break;}
      if(ok)
        change(i,rst[tot1++]);    
    }
  qsort(rst,tot1,sizeof(rst[1]),cmp);
  printf("%d\n",tot1);
  for(i=0;i<tot1;i++)
    puts(rst[i]);             
}
int main()
{
  init();
  calc();
  return 0;  
}
