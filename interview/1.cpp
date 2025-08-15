#include<iostream> 
#include <set>

using namespace std; 
vector<vector<int>> uniqsubsets;

void solve1(vector<int> &v, int pos, vector<int> temp){
    int n = v.size();
    if(pos==n){
        uniqsubsets.push_back(temp);
        return;
    }
    for(int i=pos;i<n;i++){
        if(i>pos and v[i]==v[i-1]) continue;
        temp.push_back(v[i]);
        solve1(v, i+1,temp);
        temp.pop_back(); 
    }
}

void generateUniqueSubsets(vector<int> &v){
    sort(v.begin(),v.end());
    vector<int> temp;
    solve1(v,0,temp);
}

void permuteHelper(vector<int>& nums, vector<int>& curr, vector<vector<int>>& ans, vector<bool>& used) {
    if (curr.size() == nums.size()) {
        ans.push_back(curr);
        return;
    }

    for (int i = 0; i < nums.size(); i++) {
        if (used[i]) continue; // already used this element in current permutation
        if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue; // skip duplicates

        used[i] = true;
        curr.push_back(nums[i]);
        permuteHelper(nums, curr, ans, used);
        curr.pop_back();
        used[i] = false;
    }
}

vector<vector<int>> permuteUnique(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> ans;
    vector<int> curr;
    vector<bool> used(nums.size(), false);
    permuteHelper(nums, curr, ans, used);
    return ans;
}

int main(){
    vector<int> nums = {1,2,2};
    // generateUniqueSubsets(nums);
    // for(auto ar : uniqsubsets){
    //     for(auto i : ar){
    //         cout<<i<<" ";
    //     }
    //     cout<<endl;
    // }
    auto ans = permuteUnique(nums);
    for (auto &perm : ans) {
        cout << "[ ";
        for (int x : perm) cout << x << " ";
        cout << "]\n";
    }
    return 0;
}