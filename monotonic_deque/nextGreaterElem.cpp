#include<iostream>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& a) {
        int n = a.size();
        stack<int> st;
        vector<int> nextg(n, -1);
        for (int i = n - 1; i >= 0; i--) {
            if (st.empty()) {
                st.push(a[i]);
            } else {
                while (!st.empty() && st.top() <= a[i]) {
                    st.pop();
                }
                if(!st.empty() && st.top() >= a[i]){
                    nextg[i] = st.top();
                }
                st.push(a[i]);
            }
        }
        vector<int> res(10001, -1);
        for(int i=0;i<n;i++){
            res[a[i]] = nextg[i];
        }
        vector<int> ans;
        for(auto i: nums1){
            ans.push_back(res[i]);
        }
        return ans;
    }
};