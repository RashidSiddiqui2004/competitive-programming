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
    int n;
    cin >> n;
    if (n % 4 == 0)
    {
        cout << "Bob\n";
    }
    else
    {
        cout << "Alice\n";
    }
}

void s2()
{
    int n, j, k;
    cin >> n >> j >> k;
    vector<int> v(n);
    read_vector(v);
    --j;
    int maxi = *max_element(all(v));

    if (k > 1)
    {
        yes;
    }
    else
    {
        if (v[j] == maxi)
        {
            yes;
        }
        no;
    }
}

void s3()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);
    string ans(n, '0');
    ans[0] = '1';
    ans[n - 1] = '1';
    for (int i = 1; i < n; i++)
    {
        if (v[i] < v[i - 1])
        {
            ans[i] = '1';
        }
        else
        {
            break;
        }
    }
    for (int i = n - 2; i >= 0; i--)
    {
        if (v[i] > v[i + 1])
        {
            ans[i] = '1';
        }
        else
        {
            break;
        }
    }

    cout << ans << endl;
}

void s4()
{
    int k, x;
    cin >> k >> x;

    for (int i = 1; i <= k; i++)
    {
        x = x * 2ll;
    }
    cout << x << endl;
}

void s5()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    if (n == 2)
    {
        vector<int> ans = {1, 2};
        if (v[0] == 1)
        {
            ans = {2, 1};
        }
        print_vector(ans);
        return;
    }

    vector<int> ans(n);

    fl(i, n)
    {
        if (v[i] == n)
        {
            ans[i] = n;
        }
        else
        {
            ans[i] = (n - v[i]);
        }
    }

    print_vector(ans);
}

