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

void sol1()
{
    int n;
    cin >> n;
    vector<string> v(n);
    read_vector(v);

    int x;
    cin >> x;
    string s;
    cin >> s;
    if (v[x - 1] == s)
    {
        cout << "Yes";
    }
    else
    {
        cout << "No";
    }
}

int reverse(int n)
{
    string s = to_string(n);
    reverse(all(s));
    int i = 0, len = s.size();
    while (i < len and s[i] == '0')
    {
        i++;
    }
    int rev = s[i] - '0';
    i++;
    while (i < len)
    {
        rev *= 10;
        rev += (s[i] - '0');
        i++;
    }
    return rev;
}

void s2()
{
    int x, y;
    cin >> x >> y;
    for (int i = 3; i <= 10; i++)
    {
        int temp = reverse(x + y);
        x = y;
        y = temp;
    }
    cout << y << endl;
}

void s3()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> as, bs;

    for (size_t i = 0; i < 2 * n; i++)
    {
        if (s[i] == 'A')
        {
            as.push_back(i);
        }
        else
        {
            bs.push_back(i);
        }
    }

    int oper1 = 0, oper2 = 0;

    int ptr = 0;
    for (auto i : bs)
    {
        oper1 += abs(i - (as[ptr] + 1));
        // cout<<oper1<<" ";
        ptr++;
    }

    ptr = 0;
    for (auto i : as)
    {
        oper2 += abs(i - (bs[ptr] + 1));
        ptr++;
    }

    int ans = min(oper1, oper2);

    cout << ans / 2 << endl;
}

void s4()
{
    int xt, yt, xa, ya;
    cin >> xt >> yt >> xa >> ya;
    int n, m, l;
    cin >> n >> m >> l;

    vector<pair<char, int>> t(m), a(l);
    fl(i, m)
    {
        cin >> t[i].first >> t[i].second;
    }
    fl(i, l)
    {
        cin >> a[i].first >> a[i].second;
    }

    int ans = 0;
    int p1 = 0, p2 = 0;
    while (p1 < m and p2 < l)
    {
        char dir1 = t[p1].first, dir2 = a[p2].first;
        int moves;
        if (t[p1].second == a[p2].second)
        {
            moves = t[p1].second;
            ++p1, ++p2;
        }
        else
        {
            moves = min(t[p1].second, a[p2].second);
            t[p1].second -= moves;
            a[p2].second -= moves;
            if (t[p1].second == 0)
                p1++;
            else
                p2++;
        }
        string comb = "";
        comb += dir1;
        comb += dir2;

        if (xt == xa and yt == ya and dir1 == dir2)
        {
            ans += moves;
            continue;
        }

        if (comb == "UD" || comb == "DU")
        {
            int newxt = xt + ((dir1 == 'D') ? moves : -moves);
            int newxa = xa + ((dir2 == 'D') ? moves : -moves);
            if (yt == ya)
            {
                if (newxt >= xa and newxt <= newxa)
                {
                    ans++;
                }
                else if (newxa >= xt and newxa <= newxt)
                {
                    ans++;
                }
            }
            xt = newxt;
            xa = newxa;
        }
        else if (comb == "LR" || comb == "RL")
        {
            int newyt = yt + ((dir1 == 'R') ? moves : -moves);
            int newya = ya + ((dir2 == 'R') ? moves : -moves);
            if (yt == ya)
            {
                if (newyt >= ya and newyt <= newya)
                {
                    ans++;
                }
                else if (newya >= yt and newya <= newyt)
                {
                    ans++;
                }
            }
            yt = newyt;
            ya = newya;
        }
        else
        {
            int newxt = (dir1 == 'U' || dir1 == 'D') ? (xt + ((dir1 == 'D') ? moves : -moves)) : xt;
            int newyt = (dir1 == 'L' || dir1 == 'R') ? (yt + ((dir1 == 'R') ? moves : -moves)) : yt;

            int newxa = (dir2 == 'U' || dir2 == 'D') ? (xa + ((dir2 == 'D') ? moves : -moves)) : xa;
            int newya = (dir2 == 'L' || dir2 == 'R') ? (ya + ((dir2 == 'R') ? moves : -moves)) : ya;

            if (dir1 == 'L' || dir1 == 'R')
            {
                if (((xt >= xa and xt <= newxa) || (xt >= newxa and xt <= xa)) and
                    ((ya >= yt and ya <= newyt) || (ya >= newyt and ya <= yt)))
                {
                    ans++;
                }
            }
            else
            {
                swap(xt, xa);
                swap(yt, ya);
                swap(newxt, newxa);
                swap(newyt, newya);
                if (((xt >= xa and xt <= newxa) || (xt >= newxa and xt <= xa)) and
                    ((ya >= yt and ya <= newyt) || (ya >= newyt and ya <= yt)))
                {
                    ans++;
                }
                swap(xt, xa);
                swap(yt, ya);
                swap(newxt, newxa);
                swap(newyt, newya);
            }

            xt = newxt;
            yt = newyt;
            xa = newxa;
            ya = newya;
        }
        // cout << xt << " " << yt << " " << xa << " " << ya << endl;
    }
    cout << ans << endl;
}

