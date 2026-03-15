#include<iostream>

using namespace std;

long long digit(long long x)
{
    long long sum=0;
    while(x)
    {
        sum+=x%10;
        x/=10;
    }
    return sum;
}

int main()
{
    long long t;
    cin>>t;
    while(t--)
    {
        long long x;
        cin>>x;
        if(x%9!=0)
        {
            cout<<0<<endl;
            continue;
        }
        long long sum=0;
        for(long long i=1;i<=200;i++)
        {
            long long y=x+i;
            if(digit(y)==i)
                sum++;
        }
        cout<<sum<<endl;

    }
    return 0;
}