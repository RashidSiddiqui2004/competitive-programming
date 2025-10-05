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
    string s;
    cin >> s;
    int zeros = 0;
    for (auto i : s)
    {
        if (i == '0')
            zeros++;
    }
    int k = 0;
    for (int i = 0; i < zeros; i++)
    {
        if (s[i] == '1')
            k++;
    }
    cout << k << endl;
}

void s2()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    int fa = 0;
    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
            fa += v[i];
        }
        else
        {
            fa -= v[i];
        }
    }

    int cost = (n % 2 == 0) ? n - 2 : n - 1;

    int ans = cost + fa;

    vector<long long> suff_even(n + 1, LLONG_MIN), suff_odd(n + 1, LLONG_MIN);

    for (int j = n - 1; j >= 0; j--)
    {
        suff_even[j] = suff_even[j + 1];
        suff_odd[j] = suff_odd[j + 1];

        if (j % 2 == 0)
            suff_even[j] = max(suff_even[j], -2LL * v[j] + j);
        else
            suff_odd[j] = max(suff_odd[j], 2LL * v[j] + j);
    }

    for (int i = 0; i < n - 1; i += 2)
    {
        long long left = fa - 2LL * v[i] - i;

        ans = max(ans, left + suff_odd[i + 1]);
    }

    for (int i = 1; i < n - 1; i += 2)
    {
        long long left = fa + 2LL * v[i] - i;

        ans = max(ans, left + suff_even[i + 1]);
    }

    cout << ans << endl;
}

void s3()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    vector<bool> pres(n, 0);
    for (auto i : v)
    {
        pres[i] = 1;
    }

    for (int i = 1; i <= n; i++)
    {
        if (!pres[i])
        {
            int remindex = (i != n) ? i + 1 : i - 1;
            cout << "? " << i << " " << remindex << endl;
            fflush(stdout);
            int q1;
            cin >> q1;

            if (q1 == 0)
            {
                cout << "! A\n";
            }
            else
            {
                cout << "! B\n";
            }
            fflush(stdout);
            return;
        }
    }

    int ind1, ind2;

    for (int i = 1; i <= n; i++)
    {
        if (v[i - 1] == 1)
        {
            ind1 = i;
        }
        if (v[i - 1] == n)
        {
            ind2 = i;
        }
    }
    cout << "? " << ind1 << " " << ind2 << endl;
    fflush(stdout);
    int q1;
    cin >> q1;

    if (q1 >= (n - 1))
    {
        cout << "! B\n";
    }
    else
    {
        cout << "! A\n";
    }

    fflush(stdout);
}

void s4()
{
    int n, m, p, q;
    cin >> n >> m >> p >> q;
    int l = n / p;
    bool remelem = (n % p) != 0;

    if (remelem)
    {
        cout << "YES\n";
    }
    else
    {
        if (l * q == m)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }
}

void s5()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    int f = v[0];
    int l = -abs(f), r = abs(f);
    int count = 0;

    for (int i = 1; i < n; i++)
    {
        if (v[i] >= l and v[i] <= r)
        {
            ++count;
        }
    }

    if (count <= (n / 2))
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }
}

void s6()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    int mini = 0, maxi = 0;
    bool valid = true;

    fl(i, n)
    {
        int l, r;
        cin >> l >> r;
        if (v[i] == -1)
        {
            if ((mini + 1 < l) || (mini > l))
            {
            }
            else
            {
                mini = max(mini, l);
            }
            if (r > maxi)
            {
                v[i] = 1;
                maxi++;
            }
            else
            {
                v[i] = 0;
            }

            if ((l <= mini and mini <= r) || (l <= maxi and maxi <= r))
            {
            }
            else
            {
                valid = false;
            }
        }
        else
        {
            mini += v[i];
            maxi += v[i];
            if ((l <= mini and mini <= r) || (l <= maxi and maxi <= r))
            {
            }
            else
            {
                valid = false;
            }
        }
    }

    if (valid)
        print_vector(v);
    else
    {
        cout << "-1\n";
    }
}

void s7()
{
    int n, m;
    cin >> n >> m;
    vector<int> v(m);
    read_vector(v);
    for (int i = 1; i < m; i++)
    {
        if (v[i] == 1)
        {
            cout << 1 << endl;
            return;
        }
    }
    int maxi = *max_element(v.begin(), v.end());
    int ans = n - maxi + 1;
    cout << ans << endl;
}

void s8()
{
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;

    set<int> black_cells;
    int e;
    fl(i, m)
    {
        cin >> e;
        black_cells.insert(e);
    }

    int prev_pos = 1, ult_pos = 1;
    fl(i, n)
    {
        int next_pos;
        int lb = *black_cells.lower_bound(ult_pos);
        ult_pos = prev_pos;
        prev_pos = next_pos;
    }
}

