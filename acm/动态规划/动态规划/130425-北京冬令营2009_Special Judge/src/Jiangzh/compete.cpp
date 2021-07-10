#include<cstdio>
#include<cmath>
const int N=100;
#define max(a,b) ((a)>(b)?(a):(b))

int n;
int a[N],b[N],L;
bool h[N];
int ans[N];
double best=0;

double calc(int A,int B)
{
	return 1.0/(1.0+pow(10,((double)B-A)/400.0));
}

double getans()
{
	double res=0;
	for(int i=1;i<=n;i++)
	{
		res+=calc(a[ans[i]],b[i]);
		//printf("%.3lf,",calc(a[ans[i]],b[i]));
	}
	return res;
}

bool check()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i!=j)
			{
				if(a[ans[i]]-L>a[ans[j]])
					if(j<i) return 0;
			}
	return 1;
}

void dfs(int x)
{
	if(x>n)
	{
		//for(int i=1;i<=n;i++) printf("%d ",a[ans[i]]);puts("");
		if(check())best=max(best,getans());
		return;
	}
	for(int i=1;i<=n;i++)
	if(!h[i])
	{
		h[i]=1;ans[x]=i;
		dfs(x+1);
		h[i]=0;
	}
}

int main()
{
	freopen("compete.in","r",stdin);
	freopen("compete.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%d",&b[i]);
	scanf("%d",&L);
	dfs(1);
	printf("%.6lf\n",best);
	return 0;
}
