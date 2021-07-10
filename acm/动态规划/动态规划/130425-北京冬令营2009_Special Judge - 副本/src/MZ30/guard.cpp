#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<stdlib.h>
#include<string.h>
using namespace std;
int shut=0,step=0,n,g;
char ans[110];
int a[110][110];
bool vis[110][110];
struct point
{
       int x,y;
}stu[15],cl,ga;

void init()
{
     freopen("guard.in","r",stdin);
     freopen("guard.out","w",stdout);
}

void readdata()
{
     scanf("%d%d",&n,&g);
     char R;
     for(int i=0;i<=n+1;i++)
      for(int j=0;j<=n+1;j++)
       a[i][j]=1;
     for(int i=1;i<=n;i++)
      {
      scanf("\n");
      for(int j=1;j<=n;j++)
       {
              scanf("%c",&R);
              if(R=='.') a[i][j]=0;
              else if(R=='X') a[i][j]=1;
              else if(R=='C') {a[i][j]=0;cl.x=i;cl.y=j;}
              else if(R=='E') {a[i][j]=0;ga.x=i;ga.y=j;}
              else {a[i][j]=0;stu[R-'0'].x=i;stu[R-'0'].y=j;}
       }
      }
      int s;
      for(int i=1;i<=g;i++)
      {
              scanf("\n");
              scanf("%d %c",&s,&R);
              if(R=='N') {for(int j=stu[s].x;;j--) {if(a[j][stu[s].y]==1||!j) break; a[j][stu[s].y]=2;}}
              else if(R=='S') {for(int j=stu[s].x;;j++) {if(a[j][stu[s].y]==1||j==n+1) break; a[j][stu[s].y]=2;}}
              else if(R=='E') {for(int j=stu[s].y;;j++) {if(a[stu[s].x][j]==1||j==n+1) break; a[stu[s].x][j]=2;}}
              else {for(int j=stu[s].y;;j--) {if(a[stu[s].x][j]==1||!j) break; a[stu[s].x][j]=2;}}
      }
}

int dx[]={0,-1,1,0},dy[]={1,0,0,-1};
    char dr[]="ENSW";

void dfs(point q,char c)
{
     if(q.x==cl.x&&q.y==cl.y) {shut=1;ans[++step]=c;return;}
     point p;
     for(int i=0;i<4;i++)
     {
             if(shut) break;
             p.x=q.x+dx[i];
             p.y=q.y+dy[i];
             if(a[p.x][p.y]||vis[p.x][p.y]) continue;
             vis[p.x][p.y]=1;
             dfs(p,dr[i]);
     }
     if(shut&&c!='L') ans[++step]=c;
}

void work()
{
     memset(vis,0,sizeof(vis));
     memset(ans,0,sizeof(ans));
     vis[ga.x][ga.y]=1;
     dfs(ga,'L');
}

void print()
{
     if(shut)
     for(int i=step;i>=1;i--) {printf("%c\n",ans[i]);}
     else printf("-1\n");
}

int main()
{
    init();
    readdata();
    work();
    print();
    return 0;
} 
