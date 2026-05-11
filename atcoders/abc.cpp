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

int cnt(string &s)
{
    int n = s.size(), i = 0;
    int ans = 0;

    while (i < n)
    {
        char curr = s[i++];
        while (i < n && s[i] == curr)
        {
            ++i;
        }
        ++ans;
    }

    return ans;
}

void s2()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int ans = cnt(s);

    for (int i = 1; i < n; i++)
    {
        string temp = s.substr(n - i);
        temp += s.substr(0, n - i);
        ans = max(ans, cnt(temp));
    }

    cout << ans << endl;
}

void s3()
{
    int n;
    cin >> n;

    string s;
    cin >> s;

    int cnt1s = 0;
    fl(i, n)
    {
        if (s[i] == '1')
            cnt1s++;
    }

    int cnt0s = n - cnt1s;

    if (cnt1s == 0)
    {
        cout << 0 << endl;
    }
    else if (cnt0s == 1)
    {
        cout << 1 << endl;
        for (int i = 1; i <= n; i++)
        {
            if (s[i - 1] == '0')
            {
                cout << i << endl;
                return;
            }
        }
    }
    else if (cnt1s == 1)
    {
        if (cnt0s & 1)
        {
            cout << n - 1 << endl;
            for (int i = 1; i <= n; i++)
            {
                if (s[i - 1] == '0')
                {
                    cout << i << ' ';
                }
            }
            cout << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }
    else if (cnt1s == 2)
    {
        cout << 2 << endl;
        for (int i = 1; i <= n; i++)
        {
            if (s[i - 1] == '1')
            {
                cout << i << ' ';
            }
        }
        cout << endl;
    }
    else
    {
        cout << -1 << endl;
    }
}

void s4()
{
    int n;
    cin >> n;

    string s;
    cin >> s;

    int cnt1s = 0;
    fl(i, n)
    {
        if (s[i] == '1')
            cnt1s++;
    }

    int cnt0s = n - cnt1s;

    if (cnt0s == n)
    {
        cout << 0 << endl;
        return;
    }

    int selfdiff = cnt0s - 1;
    if (selfdiff % 2 == 0)
    {
        cout << cnt0s << endl;
        for (int i = 1; i <= n; i++)
        {
            if (s[i - 1] == '0')
            {
                cout << i << ' ';
            }
        }
        cout << endl;
        return;
    }

    int oppdiff = cnt1s - 1;
    if (oppdiff % 2 != 0)
    {
        cout << cnt1s << endl;
        for (int i = 1; i <= n; i++)
        {
            if (s[i - 1] == '1')
            {
                cout << i << ' ';
            }
        }
        cout << endl;
        return;
    }

    cout << -1 << endl;
}

void s5()
{
    map<int, int> mp;
    int n, h, k;
    cin >> n >> h >> k;

    vector<int> v(n);
    fl(i, n)
    {
        int e;
        cin >> e;
        v[i] = e;
        mp[e]++;
    }

    int total = accumulate(all(v), 0ll);

    int rounds = h / total;

    if ((h % total) == 0)
    {
        rounds--;
    }

    int time = rounds * 1ll * k;

    time += (n * 1ll * rounds);

    h = h - (total * 1ll * rounds);

    fl(i, n)
    {
        auto lb = mp.rbegin();
        ++time;
        if ((*lb).first < h)
        {
            h -= v[i];
            if (h <= 0)
            {
                break;
            }
            if (--mp[v[i]] == 0)
            {
                mp.erase(v[i]);
            }
        }
        else
        {
            h = 0;
            break;
        }
    }

    cout << time << endl;
}

void s6()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    bool has2025 = s.find("2025") != string::npos;
    bool has2026 = s.find("2026") != string::npos;

    if (has2026 || !has2025)
    {
        cout << 0 << endl;
    }
    else
    {
        cout << 1 << endl;
    }
}

