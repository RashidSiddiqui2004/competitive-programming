#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <array>
#include <deque>
#include <cstring>
#include <queue>
#include <stack>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <functional>
#include <utility>
#include <tuple>
#include <cmath>
#include <climits>
#include <cfloat>
#include <bitset>
#include <cassert>
#include <random>
#include <chrono>

using namespace std;

int dp[10][90][90][2];

int t6helper(string &s, int pos = 0, int oddsum = 0, int evensum = 0, bool istight = 1)
{
    int n = s.size();
    if (pos == n)
    {
        if ((n % 2) == 0)
        {
            swap(oddsum, evensum);
        }
        // cout << evensum << ' ' << oddsum << endl;
        int diff = evensum - oddsum;
        return (diff == 1);
    }
    int &memvalue = dp[pos][oddsum][evensum][istight];

    if (memvalue != -1)
    {
        return memvalue;
    }

    int upperlimit = istight ? (s[pos] - '0') : 9;
    int ans = 0;
    for (int digit = 0; digit <= upperlimit; digit++)
    {
        // 1-based positioning
        int newOdd = oddsum;
        int newEven = evensum;

        if ((pos + 1) & 1)
            newOdd += digit;
        else
            newEven += digit;

        ans += t6helper(
            s,
            pos + 1,
            newOdd,
            newEven,
            istight && (digit == upperlimit));
    }
    return memvalue = ans;
}

// https://www.spoj.com/problems/RAONE/
void t6()
{
    int l, r;
    cin >> l >> r;

    string ls = to_string(l - 1);
    string rs = to_string(r);

    memset(dp, -1, sizeof(dp));
    int lessthanr = t6helper(rs);

    memset(dp, -1, sizeof(dp));
    int lessthanl = (l == 0) ? 0 : t6helper(ls);

    int ans = lessthanr - lessthanl;
    cout << ans << endl;
}
