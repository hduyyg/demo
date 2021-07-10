#include<cstdio>
#include<cmath>
using namespace std;

const double precision=1e-6;
const int maxn=2e3;
double dp[maxn+5][maxn+5],c[maxn+5];

int main()
{
  int n,m,k,i,j;double p1,p2,p3,p4,p21,p31,p41,p,tmp;
  while(scanf("%d%d%d%lf%lf%lf%lf",&n,&m,&k,&p1,&p2,&p3,&p4)==7)
    {
      if(abs(p4)<precision){printf("%.5f\n",0);continue;}
      p21=p2/(1-p1),p31=p3/(1-p1),p41=p4/(1-p1);
      dp[1][1]=p4/(1-p1-p2);
      for(i=2;i<=n;i++)
	    {
          for(j=2;j<=(i<k?i:k);j++)c[j]=dp[i-1][j-1]*p31+p41;
          for(j=k+1;j<=i;j++)c[j]=dp[i-1][j-1]*p31;
          for(p=1,tmp=0,j=i;j>1;j--)tmp+=p*c[j],p*=p21;
          dp[i][i]=(tmp+p*p41)/(1-p*p21);
          dp[i][1]=p21*dp[i][i]+p41;
          for(j=2;j<i;j++)dp[i][j]=p21*dp[i][j-1]+c[j];
        }
      printf("%.5f\n",dp[n][m]);
    }
    return 0;
}

