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

    vector<string> v(n);

    int maxlen = 0;
    fl(i, n)
    {
        string s;
        cin >> s;
        v[i] = s;
        maxlen = max(maxlen, (int)s.size());
    }

    for (auto i : v)
    {
        int len = i.size();
        int diff = maxlen - len;
        string ans = string(diff / 2, '.');
        ans += i;
        ans += string(diff / 2, '.');
        cout << ans << endl;
    }
}

void s2()
{
    int n, k;
    cin >> n >> k;
    ++k;

    map<int, vector<int>> ind;
    vector<int> freq(n + 2, 0ll);

    fl(i, n)
    {
        int e;
        cin >> e;
        ind[e].push_back(i);
        ++freq[e];
    }

    vector<int> ans(n, 0);

    vector<int> pool;

    int globalcnt = 1;
    for (int i = 1; i <= n; i++)
    {
        if (freq[i] == 0)
        {
            continue;
        }
        if (freq[i] < k)
        {
            for (auto j : ind[i])
            {
                ans[j] = globalcnt;
                globalcnt = (globalcnt + 1) % k;
                if (globalcnt == 0)
                    globalcnt = 1;
            }
        }
        else
        {
            int curr = 1;
            for (auto j : ind[i])
            {
                ans[j] = curr;
                curr = (curr + 1) % k;
                if (curr == 0)
                    break;
            }
        }
    }

    print_vector(ans);
}

void s3()
{
    int n;
    cin >> n;
    vector<int> a(n);
    read_vector(a);

    int mx = *max_element(all(a));

    int ans = 0;

    for (auto i : a)
    {
        if (i == mx)
            ++ans;
    }

    cout << ans << endl;
}

void s4()
{
    int n;
    cin >> n;
    vector<int> a(n);
    read_vector(a);

    bool issorted = true;

    for (int i = 0; i < n - 1; i++)
    {
        if (a[i] > a[i + 1])
        {
            issorted = false;
            break;
        }
    }

    int ans = issorted ? n : 1;

    cout << ans << endl;
}

void s5()
{
    int n;
    cin >> n;

    string s;
    cin >> s;

    stack<char> st;

    fl(i, n)
    {
        if (st.empty())
        {
            st.push(s[i]);
        }
        else
        {
            if (st.top() == s[i])
            {
                st.pop();
            }
            else
            {
                st.push(s[i]);
            }
        }
    }

    if (st.empty())
    {
        yes;
    }
    else
    {
        no;
    }
}

void s6()
{
    int n, x, y;
    cin >> n >> x >> y;

    vector<int> v(n);
    read_vector(v);

    vector<int> t;
    for (int i = x; i < y; i++)
    {
        t.push_back(v[i]);
    }

    int mn = *min_element(all(t));
    int i = 0;

    for (; i < n; i++)
    {
        if (t[i] == mn)
        {
            break;
        }
    }

    vector<int> a;
    for (int j = i; j < t.size(); j++)
    {
        a.push_back(t[j]);
    }
    for (int j = 0; j < i; j++)
    {
        a.push_back(t[j]);
    }

    i = x - 1;
    vector<int> later;

    while (i >= 0)
    {
        if (v[i] > mn)
        {
            later.push_back(v[i]);
            --i;
        }
        else
        {
            break;
        }
    }

    // print_vector(a);
    // print_vector(later);

    if (!later.empty())
    {
        for (int j = 0; j <= i; j++)
        {
            cout << v[j] << ' ';
        }
        int m = a.size();
        for (int j = 0; j < m; j++)
        {
            cout << a[j] << ' ';
        }
        m = later.size();
        for (int j = m - 1; j >= 0; j--)
        {
            cout << later[j] << ' ';
        }
        for (int j = y; j < n; j++)
        {
            cout << v[j] << ' ';
        }
    }
    else
    {
        i = y;
        vector<int> before;

        while (i < n)
        {
            if (v[i] < mn)
            {
                before.push_back(v[i]);
                ++i;
            }
            else
            {
                break;
            }
        }

        for (int j = 0; j < x; j++)
        {
            cout << v[j] << ' ';
        }

        int m = before.size();
        for (int j = 0; j < m; j++)
        {
            cout << before[j] << ' ';
        }

        m = a.size();
        for (int j = 0; j < m; j++)
        {
            cout << a[j] << ' ';
        }

        for (int j = i; j < n; j++)
        {
            cout << v[j] << ' ';
        }
    }

    cout << endl;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;

    while (t--)
    {
        s6();
    }

    khalaas
}