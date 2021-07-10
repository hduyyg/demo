#include<cstdio>
#include<cstring>
long n,m,i,j,c,a[300],d[300][300];
long cost(long x,long y,long k)
{
     long s,t;
     if (x==0) s=1; else s=a[x-1]+1;
     if (y==n-1) t=m; else t=a[y+1]-1;
     t<?=m;
     if (s>t) return(0); else return(t-s+1);
}
long dfs(long x,long y)
{
     long k;
     if (x>y) return(0);
     if (d[x][y]<2000000000) return(d[x][y]);
     for (k=x;k<=y;k++) d[x][y]<?=dfs(x,k-1)+dfs(k+1,y)+cost(x,y,k);
     return(d[x][y]);
}
int main()
{
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    memset(d,-5000,sizeof(d));
    scanf("%d%d",&m,&n);
    for (i=0;i<n;i++) scanf("%d",&a[i]);
    for (i=0;i<n;i++)
        for (j=i+1;j<n;j++) if (a[i]>a[j])
                            {
                               c=a[i];
                               a[i]=a[j];
                               a[j]=c;
                            }
    printf("%d\n",dfs(0,n-1));
    fclose(stdin);
    fclose(stdout);
    return(0);
}
