#include <iostream>
#include <string.h>
using namespace std;

using ll = long long;

// A number is said to be a "good integer"
// if its digit sum is between [min_sum, max_sum]

// For handling large integers
const ll mod = 1e9 + 7;

ll dp[23][401][2][2];

ll numberOfGoodIntegersWithAtmostKSum(string lower_bound, string upper_bound,
                                      int k,
                                      int pos,
                                      bool isLowerBoundTight,
                                      bool isUpperBoundTight)
{
    if (k < 0)
    {
        return 0;
    }

    if (pos == (int)lower_bound.size())
    {
        return 1;
    }

    if (dp[pos][k][isLowerBoundTight][isUpperBoundTight] != -1)
    {
        return dp[pos][k][isLowerBoundTight][isUpperBoundTight] % mod;
    }

    int lowerLimit = isLowerBoundTight ? lower_bound[pos] - '0' : 0;
    int upperLimit = isUpperBoundTight ? upper_bound[pos] - '0' : 9;

    ll ans = 0;

    for (int i = lowerLimit; i <= upperLimit; i++)
    {
        ans = (ans + numberOfGoodIntegersWithAtmostKSum(lower_bound, upper_bound, k - i, pos + 1, isLowerBoundTight && (i == lowerLimit), isUpperBoundTight && (i == upperLimit))) % mod;
    }

    return dp[pos][k][isLowerBoundTight][isUpperBoundTight] = ans % mod;
}

/// Find all the "good integers" in the range [lower_bound, upper_bound].
/// Reference -
/// https://leetcode.com/discuss/post/4130281/digit-dp-day1-count-of-integers-day110-b-js3w/
ll numberOfGoodIntegers(string lower_bound, string upper_bound, int minsum, int maxsum)
{
    memset(dp, -1, sizeof(dp));
    int trailingZerosCount = upper_bound.length() - lower_bound.length();
    string trailingZeros = string(trailingZerosCount, '0');
    string updatedLowerBound = trailingZeros + lower_bound;

    ll atmostmaxsum = numberOfGoodIntegersWithAtmostKSum(updatedLowerBound, upper_bound, maxsum, 0, true, true) % mod;
    ll atmostminsumminus1 = numberOfGoodIntegersWithAtmostKSum(updatedLowerBound, upper_bound, minsum - 1, 0, true, true) % mod;

    ll ans = (atmostmaxsum - atmostminsumminus1) % mod;
    return ans;
}

int main()
{
    string lower_bound, upper_bound;
    cin >> lower_bound >> upper_bound;

    int minsum, maxsum;
    cin >> minsum >> maxsum;

    cout << numberOfGoodIntegers(lower_bound, upper_bound, minsum, maxsum);
    return 0;
}