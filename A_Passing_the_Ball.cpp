#include<iostream>
#include<set>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        string s;
        cin>>s;
        int pos=0; // 0-indexed, student 1 = index 0
        set<int> vis;
        vis.insert(pos);
        for(int i=0;i<n;i++){
            if(s[pos]=='R')
                pos++;
            else
                pos--;
            vis.insert(pos);
        }
        cout<<vis.size()<<endl;
    }

    return 0;
}