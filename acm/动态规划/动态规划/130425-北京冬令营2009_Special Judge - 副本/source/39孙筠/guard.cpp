#include <iostream>
#include <cstring>
#include <cstdio>
#include <string> 
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;

struct p
{
       int x,y;
       } B,E;
struct wh
{
       char f;
       int x;
       }from [20000];

int map[100][100];
int hash[100][100];
int N,G,x,y;
p queue[20000];

void print(int v)
{
     if (from[v].x==0) return;
     print(from[v].x);
     cout<<from[v].f<<endl;
     }

int main()
{
     //===============================先把兽哥割了==========================================init
     freopen("guard.in","r",stdin);
     freopen("guard.out","w",stdout);
     ios::sync_with_stdio(false);       
     for (int i=0;i<=99;i++)
       for (int j=0;j<=99;j++)
         map[i][j]=1;     
     //===============================再把罗睿割了==========================================readdata
     string str;
     cin>>N>>G;
     p g[G];
     getline(cin,str);
     for (int i=1;i<=N;i++)
     {
         getline(cin,str);
         aa:
           if (str[0]==' ') 
           {
                         str.erase(0,1);
                         goto aa;
                         }
         for (int j=1;j<=str.size();j++)
         {
             if (str[j-1]>='1' && str[j-1]<='9')
             {
                               g[int(str[j-1])-48].x=i;
                               g[int(str[j-1])-48].y=j;
                               map[i][j]=2; continue;                               
                               }
             if (str[j-1]=='C')
             {
                               E.x=i; E.y=j; map[i][j]=4; 
                               continue;
                               }
             if (str[j-1]=='E')
             {
                               B.x=i; B.y=j; map[i][j]=0;
                               continue;
                               }
             if (str[j-1]=='X')
             {
                               map[i][j]=1;
                               continue;
                               }
             map[i][j]=0;
             }
         }
     char fx;
     int xx,yy,cx,cy;
     for (int i=1;i<=G;i++)
     {
         getline(cin,str);
         aaa:
           if (str[0]==' ') 
           {
                         str.erase(0,1);
                         goto aaa;
                         }
         aaaa:
           if (str[str.size()-1]==' ') 
           {
                         str.erase(str.size()-2,str.size()-1);
                         goto aaaa;
                         }
         fx=str[str.size()-1];
         cx=xx=g[int(str[0])-48].x;
         cy=yy=g[int(str[0])-48].y;
         if (fx=='W')
         {
                     while (map[cx][cy]!=1)
                     {
                           map[cx][cy]=1;
                           cy--;
                           }
                     }
         if (fx=='E')
         {
                     while (map[cx][cy]!=1)
                     {
                           map[cx][cy]=1;
                           cy++;
                           }
                     }
         if (fx=='N')
         {
                     while (map[cx][cy]!=1)
                     {
                           map[cx][cy]=1;
                           cx++;
                           }
                     }
         if (fx=='S')
         {
                     while (map[cx][cy]!=1)
                     {
                           map[cx][cy]=1;
                           cx--;
                           }
                     }
         }
     //===============================最后割李宸宸==========================================main 
     int l,r,rr;
     l=0; r=1;
     memset(hash,0,sizeof(hash));
     queue[1].x=B.x;
     queue[1].y=B.y;
     bool flag=false;
     hash[queue[1].x][queue[1].y]=true;
     while (l<r)
     {
           l++;
           rr=l;
           xx=queue[l].x;
           yy=queue[l].y;
           if (map[xx+1][yy]!=1 && (!hash[xx+1][yy]))
           {
                               r++;
                               queue[r].x=xx+1;
                               queue[r].y=yy;
                               from[r].f='S';
                               from[r].x=rr;
                               if (map[xx+1][yy]==4)
                               {
                                                    flag=true;
                                                    break;
                                                    }
                               hash[xx+1][yy]=true;
                               }
           if ((map[xx-1][yy]!=1) && (!hash[xx-1][yy]))
           {
                               r++;
                               queue[r].x=xx-1;
                               queue[r].y=yy;
                               from[r].f='N';
                               from[r].x=rr;
                               if (map[xx-1][yy]==4)
                               {
                                                    flag=true;
                                                    break;
                                                    }
                               hash[xx-1][yy]=true;
                               }
           if ((map[xx][yy+1]!=1) && (!hash[xx][yy+1]))
           {
                               r++;
                               queue[r].x=xx;
                               queue[r].y=yy+1;
                               from[r].f='E';
                               from[r].x=rr;
                               if (map[xx][yy+1]==4)
                               {
                                                    flag=true;
                                                    break;
                                                    }
                               hash[xx][yy+1]=true;
                               }
           if ((map[xx][yy-1]!=1) && (!hash[xx][yy-1]))
           {
                               r++;
                               queue[r].x=xx;
                               queue[r].y=yy-1;
                               from[r].f='W';
                               from[r].x=rr;
                               if (map[xx][yy-1]==4)
                               {
                                                    flag=true;
                                                    break;
                                                    }
                               hash[xx][yy-1]=true;
                               }
           }
     if (!flag)
     {
               cout<<(-1);
               return 0;
               }
     print(r);
     return 0;
     }















