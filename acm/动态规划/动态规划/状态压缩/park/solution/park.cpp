#include<cstdio>
#include<cstring>
struct
{
      long q,s;
      bool f;
} w[3000][7][2];
long n,m,e=1,i,j,p,q,k,ans=-100000000,d[3000],f[3000],c[101][7];
void trans(long p,long r[7])
{
     long i;
     for (i=m;i>=0;i--)
     {
         r[i]=p%3;
         p/=3;
     }     
}
long retrans(long r[7])
{
     long i,p=0;
     for (i=0;i<=m;i++) p=p*3+r[i];
     return(p);
}
long color(long p,long k,long x,long y)
{
     long i,r[7];
     trans(p,r);
     r[k]=x;
     r[k+1]=y;
     return(retrans(r));
}
long link(long p,long k)
{
     long i,j,s,r[7],v[7];
     trans(p,r);
     for (i=0;i<m;i++) if (r[i]==1)
                       {
                          s=1;
                          for (j=i+1;s;j++) if (r[j]==1) s++; else if (r[j]==2) s--;
                          v[i]=j-1;
                          v[j-1]=i;
                       }
     if (r[k]==1 && r[k+1]==1) r[v[k+1]]=1; else if (r[k]==2 && r[k+1]==2) r[v[k]]=2;
     r[k]=r[k+1]=0;
     return(retrans(r));
}
void pretreat(long p)
{
     long s,i,j,q,r[7];
     trans(p,r);
     if (p==135)
     i=1;
     for (i=j=s=0;i<=m;i++)
     {
         if (r[i]==1) s++;
         if (r[i]==2) j++;
         if (s<j) return;
     }
     if (s!=j) return;
     for (i=1;i<=m;i++) if (r[i-1]==0 && r[i]==0)
                     {
                        w[p][i][0].f=w[p][i][1].f=true;
                        w[p][i][0].q=p;
                        w[p][i][1].q=color(p,i-1,1,2);
                        w[p][i][1].s=1;
                     }
                     else if (r[i-1]!=0 && r[i]!=0)
                     {
                          if (r[i-1]==1 && r[i]==2 && s!=1) continue;
                          w[p][i][0].f=true;
                          w[p][i][0].q=link(p,i-1);
                          w[p][i][0].s=1;
                     }
                     else
                     {
                         w[p][i][0].f=w[p][i][1].f=true;
                         w[p][i][0].q=color(p,i-1,r[i-1]+r[i],0);
                         w[p][i][1].q=color(p,i-1,0,r[i-1]+r[i]);
                         w[p][i][0].s=w[p][i][1].s=1;
                     }
     if (w[p][m][0].q%3==0) w[p][m][0].q/=3; else w[p][m][0].f=false;
     if (w[p][m][1].q%3==0) w[p][m][1].q/=3; else w[p][m][1].f=false;
}
int main()
{
    freopen("park.in","r",stdin);
    freopen("park.out","w",stdout);
    memset(w,0,sizeof(w));
    scanf("%d%d",&n,&m);
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++) scanf("%d",&c[i][j]);
    for (i=0;i<=m;i++) e*=3;
    for (i=0;i<e;i++) pretreat(i);
    memset(d,-7000,sizeof(d));
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++)
        {
            d[0]=0;
            memset(f,-7000,sizeof(f));
            for (p=0;p<e;p++) if (d[p]>-100000000)
                for (k=0;k<2;k++) if (w[p][j][k].f)
                {
                    q=w[p][j][k].q;
                    f[q]>?=d[p]+c[i][j]*w[p][j][k].s;
                    if (p!=0 && q==0) ans>?=d[p]+c[i][j]*w[p][j][k].s;
                }
            memmove(d,f,sizeof(d));
        }
    printf("%d\n",ans);
    fclose(stdin);
    fclose(stdout);
    return(0);
}
