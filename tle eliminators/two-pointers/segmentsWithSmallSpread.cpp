#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define ll unsigned long long

ll segmentswithSmallspread(vector<ll> &nums, ll k)
{
    int n = nums.size();
    ll res = 0;
    ll l = 0, r = 0;

    multiset<ll> mt;

    for (; r < n; r++)
    {
        mt.insert(nums[r]);
        while (l <= r)
        {
            ll mini = *mt.begin();
            ll maxi = *(mt.rbegin());
            if ((maxi - mini) > k)
            {
                mt.erase(mt.find(nums[l++]));
            }
            else
            {
                break;
            }
        }
        if (l <= r)
            res += (r - l + 1);
    }
    return res;
}

int main()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    cout << segmentswithSmallspread(v, k);
}
