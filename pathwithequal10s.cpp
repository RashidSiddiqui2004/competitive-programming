#include<iostream>
using namespace std;

int dp[100][100][100];

bool solve(vector<vector<bool>> &grid, int i=0, int j=0,int ones=0){
    int n = grid.size(), m=grid[0].size();
    int requiredOnes = (n+m-1)/2;
    if(i==(n-1) and j==(m-1)){
        return ones==requiredOnes;
    }
    if(i>=n || j>=n){
        return false;
    }
    if(ones>=requiredOnes){
        return false;
    }
    bool isOne = grid[i][j];    
    return solve(grid, i+1, j, ones+isOne) || solve(grid, i, j+1,ones+isOne);
}

bool checkIfPathWithequalZeroOne(vector<vector<bool>> &grid){
    int n = grid.size(), m=grid[0].size();
    int pathLength = n+m-1;
    if(pathLength%2 != 0){
        return false;
    }
    return solve(grid);
}

int main(){
    vector<vector<bool>> grid1 = {
        {0,1,0,0},
        {0,1,0,0},
        {1,0,1,1}
    };
    vector<vector<bool>> grid2 = {
        {1,1,0},
        {0,0,1},
        {1,0,0}
    };
    cout<<checkIfPathWithequalZeroOne(grid1)<<endl;
    cout<<checkIfPathWithequalZeroOne(grid2)<<endl;
    return 0;
}