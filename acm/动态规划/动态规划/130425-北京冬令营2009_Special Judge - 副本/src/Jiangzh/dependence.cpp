#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#include<iostream>
using namespace std;
const int N=2000;
int n,m;
char s[N];
struct link{int y;link *next;}*head[N];
int total;
int res[N],Cnt;
int h[N];
string ans[N];

void P2(int x)
{
	int alpha='A';
	while(x)
	{
		if(x&1) printf("%c",alpha);
		alpha++;
		x=x>>1;
	}
	puts("");
}

void P(int x)
{
	int num[20];
	for(int i=1;i<=n;i++)
	{
		num[i]=x&1;
		x=x>>1;
	}
	for(int i=n;i>=1;i--) printf("%d",num[i]);
	puts("");
}

void inlink(int x,int y)
{
	link *node = new link;
	node->y = y;
	node->next = head[x];
	head[x] = node;
}

void read()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		memset(s,0,sizeof(s));
		scanf("%s",s);
		int len=strlen(s);
		int x=0,y=0,j=0;
		while(j<len && s[j]!='-')
			x = x|(1<<(s[j++]-'A'));
		j+=2;
		while(j<len)
			y = y|(1<<(s[j++]-'A'));
		//P(x);P(y);puts("");
		inlink(x,y);
	}
}

bool check(int s)
{
	int tmp=s,flag=1;
	while(flag)
	{
		flag=0;
		for(int i=1;i<=tmp;i++)
			if((tmp|i)==tmp)
				for(link *node=head[i];node;node=node->next)
					if((tmp|node->y)!=tmp)
					{
						tmp=tmp|node->y;
						flag=1;
						if(tmp==total) return true;
					}
	}
	return tmp==total;
}

void writeans()
{
	for(int i=0;i<Cnt;i++)
	{
		int alpha='A',x=res[i];
		while(x)
		{
			if(x&1) ans[i]+=alpha;
			alpha++;
			x=x>>1;
		}
	}
	sort(ans,ans+Cnt);
	printf("%d\n",Cnt);
	for(int i=0;i<Cnt;i++) cout<<ans[i]<<endl;
}

void work()
{
	total=(1<<n)-1;
	for(int S=1;S<=total;S++)
		if(check(S)) h[S]=1;

	/*for(int S=0;S<=total;S++)
		if(h[S]) P2(S);*/

	for(int S=0;S<=total;S++)
		if(h[S])
		{
			bool flag=1;
			for(int i=0;i<S;i++)
				if((i|S)==S && h[i]) {flag=0;break;}
			if(flag) res[Cnt++]=S;
		}
	if(!Cnt) printf("No candidate key\n");
	else writeans();
}

int main()
{
	freopen("dependence.in","r",stdin);
	freopen("dependence.out","w",stdout);
	read();
	work();
	return 0;
}
