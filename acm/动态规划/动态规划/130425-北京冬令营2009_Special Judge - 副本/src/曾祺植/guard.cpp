#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cctype>
using namespace std;
const char h[4] = {'N','S','W','E'};
const int dx[] = {-1,1,0,0};
const int dy[] = {0,0,-1,1};
const int maxn = 100 + 10;
int map[maxn][maxn];
int tmpx[maxn],tmpy[maxn];
char g[maxn];
bool flag[maxn][maxn];
int n,m,cnt = 0;
int sx,sy,tx,ty;
int s,t;
void init()
{
	freopen("guard.in","r",stdin);
	freopen("guard.out","w",stdout);
}

void readdata()
{
	scanf("%d%d\n",&n,&m);
	for(int i = 1;i <= n;i++)
	{
		char op;
		for(int j = 1;j <= n;j++)
		{
			scanf("%c",&op);
			if(op == '.')map[i][j] = 0;
			if(op == 'X')map[i][j] = 1;
			if(op == 'E')sx = i,sy = j;
			if(op == 'C')tx = i,ty = j;
			if(isdigit(op))
			{
				map[i][j] = 1;
				tmpx[op-'0'] = i;
				tmpy[op-'0'] = j;
			}
		}
		scanf("\n");
	}
	for(int i = 1;i <= m;i++)
	{
		int p;
		char op[4];
		scanf("%d%s",&p,op);
		if(op[0] == 'N')
		{
			for(int j = tmpx[i] - 1;j >= 1;j--)
			{
				if(map[j][tmpy[i]])break;
				map[j][tmpy[i]] = 1;
			}
		}
		if(op[0] == 'S')
		{
			for(int j = tmpx[i] + 1;j <= n;j++)
			{
				if(map[j][tmpy[i]])break;
				map[j][tmpy[i]] = 1;
			}
		}
		if(op[0] == 'W')
		{
			for(int j = tmpy[i] - 1;j >= 1;j--)
			{
				if(map[tmpx[i]][j])break;
				map[tmpx[i]][j] = 1;
			}
		}
		if(op[0] == 'E')
		{
			for(int j = tmpy[i] + 1;j <= n;j++)
			{
				if(map[tmpx[i]][j])break;
				map[tmpx[i]][j] = 1;
			}
		}
	}
}

void print(int sum)
{
    int len = strlen(g);
	for(int i = 0;i < len;i++)
    printf("%c\n",g[i]);
}

void dfs(int x,int y,int step)
{
	if(x == tx && y == ty)
	{
		print(step);
		exit(0);
	}
	for(int p = 0;p < 4;p++)
	{
		int nx = x + dx[p],ny = y + dy[p];
		if(nx < 1 || nx > n || ny < 1 || ny > n)continue;
		if(map[nx][ny] == 1 || flag[nx][ny])continue;
		map[nx][ny] = true;
		g[step] = h[p];
		dfs(nx,ny,step+1);
		g[step] = ' ';
		map[nx][ny] = false;
	}
}

void solve()
{
	memset(flag,false,sizeof(flag));
	flag[sx][sy] = true;
	if(map[sx][sy])
	{
		printf("-1\n");
		return;
	}
	dfs(sx,sy,0);
	printf("-1\n");
}

int main()
{
	init();
	readdata();
	solve();
	return 0;
}