// linked list question
void s5()
{
    int q;
    cin >> q;
    // next[i]=-1 -> denotes that i is the tail node(last element of the array)
    int next[q + 1];
    next[0] = -1;
    for (int i = 1; i <= q; i++)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int x;
            cin >> x;
            next[i] = next[x];
            next[x] = i;
        }
        else
        {
            int x, y;
            cin >> x >> y;
            int sumx = 0, sumy = 0, cx = x, cy = y;
            while (true)
            {
                if (cx != -1)
                    cx = next[cx];
                sumx += cx;
                if (cy != -1)
                    cy = next[cy];
                sumy += cy;
                if (cx == y)
                {
                    sumx -= y;
                    cout << sumx << endl;
                    next[x] = y;
                    break;
                }
                if (cy == x)
                {
                    sumy -= x;
                    cout << sumy << endl;
                    next[y] = x;
                    break;
                }
            }
        }
    }
}

void s6()
{
    int n, q;
    cin >> n >> q;
    unordered_map<int, int> mp;
    vector<ll> x(n);
    read_vector(x);
    fl(i, n)
    {
        int val = (i + 1) * 1ll * (n - i);
        --val;
        mp[val]++;
        if ((i + 1) < n)
        {
            // because for these points, there is 1 less right end-point
            mp[(i + 1) * 1ll * (n - i - 1)] += (x[i + 1] - x[i] - 1);
        }
    }

    fl(i, q)
    {
        int t;
        cin >> t;
        if (mp.count(t))
            cout << mp[t] << " ";
        else
            cout << 0 << " ";
    }
    cout << endl;
}

void s7()
{
    int n;
    cin >> n;
    vector<int> odds, evens;

    fl(i, n)
    {
        int e;
        cin >> e;
        if (e % 2 == 0)
        {
            evens.push_back(e);
        }
        else
        {
            odds.push_back(e);
        }
    }

    if (odds.empty() || evens.empty())
    {
        cout << 0 << endl;
    }
    else
    {
        int biggest_odd = *max_element(all(odds));
        sort(all(evens));
        int ans = 0;
        for (auto i : evens)
        {
            if (biggest_odd < i)
            {
                biggest_odd += *max_element(all(evens));
                ans++;
            }

            biggest_odd = min(biggest_odd + i, ll(1e9));
            ans++;
        }
        cout << ans << endl;
    }
}

void s8()
{
    int n, m;
    cin >> n >> m;

    vector<int> st;

    const int MAX_VAL = 2 * 1e5 + 2;
    vector<bool> pres;

    fl(i, n)
    {
        int len;
        cin >> len;
        pres = vector<bool>(MAX_VAL, 0);
        fl(j, len)
        {
            int e;
            cin >> e;
            if (e < MAX_VAL)
            {
                pres[e] = 1;
            }
        }
        int found = 0;
        fl(j, MAX_VAL)
        {
            if (!pres[j])
            {
                found++;
                st.push_back(j);
                if (found == 2)
                {
                    break;
                }
            }
        }
    }
    int max_value = *max_element(all(st));

    if (m <= max_value)
    {
        int ans = max_value * 1ll * (m + 1);
        cout << ans << endl;
        return;
    }

    int ans = max_value * 1ll * (max_value + 1);

    int p1 = (m * 1ll * (m + 1)) / 2;
    int p2 = (max_value * 1ll * (max_value + 1)) / 2;

    ans += p1 - p2;

    cout << ans << endl;
}

