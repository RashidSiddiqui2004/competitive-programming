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

void sol1()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        if (i <= m)
        {
            cout << "OK\n";
        }
        else
        {
            cout << "Too Many Requests\n";
        }
    }
}

void sol2()
{
    int n, m;
    cin >> n >> m;

    vector<int> v(n);
    read_vector(v);

    ll totalsum = accumulate(all(v), 0);

    fl(i, n)
    {
        if (totalsum - v[i] == m)
        {
            cout << "Yes\n";
            return;
        }
    }
    cout << "No\n";
}

void sol3()
{
    int n;
    cin >> n;

    vector<vector<int>> freq(n + 1);

    fl(i, n)
    {
        int e;
        cin >> e;
        freq[e].push_back(i);
    }

    int ans = 0;

    for (auto a : freq)
    {
        int m = a.size();
        ans = ans + (n - m) * 1ll * (1ll * m * (m - 1) / 2);
    }

    cout << ans << endl;
}

void sol4()
{
    int n, m, c;
    cin >> n >> m >> c;

    map<int, int> mp;

    fl(i, n)
    {
        int pos;
        cin >> pos;
        mp[pos]++;
    }

    vector<pll> vp;
    for (auto i : mp)
        vp.push_back({i.first, i.second});

    int k = (int)vp.size();
    for (int i = 1; i < k; i++)
        vp[i].second += vp[i - 1].second;

    ll ans = 0ll;

    for (int i = 0; i < k; i++)
    {
        int low, high;
        int remsum = vp[k - 1].second - vp[i].second;
        int required = c;
        bool ch = false;
        int res = -1;

        if (remsum < c)
        {
            ch = true;
            if (i == 0)
                low = 0, high = k - 1;
            else
                low = 0, high = i - 1;
            required = c - remsum;
        }
        else
        {
            low = i + 1;
            high = k - 1;
        }

        while (low <= high)
        {
            int mid = (low + high) / 2;
            int currsum;
            if (!ch)
                currsum = vp[mid].second - vp[i].second;
            else
                currsum = remsum + vp[mid].second;

            if (currsum >= required)
            {
                res = mid;
                high = mid - 1;
            }
            else
                low = mid + 1;
        }

        int segmentlen;
        if (k == 1)
        {
            segmentlen = m;
        }
        else if (i == k - 1)
        {
            segmentlen = (int)(vp[0].first + m - vp[i].first);
        }
        else
        {
            segmentlen = (int)(vp[i + 1].first - vp[i].first);
        }

        if (res == -1)
        {
            ans += 1ll * segmentlen * n;
        }
        else
        {
            if (!ch)
                ans += 1ll * segmentlen * (vp[res].second - vp[i].second);
            else
                ans += 1ll * segmentlen * (remsum + vp[res].second);
        }
    }

    cout << ans << '\n';
}

void p1()
{
    int a, b, c;
    cin >> a >> b >> c;

    int mini = min({a, b, c});

    for (int i = mini; i <= 1e6; i++)
    {
        int g1 = gcd(i, a), g2 = gcd(i, b), g3 = gcd(i, c);
        if (g1 == g2 and g1 == g3 and g1 == 1)
        {
            cout << i << "\n";
            return;
        }
    }
}

