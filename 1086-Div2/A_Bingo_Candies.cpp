#include<iostream>
#include<unordered_map>
using namespace std;

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        unordered_map<int,int> map;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                int num;
                cin>>num;
                map[num]++;
            }
        }
        if(n==1)
        {
            cout<<"NO"<<endl;
            continue;
        }
        bool find=false;
        for(pair<int,int> c:map)
        {
            if(c.second>n*(n-1))
            {
                find=true;
                cout<<"NO"<<endl;
                break;
            }
        }
        if(!find)
        {
            cout<<"YES"<<endl;
        }
    }


    return 0;
}