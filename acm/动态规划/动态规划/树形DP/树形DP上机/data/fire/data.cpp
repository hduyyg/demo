#include <bits/stdc++.h>
using namespace std;
#define T 3
int N;
int main(){
    freopen("fire.in","w",stdout);
    srand(clock());
    printf("%d\n",T);
    scanf("%d",&N);
    for (int o=0; o<T; o++){
        printf("%d\n",N);
        for (int i=1; i<=N; i++) printf("%d ",rand()%10000+1);
        printf("\n");
        for (int i=1; i<=N; i++) printf("%d ",rand()%10001);
        for (int i=2; i<=N; i++) printf("%d %d %d\n",i,rand()%(i-1)+1,rand()%1000+1);
    }
    return 0;
}