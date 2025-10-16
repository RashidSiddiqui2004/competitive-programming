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
    int l = 1, r = 1000000;
    while (l != r)
    {
        int mid = l + ((r - l) / 2);
        printf("%d\n", mid);
        fflush(stdout);

        char response[3];
        scanf("%s", response);
        if (strcmp(response, "<") == 0)
            r = mid - 1;
        else
            l = mid;
    }

    printf("! %d\n", l);
    fflush(stdout);
}

void s2()
{
    int n, m;
    cin >> n >> m;

    vector<string> v(n);
    vector<vector<int>> freq(m, vector<int>(26, 0));

    fl(i, n)
    {
        cin >> v[i];
        fl(j, m)
        {
            freq[j][v[i][j] - 'a']++;
        }
    }

    fl(i, n - 1)
    {
        string s;
        cin >> s;
        fl(j, m)
        {
            freq[j][s[j] - 'a']--;
        }
    }

    for (auto &s : v)
    {
        bool check = true;
        fl(j, m)
        {
            if (freq[j][s[j] - 'a'] == 0)
            {
                check = false;
                break;
            }
        }
        if (check)
        {
            cout << s << endl;
            fflush(stdout);
            return;
        }
    }
}

void s3()
{
    int n;
    cin >> n;

    int maxlen = 0;
    int startingPoint = -1;
    // N queries -> maximum path length
    unordered_map<int, vector<int>> maxpath_map;

    for (int i = 1; i <= n; i++)
    {
        cout << "? " << i << " " << n << " ";
        fflush(stdout);
        for (int j = 1; j <= n; j++)
        {
            cout << j << " ";
            fflush(stdout);
        }
        cout << endl;
        fflush(stdout);
        int currmaxlen;
        cin >> currmaxlen;
        maxpath_map[currmaxlen].push_back(i);
        if (currmaxlen > maxlen)
        {
            maxlen = currmaxlen;
            startingPoint = i;
        }
    }

    int pathlen = maxlen - 1;
    vector<int> ans = {startingPoint};

    while (pathlen > 0)
    {
        int lastnode = ans.back();
        for (auto node : maxpath_map[pathlen])
        {
            cout << "? " << lastnode << " " << 2 << " ";
            fflush(stdout);
            cout << lastnode << " " << node << endl;
            fflush(stdout);

            int len;
            cin >> len;
            if (len == 2)
            {
                ans.push_back(node);
                break;
            }
        }

        pathlen--;
    }

    cout << "! " << maxlen << " ";
    fflush(stdout);
    for (auto i : ans)
    {
        cout << i << " ";
        fflush(stdout);
    }
    cout << endl;
    fflush(stdout);
}

void s4()
{
    int n;
    cin >> n;

    vector<int> v(n + 1);
    int s1, s2, s3;
    cout << "? 1 2" << endl;
    fflush(stdout);
    cin >> s1;
    cout << "? 2 3" << endl;
    fflush(stdout);
    cin >> s2;
    cout << "? 1 3" << endl;
    fflush(stdout);
    cin >> s3;

    v[2] = (s1 + s2 - s3) / 2;
    v[1] = s1 - v[2];
    v[3] = s2 - v[2];

    for (int i = 4; i <= n; i++)
    {
        cout << "? 1 " << i << endl;
        fflush(stdout);
        int sum;
        cin >> sum;
        v[i] = sum - v[1];
    }

    cout << "! " << endl;
    fflush(stdout);

    for (int i = 1; i <= n; i++)
    {
        cout << v[i] << " ";
        fflush(stdout);
    }

    cout << endl;
    fflush(stdout);
}

void s5()
{
    int n;
    cin >> n;

    vector<int> v(n + 1);
    int s1, s2, s3;
    cout << "? 1 2" << endl;
    fflush(stdout);
    cin >> s1;
    cout << "? 2 3" << endl;
    fflush(stdout);
    cin >> s2;
    cout << "? 1 3" << endl;
    fflush(stdout);
    cin >> s3;

    v[2] = (s1 + s2 - s3);
    v[1] = s1 - v[2];
    v[3] = s2 - v[2];

    int prevsum = v[1] + v[2] + v[3];
    for (int i = 4; i <= n; i++)
    {
        cout << "? 1 " << i << endl;
        fflush(stdout);
        int sum;
        cin >> sum;
        v[i] = sum - prevsum;
        prevsum += v[i];
    }

    cout << "! " << endl;
    fflush(stdout);

    for (int i = 1; i <= n; i++)
    {
        cout << v[i] << " ";
        fflush(stdout);
    }

    cout << endl;
    fflush(stdout);
}

