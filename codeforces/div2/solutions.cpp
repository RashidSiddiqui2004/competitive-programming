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
    int n, y, r;
    cin >> n >> y >> r;

    int ans = (y / 2) + r;
    ans = min(n, ans);

    cout << ans << endl;
}

void s2()
{
    int n;
    cin >> n;

    map<int, int> freq;
    fl(i, 2 * n)
    {
        int e;
        cin >> e;
        ++freq[e];
    }

    int ans = 0;
    int oddCnt = 0;
    int cnt4 = 0;

    for (auto &p : freq)
    {
        int f = p.second;

        if (f % 2 == 1)
        {
            ans += 1;
            oddCnt++;
        }
        else
        {
            if ((f / 2) % 2 == 1)
            {
                ans += 2;
            }
            else
            {
                cnt4++;
            }
        }
    }

    if (cnt4 % 2 == 0)
    {
        ans += 2 * cnt4;
    }
    else
    {
        if (oddCnt > 0)
        {
            ans += 2 * cnt4;
        }
        else
        {
            ans += 2 * (cnt4 - 1);
        }
    }

    cout << ans << endl;
}

void fool1()
{
    int n;
    cin >> n;

    vector<int> v = {1200, 1400, 1600, 1900, 2100, 2300, 2400, 2600, 3000};
    for (auto i : v)
    {
        if (i > n)
        {
            cout << i;
            return;
        }
    }
}

void fool2()
{
    string s;
    cin >> s;

    int n = s.size();

    if (n == 4)
    {
        cout << "none" << endl;
    }
    else
    {
        map<int, string> mp;
        mp[3] = "the";
        mp[5] = "buffy";
        mp[6] = "slayer";
        mp[7] = "vampire";

        string a = mp[n];

        string ans = "";

        fl(i, n)
        {
            int ind1 = s[i] - 'a', ind2 = a[i] - 'a';
            char ch = 'a' + ((ind1 + ind2) % 26);
            ans += ch;
        }

        cout << ans << endl;
    }
}

void fool3()
{
    cout << "security";
}

void fool4(int n)
{
    int ans = 1;
    int e;
    fl(i, n)
    {
        cin >> e;
        ans *= e;
    }
    cout << ans << endl;
}

using uint32 = unsigned int;

struct MT19937Clone
{
    static const int N = 624;
    static const int M = 397;
    uint32 state[N];
    int index = N;

    // Untemper helpers
    uint32 unshiftRight(uint32 y, int shift)
    {
        uint32 res = 0;
        for (int i = 0; i < 32; i++)
        {
            uint32 bit = (y >> i) & 1;
            if (i >= shift)
                bit ^= (res >> (i - shift)) & 1;
            res |= (bit << i);
        }
        return res;
    }

    uint32 unshiftLeft(uint32 y, int shift, uint32 mask)
    {
        uint32 res = 0;
        for (int i = 31; i >= 0; i--)
        {
            uint32 bit = (y >> i) & 1;
            if (i + shift < 32)
                bit ^= ((res >> (i + shift)) & 1) & ((mask >> i) & 1);
            res |= (bit << i);
        }
        return res;
    }

    uint32 untemper(uint32 y)
    {
        y = unshiftRight(y, 18);
        y = unshiftLeft(y, 15, 0xefc60000);
        y = unshiftLeft(y, 7, 0x9d2c5680);
        y = unshiftRight(y, 11);
        return y;
    }

    void seedFromOutputs(const vector<uint32> &outputs)
    {
        for (int i = 0; i < N; i++)
        {
            state[i] = untemper(outputs[i]);
        }
        index = N;
    }

    void twist()
    {
        for (int i = 0; i < N; i++)
        {
            uint32 x = (state[i] & 0x80000000) | (state[(i + 1) % N] & 0x7fffffff);
            uint32 xA = x >> 1;
            if (x & 1)
                xA ^= 0x9908b0df;
            state[i] = state[(i + M) % N] ^ xA;
        }
        index = 0;
    }

    uint32 extract()
    {
        if (index >= N)
            twist();

        uint32 y = state[index++];

        y ^= (y >> 11);
        y ^= (y << 7) & 0x9d2c5680;
        y ^= (y << 15) & 0xefc60000;
        y ^= (y >> 18);

        return y;
    }
};

int query(int l, int r)
{
    cout << "? " << l << ' ' << r << "\n";
    fflush(stdout);
    int ans;
    cin >> ans;
    return ans;
}

void result(int ans)
{
    cout << "! " << ans << "\n";
    fflush(stdout);
}

void fool5()
{
    int n;
    cin >> n;

    vector<uint32> v(n);
    
    int M = min(624ll, n);
    for (int i = 1; i <= M; i++)
    {
        v[i - 1] = query(i, i);
    }

    if (n <= 624)
    {
        int ans = *min_element(all(v));
        result(ans);
        return;
    }

    MT19937Clone mt;
    mt.seedFromOutputs(v);

    for (int i = 625; i <= n; i++)
    {
        v[i-1] = mt.extract();
    }

    int ans = *min_element(all(v));
    result(ans);
}

int32_t main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int t = 1;
    // cin >> t;

    while (t--)
    {
        fool5();
    }

    // string pi = "3141592653589793238462643383279502884197";
    // for (int i = 0; i < t; i++)
    // {
    //     fool4(pi[i]-'0');
    // }

    khalaas
}