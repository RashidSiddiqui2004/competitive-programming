#include<iostream>
using namespace std;

class DSU{
    vector<int> parent;
    vector<int> rank;
public:
    DSU(int n){
        parent = vector<int> (n);
        rank = vector<int> (n);
        numberOfComponents = n;
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
        numberOfComponents--;
        if(rank[x]==rank[y])
            rank[x]++;
        parent[y]=x;
    }

    int numberOfComponents;
};

int minTimeforFriends(int n, vector<vector<int>> &logs){    
    sort(logs.begin(), logs.end(), [](vector<int> &v1, vector<int> &v2){
        return v1[0] < v2[0];
    });
    DSU dsu = DSU(n);
    for(auto i: logs){
        auto time=i[0], u=i[1], v=i[2];
        dsu.unionSets(u, v);
        if(dsu.numberOfComponents == 1){
            return time;
        }
    }
}

int main(){
    int n;
    cin>>n;
    int m;cin>>m;
    vector<vector<int>> logs(m, vector<int> (3));

    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            cin>>logs[i][j];
        }
    }

    cout<<minTimeforFriends(n, logs)<<endl;
    return 0;
}