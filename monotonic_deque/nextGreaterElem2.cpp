#include<iostream>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int> a = nums;
        int n = nums.size();
        for(int i=0;i<n;i++){
            a.push_back(nums[i]);
        }
        int m = a.size();
        stack<int> st;
        vector<int> nextg(2*n, -1);
        for (int i = m - 1; i >= 0; i--) {
            if (st.empty()) {
                st.push(i);
            } else {
                while (!st.empty() && a[st.top()] <= a[i]) {
                    st.pop();
                }
                if(!st.empty() && abs(i - st.top()) != n && a[st.top()] >= a[i]){
                    nextg[i] = st.top();
                }
                st.push(i);
            }
        }
        vector<int> res(n, -1);
        for(int i=0;i<n;i++){
            if(nextg[i]!=-1){
                res[i] = a[nextg[i]];
            }
        }
        return res;
    }
};