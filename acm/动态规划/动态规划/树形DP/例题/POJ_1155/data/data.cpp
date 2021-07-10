#include <bits/stdc++.h>
using namespace std;
int N;
vector <int> a[3000];
int main(){
    freopen("tele.in","w",stdout);
    srand(clock());
    scanf("%d",&N);
    int M=rand()%(N-1)+1;
    printf("%d %d\n",N,M);
    for (int i=2; i<=N; i++){
        int x=rand()%(min(i-1,N-M))+1;
        a[x].push_back(i);
    }
    for (int i=1; i<=N-M; i++){
        printf("%d",a[i].size());
        for (int j=0; j<a[i].size(); j++) printf(" %d %d",a[i][j],rand()%5000+1);
        printf("\n");
    }
    for (int i=0; i<M; i++) printf("%d ",rand()%15000+1);
    return 0;
}