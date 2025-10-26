#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

int main()
{
    ll n, s;
    cin >> n >> s;

    vector<ll> w(n), c(n);

    for (size_t i = 0; i < n; i++)
    {
        cin >> w[i];
    }
    for (size_t i = 0; i < n; i++)
    {
        cin >> c[i];
    }

    vector<ll> prefcost(n);
    prefcost[0] = c[0];

    for (size_t i = 1; i < n; i++)
    {
        prefcost[i] = prefcost[i - 1] + c[i];
    }

    int l = 0, r = 0;
    ll sumweight = 0;

    ll maxProfit = 0ll;

    for (; r < n; r++)
    {
        sumweight += w[r];
        while (l < r and sumweight > s)
        {
            sumweight-=w[l];
            l++;
        }
        if (sumweight <= s)
        {
            maxProfit = max(maxProfit, prefcost[r] - (l == 0 ? 0 : prefcost[l - 1]));
        }
    }

    cout << maxProfit << endl;

    return 0;
}