void p2()
{
    int n, k;
    cin >> n >> k;
    map<long long, int> freq;

    while (k % 2 == 0)
    {
        freq[2]++;
        k /= 2;
    }

    for (long long i = 3; i * i <= k; i += 2)
    {
        while (k % i == 0)
        {
            freq[i]++;
            k /= i;
        }
    }

    if (k > 2)
        freq[k]++;

    vector<int> ans;
    vector<int> pres(n + 1, 0);
    for (auto [p, f] : freq)
    {
        int x = pow(p, f);
        if (x > n)
        {
            cout << "NO\n";
            return;
        }
        else
        {
            ans.push_back(x);
            pres[x] = 1;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (!pres[i])
        {
            ans.push_back(i);
        }
    }

    cout << "YES\n";
    print_vector(ans);
}

void p3()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    int start = n - 1;

    for (int k = 12; k >= 0; k--)
    {
        for (int i = start; i >= 0; i--)
        {
            if ((v[i] & (1 << k)) != 0)
            {
                start = i - 1;
                int currxor = v[i];
                for (int j = i - 1; j >= 0; j--)
                {
                    currxor ^= v[j];
                    if ((v[j] & (1 << k)) != 0)
                    {
                        int temp = v[j];
                        v[j] = currxor;
                        currxor = temp;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n - 1; i++)
    {
        if (v[i] > v[i + 1])
        {
            cout << -1 << endl;
            return;
        }
    }

    print_vector(v);
}

void p4()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    fl(i, n)
    {
        cin >> a[i + 1];
    }
    vector<int> prefsum(n + 1, 0ll);
    for (int i = 1; i <= n; i++)
    {
        prefsum[i] = prefsum[i - 1] + a[i];
    }

    int totalsum = prefsum.back();

    int l, r;
    fl(i, q)
    {
        cin >> l >> r;
        int startsubarray = (l + n - 1) / n, endsubarray = (r + n - 1) / n;
        cout << startsubarray << " " << endsubarray << endl;
        int ans = 1ll * max(0ll, (endsubarray - startsubarray - 1)) * totalsum;
        if (startsubarray == endsubarray)
        {
            // ek hi perm cover hai
            int s = (startsubarray - 1) * n + 1;
            int e = s + n - 1;
            // cout << s << " " << e << endl;
            // sum from perm[max(l, start), min(r, end)]
            for (int j = max(l, s); j <= min(r, e); j++)
            {
                ans += a[((j - s + 1) + startsubarray - 1) % n];
            }
        }
        else
        {
            // do covered hai
            int s = (startsubarray - 1) * n + 1;
            int e = s + n - 1;
            cout << s << " " << e << endl;
            // sum from perm[max(l, start), min(r, end)]
            for (int j = max(l, s); j <= min(r, e); j++)
            {
                ans += a[((j - s + 1) + startsubarray - 1) % n];
            }
            cout << "ans: " << ans << endl;
            s = (endsubarray - 1) * n + 1;
            e = s + n - 1;
            cout << s << " " << e << endl;
            // sum from perm[max(l, start), min(r, end)]
            for (int j = max(l, s); j <= min(r, e); j++)
            {
                ans += a[((j - s + 1) + endsubarray - 1) % n];
            }
        }
        cout << ans << endl;
    }
}

void s1()
{
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    sort(all(s));
    sort(all(t));
    if (s == t)
    {
        yes;
    }
    else
    {
        no;
    }
}

void s2()
{
    int n;
    cin >> n;
    vector<int> v(n);
    bool odd = false, even = false;
    fl(i, n)
    {
        cin >> v[i];
        if (v[i] & 1)
        {
            odd = true;
        }
        else
        {
            even = true;
        }
    }

    if (even and odd)
    {
        sort(all(v));
    }

    print_vector(v);
}

void s4()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    sort(all(v));
    int ans = LLONG_MAX;

    for (auto i : v)
    {
        for (auto j : primes)
        {
            if (i % j != 0)
            {
                ans = min(ans, j);
            }
        }
    }

    cout << ans << endl;
}

void s5()
{
    int n, k, x;
    cin >> n >> k >> x;

    vector<int> v(n);
    read_vector(v);
    sort(all(v));

    using pll2 = pair<pll, int>;

    priority_queue<pll2> pq;

    pq.push({{v[0], 0}, 1});

    pq.push({{x - v.back(), x}, 2});

    for (int i = 1; i < n; i++)
    {
        bool isodd = (v[i] - v[i - 1] - 1) % 2 != 0;
        pq.push({{(v[i] - v[i - 1]) / 2, v[i - 1]}, isodd ? 3 : 4});
    }

    vector<int> ans;
    set<int> st;

    while (!pq.empty() and k > 0)
    {
        auto top = pq.top();
        pq.pop();

        int gap = top.first.first, start = top.first.second, typeofgap = top.second;
        // cout << start << " " << gap << " " << typeofgap << endl;
        if (typeofgap == 3)
        {
            if (!st.count(start + gap))
            {
                st.insert(start + gap);
                k--;
                ans.push_back(start + gap);
                int gap1 = ((start + gap) - start) / 2;
                if (gap1 > 0)
                {
                    pq.push({{gap1, start}, 4});
                    pq.push({{gap1, start + gap}, 4});
                }
            }
        }
        else if (typeofgap == 1)
        {
            if (!st.count(start))
            {
                st.insert(start);
                k--;
                ans.push_back(start);
                if (gap > 0)
                    pq.push({{gap - 1, start + 1}, 1});
            }
        }
        else if (typeofgap == 2)
        {

            if (!st.count(start))
            {
                st.insert(start);
                k--;
                ans.push_back(start);
                if (gap > 0)
                    pq.push({{gap - 1, start - 1}, 2});
            }
        }
        else
        {
            if (!st.count(start + gap))
            {
                st.insert(start + gap);
                k--;
                ans.push_back(start + gap);
                int gap1 = ((start + gap) - start) / 2;
                if (gap1 > 0)
                {
                    pq.push({{gap1, start}, 3});
                }
                int gap2 = gap1 + 1;
                if (gap2 > 0)
                {
                    pq.push({{gap2, start + gap}, 4});
                }
            }
        }
    }

    sort(all(ans));
    print_vector(ans);
}

void encoding()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);
    string ans = "";
    for (auto i : v)
    {
        i = i % 26;
        ans += ('a' + i - 1);
    }
    cout << ans << endl;
}

