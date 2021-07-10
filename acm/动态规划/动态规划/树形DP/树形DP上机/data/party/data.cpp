#include <bits/stdc++.h>
using namespace std;
int N;
int main(){
    freopen("party.in","w",stdout);
    srand(clock());
    scanf("%d",&N);
    printf("%d\n",N);
    for (int i=0; i<N; i++) printf("%d\n",rand()%256-128);
    for (int i=2; i<=N; i++) printf("%d %d\n",i,rand()%(i-1)+1);
    printf("0 0\n");
    return 0;
}