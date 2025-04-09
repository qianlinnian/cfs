#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
bool isPrime(int num)
{
    if(num<=1)
        return false;
    if(num==2)
        return true;
    else if(num%2==0)
        return false;    
    for(int i=3;i*i<=num;i+=2)
    {
        if(num%i==0)
            return false;
    }
    return true;
}
bool canPrime(int x,int k)
{
    if(k==1)
    {
        if(isPrime(x))
        {
            return true;
        }
        else
        {
            return false;
        }
    }   
    else 
    {
        if(x==1 && k==2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int x,k;
        cin>>x>>k;

        if(canPrime(x,k))
        {
            cout<<"YES"<<endl;
        }
        else
        {
            cout<<"NO"<<endl;
        }
    }
    return 0;

}
