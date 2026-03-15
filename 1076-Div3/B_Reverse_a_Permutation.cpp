#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
    int t,n;
    vector<int> p;
    cin>>t;
    while(t--)
    {
        cin>>n;
        p.resize(n);
        int l=0,r=0;
        for(int i=0;i<n;i++)
        {
            cin>>p[i];
            if(p[i]==n-i) l++;
        }
        if(l==n)
        {
            for(int i=0;i<n;i++)
            {
                cout<<p[i]<<" ";
            }
            cout<<endl;
            continue;
        }
        int max=p[l];
        for(int i=l+1;i<n;i++)
        {
            if(p[i]>max) {
                max=p[i];
                r=i;
            }
        }
        reverse(p.begin()+l,p.begin()+r+1);
        for(int i=0;i<n;i++)
        {
            cout<<p[i]<<" ";
        }
        cout<<endl;

        }

    return 0;
}