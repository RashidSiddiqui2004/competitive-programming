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

#define int long long

// https://atcoder.jp/contests/abc336/submissions/me
string s;
int targetSum;
int dp[16][136][136][2];

int dfs(int pos = 0, int sum = 0, int mod = 0, bool tight = true)
{
    if (pos == (int)s.size())
    {
        return (sum == targetSum) && (mod == 0);
    }

    int &res = dp[pos][sum][mod][tight];
    if (res != -1)
        return res;

    int limit = tight ? s[pos] - '0' : 9;

    int ans = 0;

    for (int d = 0; d <= limit; d++)
    {
        if (sum + d > targetSum)
            break;
        ans += dfs(
            pos + 1,
            sum + d,
            (mod * 10 + d) % targetSum,
            tight && (d == limit));
    }

    return res = ans;
}

int solve(long long x)
{
    s = to_string(x);

    int ans = 0;

    for (int i = 1; i < 130; i++)
    {
        targetSum = i;
        memset(dp, -1, sizeof(dp));
        ans += dfs();
    }
    return ans;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int r;
    cin >> r;
    cout << solve(r) << endl;

    return 0;
}