#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<cstdlib>
using namespace std;

struct tnode{int x,y;}q[10000];
int n,g,sx,sy,ex,ey;
int xpre[20][20],ypre[20][20];
char to[20][20];
int x[20],y[20],fan[20];
bool f[20][20];

void init()
{
  freopen("guard.in","r",stdin);
  freopen("guard.out","w",stdout);
}

void readdata()
{
  memset(f,1,sizeof(f));
  scanf("%d%d\n",&n,&g);
  int i,j,k;
  char s[20];
  for(i=1;i<=n;i++)
    {
      scanf("%s\n",s);
      for(j=0;j<n;j++)
        {
          if(s[j]=='X')f[i][j+1]=0;
          if(s[j]=='E')ex=i,ey=j+1;
          if(s[j]=='C')sx=i,sy=j+1;
          if(isdigit(s[j]))
            {k=s[j]-'0',x[k]=i,y[k]=j+1;f[i][j+1]=0;}
        }
    }

  for(i=1;i<=g;i++)
    {
      scanf("%d%s\n",&j,s);
      if(s[0]=='W')fan[j]=1;
      if(s[0]=='N')fan[j]=2;
      if(s[0]=='E')fan[j]=3;
      if(s[0]=='S')fan[j]=4;
    }  
  for(i=1;i<=g;i++)
    {
      if(fan[i]==1)
        {
          for(j=y[i]-1;j>0;j--)
            if(f[x[i]][j])f[x[i]][j]=0;
            else break;
        }
      if(fan[i]==3)
        {
          for(j=y[i]+1;j<=n;j++)
            if(f[x[i]][j])f[x[i]][j]=0;
            else break;
        }
      if(fan[i]==2)
        {
          for(j=x[i]-1;j>0;j--)
            if(f[j][y[i]])f[j][y[i]]=0;
            else break;
        }
      if(fan[i]==4)
        {
          for(j=x[i]+1;j<=n;j++)
            if(f[j][y[i]])f[j][y[i]]=0;
            else break;
        }      
    }  
}

void write(int i,int j)
{
  if(i==sx && j==sy)return;
  printf("%c\n",to[i][j]);
  write(xpre[i][j],ypre[i][j]);
}

void work()
{
  if(!f[ex][ey] || !f[sx][sy])
    {
      printf("%d\n",-1);
      exit(0);
    }
  int l=1,r=1,i;
  q[1].x=sx,q[1].y=sy;
  f[sx][sy]=0;
  while(l<=r)
    {
      i=l; l++;
      if(q[i].y-1>0 && f[q[i].x][q[i].y-1])
        {
          q[++r].x=q[i].x,q[r].y=q[i].y-1;
          xpre[q[i].x][q[i].y-1]=q[i].x,ypre[q[i].x][q[i].y-1]=q[i].y;
          to[q[i].x][q[i].y-1]='E';  f[q[i].x][q[i].y-1]=0;
        }
      if(q[i].y+1<=n && f[q[i].x][q[i].y+1])
        {
          q[++r].x=q[i].x,q[r].y=q[i].y+1;
          xpre[q[i].x][q[i].y+1]=q[i].x,ypre[q[i].x][q[i].y+1]=q[i].y;
          to[q[i].x][q[i].y+1]='W'; f[q[i].x][q[i].y+1]=0;
        }  
      if(q[i].x-1>0 && f[q[i].x-1][q[i].y])
        {
          q[++r].x=q[i].x-1,q[r].y=q[i].y;
          xpre[q[i].x-1][q[i].y]=q[i].x,ypre[q[i].x-1][q[i].y]=q[i].y;
          to[q[i].x-1][q[i].y]='S'; f[q[i].x-1][q[i].y]=0;
        }  
      if(q[i].x+1<=n && f[q[i].x+1][q[i].y])
        {
          q[++r].x=q[i].x+1,q[r].y=q[i].y;
          xpre[q[i].x+1][q[i].y]=q[i].x,ypre[q[i].x+1][q[i].y]=q[i].y;
          to[q[i].x+1][q[i].y]='N'; f[q[i].x+1][q[i].y]=0;
        }  
    }
  write(ex,ey);
}

int main()
{
  init();
  readdata();
  work();
  return 0;
}
