#include <iostream>
using namespace std;

// DIGIT DP template
// Author: Rashid Siddiqui
class Solution {
    int dp[10][10][10][21][2][2];
    int k;
    int solve(string upper, int pos = 0, int odds = 0, int evens = 0,
              int mod = 0, bool tight = 1, bool zero = true) {
        if (pos == (int)upper.size()) {
            return evens==odds and !zero and mod == 0;
        }
        if(dp[pos][odds][evens][mod][tight][zero]!=-1){
            return dp[pos][odds][evens][mod][tight][zero];
        }
        int upperlimit = tight ? upper[pos] - '0' : 9;
        int ans = 0;
        for (int digit = 0; digit <= upperlimit; digit++) {
            int neweven = evens + (digit % 2 == 0 && (digit > 0 || !zero));
            ans += solve(upper, pos + 1, odds + (digit % 2 != 0), neweven,
                         (mod * 10 + digit) % k, tight && (digit == upperlimit),
                         zero && digit == 0);
        }
        return dp[pos][odds][evens][mod][tight][zero] = ans;
    }

public:
    int numberOfBeautifulIntegers(int low, int high, int k) {
        this->k = k;
        string lower = to_string(low - 1);
        string upper = to_string(high);
        memset(dp, -1, sizeof(dp));
        int uptoupper = solve(upper);
        memset(dp, -1, sizeof(dp));
        int lessthanlower = solve(lower);
        return uptoupper - lessthanlower;
    }
};