void r1()
{
    int n, a, b;
    cin >> n >> a >> b;

    if (abs(a - b) % 2 == 0)
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }
}

void r2()
{
    int n;
    cin >> n;

    if (n <= 3)
    {
        cout << 0 << endl;
    }
    else
    {
        int p = n - 3;
        cout << p << endl;
    }
}

void r3()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    if (n % 2 == 0)
    {
        cout << 2 << endl;
        cout << 1 << " " << n << endl;
        cout << 1 << " " << n << endl;
    }
    else
    {
        cout << 4 << endl;
        cout << 1 << " " << n - 1 << endl;
        cout << 1 << " " << n - 1 << endl;
        cout << n - 1 << " " << n << endl;
        cout << n - 1 << " " << n << endl;
    }
}

void r4()
{
    int n, k, a, b;
    cin >> n >> k >> a >> b;

    vector<pair<int, int>> cities(n);

    fl(i, n)
    {
        cin >> cities[i].first >> cities[i].second;
    }

    auto cooda = make_pair(cities[a - 1].first, cities[a - 1].second);
    auto coodb = make_pair(cities[b - 1].first, cities[b - 1].second);

    int mina = LLONG_MAX / 2, minb = LLONG_MAX / 2;

    for (int i = 0; i < k; i++)
    {
        mina = min(mina, a <= k ? 0 : abs(cities[i].first - cooda.first) + abs(cities[i].second - cooda.second));
        minb = min(minb, b <= k ? 0 : abs(cities[i].first - coodb.first) + abs(cities[i].second - coodb.second));
    }

    cout << min(mina + minb, abs(cooda.first - coodb.first) + abs(cooda.second - coodb.second)) << endl;
}

void r5()
{
    int n, m;
    cin >> n >> m;
    int sum = 0;
    fl(i, n)
    {
        int a, b;
        cin >> a >> b;
        if (i == 0)
            continue;
        else
            sum += 2 * (a + b);
    }
    sum += 4 * m;
    cout << sum << endl;
}

void r6()
{
    int n;
    cin >> n;
    vector<string> g(n);
    fl(i, n)
    {
        cin >> g[i];
    }
    vector<int> ans(n);
    iota(all(ans), 0);

    sort(all(ans), [&](int a, int b)
         {
        if(g[a][b]=='1'){
            return a < b;
        }
        return a > b; });

    for (auto i : ans)
    {
        cout << 1 + i << " ";
    }
    cout << endl;
}

void r7()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    int mx = *max_element(v.begin(), v.end());
    vector<char> pres(mx + 1, 0);
    for (int x : v)
        pres[x] = 1;

    long long ans = 1LL * n * (n + 1) / 2;

    for (int x = 1; x <= mx; ++x)
    {
        if (!pres[x])
            continue;

        vector<int> b(n);
        for (int i = 0; i < n; ++i)
            b[i] = (v[i] > x ? 1 : -1);

        // pref[i] = prefix sum (with offset) BEFORE adding b[i]
        int offset = n;
        vector<int> pref(n);
        int cursum = offset;
        for (int i = 0; i < n; ++i)
        {
            pref[i] = cursum;
            cursum += b[i];
        }

        // cnt array for frequencies of prefix sums (index = prefix + offset)
        vector<int> cnt(2 * n + 5, 0);
        int j = 0;
        int sum = offset;
        long long badsubarrayscnt = 0;

        for (int i = 0; i < n; ++i)
        {
            if (v[i] == x)
            {
                // add pref[0..i] into cnt
                while (j <= i)
                {
                    cnt[pref[j]]++;
                    j++;
                }
            }
            // advance sum by b[i] and add how many previous prefixes equal this sum
            sum += b[i];
            badsubarrayscnt += cnt[sum];
        }

        ans -= badsubarrayscnt;
    }

    cout << ans << '\n';
}