int maxLayers(int a, int b)
{
    int maxa, maxb;
    int low = 0, high = 50, mid;

    while (low <= high)
    {
        mid = (low + high) / 2;
        int sum = (pow(4, mid) - 1) / 3;
        if (sum <= a)
        {
            maxa = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    low = 0, high = 50;

    while (low <= high)
    {
        mid = (low + high) / 2;
        int sum = (2 * 1ll * (pow(4, mid) - 1)) / 3;
        if (sum <= b)
        {
            maxb = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    int ans = min(maxa, maxb) * 2ll;

    if (maxa > maxb)
    {
        ++ans;
    }

    return ans;
}

void s7()
{
    int a, b;
    cin >> a >> b;

    int ans = max(maxLayers(a, b), maxLayers(b, a));

    cout << ans << endl;
}

void s8()
{
    int n;
    cin >> n;

    vector<int> a(n), b(n), c(n);
    read_vector(a);
    read_vector(b);
    read_vector(c);

    int gooda = 0, goodc = 0;

    for (int i = 0; i < n; i++)
    {
        bool isgood = true;
        for (int p = 0; p < n; p++)
        {
            if (a[(p + i) % n] >= b[p])
            {
                isgood = false;
                break;
            }
        }
        if (isgood)
            gooda++;
    }

    for (int i = 0; i < n; i++)
    {
        bool isgood = true;
        for (int p = 0; p < n; p++)
        {
            if (c[(p + i) % n] <= b[p])
            {
                isgood = false;
                break;
            }
        }
        if (isgood)
            goodc++;
    }

    int ans = (gooda * 1ll * goodc) * 1ll * n;
    cout << ans << endl;
}

bool isPossible(string &s, int k)
{
    int n = s.size();
    vector<bool> isused(n, false);
    for (int i = n - 1; i >= 0; i--)
    {
        if (k == 0)
            break;
        if (s[i] == '1')
        {
            isused[i] = true;
            --k;
        }
    }
    int p = 0;
    fl(i, n)
    {
        if (isused[i])
        {
            --p;
            if (p < 0)
            {
                return false;
            }
        }
        else
        {
            ++p;
        }
    }
    return true;
}

// https://codeforces.com/contest/2026/problem/C
void s10()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    if (n == 1)
    {
        cout << 1 << endl;
        return;
    }

    int count1s = 0;
    fl(i, n)
    {
        if (s[i] == '1')
            count1s++;
    }

    int low = 0, high = count1s + 1, mid, freeFigures;

    while (low <= high)
    {
        mid = (low + high) / 2;
        if (isPossible(s, mid))
        {
            freeFigures = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    int ans = 0;
    for (int i = n - 1; i >= 0; i--)
        if (s[i] == '1' && freeFigures > 0)
            freeFigures--;
        else
            ans += (i + 1);

    cout << ans << endl;
}

void r1()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    if (n == 1)
    {
        cout << 1 << endl;
        return;
    }

    vector<int> diffs;
    fl(i, n - 1)
    {
        diffs.push_back(v[i + 1] - v[i]);
    }

    sort(all(diffs));

    if (n & 1)
    {
        int m = (int)diffs.size();
        int maxdiff = diffs[m - 2];
        cout << maxdiff << endl;
    }
    else
    {
        cout << diffs.back() << endl;
    }
}

// leetcode problem
void r2()
{
    string s;
    cin >> s;

    int q;
    cin >> q;

    fl(i, q)
    {
        int l, r;
        cin >> l >> r;
    }
}

void r3()
{
    int n, k;
    cin >> n >> k;

    int low = 1, high = 1e9, mid, ans = 0;
    int t = (((n + k - 1) / k) * k) - n;
    while (low <= high)
    {
        mid = (low + high) / 2;
        int sum = n * 1ll * (mid - 1);
        if (sum >= (t))
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    cout << ans << endl;
}

void r4()
{
    int n, k;
    cin >> n >> k;

    vector<int> v(n);
    read_vector(v);

    int sumChanges = 0;
    int cost = v.front();

    for (int i = 1; i < n; i++)
    {
        int p1 = v[i] * 100ll;
        int p2 = k * 1ll * cost;
        if (p1 > p2)
        {
            sumChanges += (((p1 + k - 1) / k) - cost);
            cost += ((p1 + k - 1) / k);
        }
        cost += v[i];
    }

    cout << sumChanges << endl;
}

void r5()
{
    int n;
    cin >> n;

    vector<int> c(n), a(n), b(n);
    read_vector(c);
    read_vector(a);
    read_vector(b);

    int lastlen = 0;
    int ans = 0;

    for (int i = 1; i < n; i++)
    {
        int currlen = c[i] + 1 + abs(a[i] - b[i]);
        if (a[i] != b[i])
        {
            currlen = max(currlen, c[i] + 1 + lastlen - abs(a[i] - b[i]));
        }
        ans = max(ans, currlen);
        lastlen = currlen;
    }

    cout << ans << endl;
}

// https://codeforces.com/contest/1519/problem/D
void r6()
{
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    read_vector(a);
    read_vector(b);

    int origsum = 0;
    for (int i = 0; i < n; i++)
    {
        origsum += (a[i] * 1ll * b[i]);
    }

    int result = origsum;

    // odd subarrays
    for (int i = 0; i < n; i++)
    {
        int currsum = origsum;
        for (int j = 1; (i - j) >= 0 && (i + j) < n; j++)
        {
            currsum -= (a[i - j] * b[i - j] + a[i + j] * b[i + j]);
            currsum += (a[i - j] * b[i + j] + a[i + j] * b[i - j]);
            result = max(result, currsum);
        }
    }

    // even subarrays
    for (int i = 0; i < n - 1; i++)
    {
        int currsum = origsum;
        for (int j = 0; i - j >= 0 && (i + j + 1) < n; j++)
        {
            currsum -= (a[i - j] * b[i - j] + a[i + j + 1] * b[i + j + 1]);
            currsum += (a[i - j] * b[i + j + 1] + a[i + j + 1] * b[i - j]);
            result = max(result, currsum);
        }
    }

    cout << result << endl;
}

void t1()
{
    int n, m, d;
    cin >> n >> m >> d;

    int p = (d / m);
    ++p;
    int ans = (n + p - 1) / p;

    cout << ans << endl;
}

void t2()
{
    string s;
    cin >> s;

    int n = s.size();

    int sum = 0;

    for (auto i : s)
    {
        sum += (i - '0');
    }

    if (sum < 10)
    {
        cout << 0 << endl;
        return;
    }

    string t = "";
    t += '1';

    fl(i, n - 1)
    {
        t += '0';
    }
    vector<int> diffs;

    fl(i, n)
    {
        int p1 = s[i] - '0', p2 = t[i] - '0';
        diffs.push_back(p1 - p2);
    }
    sort(all(diffs));
    reverse(all(diffs));

    int ans = 0;

    fl(i, n)
    {
        sum -= diffs[i];
        ++ans;
        if (sum < 10)
        {
            break;
        }
    }

    cout << ans << endl;
}

bool isposs(ull s, ull m, ull n)
{
    ull prod = n * 1ll * m;
    if (prod < s)
    {
        return false;
    }
    ull remsum = s;
    for (int i = 60; i >= 0 && remsum > 0; --i)
    {
        if ((m & (1ll << i)) == 0)
        {
            continue;
        }
        ull maxk = remsum >> i;
        ull use = min(n, maxk);
        remsum -= (use << i);
    }
    return remsum == 0;
}

void t3()
{
    ull s, m;
    cin >> s >> m;

    ull low = 1, high = s + 1, ans = LLONG_MAX;

    while (low < high)
    {
        ull mid = (low + high) / 2;
        if (isposs(s, m, mid))
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    if (ans == LLONG_MAX)
    {
        cout << -1 << "\n";
    }
    else
    {
        cout << ans << "\n";
    }
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;

    while (t--)
    {
        t3();
    }

    khalaas
}