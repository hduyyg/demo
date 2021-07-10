#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn = 25;
const int maxm = 2200000;
const double lg10 = log(10.0);
double dp[maxm],w[maxn][maxn];
int a[maxn],b[maxn],x[maxn];
bool vis[maxm];
int n,l;
void init()
{
	freopen("compete.in","r",stdin);
	freopen("compete.out","w",stdout);
}

double calc(int i,int j)
{
	return 1.0 / (1 + exp((double)(b[j]-a[i]) / 400 * lg10));
}

double dfs(int pos,int sta)
{
	if(pos > n)return 0;
	if(vis[sta])return dp[sta];
	vis[sta] = true;
	double ans = 0.0;
	for(int i = 1;i <= n;i++)
		if((sta & x[i]) == x[i] && !(sta & (1 << i)))
			ans = max(ans,dfs(pos + 1,sta | (1 << i)) + w[i][pos]);
	dp[sta] = ans;
	return ans;
}

void solve()
{
	stable_sort(a + 1,a + n + 1);
	stable_sort(b + 1,b + n + 1);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j < i;j++)
			if(a[i] - a[j] > l)
				x[i] = x[i] | (1 << j);
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= n;j++)
			w[i][j] = calc(i,j);
	double ans = dfs(1,0);
	printf("%.6lf\n",ans);
}

void readdata()
{
	scanf("%d",&n);
	for(int i = 1;i <= n;i++)
		scanf("%d",&a[i]);
	for(int i = 1;i <= n;i++)
		scanf("%d",&b[i]);
	scanf("%d",&l);
}

int main()
{
	init();
	readdata();
	solve();
	return 0;
}
