#include<iostream>
#include<vector>
using namespace std;

int main()
{
    int n,x,s;
    vector<int> a;
    int t;
    cin>>t;
    while(t--)
    {
        ci
        n>>n>>s>>x;
        int total=0;
        while(n--)
        {
            int tmp;
            cin>>tmp;
            total+=tmp;
            a.push_back(tmp);
        }
        if(total>s){cout<<"NO"<<endl;}
        else{
            int need=s-total;
            if(need%x==0){cout<<"YES"<<endl;}
            else{cout<<"NO"<<endl;}
        }
        a.clear();
    }
    return 0;
}