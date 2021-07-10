#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<string>
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

int n,g,tx,ty,sx,sy;
const int maxn=10;
char map[maxn+1][maxn+1];
const int x[4]={1,0,-1,0};
const int y[4]={0,1,0,-1};
const char z[4]={'S','E','N','W'};

void read()
{
     freopen("guard.in","r",stdin);
     freopen("guard.out","w",stdout);
     scanf("%d%d",&n,&g);
     for (int i=1; i<=n; i++)
     {
         string now;
         cin>>now;
         for (int j=0; j<n; j++)
         {
             map[i][j+1]=now[j];
             if (now[j]=='C')
                 tx=i,ty=j+1;
             if (now[j]=='E')
                 sx=i,sy=j+1;
         }
     }
     for (int k=1; k<=g; k++)
     {
         char c,d;
         c=(getchar(),getchar());
         for (int i=1; i<=n; i++)
             for (int j=1; j<=n; j++)
                 if (map[i][j]==c)
                 {
                     d=(getchar(),getchar());
                     if (d=='E') for (int l=j; l<=n && map[i][l]!='X'; l++)
                                     if (map[i][l]!='C') map[i][l]='X';
                     if (d=='W') for (int l=j; l>0 && map[i][l]!='X'; l--)
                                     if (map[i][l]!='C') map[i][l]='X';
                     if (d=='N') for (int l=i; l>0 && map[l][j]!='X'; l--)
                                     if (map[l][j]!='C') map[l][j]='X';
                     if (d=='S') for (int l=i; l<=n && map[l][j]!='X'; l++)
                                     if (map[l][j]!='C') map[l][j]='X';
                                    }
     }
 }

priority_queue <pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
struct point
{
       int f,s,w,x,y;
       }l[100000];
int k=0;
bool hash[11][11];

int f(int x)
{
    int a=abs(l[x].x-tx),b=abs(l[x].y-ty);
    return l[x].s+a+b;
}

void A_star()
{
     while (!q.empty()) q.pop();
     l[k].f=0;  l[k].s=0;
     l[k].w=-1; l[k].x=sx; l[k].y=sy;
     hash[sx][sy]=1;
     q.push(make_pair(f(k),k));
     if (map[sx][sy]=='X') 
     {
         printf("%d",-1);
         exit(0);
                           }
     
     while (!q.empty())
     {
         int now=q.top().second;
         q.pop();
         int a=l[now].x,b=l[now].y;
         
         for (int i=0; i<4; i++)
             if (map[a+x[i]][b+y[i]]!='X' && !hash[a+x[i]][b+y[i]])
             {
                 ++k;
                 l[k].f=now;  l[k].s=l[now].s+1;
                 l[k].w=i;   l[k].x=a+x[i];  l[k].y=b+y[i];
                 hash[a+x[i]][b+y[i]]=1;
                 q.push(make_pair(f(k),k));
                 
                 if (a+x[i]==tx && b+y[i]==ty) return;
                                          }
           }
     printf("%d",-1);
     exit(0);
 }
 
void print(int x)
{
     if (!x) return;
     print(l[x].f);
     printf("%c\n",z[l[x].w]);
 }

int main()
{
    read();
    A_star();
    print(k);
return 0;
}
