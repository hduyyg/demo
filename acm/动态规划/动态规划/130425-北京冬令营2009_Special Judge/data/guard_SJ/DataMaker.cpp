/**********************************************************
*    Description:     Use standard to make test data      *
*    Environment:     DEV C++ 4.9.9.1 , windows xp        *
*    Version:         1.0                                 *
*    Author:          jiangzh                             *
*    Date:            20121026                            *
***********************************************************/
#include<cstdio>
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<ctime>
#include<cctype>
#include<windows.h>
using namespace std;


//Attention:标程必须   标准   输入输出！！！

typedef long long LL;

string  STD_FILE=  "guard" ;            //题目文件名 (不含后缀名)
int     MinNum= 1  ;                     //输入输出最小下标
int     MaxNum= 10 ;                    //输入输出最大下标
string  STD_IN=  ".in" ;                 //标准输入文件后缀名
string  STD_OUT=  ".ans" ;               //标准输出文件后缀名

string tostring(int x)
{
    string s="";
    do{
        char ch=x%10+'0';
        s=ch+s;
        x/=10;
    }while(x);
    return s;
}

int random(int n)
{
    double ran=(double)rand()/(double)RAND_MAX;//生成[0,1]的随机数
    return (int)(ran*(n-1)+0.5);//返回区间[0,n)中的整数
}

void mkdata(int k)//自定义随机数据生成数据
{
	int n,m;
	if(k<3) n=5,m=2;
	else if(k<7) n=rand()%5+4,m=rand()%2+2;
	else n=10,m=4;
	printf("%d %d\n",n,m);
	char map[20][20];
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			char op=(rand()%100>75)?'X':'.';
			map[i][j]=op;
		}
	}
	int h[20][20]={0};
	for(int i=1;i<=m;i++)
	{
		int x=rand()%n+1,y=rand()%n+1;
		while(h[x][y])
		{
			x=rand()%n+1;
			y=rand()%n+1;
		}
		h[x][y]=1;
		map[x][y]=i+'0';
	}

	int x=rand()%n+1,y=rand()%n+1;
	while(h[x][y])
	{
		x=rand()%n+1;
		y=rand()%n+1;
	}
	h[x][y]=1;
	map[x][y]='E';

	x=rand()%n+1,y=rand()%n+1;
	while(h[x][y])
	{
		x=rand()%n+1;
		y=rand()%n+1;
	}
	h[x][y]=1;
	map[x][y]='C';

	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			printf("%c",map[i][j]);
		printf("\n");
	}
	for(int i=1;i<=m;i++)
	{
		int ra=rand()%100;
		char op;
		if(ra>75) op='N';
		else if(ra>50) op='S';
		else if(ra>25) op='W';
		else op='E';
		printf("%d %c\n",i,op);
	}
}

int main()
{
    string COMMAND;
    srand(time(0));
    for(int i = MinNum ; i <= MaxNum ; i++)
    {
        cerr<<"正在生成第 "<<i<<" 组数据.............."<<endl;

        string   IN_FILE  =  STD_FILE + tostring(i) + STD_IN  ;  //输入文件名
        string  OUT_FILE  =  STD_FILE + tostring(i) + STD_OUT ;  //输出文件名

        //生成输入数据
        freopen((char*)IN_FILE.c_str(),"w",stdout);
        mkdata(i);
        fclose(stdout);

        //生成输出数据
        COMMAND = STD_FILE + ".exe < " + IN_FILE  + " > " + OUT_FILE ;
        system((char*)COMMAND.c_str());
    }

    cerr<<endl<<MinNum<<" ~ "<<MaxNum<<" 共 "<<MaxNum-MinNum+1<<" 组数据生成完毕！"<<endl;
    cerr<<endl<<"--------------按任意键结束--------------"<<endl;
    system("pause");
    return 0;
}
