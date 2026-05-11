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

// https://codeforces.com/contest/2121/problem/E
string sl, sr;
int dp[11][2][2];  

int dfs(int pos = 0, bool lowertight = 1, bool uppertight = 1)
{
    if (pos == (int)sr.size())
    {
        return 0;
    }

    int &res = dp[pos][lowertight][uppertight];
    if (res != -1)
        return res;

    int lowerlimit = lowertight ? sl[pos] - '0' : 0;
    int upperlimit = uppertight ? sr[pos] - '0' : 9;

    int ans = INT_MAX;

    for (int d = lowerlimit; d <= upperlimit; d++)
    {
        int ldigit = sl[pos]-'0'; 
        int rdigit = sr[pos]-'0';

        ans = min(ans, (d==ldigit) + (d==rdigit) + dfs(pos+1, 
            lowertight && d==lowerlimit, uppertight && d==upperlimit));
    }
    return res = ans;
}

int rangeQuery(long long L, long long R)
{
    sl = to_string(L);
    sr = to_string(R);
    memset(dp, -1, sizeof(dp));
    return dfs();
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;

    for (size_t i = 1; i <= t; i++)
    {
        int l, r;
        cin >> l >> r;
        int ans = rangeQuery(l, r);
        cout << ans << endl;
    }

    return 0;
}