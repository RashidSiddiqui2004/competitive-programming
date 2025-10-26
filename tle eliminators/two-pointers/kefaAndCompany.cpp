#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

using ll = long long;

int main()
{
    ll n, maximumDifferenceAllowed;
    cin >> n >> maximumDifferenceAllowed;

    vector<pair<ll, ll>> vp;

    for (int i = 0; i < n; i++)
    {
        ll money, friendshipfactor;
        cin >> money >> friendshipfactor;
        vp.emplace_back(money, friendshipfactor);
    }

    sort(vp.begin(), vp.end());

    vector<ll> prefixFriendshipFactor(n);
    prefixFriendshipFactor[0] = vp[0].second;

    for (int i = 1; i < n; i++)
    {
        prefixFriendshipFactor[i] = prefixFriendshipFactor[i - 1] + vp[i].second;
    }

    // for(auto i: vp){
    //     cout<<i.first<<" "<<i.second<<endl;
    // }

    ll maximumFriendshipFactor = 0ll;
    ll l = 0, r = 0;

    for (; r < n; r++)
    {
        while (l <= r and vp[r].first - vp[l].first >= maximumDifferenceAllowed)
        {
            ++l;
        }
        if (l <= r)
        {
            maximumFriendshipFactor = max(maximumFriendshipFactor, prefixFriendshipFactor[r] - (l == 0 ? 0ll : prefixFriendshipFactor[l - 1]));
        }
    }

    cout << maximumFriendshipFactor << endl;

    return 0;
}