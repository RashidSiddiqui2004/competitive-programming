#include<iostream>
using namespace std;

class Solution {
    using ll = long long;
    const ll mod = 1e9 + 7;

public:
    int sumSubarrayMins(vector<int>& a) {
        int n = a.size();
        vector<int> prevsmaller(n, -1), nextsmaller(n, -1);
        stack<int> st;

        for (int i = n - 1; i >= 0; i--) {
            if (st.empty()) {
                st.push(i);
            } else {
                while (!st.empty() && a[st.top()] > a[i]) {
                    st.pop();
                }
                if (!st.empty() && abs(i - st.top()) != n &&
                    a[st.top()] <= a[i]) {
                    nextsmaller[i] = st.top();
                }
                st.push(i);
            }
        }

        while (!st.empty()) {
            st.pop();
        }

        for (int i = 0; i < n; i++) {
            if (st.empty()) {
                st.push(i);
            } else {
                while (!st.empty() && a[st.top()] >= a[i]) {
                    st.pop();
                }
                if (!st.empty() && abs(i - st.top()) != n &&
                    a[st.top()] < a[i]) {
                    prevsmaller[i] = st.top();
                }
                st.push(i);
            }
        }

        ll res = 0;

        for (int i = 0; i < n; i++) {
            int prev = prevsmaller[i]==-1 ? -1 : prevsmaller[i];
            int next = nextsmaller[i] == -1 ? n : nextsmaller[i];
            int back = (i - prev);
            int front = (next - i);
            res = (res + (a[i] * 1ll * back * front)) % mod;
        }

        return res % mod;
    }
};