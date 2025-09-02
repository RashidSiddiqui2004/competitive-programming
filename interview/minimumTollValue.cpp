#include<iostream>
using namespace std;

using pii = pair<int,int>;
using piii = pair<int, pii>;
using minheap = priority_queue<piii, vector<piii>, greater<piii>>;

int minTollValue(vector<vector<int>> &edges, vector<int> tolls, int k){
    int n = tolls.size();
    vector<vector<pii>> adj(n);
    for(auto i: edges){
        int u=i[0],v=i[1],w=i[2];
        --u,--v;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    vector<int> cost(n,INT_MAX);
    cost[0]=tolls[0];
    // tollcost, node, latency
    minheap pq;
    pq.push({cost[0], {0, 0}});

    while (!pq.empty())
    {
        auto [tollcost, p] = pq.top();
        auto [node, latency] = p;
        pq.pop();

        for(auto i: adj[node]){
            int neigh=i.first, w=i.second;
            int newtollcost = tollcost + tolls[neigh];
            int newlatency = latency + w;
            if(newlatency <= k and  newtollcost < cost[neigh]){
                cost[neigh]=newtollcost;
                pq.push({newtollcost, {neigh, newlatency}});
            }
        }
    }

    return cost[n-1]==INT_MAX ? -1 : cost[n-1];
}

int main(){
    int n,m;cin>>n>>m;
    vector<vector<int>> edges(m);
    for (size_t i = 0; i < m; i++)
    {
        int u,v,w;cin>>u>>v>>w;
        edges[i]={u,v,w};
    }
    int k;cin>>k;
    vector<int> tolls(n);
    for (size_t i = 0; i < n; i++)
    {
        cin>>tolls[i];
    }
    cout<<minTollValue(edges, tolls,k);
    return 0;
}