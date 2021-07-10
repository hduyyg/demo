#include <bits/stdc++.h>
using namespace std;
int N;
int main(){
    freopen("godfather.in","w",stdout);
    srand(clock());
    scanf("%d",&N);
    printf("%d\n",N);
    for (int i=2; i<=N; i++) printf("%d %d\n",i,rand()%(i-1)+1);
    return 0;
}