void r8()
{
    int n;
    cin >> n;
    vector<int> a(n + 1), num_to_ind(n + 1);
    for (size_t i = 1; i <= n; i++)
    {
        cin >> a[i];
        num_to_ind[a[i]] = i;
    }

    vector<int> p(n + 1), q(n + 1);

    for (size_t i = 1; i <= n; i++)
    {
        int rval = num_to_ind[i];
        q[i] = rval;
    }
    set<int> st;
    for (int i = 1; i <= n; i++)
    {
        st.insert(i);
    }
    for (int i = 1; i <= n; i++)
    {
        int smval = *st.begin();
        int nottake1 = q[i], nottake2 = i;
        if (smval != nottake1 and smval != nottake2)
        {
            q[i] = smval;
            st.erase(smval);
        }
        else
        {
            st.erase(smval);
            q[i] = *st.begin();
            st.erase(q[i]);
            st.insert(smval);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        int rval = num_to_ind[i];
        p[q[i]] = rval;
        if (q[i] == rval)
        {
            cout << "Impossible\n";
            return;
        }
    }
    cout << "Possible\n";
    for (size_t i = 0; i < n; i++)
    {
        cout << p[i + 1] << " ";
    }
    cout << endl;
    for (size_t i = 0; i < n; i++)
    {
        cout << q[i + 1] << " ";
    }
    cout << endl;
}

int r9helper(int n, int k)
{
    if (n <= 1)
    {
        return 0;
    }
    return 1 + r9helper(n - k + 1, k);
}

void r9()
{
    int n, k;
    cin >> n >> k;
    cout << r9helper(n, k) << endl;
}

void r10()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int ones = 0, zerogrps = 0;
    int i = 0;
    while (i < n)
    {
        while (i < n and s[i] == '1')
        {
            ones++;
            i++;
        }
        bool haszero = false;
        while (i < n and s[i] == '0')
        {
            haszero = true;
            i++;
        }
        if (haszero)
            zerogrps++;
    }

    if (ones > zerogrps)
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }
}

void r11()
{
    int n;
    cin >> n;
    int ones = 0, two = 0, thr = 0;
    fl(i, n)
    {
        int e;
        cin >> e;
        if (e == 1)
            ones++;
        else if (e == 2)
            two++;
        else
            thr++;
    }

    int ans = (ones * (ones - 1)) / 2 + (ones * two) + (two * thr);
    cout << ans << endl;
}

void sol1()
{
    int n;
    cin >> n;
    int maxi = ((n - 2) * (n - 1)) / 2;
    int minu = n - 2;
    cout << minu << " " << maxi << endl;
}

void sol2()
{
    int n;
    cin >> n;

    if (n % 2 == 0)
    {
        vector<int> ans(n);
        int val = 1;
        for (int i = (n / 2) - 1; i >= 0; i--)
        {
            ans[i] = val;
            val += 2;
        }
        val = 2;
        for (int i = n - 1; i >= (n / 2); i--)
        {
            ans[i] = val;
            val += 2;
        }
        print_vector(ans);
    }
    else
    {
        vector<int> ans(n);
        for (int i = 0; i < n; i++)
        {
            ans[i] = n - i;
        }
        print_vector(ans);
    }
}

void sol3()
{
    int n, d;
    cin >> n >> d;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, 1});

    if (n == 1)
    {
        cout << 0 << endl;
        return;
    }

    set<int> st;
    st.insert(1);

    while (!pq.empty())
    {
        auto [step, val] = pq.top();
        pq.pop();

        if (step > 50)
            continue;

        int v1 = val * 2ll;
        if (v1 == n)
        {
            cout << step + 1 << endl;
            return;
        }
        if (!st.count(v1) and v1 < n)
        {
            pq.push({step + 1, v1});
            st.insert(v1);
        }
        int v2 = val + d;
        if (v2 == n)
        {
            cout << step + 1 << endl;
            return;
        }
        if (!st.count(v2) and v2 < n)
        {
            pq.push({step + 1, v2});
            st.insert(v2);
        }
    }

    cout << -1 << endl;
}

void sol4()
{
    int n, d;
    cin >> n >> d;
    int b = 0, a;
    int ans = LLONG_MAX;

    if ((n - 1) % d == 0)
    {
        ans = (n - 1) / d;
    }

    while (true)
    {
        int curr = pow(2, b);
        if ((n % curr) == 0)
        {
            int t = n / curr;
            if ((t - 1) % d == 0)
            {
                a = (t - 1) / d;
                ans = min(ans, a + b);
            }
            b++;
        }
        else
        {
            break;
        }
    }

    for (int i = 0; i < 32; i++)
    {
        int v = pow(2, i);
        if (v > n)
            break;
        int t = n - v;
        if (t % d == 0 and t > d)
        {
            ans = min(ans, i + (t / d));
        }
    }

    ans = (ans == LLONG_MAX) ? -1 : ans;

    cout << ans << endl;
}

void sol5()
{
    int n, d;
    cin >> n >> d;
    int ans = LLONG_MAX;

    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            for (int k = 0; k < 32; k++)
            {
                for (int l = 0; l < 100; l++)
                {
                    int val = ((1 << i) + j * d) * (1 << k) + (l * d);
                    if (val == n)
                    {
                        ans = min(ans, i + j + k + l);
                    }
                }
            }
        }
    }

    if (ans == LLONG_MAX)
    {
        ans = -1;
    }

    cout << ans << endl;
}

void s9(){

}

int32_t main()
{
    int t = 1;
    cin >> t;

    while (t--)
    {
        s9();
    }

    return 0;
}