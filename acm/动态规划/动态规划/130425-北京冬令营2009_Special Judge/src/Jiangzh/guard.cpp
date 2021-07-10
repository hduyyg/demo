#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<queue>
#include<string>
#include<iostream>
using namespace std;
const int N=50;
const int dx[]={0,0,1,-1};
const int dy[]={1,-1,0,0};
const string way[]={"E","W","S","N"};
int n,m;
char map[N][N];
char look[N];
bool g[N][N];
struct node{int x,y,step;string s;}s,t;
bool h[N][N];
queue<node> q;

void read()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++) scanf("%s",map[i]);
	for(int i=1;i<=m;i++)
	{
		int x;char op;
		scanf("%d %c",&x,&op);
		look[x]=op;
	}	
	//for(int i=0;i<n;i++) puts(map[i]);
	//for(int i=1;i<=m;i++) printf("%d %c\n",i,look[i]);
}

void doit(int x,int y,int s)
{
	if(x<0||x>=n||y<0||y>=n) return;
	if(map[x][y]=='X') return;
	g[x][y]=1;
	if(look[s]=='N') doit(x-1,y,s);
	else if(look[s]=='S') doit(x+1,y,s);
	else if(look[s]=='W') doit(x,y-1,s);
	else if(look[s]=='E') doit(x,y+1,s);
}

void build_map()
{
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)
	{
		if(map[i][j]=='E') s.x=i,s.y=j;
		else if(map[i][j]=='C') t.x=i,t.y=j;
		else if(map[i][j]=='X') g[i][j]=1;
		else if(isdigit(map[i][j])) doit(i,j,map[i][j]-'0');
	}
}

node expand(node a,int k)
{
	node res=a;
	res.x=a.x+dx[k];
	res.y=a.y+dy[k];
	res.step++;
	res.s+=way[k];
	if(res.x<0||res.x>=n) return a;
	if(res.y<0||res.y>=n) return a;
	if(g[res.x][res.y]) return a;
	return res;
}

void work()
{
	build_map();
	
	s.step=0;q.push(s);
	if(g[s.x][s.y]) {printf("-1\n");exit(0);}
	
	while(!q.empty())
	{
		node tmp=q.front();q.pop();
		//printf("%d %d %d ",tmp.x,tmp.y,tmp.step);
		//cout<<tmp.s<<endl;
		for(int k=0;k<4;k++)
		{
			node newtmp=expand(tmp,k); 
			if(!h[newtmp.x][newtmp.y]&&!g[newtmp.x][newtmp.y])
			{
				h[newtmp.x][newtmp.y]=1;
				q.push(newtmp);
				if(newtmp.x==t.x&&newtmp.y==t.y)
				{
					//printf("%d\n",newtmp.step);
					//cout<<newtmp.s<<endl;
					for(int i=0;i<newtmp.step;i++)
						printf("%c\n",newtmp.s[i]);
					exit(0);
				}
			}
		}
	}
	printf("-1\n");
}

int main()
{
	freopen("guard.in","r",stdin);
	freopen("guard.out","w",stdout);
	read();
	work();
	return 0;
}