void decoding()
{
    string s;
    cin >> s;
    int n = s.size();
    cout << n << endl;
    for (auto i : s)
    {
        int ch = i - 'a';
        cout << ch + 1 << " ";
    }
    cout << endl;
}

void t1()
{
    int n;
    cin >> n;

    int mini = LLONG_MAX, maxi = LLONG_MIN;

    fl(i, n)
    {
        int e;
        cin >> e;
        mini = min(mini, e);
        maxi = max(maxi, e);
    }

    int x;
    cin >> x;

    if (x >= mini and x <= maxi)
    {
        yes;
    }
    else
    {
        no;
    }
}

int f(int n, int r, int c)
{
    int base = max(0ll, n * (r - 1));
    return base + c;
}

void t2()
{
    int n;
    cin >> n;

    if (n == 1)
    {
        cout << 1 << endl;
    }
    else if (n == 2)
    {
        cout << 9 << endl;
    }
    else
    {
        int max_ans = 0ll;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                int ans = f(n, i, j);
                if (i - 1 >= 1)
                {
                    ans += f(n, i - 1, j);
                }
                if (i + 1 <= n)
                {
                    ans += f(n, i + 1, j);
                }
                if (j - 1 >= 1)
                {
                    ans += f(n, i, j - 1);
                }
                if (j + 1 <= n)
                {
                    ans += f(n, i, j + 1);
                }
                max_ans = max(max_ans, ans);
            }
        }
        cout << max_ans << endl;
    }
}

void t3()
{
    int n;
    cin >> n;

    vector<int> b(n);
    read_vector(b);

    sort(all(b));

    int ptr = n - 1;

    while (ptr >= 0)
    {
        if (b[ptr] == 0)
            break;
        --ptr;
    }

    int window_size = 0;
    int sum = accumulate(all(b), 0ll);
    int ans = 0ll;

    // sum - window_size >= n-1
    for (int i = max(0ll, ptr); i < n; i++)
    {
        sum--;
        if (sum >= (n - 1))
        {
            ans++;
        }
        else
        {
            break;
        }
    }

    cout << ans << endl;
}

void t5()
{
    int n, s;
    cin >> n >> s;
    vector<int> v(n);
    read_vector(v);

    int sum = accumulate(all(v), 0);

    if (s > sum)
    {
        cout << -1 << endl;
        return;
    }
    else if (s == sum)
    {
        cout << 0 << endl;
        return;
    }

    vector<int> onesInarray;
    fl(i, n)
    {
        if (v[i] == 1)
        {
            onesInarray.push_back(i + 1);
        }
    }

    int extraones = sum - s;
    int minSteps = INT_MAX;

    for (int forwones = 0; forwones <= extraones; forwones++)
    {
        int backones = extraones - forwones;
        int steps = (forwones == 0) ? 0 : onesInarray[forwones - 1];
        steps += (backones == 0) ? 0 : (1 + n - onesInarray[sum - backones]);
        minSteps = min(minSteps, steps);
    }

    cout << minSteps << endl;
}

