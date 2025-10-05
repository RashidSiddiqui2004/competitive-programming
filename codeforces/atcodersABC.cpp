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

vector<int> sieve(int n)
{
    primes.clear();
    isPrime.assign(n + 1, true);
    isPrime[0] = false;
    isPrime[1] = false;
    for (int i = 2; i <= n; i++)
    {
        if (isPrime[i])
        {
            primes.pb(i);
            for (int j = i * 2; j <= n; j += i)
            {
                isPrime[j] = false;
            }
        }
    }
    return primes;
}

const int maxn = 1e6 + 1;
vector<int> spf;

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
    string x, y;
    cin >> x >> y;
    unordered_map<string, int> mp;
    mp["Ocelot"] = 1;
    mp["Serval"] = 2;
    mp["Lynx"] = 3;
    int x1 = mp[x], y1 = mp[y];
    if (x1 >= y1)
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
}

void s2()
{
    string s;
    cin >> s;
    vector<int> mp(26, 0);
    for (auto i : s)
    {
        mp[i - 'a']++;
    }
    for (int i = 0; i < 26; i++)
    {
        if (mp[i] == 1)
        {
            char ans = ('a' + i);
            cout << ans << endl;
            return;
        }
    }
}

void s3()
{
    int n, q;
    cin >> n >> q;

    int high = 0;
    vector<int> v(n + 1, 1);
    v[0] = 0;

    fl(i, q)
    {
        int x, y;
        cin >> x >> y;
        int rem = 0;
        if (x <= high)
        {
            rem = 0;
        }
        else
        {
            for (int j = high + 1; j <= x; j++)
            {
                rem += v[j];
            }
        }
        high = max(high, x);
        v[y] += rem;
        cout << rem << endl;
    }
}

void s4()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int ans1 = 0, ans2 = 0;

    {
        // all 0s
        int p1 = 0, p2 = n - 1;
        while (p1 < n and s[p1] == '1')
        {
            p1++;
            ans1++;
        }

        while (p2 > p1 and s[p2] == '1')
        {
            p2--;
            ans1++;
        }

        vector<int> ones;

        for (int i = p1; i <= p2; i++)
        {
            if (s[i] == '1')
                ones.push_back(i + 1);
        }

        int rem = INT_MAX;

        int m = ones.size();
        for (int i = 0; i <= m; i++)
        {
            int prevones = i;
            int nextones = m - i;
            int t1 = i == 0 ? 0 : (ones[i - 1] - p1) * 2;
            int t2 = i == m ? 0 : (p2 - ones[i] + 2) * 2;
            rem = min(rem, (t1 - prevones) + (t2 - nextones));
        }

        if (rem != INT_MAX)
            ans1 += rem;
    }

    {
        int p1 = 0, p2 = n - 1;
        while (p1 < n and s[p1] == '0')
        {
            p1++;
            ans2++;
        }

        while (p2 > p1 and s[p2] == '0')
        {
            p2--;
            ans2++;
        }

        vector<int> ones;

        for (int i = p1; i <= p2; i++)
        {
            if (s[i] == '0')
                ones.push_back(i + 1);
        }

        int rem = INT_MAX;

        int m = ones.size();
        for (int i = 0; i <= m; i++)
        {
            // cout<<ones[i]<<" ";
            int prevones = i;
            int nextones = m - i;
            int t1 = i == 0 ? 0 : (ones[i - 1] - p1) * 2;
            int t2 = i == m ? 0 : (p2 - ones[i] + 2) * 2;
            rem = min(rem, (t1 - prevones) + (t2 - nextones));
            // cout<<rem<<" ";
        }
        if (rem != INT_MAX)
            ans2 += rem;
    }

    cout << min(ans1, ans2) << endl;
}

struct Node
{
    long long sum, minv;
};

struct SegmentTree
{
    int n;
    vector<Node> tree;
    vector<long long> lazy;

    SegmentTree(vector<long long> &arr)
    {
        n = arr.size();
        tree.resize(4 * n);
        lazy.assign(4 * n, 0);
        build(1, 0, n - 1, arr);
    }

    void build(int node, int start, int end, vector<long long> &arr)
    {
        if (start == end)
        {
            tree[node] = {arr[start], arr[start]};
            return;
        }
        int mid = (start + end) / 2;
        build(2 * node, start, mid, arr);
        build(2 * node + 1, mid + 1, end, arr);
        pull(node);
    }

    void pull(int node)
    {
        tree[node].sum = tree[2 * node].sum + tree[2 * node + 1].sum;
        tree[node].minv = min(tree[2 * node].minv, tree[2 * node + 1].minv);
    }

    void push(int node, int start, int end)
    {
        if (lazy[node] != 0)
        {
            long long val = lazy[node];
            tree[node].sum -= val * (end - start + 1);
            tree[node].minv -= val;
            if (start != end)
            {
                lazy[2 * node] += val;
                lazy[2 * node + 1] += val;
            }
            lazy[node] = 0;
        }
    }

    long long query(int l, int r, int k)
    {
        return query(1, 0, n - 1, l, r, k);
    }

    long long query(int node, int start, int end, int l, int r, int k)
    {
        push(node, start, end);
        if (start > r || end < l)
            return 0;

        if (l <= start && end <= r)
        {
            if (tree[node].minv >= k)
            {
                ll ans = k * (end - start + 1);
                lazy[node] += k;
                push(node, start, end);
                return ans;
            }
            if (tree[node].minv == 0 && tree[node].sum == 0)
                return 0;
        }

        if (start == end)
        {
            long long take = min(tree[node].sum, 1ll * k);
            tree[node].sum -= take;
            tree[node].minv = tree[node].sum;
            return take;
        }

        int mid = (start + end) / 2;
        ll l1 = query(2 * node, start, mid, l, r, k);
        ll r1 = query(2 * node + 1, mid + 1, end, l, r, k);
        pull(node);
        return l1 + r1;
    }
};

void s5()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);
    int q;
    cin >> q;

    SegmentTree st(v);

    fl(i, q)
    {
        int l, r, k;
        cin >> l >> r >> k;
        --l, --r;
        cout << st.query(l, r, k) << endl;
    }
}

int32_t main()
{
    int t = 1;
    // cin >> t;

    while (t--)
    {
        s5();
    }

    return 0;
}