void s6()
{
    int a, b;
    cin >> a >> b;

    if (a % 2 != 0 and b % 2 != 0)
    {
        cout << (a * 1ll * b) + 1 << endl;
        return;
    }

    if (a % 2)
    {
        if (b % 2 == 0)
        {
            int ans = -1;
            int i = b / 2;

            if (b % i == 0 and (a * i + (b / i)) % 2 == 0)
            {
                ans = max(ans, (a * i + (b / i)));
            }

            cout << ans << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }
    // a even
    else
    {
        if (b % 2 != 0)
        {
            cout << -1 << endl;
        }
        else
        {
            int ans = a + b;
            int i = b / 2;
            if (b % i == 0 and (a * i + (b / i)) % 2 == 0)
            {
                ans = max(ans, (a * i + (b / i)));
            }
            // for (int i = b - 1; i >= 3; i -= 2)
            // {
            //     if (b % i == 0 and (b / i) % 2 == 0)
            //     {
            //         ans = max(ans, (a * i + (b / i)));
            //         break;
            //     }
            // }
            cout << ans << endl;
        }
    }
}

void s7()
{
    int n;
    cin >> n;
    vector<int> ans(n);
    vector<int> b(n);
    vector<int> freq(n + 1, 0);

    fl(i, n)
    {
        int e;
        cin >> e;
        b[i] = e;
        freq[e]++;
    }
    int id = 1;
    vector<vector<int>> t(n + 1);
    fl(i, n)
    {
        if (freq[i + 1] != 0)
        {
            int cnt = freq[i + 1] / (i + 1);
            if (freq[i + 1] % (i + 1) != 0)
            {
                cout << -1 << endl;
                return;
            }
            for (int k = 1; k <= cnt; k++)
            {
                for (int j = 1; j <= (i + 1); j++)
                {
                    t[i + 1].push_back(id);
                }
                ++id;
            }
        }
    }
    fl(i, n)
    {
        ans[i] = t[b[i]].back();
        t[b[i]].pop_back();
    }
    if (ans.size() > n)
    {
        cout << -1 << endl;
        return;
    }
    print_vector(ans);
}

void s8()
{
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    read_vector(v);
    sort(all(v));
    vector<int> freq(n + 1, 0);
    for (auto i : v)
    {
        freq[i]++;
    }
    int mex = 0;
    for (int i = 0; i < n; i++)
    {
        if (v[i] == mex)
        {
            mex++;
        }
    }
    int sum = 0;

    if (freq[0] == n)
    {
        sum = ((k % 2) == 0) ? 0 : n;
        cout << sum << endl;
        return;
    }

    bool haszero = freq[0] == 1;

    if (k == 1)
    {
        for (int i = 0; i < n; i++)
        {
            if (freq[v[i]] == 1)
                sum += min(v[i], mex);
            else
                sum += mex;
        }
        cout << sum << endl;
        return;
    }
    else
    {
        if (haszero)
        {
            int oddsum = 0, evensum = 0;
            for (int i = 0; i < n; i++)
            {
                if (freq[v[i]] == 1)
                {
                    v[i] = min(v[i], mex);
                }
                else
                {
                    v[i] = mex;
                }
                oddsum += v[i];
            }
            vector<int> freq(n + 1, 0);
            for (auto i : v)
            {
                freq[i]++;
            }
            int mex2 = 0;
            for (int i = 0; i < n; i++)
            {
                if (v[i] == mex2)
                {
                    mex2++;
                }
            }
            for (int i = 0; i < n; i++)
            {
                if (freq[v[i]] == 1)
                {
                    v[i] = min(v[i], mex2);
                }
                else
                {
                    v[i] = mex2;
                }
                evensum += v[i];
            }
            sum = (k % 2 == 0) ? evensum : oddsum;
        }
        else
        {
            sum = (k % 2 == 0) ? 0 : n;
        }
    }

    cout << sum << endl;
}

void s9()
{
    int n, m, k, d;
    cin >> n >> m >> k >> d;

    vector<int> a(n);

    fl(j, n)
    {
        vector<int> dp(m);
        multiset<int> mst;
        int e;
        cin >> e;
        dp[0] = 1;
        mst.insert(dp[0]);

        fl(i, m - 2)
        {
            cin >> e;
            int index = i + 1;
            dp[index] = *mst.begin() + e + 1;
            if (index - d - 1 >= 0)
                mst.erase(mst.find(dp[index - d - 1]));
            mst.insert(dp[index]);
        }

        cin >> e;
        dp.back() = 1 + *mst.begin();
        a[j] = dp.back();
    }

    int ans = INT_MAX;

    for (int i = 1; i < n; i++)
    {
        a[i] += a[i - 1];
    }

    for (int i = 0; (i + k - 1) < n; i++)
    {
        ans = min(ans, a[i + k - 1] - (i == 0 ? 0 : a[i - 1]));
    }

    cout << ans << endl;
}

void r1()
{
    int n, m, x, y;
    cin >> n >> m >> x >> y;
    fl(i, n)
    {
        int e;
        cin >> e;
    }
    fl(i, m)
    {
        int e;
        cin >> e;
    }
    cout << n + m << endl;
}
void r2()
{
    int x, n;
    cin >> x >> n;
    int sum = (n % 2 == 0) ? 0 : x;
    cout << sum << endl;
}

void r3()
{
    int n, m;
    cin >> n >> m;

    int ans = m;
    vector<pair<int, int>> vp;

    fl(i, n)
    {
        int a, b;
        cin >> a >> b;
        vp.push_back({a, b});
    }

    int temp = (vp[0].first % 2 == 0) ? 0 : 1;

    if (vp[0].second != temp)
    {
        ans--;
        temp = !temp;
    }

    for (int i = 1; i < n; i++)
    {
        if (vp[i].first % 2 != vp[i - 1].first % 2)
        {
            temp = !temp;
        }
        auto [a, b] = vp[i];
        if (a % 2 == 0)
        {
            if (b != temp)
            {
                ans--;
                temp = !temp;
            }
        }
        else
        {
            if (b != temp)
            {
                ans--;
                temp = !temp;
            }
        }
    }
    cout << ans << endl;
}

void r4()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    int maxodd = -1, evensum = 0;
    vector<int> odds;
    for (auto i : v)
    {
        if (i % 2 == 1)
        {
            maxodd = max(maxodd, i);
            odds.push_back(i);
        }
        else
        {
            evensum += i;
        }
    }

    if (maxodd == -1)
    {
        cout << 0 << endl;
    }
    else
    {
        sort(all(odds));
        int sum = evensum;
        int m = odds.size();

        for (int i = m - 1; i >= m / 2; i--)
        {
            sum += odds[i];
        }
        cout << sum << endl;
    }
}

