#include<iostream>
#include<vector>
using namespace std;

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,m,l,r;
        cin>>n>>m>>l>>r;
        while(n>m)
        {
            if(l<0)
            {
                n--;
                l++;
            }
            else if( r>0)
            {
                n--;
                r--;
            }
        }
        cout<<l<<' '<<r<<endl;
    }
    return 0;
}