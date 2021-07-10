#include<cstdio>
#include<algorithm>
#include<iostream>
#include<queue>
using namespace std;
const int dx[4]={-1,0,1,0};
const int dy[4]={0,-1,0,1};
struct node
{
    int x,y,pre;
};
node q[500000];
int n,g;
char map[20][20];
int vis[20][20];
bool col[20][20];
int sx,sy,ex,ey;
bool color[20][20];
char ans[200];

void read()
{
	freopen("guard.in","r",stdin);
	freopen("guard.out","w",stdout);
	scanf("%d%d",&n,&g);
	for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            cin>>map[i][j];
        }
    for(int i=1;i<=g;i++)
    {
        char op[3],x[3];
        cin>>x>>op;
        for(int j=1;j<=n;j++)
            for(int k=1;k<=n;k++)
            {
                if(map[j][k]==x[0])
                {
                    if(op[0]=='W')vis[j][k]=1;
                    if(op[0]=='S')vis[j][k]=2;
                    if(op[0]=='E')vis[j][k]=3;
                    if(op[0]=='N')vis[j][k]=4;
                }
            }
    }
}

bool check(node tmp)
{
    int x=tmp.x,y=tmp.y;
    if(x>=1 &&x<=n && y>=1 &&y<=n && col[x][y]!=true &&(map[x][y]=='.'||map[x][y]=='C')&&!color[x][y])return true;
    return false;
}

void end(int r)
{
	int cnt=0;
	while (q[r].pre)
	{
        int l=q[r].pre;
		if (q[r].x==q[l].x)
		{
			if (q[r].y>q[l].y)
				ans[++cnt]='E';
			else
				ans[++cnt]='W';
		}
		else
		{
			if (q[r].x<q[l].x)
				ans[++cnt]='N';
			else
				ans[++cnt]='S';
		}
		r=l;
	}
	for (int i=cnt;i>0;i--)
	{
		printf("%c\n",ans[i]);
	}
}

void bfs()
{
    memset(q,0,sizeof(q));
    node tmp;
	tmp.x=sx;
	tmp.y=sy;
	tmp.pre=0;
	int l=0,r=0;
	q[++r]=tmp;

	while(l<r)
	{
        if(col[sx][sy])break;
		node u=q[++l];
		if(u.x==ex && u.y==ey)
		{
			end(l);
			return;
		}
		for(int i=0;i<4;i++)
		{
            node v;
			v.x=u.x+dx[i];
			v.y=u.y+dy[i];
			if(check(v))
			{
				v.pre=l;
	  			color[v.x][v.y]=false;
				q[++r]=v;
			}
		}
	}
	printf("-1");
}

void work()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(map[i][j]=='E'){sx=i;sy=j;}
            if(map[i][j]=='C'){ex=i;ey=j;}
            if(vis[i][j]==1)
            {
                for(int k=j;k>=1;k--)
                {
                    if(map[i][k]=='X')break;
                    col[i][k]=true;
                }
            }
            if(vis[i][j]==2)
            {
                for(int k=i;k<=n;k++)
                {
                    if(map[k][j]=='X')break;
                    col[k][j]=true;
                }
            }
            if(vis[i][j]==3)
            {
                for(int k=j;k<=n;k++)
                {
                    if(map[i][k]=='X')break;
                    col[i][k]=true;
                }
            }
            if(vis[i][j]==4)
            {
                for(int k=i;k>=1;k--)
                {
                    if(map[k][j]=='X')break;
                    col[k][j]=true;
                }
            }
            //if(col[i][j]==true)printf("%d %d\n",i,j);
        }
    }
    bfs();

}

int main()
{
	read();
	work();
	return 0;
}