void t6()
{
    int n;
    cin >> n;
    vector<int> v;
    map<int, int> freq;

    fl(i, n)
    {
        int m;
        cin >> m;
        m = m % 10;
        if (!freq.count(m) || freq[m] < 3)
        {
            freq[m]++;
        }
    }

    for (auto i : freq)
    {
        while (i.second--)
            v.push_back(i.first);
    }

    int m = v.size();
    for (int i = 0; i < m; i++)
    {
        for (int j = i + 1; j < m; j++)
        {
            for (int k = j + 1; k < m; k++)
            {
                int digit = (v[i] + v[j] + v[k]) % 10;
                if (digit == 3)
                {
                    yes;
                }
            }
        }
    }

    no;
}

// https://codeforces.com/contest/1692
void t7()
{
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    read_vector(v);

    int m = n - 1;
    vector<int> t(m);
    for (int i = 0; i < m; i++)
    {
        t[i] = (v[i] < (2 * v[i + 1]));
    }
    for (int i = 1; i < m; i++)
    {
        t[i] += t[i - 1];
    }

    int ans = 0;
    for (int i = 0; i < m; i++)
    {
        // check sum of subarray t[i...i+k-1]
        if (i + k - 1 >= m)
            break;
        int sum = t[i + k - 1] - ((i == 0) ? 0 : t[i - 1]);
        if (sum == k)
        {
            ans++;
        }
    }
    cout << ans << endl;
}

// https://codeforces.com/contest/1183/problem/A
void t8()
{
    int a;
    cin >> a;
    while (true)
    {
        int curr = a, sumofdigits = 0;
        while (curr > 0)
        {
            sumofdigits += curr % 10;
            curr /= 10;
        }

        if (sumofdigits % 4 == 0)
        {
            cout << a << endl;
            return;
        }
        ++a;
    }
}

void t9()
{
    int n, k;
    cin >> n >> k;

    vector<int> v(n);
    read_vector(v);
    sort(all(v));

    int mini = 0, maxi = LLONG_MAX;
    for (auto i : v)
    {
        mini = max(mini, i - k);
        maxi = min(maxi, i + k);
    }

    if (mini > maxi)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << maxi << endl;
    }
}

void t10()
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

    vector<int> allfreq;
    for (auto i : freq)
    {
        allfreq.push_back(i.second);
    }
    sort(all(allfreq), greater<int>());

    int res = 0;

    const int MAX_FREQ = 2e5;
    int nextFreeElement = MAX_FREQ;

    for (auto i : allfreq)
    {
        int curr = min(i, nextFreeElement);
        res += curr;
        nextFreeElement = max(0ll, curr - 1);
        if (nextFreeElement == 0ll)
        {
            break;
        }
    }

    cout << res << endl;
}

void t11()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    int ans = 0ll;

    queue<string> q;
    unordered_set<string> st;
    q.push(s);
    st.insert(s);

    while (!q.empty() and (int) st.size() != k)
    {
        string t = q.front();
        q.pop();
        int m = t.size();
        for (int i = 0; i < m; i++)
        {
            string neighbor = t.substr(0, i) + t.substr(i + 1);
            if (!st.count(neighbor))
            {
                q.push(neighbor);
                st.insert(neighbor);
                ans += (n - m + 1);
            }
            if (st.size() == k)
            {
                break;
            }
        }
    }

    if ((int)st.size() != k)
    {
        cout << -1 << endl;
        return;
    }
    cout << ans << endl;
}

void t12()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);
    int ans = 1, i = 1;
    int prevmax = v[0];
    while (i < n)
    {
        while (i < n and v[i] <= prevmax)
        {
            ++i;
        }
        if (i != n)
        {
            ans++;
            prevmax = v[i++];
        }
    }
    cout << ans << endl;
}

void r1()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    int currmax = v[0], ans = 0;
    for (int i = 1; i < n; i++)
    {
        if (v[i] < currmax)
        {
            ans++;
        }
        else
        {
            currmax = v[i];
        }
    }

    cout << ans << endl;
}