int dfs(int node, vector<vector<int>> &adj, vector<int> &max_achievable_value)
{
    if (max_achievable_value[node] != -1)
    {
        return max_achievable_value[node];
    }
    int max_value = node;
    for (auto i : adj[node])
    {
        max_value = max(max_value, dfs(i, adj, max_achievable_value));
    }
    return max_achievable_value[node] = max_value;
}

// https://codeforces.com/contest/2003/problem/D2
void sol9()
{
    int n, m;
    cin >> n >> m;

    const int MAX_VAL = 2 * 1e5 + 2;
    vector<vector<int>> adj(MAX_VAL);
    vector<bool> pres;

    int max_first_value = 0;
    fl(i, n)
    {
        int len;
        cin >> len;
        pres = vector<bool>(MAX_VAL, 0);
        fl(j, len)
        {
            int e;
            cin >> e;
            if (e < MAX_VAL)
            {
                pres[e] = 1;
            }
        }
        int found = 0;
        int u, v;
        fl(j, MAX_VAL)
        {
            if (!pres[j])
            {
                found++;
                if (found == 1)
                {
                    u = j;
                }
                if (found == 2)
                {
                    v = j;
                    break;
                }
            }
        }
        adj[u].push_back(v);
        max_first_value = max(max_first_value, u);
    }

    vector<int> max_achievable_value(MAX_VAL, -1);

    fl(i, max_first_value + 1)
    {
        if (max_achievable_value[i] == -1)
        {
            dfs(i, adj, max_achievable_value);
        }
    }

    int max_value = *max_element(all(max_achievable_value));

    if (m <= max_first_value)
    {
        int ans = 0;
        fl(i, m + 1)
        {
            ans += max_achievable_value[i];
        }
        cout << ans << endl;
        return;
    }

    int ans = 0;
    fl(i, max_first_value + 1)
    {
        ans += max_achievable_value[i];
    }

    cout << ans << " ";

    int p1 = (m * 1ll * (m + 1)) / 2;
    int p2 = (max_first_value * 1ll * (max_first_value + 1)) / 2;

    ans += p1 - p2;

    cout << ans << endl;
}

void s10()
{
    int n;
    cin >> n;
    map<int, int> freq;
    fl(i, n)
    {
        int e;
        cin >> e;
        freq[e]++;
    }
    for (auto i : freq)
    {
        if (i.first == 0)
        {
            continue;
        }
        else
        {
            if (i.second > freq[i.first - 1])
            {
                no;
            }
        }
    }
    yes;
}

void s11()
{
    int n, k, g;
    cin >> n >> k >> g;

    int total = 1ll * k * g;

    int p = min(total, (n - 1) * 1ll * ((g / 2) - 1));
    int x = total - p;
    int r = x % g;
    int amountpaid;

    if (r >= ((g + 1) / 2))
    {
        amountpaid = x + g - r;
    }
    else
    {
        amountpaid = x - r;
    }

    cout << (total - amountpaid) << endl;
}

void s12()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    // check if cons k 1s are there
    int i = 0;
    while (i < n)
    {
        while (i < n and s[i] == '0')
            i++;
        int len = 0;
        while (i < n and s[i] == '1')
        {
            len++;
            i++;
        }
        if (len >= k)
        {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";

    vector<int> ans(n);
    int nextelem = 1;

    for (int i = 0; i < n; i++)
    {
        if (s[i] == '1')
        {
            ans[i] = nextelem++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (s[i] == '0')
        {
            ans[i] = nextelem++;
        }
    }

    print_vector(ans);
}

const int MAXN = 200005;
int dp[MAXN], nextJump[MAXN];

int maxlenneatSubs(int n, vector<int> &v, unordered_map<int, vector<int>> &positions)
{

    for (int i = 0; i < n; i++)
    {
        auto &indices = positions[v[i]];
        auto itr = lower_bound(indices.begin(), indices.end(), i) - indices.begin();
        int rem = (int)indices.size() - itr;
        if (rem >= v[i])
        {
            nextJump[i] = indices[itr + v[i] - 1] + 1;
        }
        else
        {
            nextJump[i] = -1;
        }
    }

    // Bottom-up DP
    dp[n] = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        dp[i] = dp[i + 1];
        if (nextJump[i] != -1)
        {
            dp[i] = max(dp[i], v[i] + dp[nextJump[i]]);
        }
    }
    return dp[0];
}

void s13()
{
    int n;
    cin >> n;
    vector<int> v(n);
    unordered_map<int, vector<int>> positions;

    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
        positions[v[i]].push_back(i);
    }

    cout << maxlenneatSubs(n, v, positions) << "\n";
}

