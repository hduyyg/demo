#include <cstdio>
#include <cstring>
using namespace std;

const int maxn=64,maxm=256,maxv=1024,maxk=32,Inf=1000000000;
int N,M,V,K;

int g[maxn][maxk];//g[i][k]表示第i种魔药花k个魔法的最低成本

void update(int& o,int x){
	if(o>x)o=x;
}

struct way{
	int target;
	int* s;//原料
	int n;
	void input(){
		scanf("%d%d",&target,&n);
		s=new int[n+1];
		for(int i=1;i<=n;++i)
			scanf("%d",s+i);
	}
	int DP(int K){
		static int f[maxn][maxk];//f[i][k]表示在前i个原料身上花k个魔法的最低成本
		for(int i=0;i<=n;++i)
			for(int k=0;k<=K;++k)
				f[i][k]=Inf;
		f[0][0]=0;
		for(int i=1;i<=n;++i)
			for(int k=0;k<=K;++k)
				for(int j=0;j<=k;++j){
					update(f[i][k],f[i-1][k-j]+g[s[i]][j]);
				}
		return f[n][K];
	}
}W[maxm];

int price0[maxn],price1[maxn];

void input(){
	scanf("%d%d%d%d",&N,&M,&V,&K);
	for(int i=1;i<=N;++i)
		scanf("%d%d",price0+i,price1+i);
	for(int i=1;i<=M;++i)
		W[i].input();
}

void update2(int& o,int x){
	if(o<x)o=x;
}
int f[maxv][maxk];
void Pack2D(int c1,int c2,int w){
	if(w<=0)return;
	for(int v=c1;v<=V;++v)
		for(int k=c2;k<=K;++k){
			update2(f[v][k],f[v-c1][k-c2]+w);
		}
}
void solve(){
	for(int i=1;i<=N;++i){
		g[i][0]=price0[i];
	}
	for(int k=1;k<=K;++k){
		for(int i=1;i<=N;++i){
			g[i][k]=g[i][k-1];
		}
		for(int i=1;i<=M;++i){
			update(g[W[i].target][k],W[i].DP(k-1));
		}
	}
	memset(f,0,sizeof(f));
	for(int i=1;i<=N;++i)
		for(int k=1;k<=K;++k){
			Pack2D(g[i][k],k,price1[i]-g[i][k]);
		}
}
void output(){
	printf("%d\n",f[V][K]);
}
int main(){
	freopen("magic.in","r",stdin);
	freopen("magic.out","w",stdout);
	input();
	solve();
	output();
}