void r2()
{
    // 10101010100
    // 01010101010 (d=1)
    // result
    // 11111111110
    // 01111111111 (d=1)
    // result
    // 11111111111
    // cost = 1+1 = 2;
    int n;
    cin >> n;
    string s;
    cin >> s;

    int maxgrouplen = 0;
    s += s;
    int i = 0;
    n = s.size();
    while (i < n)
    {
        while (i < n and s[i] == '1')
        {
            ++i;
        }
        int currgrplen = 0;
        while (i < n and s[i] == '0')
        {
            ++i;
            ++currgrplen;
        }
        maxgrouplen = max(maxgrouplen, currgrplen);
    }

    cout << maxgrouplen << endl;
}

void r3()
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

    sort(all(odds));
    sort(all(evens));

    int numodds = odds.size(), numevens = evens.size();

    if (numodds == 0)
    {
        // all evens
        fl(i, n)
        {
            cout << 0 << ' ';
        }
    }
    else if (numodds == 1)
    {
        int currans = odds.back();
        cout << currans << ' ';
        for (size_t i = 0; i < numevens; i++)
        {
            currans += evens[numevens - i - 1];
            cout << currans << ' ';
        }
    } 
    else if (numevens != 0)
    {
        vector<int> ans;
        int currans = odds.back();
        ans.push_back(currans);
        for (size_t i = 0; i < numevens; i++)
        {
            currans += evens[numevens - i - 1];
            ans.push_back(currans);
        }
        int rem = numodds - 1;
        int seclast = ans[(int)ans.size() - 2], last = ans.back();
        for (int i = 1; i < rem; i++)
        {
            if (i % 2 == 1)
            {
                ans.push_back(seclast);
            }
            else
            {
                ans.push_back(last);
            }
        }
        if (numodds % 2 == 0)
        {
            ans.push_back(0);
        }
        else
        {
            ans.push_back(last);
        }
        for (auto i : ans)
        {
            cout << i << ' ';
        }
    }
    else
    {
        // all odds
        fl(i, n)
        {
            if (i % 2 == 0)
            {
                cout << odds.back() << ' ';
            }
            else
            {
                cout << 0 << ' ';
            }
        }
    }
    cout << endl;
}

ll mod_ajeeb = 998244353;
int totalFibSequences = 0ll;

int helper(int node, vector<vector<int>> &adj, vector<int> &values,
           vector<bool> &vis, int a = -1, int b = -1)
{
    int continueAns = 0, newBeginningAns = 0;
    vis[node] = 1;
    for (auto i : adj[node])
    {
        if (vis[i])
        {
            continue;
        }
        if (b == -1)
        {
            continueAns += (1 + helper(i, adj, values, vis, a, values[i])) % mod_ajeeb;
        }
        else if (values[i] == (a + b))
        {
            continueAns += (1 + helper(i, adj, values, vis, b, a + b)) % mod_ajeeb;
        }
        newBeginningAns += (1 + helper(i, adj, values, vis, values[i], -1)) % mod_ajeeb;
    }
    totalFibSequences += newBeginningAns % mod_ajeeb;
    return continueAns % mod_ajeeb;
}

void r4()
{
    totalFibSequences = 0ll;
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);

    vector<int> values(n);
    read_vector(values);

    fl(i, m)
    {
        int u, v;
        cin >> u >> v;
        adj[u - 1].push_back(v - 1);
    }

    vector<bool> vis(n, false);

    fl(i, n)
    {
        if (!vis[i])
        {
            totalFibSequences += helper(i, adj, values, vis, values[i], -1) % mod_ajeeb;
        }
    }

    cout << totalFibSequences << endl;
}

int32_t main()
{
    int t = 1;
    cin >> t;

    while (t--)
    {
        r3();
    }

    // int MAXN = 5 * 1e5;
    // sieve(MAXN);

    // while (t--)
    // {
    //     string s;
    //     cin >> s;
    //     if (s == "first")
    //     {
    //         encoding();
    //     }
    //     else
    //     {
    //         decoding();
    //     }
    // }

    khalaas
}