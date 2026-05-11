#include <iostream>
using namespace std;

// DIGIT DP template
// Author: Rashid Siddiqui
class Solution {
    int dp[23][401][2][2];
    int mod = 1e9+7;

    int countSumatmostk(string& lower_bound, string& upper_bound, int k,
                        int pos = 0, bool ltight = 1, bool utight = 1) {
        if (k < 0) {
            return 0;
        }
        int n = lower_bound.size();
        if (pos == n) {
            return 1;
        }
        if (dp[pos][k][ltight][utight] != -1) {
            return dp[pos][k][ltight][utight];
        }
        int llim = ltight ? lower_bound[pos] - '0' : 0;
        int ulim = utight ? upper_bound[pos] - '0' : 9;
        int ans = 0;
        for (int i = llim; i <= ulim; i++) {
            ans = (ans + countSumatmostk(lower_bound, upper_bound, k - i,
                                         pos + 1, ltight && i == llim,
                                         utight && i == ulim)) %
                  mod;
        }
        return dp[pos][k][ltight][utight] = ans % mod;
    }

public:
    int count(string num1, string num2, int min_sum, int max_sum) {
        memset(dp, -1, sizeof(dp));
        int zerocnt = (int)num2.size() - (int)num1.size();
        string trailingzeros = string(zerocnt, '0');
        num1 = trailingzeros + num1;

        int atmostmaxsum = countSumatmostk(num1, num2, max_sum) % mod;
        int atmostminsum_1 = countSumatmostk(num1, num2, min_sum - 1) % mod;
        return ((atmostmaxsum - atmostminsum_1) + mod) % mod;
    }
};