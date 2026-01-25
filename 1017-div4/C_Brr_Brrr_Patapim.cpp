#include<iostream>
#include<vector>

using namespace std;

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        vector<vector<int>> G(n,vector<int>(n));
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                cin>>G[i][j];
            }
        }
        int len=2*n;
        vector<int> ans(len,0);
        long long int sum=(1+len)*n;
        long long int now=0;
        for(int i=n-1;i>0;i--)
        {
            ans[i+n]=G[i][n-1];
            now+=G[i][n-1];
        }
        for(int i=n-1;i>=0;i--)
        {
            ans[i+1]=G[0][i];
            now+=G[0][i];
        }
        ans[0]=sum-now;
        for(int i=0;i<len;i++)
        {
            cout<<ans[i]<<" ";
        }
        cout<<endl;

    }
    return 0;
}