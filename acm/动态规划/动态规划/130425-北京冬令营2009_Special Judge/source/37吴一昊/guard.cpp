#include <cstdio>
long N;long G;
long gx[15];
long gy[15];
long dx[4] = {-1,0,1,0};
long dy[4] = {0,-1,0,1};

long Sx;long Sy;
long Ex;long Ey;

struct node
{
	long x;
	long y;	
	long f;
};
node que[500000];
bool map[15][15];
char ans[200];
long cnt=0;

void output(long r)
{
	cnt = 0;
	while (que[r].f)
	{
		long l = que[r].f;
		if (que[r].x==que[l].x)
		{
			if (que[r].y>que[l].y)
				ans[++cnt] = 'E';
			else
				ans[++cnt] = 'W';
		}
		else
		{
			if (que[r].x<que[l].x)
				ans[++cnt] = 'N';
			else
				ans[++cnt] = 'S';
		}
		r = l;
	}
	for (long i=cnt;i>0;i--)
	{
		printf("%c\n",ans[i]);
	}
}

void bfs()
{
	node uu;
	node vv;
	uu.x = Sx;
	uu.y = Sy;
	uu.f = 0;
	long l = 0;
	long r = 0;
	que[++r] = uu;
	
	while (l < r)
	{
		uu = que[++l];
		if (uu.x == Ex && uu.y == Ey)
		{
			output(l);
			return;
		}
		for (long i=0;i<4;i++)
		{
			vv.x = uu.x+dx[i];
			vv.y = uu.y+dy[i];
			if (map[vv.x][vv.y])
			{
				vv.f = l;
	  			map[vv.x][vv.y] = false;
				que[++r] = vv;
			}
		}
	}
	printf("-1");
}

int main()
{
	freopen("guard.in","r",stdin);
	freopen("guard.out","w",stdout);
	
	scanf("%ld%ld",&N,&G);
 	for (long i=1;i<N+1;i++)
	{
		scanf("\n");
 		for (long j=1;j<N+1;j++)
		{
			char tmp;
			scanf("%c",&tmp);
			if (tmp == 'E')
			{
				Sx = i;
				Sy = j;
				map[i][j] = true;
			}
			else if (tmp == 'X')
			{
				map[i][j] = false;
			}
			else if (tmp == '.')
			{
				map[i][j] = true;
			}
			else if (tmp == 'C')
			{
				map[i][j] = true;
				Ex = i;
				Ey = j;
			}
			else
			{
				long index = tmp-'0';
				gx[index] = i;
				gy[index] = j;
				map[i][j] = true;
			}
		}
	}
	for (long i=0;i<N+2;i++)
	{
		map[0][i] = map[i][0] = map[N+1][i] = map[i][N+1] = false;
	}
	for (long k=1;k<G+1;k++)
	{
		long ind;char dir;
		scanf("%ld",&ind);
		scanf(" ");
		scanf("%c",&dir);
		if (dir == 'N')
		{
			long j = gy[ind];
			for (long i=gx[ind];i>0&&map[i][j];i--)
			{
				map[i][j] = false;
			}
		}
		if (dir == 'S')
		{
			long j = gy[ind];
			for (long i=gx[ind];i<N+1&&map[i][j];i++)
			{
				map[i][j] = false;	
			}	
		}
		if (dir == 'W')
		{
			long i = gx[ind];
			for (long j=gy[ind];j>0&&map[i][j];j--)
			{
				map[i][j] = false;
			}
		}
		if (dir == 'E')
		{
			long i = gx[ind];
			for (long j=gy[ind];j<N+1&&map[i][j];j++)
			{
				map[i][j] = false;	
			}
		}
	}
	if (!map[Sx][Sy])
	{
		printf("-1");
		return 0;
	}
	bfs();
	return 0;
}
