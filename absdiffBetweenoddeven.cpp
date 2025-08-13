#include<iostream>
using namespace std;

// n<=1e5
// M trips are given of the form [st,end,w]
// increase ratings of city on path st---end by w

int main(){
    int n,m;
    cin>>n>>m;
    vector<int> ratings(n);
    for(int i=0;i<n-1;i++){
        cin>>ratings[i];
    }
    vector<vector<int>> adj(n);
    int u,v;
    for(int i=0;i<n;i++){
        cin>>u>>v;
        --u,--v;
        adj[u].push_back(v);
        adj[v].push_back(u);   
    }
    vector<vector<int>> routes(m);
    int w;
    for(int i=0;i<m;i++){
        cin>>u>>v>>w;
        --u,--v;
        routes.push_back({u,v,w});
    }
    return 0;
}
