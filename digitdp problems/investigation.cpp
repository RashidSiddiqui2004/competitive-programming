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

int dp[11][105][105][2];

int solver(string &s, int k, int pos = 0, int num = 0, int modsum = 0, bool istight = 1)
{
    int n = s.size();

    if (pos == n)
    {
        return (modsum == 0) && ((num % k) == 0);
    }

    int &memvalue = dp[pos][num][modsum][istight];

    if (memvalue != -1)
    {
        return memvalue;
    }

    int upperlimit = istight ? (s[pos] - '0') : 9;
    int ans = 0;
    for (int digit = 0; digit <= upperlimit; digit++)
    {
        ans += solver(
            s,
            k,
            pos + 1,
            (num * 10 + digit) % k,
            (modsum + digit) % k,
            istight && (digit == upperlimit));
    }
    return memvalue = ans;
}

// https://lightoj.com/problem/investigation
void solution()
{
    int l, r, k;
    cin >> l >> r >> k;

    if (k > 90)
    {
        cout << 0 << endl;
        return;
    }

    string ls = to_string(l - 1);
    string rs = to_string(r);

    memset(dp, -1, sizeof(dp));
    int lessthanr = solver(rs, k);

    memset(dp, -1, sizeof(dp));
    int lessthanl = solver(ls, k);

    int ans = lessthanr - lessthanl;
    cout << ans << endl;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;

    for (size_t i = 1; i <= t; i++)
    {
        cout << "Case " << i << ": ";
        solution();
    }

    return 0;
}