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

// vector<ll> pow2;

// void mod_pow2_memo()
// {
//     pow2.resize(1e5 + 1);

//     ll curr = 1ll;
//     for (int i = 0; i <= 1e5; i++)
//     {
//         pow2[i] = curr;
//         curr = (curr * 2) % MOD;
//     }
// }

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
    cout << "Yes\n"; \
    return;

#define no          \
    cout << "No\n"; \
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

void s1()
{
    int n;
    cin >> n;
    bool isf = false;
    fl(i, n)
    {
        int e;
        cin >> e;
        if (e == 67)
            isf = true;
    }

    if (isf)
    {
        cout << "Yes\n";
    }
    else
    {
        cout << "No\n";
    }
}

void s2()
{
    int n;
    cin >> n;

    vector<int> v(n + 1);
    fl(i, n)
    {
        cin >> v[i + 1];
    }

    // vector<vector<int>> g;
    vector<bool> mark(n + 1, false);

    for (size_t i = 1; i <= n / 2; i++)
    {
        if (mark[i])
        {
            continue;
        }
        vector<int> grp;
        for (int j = i; j <= n; j += j)
        {
            mark[j] = true;
            grp.push_back(v[j]);
        }
        sort(all(grp));
        // print_vector(grp);
        int ptr = 0;
        for (int j = i; j <= n; j += j)
        {
            v[j] = grp[ptr++];
        }
    }
    int i = 1;
    while ((i + 1) <= n)
    {
        if (v[i] > v[i + 1])
        {
            cout << "No\n";
            return;
        }
        ++i;
    }
    cout << "Yes\n";
}

void s3()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    vvi dp(n, vi(7, INT_MAX));

    for (int f = 1; f <= 6; f++)
    {
        dp[0][f] = (v[0] == f ? 0 : 1);
    }

    for (int i = 1; i < n; i++)
    {
        for (int f = 1; f <= 6; f++)
        {
            for (int prev = 1; prev <= 6; prev++)
            {
                if (f != prev && (f + prev != 7))
                {
                    dp[i][f] = min(dp[i][f], dp[i - 1][prev] + (v[i] == f ? 0 : 1));
                }
            }
        }
    }

    int ans = INT_MAX;
    for (int f = 1; f <= 6; f++)
        ans = min(ans, dp[n - 1][f]);

    cout << ans << endl;
}

void s4()
{
    int n;
    cin >> n;
    vector<int> f(n + 1);
    fl(i, n)
    {
        cin >> f[i + 1];
    }

    if (n == 2)
    {
        cout << f[2] << ' ' << f[1] << endl;
        return;
    }

    vector<int> a(n + 1);

    for (int i = 2; i <= n - 1; i++)
    {
        a[i] = (f[i + 1] + f[i - 1] - 2 * f[i]) / 2;
    }

    int p = 0, q = 0;

    for (int i = 1; i <= n - 2; i++)
    {
        p += (i * a[i + 1]);
    }

    for (int i = 1; i <= n - 2; i++)
    {
        q += (i * a[n - i]);
    }

    a[1] = (f[n] - q) / (n - 1);
    a[n] = (f[1] - p) / (n - 1);

    for (int i = 1; i <= n; i++)
    {
        cout << a[i] << ' ';
    }
    cout << endl;
}

int dfs(vector<vector<int>> &adj, int node, vector<int> &subtree)
{
    int curr = 0;

    for (auto i : adj[node])
    {
        curr += 2 + dfs(adj, i, subtree);
    }

    return subtree[node] = curr;
}

void dfs2(vector<vector<int>> &adj, int node, int par, vector<int> &subtree,
          vector<int> &ans, int psum)
{
    ans[node] = (psum + subtree[node] + 1) % MOD;

    for (auto i : adj[node])
    {
        if (i == par)
            continue;
        dfs2(adj, i, node, subtree, ans, ans[node]);
    }
}

