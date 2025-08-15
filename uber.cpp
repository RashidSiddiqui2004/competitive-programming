#include<iostream>
using namespace std;

const int MAX_NODES=1e3;

int dp1[MAX_NODES][2];
int dp2[MAX_NODES][MAX_NODES];
int values[MAX_NODES];
vector<int> adj[MAX_NODES];
int visited[MAX_NODES]={0};

int maxSum(vector<int> &even, vector<int> &odd, int pos=0, int oddCnt=0, int currSum=0){
    int n = even.size();
    if(pos==n){
        return currSum;
    }
    if(dp2[pos][oddCnt]!=-1){
        return dp2[pos][oddCnt];
    }
    return dp2[pos][oddCnt]=max(maxSum(even, odd, pos+1, oddCnt, currSum + even[pos]), 
        maxSum(even, odd, pos+1, oddCnt+1, currSum + odd[pos]));
}

int maxValuesSum(int node){
    // don't forget to initialize dp array
}

int main(){
    int n;cin>>n;
    for(int i=0;i<n;i++){
        int u,v;cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    return 0;
}