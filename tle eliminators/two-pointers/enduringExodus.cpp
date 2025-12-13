#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using ll = long long;

int main()
{
    ll n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    vector<int> spaces;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '0')
            spaces.push_back(i);
    }

    int m = spaces.size();
    if (m == 0)
    {
        cout << -1 << endl;
        return 0;
    }

    auto possible = [&](int maxdist)
    {
        for (int i = 0; i < m; i++)
        {
            auto l = lower_bound(spaces.begin(), spaces.end(), spaces[i] - maxdist);
            auto r = upper_bound(spaces.begin(), spaces.end(), spaces[i] + maxdist);
            int count = r - l;
            // this count should be sufficient enough to accomodate 
            // both the farmer and his k cows.
            if (count >= (k + 1))
                return true;
        }
        return false;
    };

    ll low = 0, high = spaces.back() - spaces.front();
    ll ans = -1;

    while (low <= high)
    {
        ll mid = (low + high) / 2;
        if (possible(mid))
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    cout << ans << endl;
    return 0;
}
