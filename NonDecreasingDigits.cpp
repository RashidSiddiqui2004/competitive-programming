#include <iostream>
#include <string.h>
using namespace std;

using ll = long long;

// A number is said to be a "good integer"
// if its decimal representation has digits in non-decreasing order.

// For handling large integers
// len(number) <= 100
const ll mod = 1e9 + 7;

ll dp[100][10][2];

ll helper(string bound,
          int pos,
          bool istight,
          int lastdigit)
{

    if (pos == (int)bound.size())
    {
        return 1;
    }

    if (dp[pos][lastdigit][istight] != -1)
    {
        return dp[pos][lastdigit][istight] % mod;
    }

    int limit = istight ? bound[pos] - '0' : 9;

    ll ans = 0;

    for (int i = lastdigit; i <= limit; i++)
    {
        ans = (ans + helper(bound, pos + 1, istight && (i == limit), i)) % mod;
    }

    return dp[pos][lastdigit][istight] = ans % mod;
}

/// Find all the "good integers" in the range [lower_bound, upper_bound].
/// Reference -
// https://leetcode.com/problems/count-numbers-with-non-decreasing-digits
ll numberOfGoodIntegers(string lower_bound, string upper_bound)
{
    memset(dp, -1, sizeof(dp));
    ll tillupperbound = helper(upper_bound, 0, true, true) % mod;

    memset(dp, -1, sizeof(dp));
    ll tilllowerbound = helper(lower_bound, 0, true, true) % mod;

    ll ans = ((tillupperbound - tilllowerbound) + mod) % mod;

    // check if lower_bound is good integer to include in final answer
    bool check = true;
    for (int i = 1; i < lower_bound.size(); i++)
    {
        if (lower_bound[i] < lower_bound[i - 1])
        {
            check = false;
            break;
        }
    }
    if (check)
    {
        ans = (ans + 1) % mod;
    }
    return ans;
}

int main()
{
    string lower_bound, upper_bound;
    cin >> lower_bound >> upper_bound;

    cout << numberOfGoodIntegers(lower_bound, upper_bound);
    return 0;
}