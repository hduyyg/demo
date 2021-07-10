#include <cstdio>
#include <cstring>
using namespace std;

const int maxn=128,maxm=1024;
char maze[maxn][maxn];
char query[maxm];//F:FORWARD B:BACK L:LEFT R:RIGHT
int N,M,X0,Y0;
unsigned f[2][maxn][maxn][4];//表示前i条命令执行完以后在X、Y时，面朝某方向时最少需要删除的命令，0123上右下左 

void input(){
	scanf("%d %d %d %d\n",&N,&M,&X0,&Y0);
	memset(maze,'*',sizeof(maze));
	for(int i=1;i<=N;++i){
		gets(maze[i]+1);
		maze[i][N+1]='*';
	}
	for(int i=0;i<M;++i){
		gets(query+i);
	}
}
template <class T>
void update(T& o,T x){
	if(o>x)o=x;
}
void solve(){
	const int dx[4]={-1,0,1,0};
	const int dy[4]={0,1,0,-1};
	memset(f,~0,sizeof(f));
	f[0][X0][Y0][0]=0;
	for(int k=0;k<M;++k){
		memset(f[!(k&1)],~0,sizeof(f)/2);
		for(int x=1;x<=N;++x)
			for(int y=1;y<=N;++y){
				if(maze[x][y]=='*')continue;
				for(int d=0;d<4;++d){
					if(f[k&1][x][y][d]==~0)continue;
					update(f[!(k&1)][x][y][d],f[k&1][x][y][d]+1);
					int nextx=x,nexty=y,nextd=d;
					switch(query[k]){
						case 'F':
							nextx+=dx[d];
							nexty+=dy[d];
							break;
						case 'B':
							nextx-=dx[d];
							nexty-=dy[d];
							break;
						case 'R':
							nextd++;
							nextd%=4;
							break;
						case 'L':
							nextd--;
							if(nextd==-1)
								nextd=3;
					}
					update(f[!(k&1)][nextx][nexty][nextd],f[k&1][x][y][d]);
			}
		}
	}
}
void output(){
	unsigned int res=~0;
	for(int x=1;x<=N;++x)
		for(int y=1;y<=N;++y){
			if(maze[x][y]=='*')continue;
			for(int d=0;d<4;++d)
				update(res,f[M&1][x][y][d]);
	}
	printf("%d\n",res);
}
int main(){
	freopen("robot.in","r",stdin);
	freopen("robot.out","w",stdout);
	input();
	solve();
	output();
}
