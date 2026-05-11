#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <array>
#include <deque>
#include <cstring>
#include <queue>
#include <stack>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <functional>
#include <utility>
#include <tuple>
#include <cmath>
#include <climits>
#include <cfloat>
#include <bitset>
#include <cassert>
#include <random>
#include <chrono>

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef tree<
    pair<int, int>,
    null_type,
    less<pair<int, int>>,
    rb_tree_tag,
    tree_order_statistics_node_update>
    ordered_set;

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
#define khalaas return 0;

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
#ifndef OnLInE_JUDGE
#define debug(x) cerr << #x << " = " << (x) << endl;
#else
#define debug(x)
#endif

// Utility Functions
inline ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
inline ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

inline ll mod_add(ll a, ll b, ll m = MOD)
{
    return (a + b) % m;
}

inline ll mod_sub(ll a, ll b, ll m = MOD)
{
    return (a - b + m) % m;
}

inline ll mod_mul(ll a, ll b, ll m = MOD)
{
    return (a * b) % m;
}

ll mod_pow(ll a, ll b, ll m = MOD)
{
    ll res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = mod_mul(res, a, m);
        a = mod_mul(a, a, m);
        b >>= 1;
    }
    return res;
}

ll exp_fast(ll a, ll b)
{
    ll res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * 1ll * a;
        a = 1 * 1ll * a;
        b >>= 1;
    }
    return res;
}

ll mod_inv(ll a, ll m = MOD)
{
    // Modular inverse using Fermat's Little Theorem: a^(m-2) % m
    return mod_pow(a, m - 2, m);
}

vector<ll> factorial, inv_factorial;

void precompute_factorials(int maxn, ll m = MOD)
{
    factorial.resize(maxn + 1);
    inv_factorial.resize(maxn + 1);

    factorial[0] = 1;
    for (int i = 1; i <= maxn; ++i)
    {
        factorial[i] = mod_mul(factorial[i - 1], i, m);
    }

    inv_factorial[maxn] = mod_inv(factorial[maxn], m);

    // (n)^-1 = ((n+1)^-1) * (n+1)
    for (int i = maxn - 1; i >= 0; --i)
    {
        inv_factorial[i] = mod_mul(inv_factorial[i + 1], i + 1, m);
    }
}

ll ncr(ll n, ll r, ll m = MOD)
{
    if (r > n || r < 0)
        return 0;
    return mod_mul(factorial[n], mod_mul(inv_factorial[r], inv_factorial[n - r], m), m);
}

