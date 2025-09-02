#include<iostream>
using namespace std;
 
string sswaps(){
    int n,m;cin>>n>>m;
    string a, b;
    cin>>a>>b;
    vector<int> fr(n+1, 0);
    int u,v;

    for (size_t i = 0; i < m; i++)
    {
        cin>>u>>v;
        --u,--v;
        fr[u]=!fr[u];
        fr[v+1]=!fr[v+1];
    }
    
    for (size_t i = 1; i < n; i++)
    {
        fr[i] = fr[i] ^ fr[i-1];
    }

    string ans = "";

    for (size_t i = 0; i < n; i++)
    {
        if(fr[i]){
            ans+=b[i];
        }else{
            ans+=a[i];
        }
    }
    
    return ans;
}

int main(){
    cout<<sswaps()<<endl;
    return 0;
}