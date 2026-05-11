#include <iostream>
using namespace std;

#define int long long

string s;
int dp[20][200][2]; // adjust dimensions depending on state

int dfs(int pos, int state, bool tight)
{
    if (pos == s.size())
    {
        // base condition depending on problem
        return (state == 0);
    }

    int &res = dp[pos][state][tight];
    if (res != -1)
        return res;

    int limit = tight ? s[pos] - '0' : 9;

    int ans = 0;

    for (int d = 0; d <= limit; d++)
    {
        int newState = (state + d);  // update state logic

        ans += dfs(
            pos + 1,
            newState,
            tight && (d == limit));
    }

    return res = ans;
}

int solve(long long x)
{
    s = to_string(x);
    memset(dp, -1, sizeof(dp));

    return dfs(0, 0, 1);
}

int rangeQuery(long long L, long long R)
{
    return solve(R) - solve(L - 1);
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