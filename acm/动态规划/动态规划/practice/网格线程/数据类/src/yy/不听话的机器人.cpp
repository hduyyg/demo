#include<cstdio>
#include<algorithm>
#define maxn (100+10)
#define maxd (4*100*100+100)
using namespace std;

int n,m,x0,y0,sump;
int newd,newx,newy;
int f[2][maxn][maxn][4];
bool flag[maxn][maxn];
char s[20];
struct tnode{int x,y,d;}p[maxd];

void init()
{
  freopen("robot.in","r",stdin);
  freopen("robot.out","w",stdout);
}

void readdata()
{
  scanf("%d%d%d%d\n",&n,&m,&x0,&y0);
  sump=1,p[1].x=x0,p[1].y=y0,p[1].d=0;
  f[0][x0][y0][0]=1;
  
  int i,j;
  for(i=1;i<=n;i++)
    for(scanf("%s\n",s+1),j=1;j<=n;j++)
      if(s[j]=='.')flag[i][j]=1;
}

inline bool forward(int j)
{
  newd=p[j].d;  
  switch(p[j].d)
    {
      case 0 :newx=p[j].x-1,newy=p[j].y;
              break;
      case 1 :newx=p[j].x,newy=p[j].y-1;
	          break;
	  case 2 :newx=p[j].x+1,newy=p[j].y;
	          break;
	  default:newx=p[j].x,newy=p[j].y+1;
	          break;	 			        
    }
  if(newx<1 || newx>n || newy<1 || newy>n)return 0;
  return flag[newx][newy];  
}

inline bool back(int j)
{
  newd=p[j].d;  
  switch(p[j].d)
    {
      case 0 :newx=p[j].x+1,newy=p[j].y;
              break;
      case 1 :newx=p[j].x,newy=p[j].y+1;
	          break;
	  case 2 :newx=p[j].x-1,newy=p[j].y;
	          break;
	  default:newx=p[j].x,newy=p[j].y-1;
	          break;	 			        
    }
  if(newx<1 || newx>n || newy<1 || newy>n)return 0;
  return flag[newx][newy];  
} 

bool get_new(int j)
{
  switch(s[0])
    {
      case 'F':return forward(j);
      case 'B':return back(j);
	  case 'L':newd=(p[j].d+1)%4;
	           break;
	  default :newd=(p[j].d+3)%4;
	           break;   		   		            
    }
  newx=p[j].x,newy=p[j].y;
  return 1;	  
}

void work()
{
  int i,j,k,len;
  for(i=1;i<=m;i++)
    {
	  //不执行指令	
      for(j=1;j<=sump;j++)
        f[i%2][p[j].x][p[j].y][p[j].d]=f[(i+1)%2][p[j].x][p[j].y][p[j].d];
      
	  //执行指令  
      for(scanf("%s",s),j=sump;j>0;j--)
        {
          if(!get_new(j))continue;
        
		  if(f[i%2][newx][newy][newd]==0)
		    p[++sump].d=newd,p[sump].x=newx,p[sump].y=newy;
          
	      if(f[i%2][newx][newy][newd]<f[(i+1)%2][p[j].x][p[j].y][p[j].d]+1)
            f[i%2][newx][newy][newd]=f[(i+1)%2][p[j].x][p[j].y][p[j].d]+1;
        }
    }
  
  k=m%2,len=0;	 
  for(i=1;i<=sump;i++)len=max(len,f[k][p[i].x][p[i].y][p[i].d]);
  printf("%d\n",m-len+1);   
}

int main()
{
  init();
  readdata();
  work();
  return 0;
}