int query(const vector<int> &s)
{
    cout << "? " << s.size() << " ";
    for (int i : s)
        cout << i << " ";
    cout << endl;
    fflush(stdout);
    int q;
    cin >> q;
    return q;
}

void s6()
{
    int n;
    cin >> n;
    int m = 2 * n;
    vector<int> ans(m + 1, 0), s, t;

    for (int i = 1; i <= m; i++)
    {
        s.push_back(i);
        int q = query(s);
        if (q != 0)
        {
            ans[i] = q;
            s.pop_back();
            t.push_back(i);
        }
    }

    for (auto i : s)
    {
        t.push_back(i);
        int q = query(t);
        ans[i] = q;
        t.pop_back();
    }

    cout << "! ";

    for (int i = 1; i <= m; i++)
    {
        cout << ans[i] << " ";
    }

    cout << endl;
    fflush(stdout);
}

void s7()
{
    int low = 2, high = 999, mid, ans;
    while (low <= high)
    {
        mid = (low + high) / 2;
        cout << "? " << mid << " " << mid << endl;
        int area;
        cin >> area;
        int side = sqrt(area);
        if (side == mid)
        {
            low = mid + 1;
        }
        else
        {
            ans = mid;
            high = mid - 1;
        }
        fflush(stdout);
    }
    cout << "! " << ans << endl;
    fflush(stdout);
}

void s8()
{
    int low = 2, high = 999, ans;
    while (low <= high)
    {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        cout << "? " << mid1 << " " << mid2 << endl;
        fflush(stdout);
        int area;
        cin >> area;

        if (area == ((mid1 + 1) * (mid2 + 1)))
        {
            ans = mid1;
            high = mid1 - 1;
        }
        else if (area == (mid1 * (mid2 + 1)))
        {
            ans = mid2;
            low = mid1 + 1;
            high = mid2 - 1;
        }
        else
        {
            low = mid2 + 1;
        }
    }
    cout << "! " << ans << endl;
    fflush(stdout);
}

void s9()
{
    int n, k;
    cin >> n >> k;
    int ones = 0;
    fl(i, n)
    {
        int e;
        cin >> e;
        if (e)
            ++ones;
    }
    int reqones = (k + 1) / 2;
    if (ones < reqones)
    {
        cout << 0 << endl;
        return;
    }
    int totalzeros = n - ones;

    int ans = 0;

    for (int i = reqones; i <= ones; i++)
    {
        int currzeros = k - i;
        ans = mod_add(ans, mod_mul(ncr(ones, i), ncr(totalzeros, currzeros))) % MOD;
    }

    cout << ans << endl;
}

void r1()
{
    int n;
    cin >> n;
    assert(n != -1);

    int low = 1, high = n;
    while (low < high)
    {
        int mid = (low + high) / 2;
        cout << "? " << low << " " << mid << endl;
        fflush(stdout);

        int x, count = 0;
        for (int i = 0; i < mid - low + 1; i++)
        {
            cin >> x;
            assert(x != -1);
            if (low <= x && x <= mid)
                count++;
        }

        if (count % 2 == 0)
            low = mid + 1;
        else
            high = mid;
    }

    cout << "! " << low << endl;
    fflush(stdout);
}

void r2()
{
    // find an index i such that a[i-1] < a[i] < a[i+1]
    // {inf, perm[1, n], inf}
    // {inf, x, x-1, .....}

    int n;
    cin >> n;
    int l = 1, r = n, mid, ans;

    while (l < r)
    {
        mid = (l + r) / 2;
        if ((mid + 1 > n) || (mid < 1))
            break;

        cout << "? " << mid << endl;
        fflush(stdout);
        int a, b;
        cin >> a;
        cout << "? " << mid + 1 << endl;
        fflush(stdout);
        cin >> b;
        if (a < b)
        {
            r = mid;
        }
        else
        {
            l = mid + 1;
        }
    }
    cout << "! " << l << endl;
    fflush(stdout);
}

int32_t main()
{
    // precompute_factorials(maxn);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;

    while (t--)
    {
        r2();
    }

    khalaas
}