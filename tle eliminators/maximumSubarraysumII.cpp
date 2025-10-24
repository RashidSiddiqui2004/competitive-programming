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

int subarrayswithSumx()
{
    int n, k;
    cin >> n >> k;

    vector<int> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    int ans = 0;
    int sum = 0;
    map<int, int> mp;
    mp[0] = 1;

    fl(i, n)
    {
        sum += v[i];
        if (mp.count(sum - k))
        {
            ans += mp[sum - k];
        }
        mp[sum]++;
    }

    return ans;
}

int subarrayswithSumDivisblebyK()
{
    int n, k;
    cin >> n;

    k = n;

    vector<int> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    int ans = 0;
    int sum = 0;
    map<int, int> mp;
    mp[0] = 1;

    fl(i, n)
    {
        sum = ((sum + v[i] % k) + k) % k;
        if (mp.count(sum))
        {
            ans += mp[sum];
        }
        mp[sum]++;
    }

    return ans;
}

// https://cses.fi/problemset/task/1644

int maximumSubarraySumII()
{
    int n, a, b;
    cin >> n >> a >> b;

    vector<int> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    // maintain prefix sum values
    // v[i] = prefixsum of i
    vector<long long> p(n + 1, 0);
    for (int i = 0; i < n; i++) p[i + 1] = p[i] + v[i];

    multiset<long long> s;
    long long ans = LLONG_MIN;

    // for first window
    // initialize with prefix sums for first range [a, b]
    for (int i = a; i <= b && i <= n; i++) {
        s.insert(p[i]);
    }

    ans = max(ans, *s.rbegin() - p[0]);

    for (int i = 1; i + a <= n; i++) {
        s.erase(s.find(p[i + a - 1]));
        if (i + b <= n) s.insert(p[i + b]);
        ans = max(ans, *s.rbegin() - p[i]);
    }

    return ans;
}

int32_t main()
{
    // cout<<subarrayswithSumx();
    // cout<<subarrayswithSumDivisblebyK();
    cout << maximumSubarraySumII();
}
