#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <array>
#include <deque>
#include <queue>
#include <algorithm>
#include <stack>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
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

// oh hello!

template <typename T>
bool allsame(vector<T> arr)
{
    int n = arr.size();
    for (int i = 1; i < n; i++)
    {
        if (arr[i] != arr[0])
        {
            return false;
        }
    }
    return true;
}

void solve1()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for (size_t i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    if (allsame(v))
    {
        cout << 0 << endl;
        return;
    }
    vector<int> diffs;
    int p1 = 0, p2 = n - 1;
    while (p1 < p2)
    {
        diffs.push_back(abs(v[p2] - v[p1]));
        ++p1, --p2;
    }
    int res = 0;
    for (auto i : diffs)
    {
        res = __gcd(res, i);
    }

    cout << res << endl;
}

void solve2(){

}

int32_t main()
{
    int t = 1;
    cin >> t;

    while (t--)
    {
        solve2();
    }

    return 0;
}