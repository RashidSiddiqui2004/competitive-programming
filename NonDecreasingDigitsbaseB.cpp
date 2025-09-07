#include <iostream>
#include <string.h>
using namespace std;

using ll = long long;
const ll mod = 1e9 + 7;

ll dp[1000][10][2]; // pos, lastdigit, istight

vector<int> toBaseB(string num, int base) {
    vector<int> digits;
    vector<int> temp;
    for (char c : num)
        temp.push_back(c - '0');

    while (!temp.empty()) {
        int carry = 0;
        vector<int> next;
        for (int d : temp) {
            int cur = carry * 10 + d;
            next.push_back(cur / base);
            carry = cur % base;
        }
        digits.push_back(carry);
        while (!next.empty() && next[0] == 0)
            next.erase(next.begin());
        temp = next;
    }
    if (digits.empty())
        digits.push_back(0);
    reverse(digits.begin(), digits.end());
    return digits;
}

ll helper(vector<int>& bound, int base, int pos, bool istight, int lastdigit) {
    if (pos == (int)bound.size())
        return 1;

    if (dp[pos][lastdigit][istight] != -1)
        return dp[pos][lastdigit][istight];

    int limit = istight ? bound[pos] : base - 1;

    ll ans = 0;
    for (int d = lastdigit; d <= limit; d++) {
        ans = (ans + helper(bound, base, pos + 1, istight && (d == limit), d)) %
              mod;
    }

    return dp[pos][lastdigit][istight] = ans;
}

ll countGood(string num, int base) {
    vector<int> bound = toBaseB(num, base);
    memset(dp, -1, sizeof(dp));
    return helper(bound, base, 0, true, 0);
}

class Solution {
public:
    int countNumbers(string l, string r, int base) {
        ll tillUpper = countGood(r, base);
        ll tillLower = countGood(l, base);

        ll ans = (tillUpper - tillLower + mod) % mod;

        // check if lower_bound itself is non-decreasing in base b
        vector<int> lb = toBaseB(l, base);
        bool good = true;
        for (int i = 1; i < (int)lb.size(); i++) {
            if (lb[i] < lb[i - 1]) {
                good = false;
                break;
            }
        }
        if (good)
            ans = (ans + 1) % mod;
        return ans;
    }
};