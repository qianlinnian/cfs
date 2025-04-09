#include<iostream>

using namespace std;

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int a;
        cin>>a;
        if(a%2==0)
        {
            cout<<"NO"<<endl;
        }
        else
            cout<<"YES"<<endl;
    }
    return 0;
}