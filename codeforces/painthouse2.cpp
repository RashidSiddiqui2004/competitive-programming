#include <iostream>
using namespace std;

int costs[1000][100];
int dp[1000][100];

int main()
{
    int n, k;
    cin >> n >> k;

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < k; j++)
        {
            cin >> costs[i][j];
            dp[i][j] = INT_MAX;
        }
    }

    // dp[i][j] = mincost to paint the houses upto index i,
    // with the ith house painted with color j

    for (int i = 0; i < k; i++)
    {
        dp[0][i] = costs[0][i];
    }

    int ans = INT_MAX;

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            for (int l = 0; l < k; l++)
            {
                if (l == j)
                    continue;

                dp[i][j] = min(dp[i][j], dp[i - 1][l] + costs[i][j]);
            }
            if (i == (n - 1))
            {
                ans = min(ans, dp[i][j]);
            }
        }
    }

    cout << ans << endl;

    return 0;
}