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
    vector<int> v(n + 1);
    fl(i, n)
    {
        cin >> v[i + 1];
    }
    vector<int> prefsum(n + 1);
    prefsum[1] = v[1];

    for (size_t i = 2; i <= n; i++)
    {
        prefsum[i] = v[i] + prefsum[i - 1];
    }

    for (int l = 1; l < n - 1; l++)
    {
        for (int r = l + 1; r < n; r++)
        {
            int sum1 = prefsum[l] % 3;
            int sum2 = (prefsum[r] - prefsum[l]) % 3;
            int sum3 = (prefsum[n] - prefsum[r]) % 3;
            bool allequal = (sum1 == sum2 and sum1 == sum3);
            bool allunequal = (sum1 != sum2 and sum1 != sum3 and sum2 != sum3);
            if (allequal || allunequal)
            {
                cout << l << " " << r << endl;
                return;
            }
        }
    }

    cout << "0 0" << endl;
}

void s2()
{
    int n;
    cin >> n;

    vector<int> ispres(n + 1, 0);
    vector<int> pos(n + 1, -1);

    int minempty = -1, maxempty = -1;
    fl(i, n)
    {
        int e;
        cin >> e;
        ispres[e]++;
        pos[e] = i + 1;
        if (e == 0)
        {
            if (minempty == -1)
            {
                minempty = i + 1;
            }
            maxempty = i + 1;
        }
    }

    int minindex = n + 1, maxindex = 0;

    for (int i = 1; i <= n; i++)
    {
        if (ispres[i] and pos[i] != i)
        {
            minindex = min({minindex, pos[i], i});
            maxindex = max({maxindex, pos[i], i});
        }
        if (!ispres[i])
        {
            if (minempty != i || maxempty != i)
            {
                minindex = min({minindex, i});
                maxindex = max({maxindex, i});
            }
        }
    }
    int maxcost = (maxindex == 0) ? 0 : (maxindex - minindex + (maxindex != minindex));

    cout << maxcost << endl;
}

// use MOD_CC

int dp[100][2];
int a[100], b[100];

int s3helper(int n, int pos, int first)
{
    if (pos == n)
    {
        return 1;
    }

    if (dp[pos][first] != -1)
    {
        return dp[pos][first] % mod_CC;
    }

    int e1 = first == 0 ? a[pos - 1] : b[pos - 1];
    int e2 = first == 0 ? b[pos - 1] : a[pos - 1];

    int ans = 0;

    if (a[pos] >= e1 and b[pos] >= e2)
    {
        ans += s3helper(n, pos + 1, 0) % mod_CC;
    }
    if (a[pos] >= e2 and b[pos] >= e1)
    {
        ans += s3helper(n, pos + 1, 1) % mod_CC;
    }

    return dp[pos][first] = ans % mod_CC;
}

void s3()
{
    memset(dp, -1, sizeof(dp));

    int n;
    cin >> n;

    fl(i, n)
    {
        cin >> a[i];
    }

    fl(i, n)
    {
        cin >> b[i];
    }

    int ans = (s3helper(n, 1, 0) % mod_CC + s3helper(n, 1, 1) % mod_CC) % mod_CC;

    cout << ans << endl;
}

void s4()
{
    int n, y;
    cin >> n >> y;
    vector<int> a(n);

    read_vector(a);

    int A = *max_element(a.begin(), a.end()) + 1;

    vector<long long> cntTags(A, 0), pSum(A, 0);

    for (int v : a)
        cntTags[v]++;

    for (int i = 1; i < A; i++)
    {
        pSum[i] = pSum[i - 1] + cntTags[i];
    }

    int ans = -(long long)1e18;

    if (A == 2)
    {
        cout << n << "\n";
        return;
    }

    for (int x = 2; x < A; x++)
    {
        int res = 0;
        int price = 1;
        for (int l = 0; l < A; l += x, ++price)
        {
            int r = min(A - 1, l + x);
            ll cnt = pSum[r] - pSum[l];
            if (cnt == 0)
                continue;
            res += cnt * price;
            ll extra = cnt - (price < A ? cntTags[price] : 0);
            if (extra > 0)
                res -= y * extra;
        }
        ans = max(ans, res);
    }
    cout << ans << "\n";
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;

    while (t--)
    {
        s4();
    }

    return 0;
}