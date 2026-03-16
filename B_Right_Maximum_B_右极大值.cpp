#include<iostream>
#include<vector>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int> a(n);
        int pos=0,max=0;
        for(int i=0;i<n;i++)
        {
            int num;
            cin>>num;
            a[i]=num;
            if(num>=max)
            {
                max=num;
                pos=i;
            }
        }
        int cnt=1;
        pos--;
        while(pos>=0){
            max=0;
            int p=0;
            for(int i=0;i<=pos;i++)
            {
                if(a[i]>=max)
                {
                    max=a[i];
                    p=i;
                }
            }
            pos=p-1;
            cnt++;
        }
        cout<<cnt<<endl;
        
    }
    return 0;
}