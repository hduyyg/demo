#include <cstdio>
#include <cmath>
#include <algorithm>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define CALC(a,b) (1.0/(1.0+pow(10.0,(double(b)-double(a))/400.0 ) ) )

long N;
long R1[25];
long R2[25];
long num[25];
bool used[25];
long L;
double ans = -1e19;

void dfs(long u)
{
	if (u == N+1)
	{
 		for (long i=1;i<N+1;i++)
		{
			for (long j=i+1;j<N+1;j++)
			{
				if (R1[num[j]]-L>=R1[num[i]])
					return;
			}
		}
		double _ans = 0;
		for (long i=1;i<N+1;i++)
		{
			_ans += CALC(R1[num[i]],R2[i]);
		}
		ans = MAX(_ans,ans);
	}
	for (long i=1;i<N+1;i++)
	{
		if (!used[i])
		{
			used[i] = true;
			num[u] = i;
			dfs(u+1);
			used[i] = false;
		}
	}
}

int main()
{
	freopen("compete.in","r",stdin);
	freopen("compete.out","w",stdout);
	
	scanf("%ld",&N);
	for (long i=1;i<N+1;i++)
		scanf("%ld",R1+i);
	for (long i=1;i<N+1;i++)
		scanf("%ld",R2+i);
	scanf("%ld",&L);
	//std::sort(R1+1,R1+N+1);
	dfs(1);
	printf("%.6lf",ans);
	return 0;
}
