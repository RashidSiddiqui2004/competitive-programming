#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);

    for (size_t i = 0; i < n; i++)
    {
        cin >> a[i + 1];
    }
    for (size_t i = 0; i < n; i++)
    {
        cin >> b[i + 1];
    }

    vector<vector<int>> dp(n + 4, vector<int>(2, -1));
    dp[0][0] = 0;
    dp[0][1] = 0;

    for (size_t i = 1; i <= n; i++)
    {
        dp[i][0] = a[i] + min(dp[i - 1][0], dp[i - 1][1]);
        if (i >= 2)
        {
            dp[i][1] = b[i] + b[i - 1] + min(dp[i - 2][0], dp[i - 2][1]);
        }
    }

    int ans = min(dp[n][0], dp[n][1]);
    cout << ans << endl;

    return 0;
}