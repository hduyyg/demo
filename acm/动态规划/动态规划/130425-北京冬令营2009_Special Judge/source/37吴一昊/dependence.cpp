#include <cstdio>
#define MIN(a,b) ((a)<(b)?(a):(b))

long N;long M;
long from[1010];
long to[1010];
long rudu[20];
long DFN[20];
long LOW[20];
bool InStack[20];
long Stack[20];
long Bcnt = 0;
long top = 0;
long Belong[20];
long rudu2[20];

struct node
{
	long ind;
	node* nxt;
};
node* head[20];
void insert(long a,long b)
{
	node* tmp = new node;
	tmp -> ind = b;
	tmp -> nxt = head[a];
	head[a] = tmp;
}

long TIME = 0;

void tarjan(long u)
{
	DFN[u]=LOW[u]=++TIME;
	InStack[u] = true;
	Stack[++top] = u;

	for (node* vv=head[u];vv;vv=vv->nxt)
	{
		long v = vv->ind;
		if (!DFN[v])
		{
			tarjan(v);
			LOW[u]=MIN(LOW[u],LOW[v]);
		}
		else if (InStack[v])
		{
			LOW[u]=MIN(LOW[u],DFN[v]);
		}
	}
	
	if (DFN[u]==LOW[u])
	{
		++Bcnt;
		long v;
		do
		{
			v = Stack[top--];
			InStack[v] = false;
			Belong[v]=Bcnt;
		}while (v!=u);
	}
}	

int main()
{
	freopen("dependence.in","r",stdin);
	freopen("dependence.out","w",stdout);
	
	scanf("%ld%ld",&N,&M);
	
	if (N == 1)
	{
		printf("1\nA");
		return 0;
	}
		
	for (long i=1;i<M+1;i++)
	{
		char tmp1;
		char tmp2;
		scanf("\n%c",&tmp1);
		scanf(" -> ");
		scanf("%c",&tmp2);
		
		if (tmp1=='-'||tmp1=='>'
			||tmp2=='-'||tmp2=='>')
		{
			printf("No candidate key");
			return 0;
		}
		
		from[i] = tmp1-'A'+1;
		to[i] = tmp2-'A'+1;
		
		rudu[to[i]]++;
		insert(from[i],to[i]);
	} 
	for (long i=1;i<N+1;i++)
	{
		if (!DFN[i])
		{
			tarjan(i);
		}
	}
	for (long u=1;u<N+1;u++)
	{
		for (node* vv=head[u];vv;vv=vv->nxt)
		{
			long v = vv->ind;
			if (Belong[u]-Belong[v])
				rudu2[Belong[v]] ++;
		}
	}
	long leaf = 0;
	for (long i=1;i<Bcnt+1;i++)
	{
		if (!rudu2[i])
		{
			if (leaf)
			{
				printf("No candidate key");
				return 0;
			}
			leaf = i;
		}
	}
	long ans[20];
	long ans2 = 0;
	for (long i=1;i<N+1;i++)
	{
		if (Belong[i] == leaf)
		{
			ans2 ++;
		}
	}
	printf("%ld\n",ans2);
	for (long i=1;i<N+1;i++)
	{
		if (Belong[i] == leaf)
		{
			printf("%c\n",i-1+'A');
		}
	}
	return 0;
}
