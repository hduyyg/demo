#include<string>
#include<iostream>
#include<cstring>
using namespace std;

int n,m,k;
struct point
{
       int x;
       point* next;
       }* p[1100];
int a[11];
char b[11];

void insert(int c,int d)
{
     point* now=new point;
     now->x=d;
     now->next=p[c];
     p[c]=now;
 }
       
void read()
{
     freopen("dependence.in","r",stdin);
     freopen("dependence.out","w",stdout);
     ios::sync_with_stdio(false);
     cin>>n>>m;
     for (int i=1; i<=n; i++)
         b[i]=(char)(64+i),a[i]=1<<(i-1);
     for (int i=0; i<m; i++)
     {
         string now;
         cin>>now;
         int c=0,d=0;
         for (int j=0; now[j]!='-'; j++)
             for (int k=1; k<=n; k++)
                 if (now[j]==b[k]) c=c | a[k];
         for (int j=now.length()-1; now[j]!='>'; j--)
             for (int k=1; k<=n; k++)
                 if (now[j]==b[k]) d=d | a[k];
         insert(c,d);
     }
 }
 
int can[1100];
bool hash[1100];
 
void work()
{
     k=1<<n;
     for (int i=1; i<k; i++)
     {
         memset(hash,0,sizeof(hash));
         int now=i;
         bool flag=1;
         while (flag)
         {
             flag=0;
             for (int j=1; j<k; j++)
                 if (!hash[j] && (now & j)==j)
                 {
                     flag=1;  hash[j]=1;
                     for (point* a=p[j]; a; a=a->next)
                         now=now | (a->x);
                              }
               }
         can[i]=now;
     }
 }
 
string kkk[1100];
 
void print()
{
     int ans=0;
     for (int i=1; i<k; i++)
         if (can[i]==k-1)
         {
             bool flag=1;
             for (int j=1; j<i; j++)
                 if ((j & i)==j && can[j]==k-1)
                 {
                     flag=0; break;
                                     }
             if (flag)
             {
                 string now;
                 for (int j=1; j<=n; j++)
                     if ((i & a[j])==a[j]) now=now+b[j];
                 kkk[++ans]=now;
                      }
                         }
     if (!ans)
     {
         cout<<"No candidate key"<<endl;
         return;
              }
     cout<<ans<<endl;
     for (int i=1; i<=ans; i++)
         cout<<kkk[i]<<endl;
 }

int main()
{
    read();
    work();
    print();
return 0;
}
