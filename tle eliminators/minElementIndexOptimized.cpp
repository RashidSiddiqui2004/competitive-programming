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
#include <cstdio> // ✅ Required for freopen

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

using pii = pair<int, int>;

vector<int> sliding_window_minimum(vector<int> &a, int k)
{
    int n = a.size();
    vector<int> ans;
    deque<int> deq;

    for (int i = 0; i < n; i++)
    {
        while (!deq.empty() && a[deq.back()] >= a[i])
            deq.pop_back();
        deq.push_back(i);

        if (deq.front() == i - k)
            deq.pop_front();

        if (i >= k - 1)
            ans.push_back(deq.front());
    }

    return ans;
}

// print the index of the first negative element of the array

vector<int> first_negative_element(vector<int> &a, int k)
{
    int n = a.size();
    vector<int> res;
    queue<int> q;

    for (int i = 0; i < n; i++)
    {
        if (a[i] < 0)
            q.push(i);
        if (!q.empty() and q.front() == (i - k))
            q.pop();
        if (i >= k - 1)
        {
            if (q.empty())
                res.push_back(-1);
            else
                res.push_back(q.front());
        }
    }
    return res;
}

int32_t main()
{
    vector<int> arr = {1, 3, 1, 2, 4, 5, 1, 7, 2};
    int k = 3;

    vector<int> res = sliding_window_minimum(arr, k);

    for (int x : res)
        cout << x << " ";
    cout << endl;

    vector<int> v = {1, 2, -1, 3, -3, 39, -19, 20, 21};
    int k2 = 2;

    vector<int> res2 = first_negative_element(v, k2);

    for (int x : res2)
        cout << x << " ";
    cout << endl;

    return 0;
}