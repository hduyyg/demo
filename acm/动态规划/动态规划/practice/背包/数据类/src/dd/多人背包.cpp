#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;

const int maxn=256,maxm=5001,maxk=64;
int W[maxn],C[maxn];
int f[maxm][maxk];
int fn[maxm];
int K,M,N;

void input(){
	scanf("%d%d%d",&K,&M,&N);
	for(int i=0;i<N;++i)
		scanf("%d%d",W+i,C+i);
}
void solve(){
	memset(f,0,sizeof(f));
	memset(fn,0,sizeof(fn));
	fn[0]=1;
	for(int k=0;k<N;++k)
		for(int i=M-W[k];i>=0;--i){
			if(fn[i]==0)continue;
			int j=i+W[k];
			static int up[maxk];
			int n=0,a=0,b=0;
			do{
				if(a<fn[i]&&f[i][a]+C[k]>f[j][b]){
					up[n++]=f[i][a++]+C[k];
				}
				else if(b<fn[j]){
					up[n++]=f[j][b++];
				}
				else break;
			}while(n<K);
			fn[j]=n;
			memcpy(f[j],up,sizeof(int)*n);
		}
}
void output(){
	int res=0;
	assert(fn[M]==K);
	for(int i=0;i<K;++i){
		res+=f[M][i];
	}
	assert(res>0);
	printf("%d\n",res);
}
int main(){
	freopen("bags.in","r",stdin);
	freopen("bags.out","w",stdout);
	
	input();
	solve();
	output();
}
