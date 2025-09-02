// Among all ways to keep pattern as a subsequence, find one where you use the fewest removable characters.
// Those "fewest removable chars" are the ones you cannot delete (otherwise pattern breaks).
// Subtract them from total removable options → answer.

#include<iostream>
using namespace std;

// cost[i] => 1 if this index is removable
// we need to minimize the total cost such that it is possible to achive pattern
class Solution {
    vector<vector<int>> dp;
    int solve(string& s, string& pat, vector<int>& cost, int i=0, int j=0) {
        int n = s.size(), m = pat.size();
        if (j == m)
            return 0;
        if (i == n)
            return INT_MAX;
        if (dp[i][j] != -1) {
            return dp[i][j];
        }
        // skip this character in s
        int ans = solve(s, pat, cost, i + 1, j);
        if (s[i] == pat[j]) {
            // take this character to be part of pattern
            int take = solve(s, pat, cost, i + 1, j + 1);
            // if it is possible to achieve pattern by including this character
            // update ans to min (ans, take + a[i])
            if (take != INT_MAX) {
                ans = min(ans, take + cost[i]);
            }
        }
        return dp[i][j] = ans;
    }

public:
    int maxRemovals(string source, string pattern, vector<int>& targetIndices) {
        int n = source.size(), m = pattern.size();
        vector<int> cost(n, 0);
        // a[i]=1 -> implies we get a price of 1 unit to skip this index
        for (auto i : targetIndices) {
            cost[i] = 1;
        }
        dp = vector<vector<int>>(n, vector<int>(m, -1));
        return (int)targetIndices.size() - solve(source, pattern, cost);
    }
};