void r5()
{
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    unordered_map<int, int> fr;

    fl(i, n)
    {
        cin >> v[i];
        ++fr[v[i]];
    }

    for (auto i : fr)
    {
        if (i.second % k != 0)
        {
            cout << 0 << endl;
            return;
        }
    }

    // count of subarray with maximum freq of any element <= p
    // count = freq[nums[i]] / k
    unordered_map<int, int> currfr;
    int ans = 0;
    int l = 0;
    for (int r = 0; r < n; r++)
    {
        currfr[v[r]]++;
        int maxfr = fr[v[r]] / k;

        while (currfr[v[r]] > maxfr)
        {
            currfr[v[l]]--;
            l++;
        }

        ans += (r - l + 1);
    }

    cout << ans << endl;
}

void r6()
{
    int n;
    cin >> n;
    unordered_set<int> st;
    vector<vector<int>> arrays;

    fl(i, n)
    {
        st.insert(i);
        int l;
        cin >> l;
        vector<int> t(l);
        read_vector(t);
        arrays.push_back(t);
    }

    int currlen = 0;
    vector<int> ans;
    while (true)
    {
        if (st.empty())
        {
            break;
        }

        vector<pair<vector<int>, int>> remarrays;

        for (auto i : st)
        {
            int sz = arrays[i].size();
            if (sz <= currlen)
            {
                continue;
            }
            remarrays.push_back({vector<int>(arrays[i].begin() + currlen, arrays[i].end()), i});
        }

        if (remarrays.size() == 0)
        {
            break;
        }

        sort(remarrays.begin(), remarrays.end());
        auto smallest = *remarrays.begin();
        currlen += smallest.first.size();

        for (auto j : smallest.first)
        {
            ans.push_back(j);
        }
        st.erase(smallest.second);
    }

    print_vector(ans);
}

void r7()
{
    int n, x;
    cin >> n >> x;

    vector<ll> v(n);
    read_vector(v);

    ll sum = accumulate(all(v), 0ll);
    ll maxi = *max_element(all(v));

    ll low = maxi, high = sum, mid, ans;

    while (low <= high)
    {
        mid = (low + high) / 2;
        if ((mid * 1ll * x) >= sum)
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    cout << ans << "\n";
}

void r8()
{
    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;

    int votes = 0;

    for (int i = 0; i < n / 3; i++)
    {
        int a11, a12, a21, a22, a31, a32;

        int pt = 3 * i;
        a11 = (a[pt] == 'A') + (b[pt] == 'A') + (a[pt + 1] == 'A');
        a12 = (b[pt + 1] == 'A') + (b[pt + 2] == 'A') + (a[pt + 2] == 'A');

        a21 = (a[pt] == 'A') + (b[pt] == 'A') + (b[pt + 1] == 'A');
        a22 = (a[pt + 1] == 'A') + (a[pt + 2] == 'A') + (b[pt + 2] == 'A');

        a31 = (a[pt] == 'A') + (a[pt + 1] == 'A') + (a[pt + 2] == 'A');
        a32 = (b[pt] == 'A') + (b[pt + 1] == 'A') + (b[pt + 2] == 'A');

        int v1 = (a11 >= 2) + (a12 >= 2);
        int v2 = (a21 >= 2) + (a22 >= 2);
        int v3 = (a31 >= 2) + (a32 >= 2);

        votes += max({v1, v2, v3});
    }

    cout << votes << endl;
}

void interact()
{
    int l = 1, r = 1000000;
    while (l != r)
    {
        int mid = (l + r + 1) / 2;
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

void sol1()
{
    
}

int32_t main()
{
    int t = 1;
    cin >> t;

    while (t--)
    {
        sol1();
    }

    khalaas
}