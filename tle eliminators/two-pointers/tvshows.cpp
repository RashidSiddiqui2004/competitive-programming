#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <array>
#include <deque>
#include <queue>
#include <stack>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <numeric>    // accumulate, gcd, lcm
#include <functional> // function, greater, less
#include <utility>    // pair, make_pair
#include <tuple>
#include <cmath>
#include <climits>
#include <cfloat>
#include <bitset>
#include <cassert>
#include <random>
#include <chrono>
#include <cstdio>

using namespace std;

// Macros
#define fast_io                  \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);            \
    cout.tie(nullptr);
#define pb push_back
#define mp make_pair
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define fi first
#define se second
#define sz(x) (int)((x).size())
#define endl '\n'
#define fl(i, n) for (int i = 0; i < n; i++)
#define fr(i, n) for (int i = n - 1; i >= 0; i--)

// Typedefs

#define int long long

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pll> vpll;

#define vvi vector<vector<int>>
// Constants
const int MOD = 1e9 + 7;
const ll InF = 1e18;
const double EPS = 1e-9;
const ll nEG = -1e18;

// Debugging
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << (x) << endl;
#else
#define debug(x)
#endif

void s1()
{
    int n, k, d;
    cin >> n >> k >> d;
    vector<int> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }
    map<int, int> mp;
    int res = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        mp[v[i]]++;

        if (i >= d)
        {
            if (--mp[v[i - d]] == 0)
            {
                mp.erase(v[i - d]);
            }
        }

        if (i >= d - 1)
        {
            res = min(res, (ll)mp.size());
        }
    }

    cout << res << endl;
}

void s2()
{
    int n, d;
    cin >> n >> d;
    vector<int> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }
    sort(all(v));

    int res = 0ll;
    fl(i, n - 1)
    {
        auto it = upper_bound(all(v), v[i] + d) - v.begin();
        res += (n - it);
    }
    cout << res << endl;
}

void s3()
{
    string t;
    cin >> t;

    string s[2];

    int n = t.size();

    for (auto i : t)
    {
        if ((int)(i - '0') & 1)
        {
            s[0] += i;
        }
        else
        {
            s[1] += i;
        }
    }

    reverse(all(s[0]));
    reverse(all(s[1]));

    string ans;

    while (!s[0].empty() || !s[1].empty())
    {
        if (s[1].empty())
        {
            ans += s[0].back();
            s[0].pop_back();
        }
        else if (s[0].empty())
        {
            ans += s[1].back();
            s[1].pop_back();
        }
        else
        {
            if (s[0].back() < s[1].back())
            {
                ans += s[0].back();
                s[0].pop_back();
            }
            else
            {
                ans += s[1].back();
                s[1].pop_back();
            }
        }
    }

    cout << ans << endl;
}

int32_t main()
{
    int t = 1;
    cin >> t;

    while (t--)
    {
        s3();
    }

    return 0;
}