void s14()
{
    int n;
    cin >> n;
    vector<int> v(n + 1);
    for (size_t i = 1; i <= n; i++)
    {
        cin >> v[i];
    }

    vector<bool> dp(n + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= n; i++)
    {
        if ((i + v[i] <= n) and dp[i - 1])
            dp[i + v[i]] = 1;
        if ((i - v[i] - 1 >= 0) and dp[i - v[i] - 1])
            dp[i] = 1;
    }

    if (dp[n])
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }
}

void r1()
{
    int n;
    cin >> n;

    vector<vector<int>> v(n, vector<int>(4));
    fl(i, n)
    {
        cin >> v[i][0] >> v[i][1] >> v[i][2];
        v[i][3] = i;
    }
    sort(v.begin(), v.end(), [](vector<int> &v1, vector<int> &v2)
         { return v1[0] < v2[0]; });
    int color, lastx = INT_MIN, ultlastx = INT_MIN;
    // traverse forwards
    lastx = v[0][1];
    color = v[0][2];
    vector<int> ans(n, INT_MAX);
    for (int i = 1; i < n; i++)
    {
        if (v[i][2] != color)
        {
            ans[v[i][3]] = max(0ll, lastx - v[i][0]);
            ultlastx = lastx;
            lastx = v[i][1];
            color = v[i][2];
        }
        else
        {
            if (ultlastx != INT_MIN)
                ans[v[i][3]] = max(0ll, ultlastx - v[i][0]);
            lastx = v[i][1];
        }
    }
    // traverse backwards
    ultlastx = INT_MIN;
    lastx = v[n - 1][0];
    color = v[n - 1][2];
    for (int i = n - 2; i >= 0; i--)
    {
        if (v[i][2] != color)
        {
            ans[v[i][3]] = min(ans[v[i][3]], max(0ll, lastx - v[i][1]));
            ultlastx = lastx;
            lastx = v[i][0];
            color = v[i][2];
        }
        else
        {
            if (ultlastx != INT_MIN)
                ans[v[i][3]] = min(ans[v[i][3]], max(0ll, ultlastx - v[i][1]));
            lastx = v[i][0];
        }
    }

    print_vector(ans);
}

bool isposs(vector<int> fr, int k, int mid)
{
    int i = 0;
    int n = fr.size();
    // all chars in pair
    int oddelem = 0;
    for (int i = 0; i < n; i++)
    {
        if (fr[i] % 2)
        {
            oddelem++;
        }
        fr[i] /= 2;
    }
    if ((mid % 2) == 0)
    {
        while (i < n)
        {
            int req = mid / 2;
            while (req > 0 and i < n)
            {
                if (fr[i] >= req)
                {
                    fr[i] -= req;
                    req = 0;
                    k--;
                }
                else
                {
                    req -= fr[i];
                    fr[i] = 0;
                    ++i;
                }
            }
            if (k == 0)
                break;
        }

        return k == 0;
    }

    i = 0;
    int origk = k;
    // 1 element will occur without pair
    while (i < n)
    {
        int req = (mid - 1) / 2;
        while (req > 0 and i < n)
        {
            if (fr[i] >= req)
            {
                fr[i] -= req;
                req = 0;
                k--;
            }
            else
            {
                req -= fr[i];
                fr[i] = 0;
                ++i;
            }
        }
        if (k == 0)
            break;
    }
    int cntrem = oddelem + (2 * accumulate(fr.begin(), fr.end(), 0));
    return k == 0 and cntrem >= origk;
}