bool is_prime(int n)
{
    if (n < 2)
        return false;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

vector<int> primes;
vector<bool> isPrime;

const int maxn = 3e5 + 1;
vector<int> spf;

vector<int> sieve(int n)
{
    primes.clear();
    isPrime.assign(n + 1, true);
    spf.assign(n + 1, 0);

    isPrime[0] = isPrime[1] = false;
    for (int i = 1; i <= n; i++)
        spf[i] = i;

    for (int i = 2; i <= n; i++)
    {
        if (isPrime[i])
        {
            primes.push_back(i);
            spf[i] = i;

            for (long long j = 1LL * i * 2; j <= n; j += i)
            {
                isPrime[j] = false;
                if (spf[j] == j)
                    spf[j] = i;
            }
        }
    }
    return primes;
}

// Input/Output
template <typename T>
void read_vector(vector<T> &v)
{
    for (auto &x : v)
        cin >> x;
}

template <typename T>
void print_vector(const vector<T> &v)
{
    for (const auto &x : v)
        cout << x << " ";
    cout << endl;
}

#define yes          \
    cout << "YES\n"; \
    return;

#define no          \
    cout << "NO\n"; \
    return;

#define impossible  \
    cout << "-1\n"; \
    return;

void getFactorization(ll n, unordered_map<ll, ll> &mp)
{
    while (n > 0)
    {
        if (spf[n] == n)
        {
            mp[n]++;
            break;
        }
        mp[spf[n]]++;
        n /= spf[n];
    }
    return;
}

const int mod_CC = 998244353;

int ceil_log2(int x)
{
    if (x <= 1)
        return 0;
    return 64 - __builtin_clzll(x - 1);
}

struct BIT
{
    int n;
    vector<int> f;
    BIT(int _n) : n(_n), f(n + 1, 0) {}
    void add(int index, int value)
    {
        while (index <= n)
        {
            f[index] += value;
            index += index & -index;
        }
    }

    int sum(int index)
    {
        int result = 0;
        while (index > 0)
        {
            result += f[index];
            index -= index & -index;
        }
        return result;
    }

    int sum(int l, int r)
    {
        if (l > r)
            return 0;
        return sum(r) - sum(l - 1);
    }
};

struct Node
{
    int key, type, pos, l, idx;
};

ll get_val(int c, int d, const vector<ll> &ps, int n)
{
    if (c < d)
        return ps[d - 1] - ps[c];
    return (ps[2 * n] - ps[c]) + ps[d - 1];
}

class DSU
{
    vector<int> parent, size;

public:
    DSU(int n)
    {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int getParent(int x)
    {
        if (parent[x] != x)
            parent[x] = getParent(parent[x]);
        return parent[x];
    }

    void unionSets(int x, int y)
    {
        int rootX = getParent(x);
        int rootY = getParent(y);

        if (rootX != rootY)
        {
            if (size[rootX] < size[rootY])
                swap(rootX, rootY);
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    }

    int getParentSize(int x)
    {
        return size[getParent(x)];
    }
};

bool checktic(vector<vector<char>> &grid, char ch)
{
    // rows
    for (int i = 0; i < 3; i++)
    {
        bool check = true;
        for (int j = 0; j < 3; j++)
        {
            if (grid[i][j] != ch)
            {
                check = false;
            }
        }
        if (check)
        {
            return true;
        }
    }

    // columns
    for (int j = 0; j < 3; j++)
    {
        bool check = true;
        for (int i = 0; i < 3; i++)
        {
            if (grid[i][j] != ch)
            {
                check = false;
            }
        }
        if (check)
        {
            return true;
        }
    }

    // diag
    if (grid[0][0] == ch && grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2])
    {
        return true;
    }

    // anti-diag
    if (grid[0][2] == ch && grid[0][2] == grid[1][1] && grid[0][2] == grid[2][0])
    {
        return true;
    }

    return false;
}

void s1()
{
    int n = 3;
    vector<vector<char>> grid(n, vector<char>(n, '.'));

    fl(i, n)
    {
        fl(j, n)
        {
            cin >> grid[i][j];
        }
    }

    if (checktic(grid, 'O'))
    {
        cout << "O\n";
    }
    else if (checktic(grid, 'X'))
    {
        cout << "X\n";
    }
    else if (checktic(grid, '+'))
    {
        cout << "+\n";
    }
    else
    {
        cout << "DRAW\n";
    }
}

void s2()
{
    int a, b;
    cin >> a >> b;

    if ((a & 1) && (b & 1))
    {
        no;
    }
    else
    {
        yes;
    }
}

void s3()
{
    int n;
    cin >> n;

    string s;
    cin >> s;

    if (n & 1)
    {
        no;
    }

    int l = 0;

    fl(i, n)
    {
        if (s[i] == '(')
        {
            ++l;
        }
        else
        {
            --l;
        }
    }

    if (l == 0)
    {
        yes;
    }
    else
    {
        no;
    }
}

void s4()
{
    int n;
    cin >> n;

    vector<int> a(n);
    read_vector(a);

    vector<int> mul6, mul2, mul3, rem;

    fl(i, n)
    {
        if (a[i] % 6 == 0)
        {
            mul6.push_back(a[i]);
        }
        else if (a[i] % 2 == 0)
        {
            mul2.push_back(a[i]);
        }
        else if (a[i] % 3 == 0)
        {
            mul3.push_back(a[i]);
        }
        else
        {
            rem.push_back(a[i]);
        }
    }

    for (auto i : mul6)
    {
        cout << i << ' ';
    }
    for (auto i : mul2)
    {
        cout << i << ' ';
    }
    for (auto i : rem)
    {
        cout << i << ' ';
    }
    for (auto i : mul3)
    {
        cout << i << ' ';
    }
    cout << endl;
}

// void s5()
// {
//     int n;
//     cin >> n;

//     int m = 2 * n;
//     vector<int> v(m);
//     read_vector(v);

//     int maxmex = 0;

//     fl(i, m)
//     {
//         int p1 = i - 1, p2 = i + 1;
//         vector<int> mark(n + 1, 0);
//         mark[v[i]] = 1;
//         int currmex = 0;
//         while (mark[currmex])
//         {
//             ++currmex;
//         }

//         while (p1 >= 0 && p2 < m && v[p1] == v[p2])
//         {
//             mark[v[p1]] = 1;
//             while (mark[currmex])
//             {
//                 ++currmex;
//             }
//             --p1, ++p2;
//         }

//         maxmex = max(maxmex, currmex);
//     }

//     fl(i, m - 1)
//     {
//         if (v[i] != v[i + 1])
//         {
//             continue;
//         }
//         int p1 = i - 1, p2 = i + 2;
//         vector<int> mark(n + 1, 0);
//         mark[v[i]] = 1;
//         mark[v[i + 1]] = 1;

//         int currmex = 0;
//         while (mark[currmex])
//         {
//             ++currmex;
//         }
//         while (p1 >= 0 && p2 < m && v[p1] == v[p2])
//         {
//             mark[v[p1]] = 1;
//             while (mark[currmex])
//             {
//                 ++currmex;
//             }
//             --p1, ++p2;
//         }

//         maxmex = max(maxmex, currmex);
//     }

//     cout << maxmex << endl;
// }

void s5()
{
    int n;
    cin >> n;

    int m = 2 * n;
    vector<int> v(m);
    read_vector(v);

    int maxmex = 0;

    vector<pair<int, int>> pos(n, {-1, -1});

    fl(i, m)
    {
        if (pos[v[i]].first == -1)
        {
            pos[v[i]].first = i;
        }
        else
        {
            pos[v[i]].second = i;
        }
    }

    fl(i, n)
    {
        if (pos[i].first == pos[i].second - 1)
        {
            int p1 = pos[i].first - 1, p2 = pos[i].first + 2;
            vector<bool> mark(n + 2, 0);
            mark[i] = 1;

            int currmex = 0;
            while (mark[currmex])
            {
                ++currmex;
            }

            while (p1 >= 0 && p2 < m && v[p1] == v[p2])
            {
                mark[v[p1]] = 1;
                while (mark[currmex])
                {
                    ++currmex;
                }
                --p1, ++p2;
            }

            maxmex = max(maxmex, currmex);
        }
        else if (pos[i].first == pos[i].second - 2)
        {
            int p1 = pos[i].first - 1, p2 = pos[i].second + 1;
            vector<bool> mark(n + 2, 0);
            mark[i] = 1;
            mark[v[pos[i].first + 1]] = 1;

            int currmex = 0;
            while (mark[currmex])
            {
                ++currmex;
            }

            while (p1 >= 0 && p2 < m && v[p1] == v[p2])
            {
                mark[v[p1]] = 1;
                while (mark[currmex])
                {
                    ++currmex;
                }
                --p1, ++p2;
            }

            maxmex = max(maxmex, currmex);
        }
    }

    if (maxmex == 0)
    {
        maxmex = 1;
    }

    cout << maxmex << endl;
}

void s6()
{
    int n;
    cin >> n;

    vector<int> v(n);
    read_vector(v);

    int minh = v.back();

    int total = 0;

    vector<int> prevmin(n);
    prevmin[n - 1] = v.back();

    for (int i = n - 2; i >= 0; i--)
    {
        if (v[i] <= minh)
        {
            minh = v[i];
        }
        else
        {
            total += (v[i] - minh);
        }
        prevmin[i] = minh;
    }

    int ans = total;

    for (int i = n - 1; i >= 0;)
    {
        int curr = v[i];
        int currres = total - 1;

        while (i >= 0 && v[i] >= curr)
        {
            ++currres;
            --i;
        }

        ans = max(ans, currres);
    }

    cout << ans << endl;
}

struct Fenwick
{
    int n;
    vector<ll> bit;

    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    void add(int idx, ll val)
    {
        for (; idx <= n; idx += idx & -idx)
            bit[idx] += val;
    }

    ll sum(int idx) const
    {
        ll res = 0;
        for (; idx > 0; idx -= idx & -idx)
            res += bit[idx];
        return res;
    }
};

void s7()
{
    int n;
    cin >> n;

    vector<ll> a(n);
    read_vector(a);

    vector<ll> vals = a;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    auto getId = [&](ll x)
    {
        return (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin()) + 1;
    };

    // number of compressed values <= x
    auto getIdLE = [&](ll x)
    {
        return (int)(upper_bound(vals.begin(), vals.end(), x) - vals.begin());
    };

    Fenwick bitCnt((int)vals.size());
    Fenwick bitSum((int)vals.size());

    vector<ll> t(n);

    for (int i = n - 1; i >= 0; i--)
    {
        int id = getId(a[i]);

        ll sumLe = bitSum.sum(id);
        ll cntLe = bitCnt.sum(id);
        ll totalCnt = bitCnt.sum((int)vals.size());
        ll cntGt = totalCnt - cntLe;

        t[i] = sumLe + cntGt * a[i];

        bitCnt.add(id, 1);
        bitSum.add(id, a[i]);
    }

    ll total = 0;
    for (int i = 0; i < n; i++)
    {
        ll area = a[i] * 1LL * (n - i - 1);
        total += (area - t[i]);
    }

    ordered_set os;

    vector<ll> greaterCnt(n);

    for (int i = 0; i < n; i++)
    {
        ll smaller = os.order_of_key({a[i], -1});
        ll currSize = (ll)os.size();
        greaterCnt[i] = currSize - smaller;
        os.insert({a[i], i});
    }

    Fenwick bitCnt2((int)vals.size());
    Fenwick bitSum2((int)vals.size());

    ll ans = total;

    for (int i = n - 1; i >= 0; i--)
    {
        int idCurr = getId(a[i]);

        ll sumLe = bitSum2.sum(idCurr);
        ll cntLe = bitCnt2.sum(idCurr);
        ll totalCnt = bitCnt2.sum((int)vals.size());
        ll cntGt = totalCnt - cntLe;

        ll origarea = sumLe + cntGt * a[i];

        int idPrev = getIdLE(a[i] - 1);

        ll sumLe2 = bitSum2.sum(idPrev);
        ll cntLe2 = bitCnt2.sum(idPrev);
        ll cntGt2 = totalCnt - cntLe2;

        ll newarea = sumLe2 + cntGt2 * (a[i] - 1);

        ans = max(ans, total + greaterCnt[i] - origarea + newarea);

        bitCnt2.add(idCurr, 1);
        bitSum2.add(idCurr, a[i]);
    }

    cout << ans << endl;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;

    while (t--)
    {
        s7();
    }

    khalaas
}