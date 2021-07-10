#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<stdlib.h>
#include<string.h>
#define LL long long 
using namespace std;
int n,m;
int own[1010],tar[1010];
int houx[1050];
char c[1050][20];
bool vis[1010];
void init()
{
     freopen("dependence.in","r",stdin);
     freopen("dependence.out","w",stdout);
}

int g(int v)
{
    int ans=1;
    while(v--)
    {
              ans*=2;
    }
    return ans;
}

void readdata()
{
     scanf("%d%d",&n,&m);
     memset(own,0,sizeof(own));
     memset(tar,0,sizeof(tar));
     char S[25];
     for(int i=1;i<=m;i++)
     {
             memset(S,0,sizeof(S));
             scanf("%s",S);
             int j;
             for(j=0;;j++)
             {
                     if(S[j]=='-') break;
                     own[i]+=g(S[j]-'A');
             }
             for(int u=j+2;u<strlen(S);u++)
             {
                     tar[i]+=g(S[u]-'A');
             }
     }
}

bool dfs(int k)
{
     int en=g(n)-1,mov=k,be;
     for(;;)
     {
            be=mov;
            for(int i=1;i<=m;i++)
            {
                    if(vis[i]) continue;
                    if((own[i]&mov)==own[i]) {mov=tar[i]|mov;vis[i]=1;}
            }
            if(mov==be||mov==en) break;
            //printf("%d\n",mov);
     }
     if(mov==en) return true;
     else return false;
}

bool cmp(int a,int b)
{
     int v=1;
     for(int i=1;i<=n;i++) {
                   if((v&a)!=(v&b)) {if(!(v&a)) return false;else return true;}//位运算的优先级很小！！！ 
                   v*=2;
             }
     return true;
}

int gf(int v)
{
    int ans=0;
    while(v>1)
    {
            v/=2;
            ans++;
    }
    return ans;
}

void work()
{
     int tot=0;
     bool ok;
     for(int i=1;i<g(n);i++)
     {
             ok=0;
             for(int j=1;j<=tot;j++)
             if((houx[j]&i)==houx[j]) {ok=1;break;}//位运算的优先级很小，要勤于打括号，例如a&b==c是错的，应该是(a&b)==c!! 
             if(ok) continue;
             memset(vis,0,sizeof(vis));
             if(dfs(i)) houx[++tot]=i;
     }
     sort(houx+1,houx+tot+1,cmp);
     int v,head;
     for(int i=1;i<=tot;i++)
     {
           v=1;
           head=0;
           for(int j=1;j<=n;j++)  
           {
           if((v&houx[i])) {c[i][head]='A'+gf(v);head++;}
           v*=2;
           }
     }
     printf("%d\n",tot);
     for(int i=1;i<=tot;i++)
     {
             printf("%s\n",c[i]);
     }
}

void print()
{
}

int main()
{
    init();
    readdata();
    work();
    print();
    return 0;
} 
