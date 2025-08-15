#include<iostream> 
#include <set>

using namespace std;

class DSU{
    vector<int> parent;
    vector<int> rank;
public:
    DSU(int n){
        parent = vector<int> (n);
        rank = vector<int> (n);
        for(int i=0;i<n;i++){
            parent[i]=i;
            rank[i]=1;
        }
    }
    int getpar(int x){
        if(parent[x]==x){
            return parent[x];
        }
        return parent[x]=getpar(parent[x]);
    }   
    void unionSets(int x, int y){
        x=getpar(x);
        y=getpar(y);
        if(x==y){return;}
        if(rank[x]<rank[y]){
            swap(x, y);
        }
        if(rank[x]==rank[y])
            rank[x]++;
        parent[y]=x;
    }
};

int minCostForWells(vector<int> &wells, vector<vector<int>> &pipes){
    int n = wells.size(); 
    // we need min-heap 
    set<vector<int>> st;
    for(auto i: pipes){
        int u=i[0],v=i[1],w=i[2]; 
        st.insert({w,u,v});
    }
    for(int i=0;i<n;i++){
        st.insert({wells[i], 0, i+1});
    }
    DSU dsu = DSU(n+1);
    int res=0;
    while(!st.empty()){
        auto fr = *st.begin();
        auto cost=fr[0], a=fr[1], b=fr[2];
        if(dsu.getpar(a)!=dsu.getpar(b)){
            res+=cost;
            dsu.unionSets(a,b);
        }
        st.erase(fr);
    }
    return res;
}

int main(){
    int n;
    cin>>n;
    vector<int> wells(n);
    for (int i = 0; i < n; i++)
    {
       cin>>wells[i];
    }
    int numPipes;
    cin>>numPipes;
    vector<vector<int>> pipes(numPipes);
    for (int i = 0; i < numPipes; i++)
    {
        int u,v,w;cin>>u>>v>>w;
        pipes[i] = {u,v,w};
    }

    cout<<minCostForWells(wells, pipes);

    return 0;
}