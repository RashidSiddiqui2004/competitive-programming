#include<iostream>
using namespace std;

int visited[26];

void dfs(int node, vector<vector<int>> &adj){
    visited[node]=1;
    for(auto i: adj[node]){
        if(!visited[i]){
            dfs(i, adj);
        }
    }
}

// Circle of strings
bool isCyclePresent(vector<string> &words){
    vector<vector<int>> adj(26);
    vector<int> indegree(26,0), outdegree(26,0);
    for(auto s: words){
        int first=s.front()-'a', last=s.back()-'a';
        adj[first].push_back(last);
        outdegree[first]++;
        indegree[last]++;
    }
    for(int i=0;i<26;i++){
        if(indegree[i]!=outdegree[i]){
            return 0;
        }
    }
    int node = words[0][0]-'a';
    dfs(node, adj);
   
    for(int i=0;i<26;i++){
        if(indegree[i] && !visited[i]){
            return 0;
        }
    }
    
    return 1;
}

int main(){
    int n;cin>>n;
    vector<string> words(n);
    for (size_t i = 0; i < n; i++)
    {
        cin>>words[i];
    }
    cout<<isCyclePresent(words)<<endl;
    return 0;
}