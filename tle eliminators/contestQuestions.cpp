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

bool ispossible(vector<int> &prefsum, int k, int operations, int minelement)
{
    int n = prefsum.size();
    int totalsum = prefsum.back();
    if (totalsum - operations <= k)
    {
        return true;
    }

    for (int i = 1; i < n; i++)
    {
        int rem_opers = operations - i;
        if (rem_opers < 0)
        {
            break;
        }
        int currsum = totalsum - rem_opers + i * 1ll * (minelement - rem_opers);
        currsum -= prefsum[i - 1];
        if (currsum <= k)
        {
            return true;
        }
    }

    return false;
}

void solve1()
{
    int n, k;
    cin >> n >> k;

    vector<int> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    sort(all(v));
    reverse(all(v));

    int min_element = v.back();

    fl(i, n - 1)
    {
        v[i + 1] += v[i];
    }

    int low = 0, high = 1e10, mid, ans;

    while (low <= high)
    {
        mid = (low + high) / 2;
        if (ispossible(v, k, mid, min_element))
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
}

void solve2()
{
    // c = a^2 - b
    int n;
    cin >> n;
    int ans = 0;

    int limit = sqrt(2 * n + 10);

    for (int a = 3; a <= min(n, limit); a += 2)
    {
        int b = ((a * a) - 1) / 2;
        int c = b + 1;
        if (c > n)
        {
            break;
        }
        else
        {
            ans++;
        }
    }
    cout << ans << endl;
}

// https://codeforces.com/problemset/problem/1873/F
void solve3()
{
    int n, k;
    cin >> n >> k;
    vector<ll> fruits(n), height(n);

    fl(i, n)
    {
        cin >> fruits[i];
    }
    fl(i, n)
    {
        cin >> height[i];
    }

    vector<vector<int>> segments;

    int i = 0;
    while (i < n)
    {
        vector<int> v = {fruits[i]};
        int prev = height[i++];
        while (i < n and (height[i - 1] % height[i]) == 0)
        {
            v.push_back(fruits[i++]);
        }
        segments.push_back(v);
    }

    int max_segmentlen = 0;
    for (auto v : segments)
    {
        int m = v.size();
        int l = 0, r = 0;
        int currentSubarraySum = 0;
        for (; r < m; r++)
        {
            currentSubarraySum += v[r];
            while (l <= r and currentSubarraySum > k)
            {
                currentSubarraySum -= v[l++];
            }
            if (l <= r)
                max_segmentlen = max(max_segmentlen, r-l+1);
        }
    }

    cout<<max_segmentlen<<endl;
}

int32_t main()
{
    int t;
    cin >> t;

    while (t--)
    {
        solve3();
    }

    return 0;
}