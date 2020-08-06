#include<iostream>
    #include<cstdio>
    using namespace std;
    
double sum=0,et=7;
double s,x;

int main(){
    cin>>s>>x;
    int left=s-x,right=s+x;
    while(sum<left)//循环 
    {
     sum+=et;
     et*=0.98;
    }
    if(sum+et>right) cout<<"n";//注意此处一定要>，游出去才会没有危险。 
    else cout<<"y";
    return 0;
}
