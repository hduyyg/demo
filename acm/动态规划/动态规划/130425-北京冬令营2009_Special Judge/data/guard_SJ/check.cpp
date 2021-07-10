#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<string>
using namespace std;
FILE *fscore,*freport,*fstd,*fin,*fout;
int n,m;
const int N=100;
char map[N][N];
char look[N];
bool g[N][N];
struct node{int x,y,step;string s;}st,ta;

void read()
{
	fscanf(fin,"%d%d",&n,&m);
	for(int i=0;i<n;i++) fscanf(fin,"%s",map[i]);
	for(int i=1;i<=m;i++)
	{
		int x;char op;
		fscanf(fin,"%d %c",&x,&op);
		look[x]=op;
	}	
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
		if(map[i][j]=='E') st.x=i,st.y=j;
		else if(map[i][j]=='C') ta.x=i,ta.y=j;
		else if(map[i][j]=='X') g[i][j]=1;
		else if(isdigit(map[i][j])) doit(i,j,map[i][j]-'0');
	}
}



bool Judge()
{
	char s[100];
	fscanf(fstd,"%s",s);
	if(s[0]=='-' && s[1]=='1')
	{
		fscanf(fout,"%s",s);
		if(s[0]=='-' && s[1]=='1') return 1;
		return 0;
	}
	
	read();
	build_map();
	int x=st.x,y=st.y;
	while(fscanf(fout,"%s",s)!=EOF)
	{
		if(s[0]=='N')
		{
			x--;
			if(x<0||x>=n||y<0||y>=n) return 0;
			if(g[x][y]) return 0;
		}
		else if(s[0]=='S')
		{
			x++;
			if(x<0||x>=n||y<0||y>=n) return 0;
			if(g[x][y]) return 0;
		}
		else if(s[0]=='W')
		{
			y--;
			if(x<0||x>=n||y<0||y>=n) return 0;
			if(g[x][y]) return 0;
		}
		else if(s[0]=='E')
		{
			y++;
			if(x<0||x>=n||y<0||y>=n) return 0;
			if(g[x][y]) return 0;
		}
		else return 0;
	}
	return (x==ta.x&&y==ta.y);
}

int main(int argc,char *argv[])
{
	fscore=fopen("score.log","w");//打开得分文件
	freport=fopen("report.log","w");//打开报告文件
	fstd=fopen(argv[2],"r");//打开测试点标准输出文件
	int score=atoi(argv[1]);//取得测试点的分数

	fin=fopen("guard.in","r");//打开测试点标准输入文件
	fout=fopen("guard.out","r");//打开用户的数据输出文件
	if (!fout)
	{
		fprintf(fscore,"%d",0);//返回0分
		fprintf(freport,"no output");//报告Judge结果为no output
	}
	else if (Judge())//Judge后结果为真
	{
		fprintf(fscore,"%d",score);//返回满分
		fprintf(freport,"Accpeted");//报告Judge结果为right
	}
	else
	{
		fprintf(fscore,"%d",0);//返回0分
		fprintf(freport,"Wrong Answer");//报告Judge结果为wrong
	}

	fclose(fscore);//关闭得分文件
	fclose(freport);//关闭报告文件
	return 0;
}
