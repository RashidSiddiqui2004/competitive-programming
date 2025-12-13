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

long long cal_ans(int a, int b, int c)
{
    return 1ll * (a - b) * (a - b) + 1ll * (b - c) * (b - c) + 1ll * (c - a) * (c - a);
}

int solve(vector<int> &a, vector<int> &b, vector<int> &c)
{
    int ans = LLONG_MAX;
    int p1 = 0, p2 = 0, p3 = 0;
    for (int p1 = 0; p1 < a.size(); p1++)
    {
        while (p2 < b.size() - 1 and b[p2] < a[p1])
        {
            ++p2;
        }

        while(p3 < c.size() -1) {
            if(c[p3+1] > a[p1]){
                break;
            }
            ++p3;
        }
        ans = min(ans, cal_ans(a[p1], b[p2], c[p3]));
    }
    return ans;
}

int32_t main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int nr, ng, nb;
        cin >> nr >> ng >> nb;

        vector<int> red(nr, 0);
        vector<int> green(ng, 0);
        vector<int> blue(nb, 0);

        for (int i = 0; i < nr; i++)
        {
            cin >> red[i];
        }
        for (int i = 0; i < ng; i++)
        {
            cin >> green[i];
        }
        for (int i = 0; i < nb; i++)
        {
            cin >> blue[i];
        }

        int ans = LLONG_MAX;

        sort(red.begin(), red.end());
        sort(green.begin(), green.end());
        sort(blue.begin(), blue.end());
        // O(nlogn)

        ans = cal_ans(red[0], blue[0], green[0]);

        ans = min(ans, solve(red, green, blue));
        ans = min(ans, solve(red, blue, green));
        ans = min(ans, solve(green, red, blue));
        ans = min(ans, solve(green, blue, red));
        ans = min(ans, solve(blue, red, green));
        ans = min(ans, solve(blue, green, red));
        // O(6*n) = O(n)
        cout << ans << endl;
    }

    return 0;
}