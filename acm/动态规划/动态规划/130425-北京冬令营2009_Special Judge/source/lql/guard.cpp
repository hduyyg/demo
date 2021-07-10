#include <iostream>
#define maxn 15
const int cx[4]={-1 , 1 , 0 , 0 };
const int cy[4]={ 0 , 0 , 1 ,-1 };
const char d[4]={'N','S','E','W'};
typedef struct node
{int x,y;};
int n,g,map[maxn][maxn],way[maxn][maxn],dir[maxn],vis[maxn][maxn],sx,sy,ex,ey;
char dat[maxn][maxn];
node dl[maxn*maxn],last[maxn][maxn];
int getdir(char c)
{
  int i;
  for(i=0;i<4;i++)
    if(c==d[i])
      return i;
}
void wipe(int a,int b,int c)
{
  int i;
  while(dat[a][b]!='X'&&a>0&&b>0&&a<=n&&b<=n)
    {
      map[a][b]=0;
      a+=cx[dir[c]];
      b+=cy[dir[c]];      
    }     
}
void write()
{
  int i,j;
  for(i=1;i<=n;i++)
    {
      for(j=1;j<=n;j++)
        printf("%d ",map[i][j]);  
      printf("\n");
    }     
}
void init()
{
  freopen("guard.in","r",stdin);
  freopen("guard.out","w",stdout);
  scanf("%d%d\n",&n,&g);
  int i,t,j;
  char t1;
  for(i=1;i<=n;i++)
    gets(dat[i]+1);
  for(i=1;i<=g;i++)
    {
      scanf("%d %c\n",&t,&t1);
      dir[t]=getdir(t1);  
    }
  for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
      map[i][j]=1;  
  for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
      {
        if(dat[i][j]=='E')
          {sx=i;sy=j;}
        if(dat[i][j]=='C')
          {ex=i;ey=j;}
        if(dat[i][j]=='X')
          map[i][j]=0;                   
        if(dat[i][j]<='9'&&dat[i][j]>='0')
          {
            wipe(i,j,dir[dat[i][j]-'0']);
          //  printf("\n%c:\n",dat[i][j]);
           // write();
          }
      }
  if(!map[sx][sy])
    {
      printf("-1");
      exit(0);
    }  
}
void out(int a,int b)
{
  if(a==sx&&b==sy) return;
  out(last[a][b].x,last[a][b].y);
  printf("%c\n",d[way[a][b]]);       
}
void calc()
{
  int p1,p2,i,nx,ny;
  dl[1].x=sx;dl[1].y=sy;
  vis[sx][sy]=1;
  for(p1=1,p2=2;p1<p2;p1++)
    for(i=0;i<4;i++)
      {
        nx=dl[p1].x+cx[i];
        ny=dl[p1].y+cy[i];
        if(nx>0&&ny>0&&nx<=n&&ny<=n&&map[nx][ny]&&!vis[nx][ny])
          {
            vis[nx][ny]=1;
            way[nx][ny]=i;
            last[nx][ny]=dl[p1];
            dl[p2].x=nx;
            dl[p2++].y=ny;                                                     
            if(nx==ex&&ny==ey)
              {out(ex,ey);return;}
          }              
      }                       
  printf("-1");
}
int main()
{
  init();
  calc();
  return 0;    
}