void s5()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    vector<int> par(n + 1);
    par[1] = 0;
    par[0] = -1;

    adj[0].push_back(1);

    vector<int> subtree(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        int u, v;
        cin >> u >> v;
        if (u == 0)
        {
            continue;
        }
        adj[i].push_back(u);
        adj[i].push_back(v);
        par[u] = i;
        par[v] = i;
    }

    dfs(adj, 1, subtree);
    // print_vector(subtree);

    vector<int> ans(n + 1);

    // for (int i = 1; i <= n; i++)
    // {
    //     int curr = i;
    //     int res = 0;
    //     while (curr != -1)
    //     {
    //         res = (res + subtree[curr]) % MOD;
    //         res = (res + 1) % MOD;
    //         curr = par[curr];
    //     }

    //     res = (res - 1 + MOD) % MOD;

    //     cout << res % MOD << ' ';
    // }

    dfs2(adj, 1, 0, subtree, ans, 0);

    fl(i, n)
    {
        cout << (ans[i + 1]) % MOD << ' ';
    }

    cout << endl;
}


void s5()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    vector<int> par(n + 1);
    par[1] = 0;
    par[0] = -1;

    adj[0].push_back(1);

    vector<int> subtree(n + 1, 0);

    for (int i = 1; i <= n; i++)
    {
        int u, v;
        cin >> u >> v;
        if (u == 0)
        {
            continue;
        }
        adj[i].push_back(u);
        adj[i].push_back(v);
        par[u] = i;
        par[v] = i;
    }

    dfs(adj, 1, subtree);

    vector<int> ans(n + 1);

    dfs2(adj, 1, 0, subtree, ans, 0);

    fl(i, n)
    {
        cout << (ans[i + 1]) % MOD << ' ';
    }

    cout << endl;
}

struct quad
{
    int a, b, c;

    quad() {}

    quad(int a, int b, int c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }

    bool isindepend(quad q1)
    {
        int a2 = q1.a, b2 = q1.b, c2 = q1.c;
        if (this->c == c2)
        {
            return false;
        }

        int d = (this->b - b2) * (this->b - b2);
        d = d - (4 * (this->a - a2) * (this->c - c2));
        return d < 0;
    }
};

int largestset[3005];
int currmaxsetsize;
vector<int> largestsetValues;

void solveset(vector<quad> &v, int pos, vector<int> &ind, int start)
{
    int n = v.size();
    if (pos == n)
    {
        if ((int)ind.size() > currmaxsetsize)
        {
            currmaxsetsize = ind.size();
            largestsetValues = ind;
        }
        return;
    }

    solveset(v, pos + 1, ind, start);
    if (pos == start)
    {
        return;
    }
    bool isind = true;
    for (auto i : ind)
    {
        if (!v[i].isindepend(v[pos]))
        {
            isind = false;
            break;
        }
    }

    if (isind)
    {
        ind.push_back(pos);
        solveset(v, pos + 1, ind, start);
        ind.pop_back();
    }
    return;
}

void s6()
{
    int n;
    cin >> n;

    for (int i = 0; i < 3005; i++)
    {
        largestset[i] = 0;
    }

    vector<quad> v;
    v.reserve(n);

    fl(i, n)
    {
        int a, b, c;
        cin >> a >> b >> c;
        v.emplace_back(a, b, c);
    }

    fl(i, n)
    {
        if (largestset[i] != 0)
        {
            cout << largestset[i] << ' ';
            continue;
        }
        currmaxsetsize = 0;
        largestsetValues.clear();

        vector<int> ind = {i};
        solveset(v, 0, ind, i);

        print_vector(largestsetValues);

        for (auto j : largestsetValues)
        {
            largestset[j] = currmaxsetsize;
        }
        cout << largestset[i] << ' ';
    }

    cout << endl;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // #ifndef ONLINE_JUDGE
    //     if (!freopen("input.txt", "r", stdin))
    //     {
    //         cerr << "Input file error\n";
    //     }
    //     if (!freopen("output.txt", "w", stdout))
    //     {
    //         cerr << "Output file error\n";
    //     }
    // #endif

    // sieve(maxn);
    int t = 1;
    cin >> t;

    while (t--)
    {
        s6();
    }

    khalaas
}