void r2()
{
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    vector<int> freq(26, 0);
    for (auto &ch : s)
    {
        freq[ch - 'a']++;
    }
    int low = 1, high = n, ans, mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (mid == 1 ? 1 : isposs(freq, k, mid))
        {
            ans = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    cout << ans << endl;
}

struct digitnode
{
    int stringpos;
    int l;

    digitnode() : stringpos(-1), l(-1) {}
    digitnode(int pos, int l) : stringpos(pos), l(l) {}
};

void r3()
{
    int n, m;
    cin >> n >> m;

    vector<vector<digitnode>> adj(10, vector<digitnode>(10));

    fl(i, n)
    {
        string s;
        cin >> s;
        for (int j = 0; j < m - 1; j++)
        {
            adj[s[j] - '0'][s[j + 1] - '0'] = digitnode(i + 1, j + 1);
        }
    }

    string friendnum;
    cin >> friendnum;

    vector<pair<int, int>> ans;

    if (m % 2 == 0)
    {
        for (int i = 0; i < m - 1; i += 2)
        {
            int curr = friendnum[i] - '0', nextchar = friendnum[i + 1] - '0';
            if (adj[curr][nextchar].stringpos == -1)
            {
                cout << -1 << endl;
                return;
            }
            else
            {
                ans.push_back({adj[curr][nextchar].l, adj[curr][nextchar].stringpos});
            }
        }

        cout << ans.size() << endl;
        for (auto i : ans)
        {
            cout << i.first << " " << i.first + 1 << " " << i.second << endl;
        }
    }
    else
    {
        cout << "Can't handle odd length phone numbers\n";
    }
}

void r4()
{
    int n, m;
    cin >> n >> m;

    vector<vector<vector<int>>> bitwiseedges(31);

    fl(i, m)
    {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        fl(j, 31)
        {
            if ((w & (1 << j)) != 0)
            {
                bitwiseedges[j].push_back({u, v, w});
            }
        }
    }

    int mask = (1 << 31) - 1;

    for (int i = 30; i >= 0; i--)
    {
        DSU dsu = DSU(n);
        int edgecnt = 0;

        for (int j = 0; j <= 30; j++)
        {
            if ((i != j) and (mask & (1 << j)) != 0)
            {
                for (auto t : bitwiseedges[j])
                {
                    if ((t[2] & (1 << i)) == 0 and dsu.getParent(t[0]) != dsu.getParent(t[1]))
                    {
                        edgecnt++;
                        dsu.unionSets(t[0], t[1]);
                    }
                    if (edgecnt == (n - 1))
                    {
                        break;
                    }
                }
            }
        }

        bool canbeunset = true;
        int par = dsu.getParent(0);
        for (int j = 1; j < n; j++)
        {
            if (dsu.getParent(j) != par)
            {
                canbeunset = false;
                break;
            }
        }
        if (canbeunset)
        {
            mask ^= (1 << i);
        }
    }

    cout << mask << endl;
}

void r5()
{
    int n;
    cin >> n;

    vector<int> v(n);
    read_vector(v);

    int val = -1, val2 = -1;
    fl(i, n)
    {
        for (size_t j = i + 1; j < n; j++)
        {
            if (v[i] > v[j])
            {
                val = v[i];
                val2 = v[j];
                break;
            }
        }
        if (val != -1)
            break;
    }

    if (val == -1)
        cout << "NO\n";
    else
    {
        cout << "YES\n";
        cout << 2 << endl;
        cout << val << " " << val2 << endl;
    }
}

void r6()
{
    int n;
    cin >> n;

    vector<int> v(n);
    read_vector(v);

    int mini = INT_MAX, minpos = -1;
    int sumofprefmin = 0;
    for (int i = 0; i < n; i++)
    {
        if (v[i] == 0)
            break;
        if (v[i] < mini)
        {
            mini = v[i];
            minpos = i;
        }
    }
    int currmini = INT_MAX;
    for (int i = 0; i <= minpos; i++)
    {
        currmini = min(currmini, v[i]);
        sumofprefmin += currmini;
    }
    if ((minpos + 1 < n) and v[minpos + 1] != 0)
        sumofprefmin += currmini;
    cout << sumofprefmin << endl;
}

void r7()
{
    int n;
    cin >> n;

    vector<int> v(n);
    read_vector(v);

    int prevk = -1;
    for (int i = 0; i < n - 1; i++)
    {
        if (v[i + 1] < v[i])
        {
            int mult = (v[i] + v[i + 1] - 1) / v[i + 1];
            if (prevk == -1 || (mult % prevk != 0))
            {
                v[i + 1] = mult * v[i];
                prevk = mult;
            }
            else 
            {

            }
        }
    }
    if (prevk == -1)
        prevk = 1;
    cout << prevk << endl;
}

int32_t main()
{
    int t = 1;
    cin >> t;

    while (t--)
    {
        r7();
    }

    return 0;
}