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

    vector<int> v(3);
    read_vector(v);

    sort(all(v));

    if (v[2] == (v[0] + v[1]))
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
    read_vector(v);

    sort(all(v));

    for (int i = 0; i < n - 1; i++)
    {
        if (v[i] == v[i + 1])
        {
            no;
        }
    }

    yes;
}

void s3()
{
    int n = 8;
    vector<string> grid(n);

    fl(i, n)
    {
        cin >> grid[i];
    }

    // {R, B}
    vector<int> rowcnt(8, 0), colcnt(8, 0);
    char ans = '$';

    fl(i, n)
    {
        fl(j, n)
        {
            rowcnt[i] += (grid[i][j] == 'R');
        }
        if (rowcnt[i] == n)
            ans = 'R';
    }

    fl(i, n)
    {
        fl(j, n)
        {
            colcnt[i] += (grid[j][i] == 'B');
        }
        if (colcnt[i] == n)
            ans = 'B';
    }

    cout << ans << endl;
}

void s4()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    unordered_map<int, vector<int>> pos;

    int res = -1;
    fl(i, n)
    {
        if (v[i] == 1)
        {
            res = (i + 1) * 2;
        }
        else
        {
            for (auto j : primes)
            {
                if (j > v[i])
                {
                    continue;
                }
                if (v[i] % j == 0)
                {
                    pos[j].push_back(i + 1);
                }
            }
        }
    }

    for (auto [elem, positions] : pos)
    {
        // cout<<elem<<' ';
        // print_vector(positions);

        int m = positions.size();
        if (m == 0)
        {
            continue;
        }
        if (m == 1)
        {
            if (positions.back() != n)
            {
                res = max(res, positions.back() + n);
            }
            else
            {
                res = max(res, 2ll * n - 1);
            }
        }
        else
        {
            if (positions.back() != n)
            {
                res = max(res, positions[m - 1] + n);
            }
            else
            {
                int i = m - 1;
                while (i > 0 && positions[i] - positions[i - 1] == 1)
                {
                    --i;
                }

                if (i > 0)
                {
                    res = max(res, positions[i - 1] + positions[i] - 1);
                }
                else
                {
                    if (positions[0] > 1)
                    {
                        res = max(res, positions[0] * 2 - 1);
                    }
                }
            }
        }
    }

    cout << res << endl;
}

void s5()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    vector<int> maxpos(1001, -1);
    int res = -1;

    fl(i, n)
    {
        if (v[i] == 1)
        {
            res = (i + 1) * 2;
        }
        maxpos[v[i]] = i + 1;
    }

    for (size_t i = 1; i <= 1000; i++)
    {
        if (maxpos[i] != -1)
        {
            for (int j = i + 1; j <= 1000; ++j)
            {
                if (maxpos[j] != -1 && gcd(i, j) == 1)
                {
                    res = max(res, maxpos[i] + maxpos[j]);
                }
            }
        }
    }

    cout << res << endl;
}

void s6()
{
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    read_vector(a);

    vector<int> prefmax(n), prefsum(n);
    prefmax[0] = a[0];
    prefsum[0] = a[0];

    for (int i = 1; i < n; i++)
    {
        prefmax[i] = max(prefmax[i - 1], a[i]);
        prefsum[i] = prefsum[i - 1] + a[i];
    }

    fl(i, q)
    {
        int k;
        cin >> k;

        int low = 0, high = n - 1, mid, ans = -1;
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (prefmax[mid] <= k)
            {
                ans = mid;
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }

        if (ans == -1)
        {
            cout << 0 << ' ';
        }
        else
        {
            cout << prefsum[ans] << ' ';
        }
    }

    cout << endl;
}

void r1()
{
    int n;
    cin >> n;

    fl(i, n)
    {
        cout << i + 1 << ' ';
    }
    cout << endl;
}

void r2()
{
    int n, q;
    cin >> n;

    vector<int> a(n);
    read_vector(a);

    sort(all(a));
    reverse(all(a));

    vector<int> prefmax(n);
    prefmax[0] = a[0];

    int ans = a[0];

    for (int i = 1; i < n; i++)
    {
        prefmax[i] = max(prefmax[i - 1], a[i]);
        ans += prefmax[i];
    }

    cout << ans << endl;
}

void r3()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    sort(all(v));

    int i = 0, maxlem = 0;

    while (i < n)
    {
        int curr = v[i], len = 1;
        while (i < n && v[i] == curr)
        {
            ++i;
        }
        while (i < n)
        {
            if (i < n and v[i] == (curr + 1))
            {
                ++i;
                ++len;
                ++curr;
                while (i < n && v[i] == curr)
                {
                    ++i;
                }
            }
            else
            {
                break;
            }
        }
        maxlem = max(maxlem, len);
    }

    cout << maxlem << endl;
}

void r4()
{
    int n, m, h;
    cin >> n >> m >> h;

    vector<int> origa(n);
    read_vector(origa);

    vector<int> temp = origa;

    set<int> changed;

    fl(i, m)
    {
        int b, c;
        cin >> b >> c;
        --b;

        if (temp[b] + c <= h)
        {
            temp[b] += c;
            changed.insert(b);
        }
        else
        {
            for (auto j : changed)
            {
                temp[j] = origa[j];
            }
            changed.clear();
        }
    }

    print_vector(temp);
}

void r5()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> a(n), b(m);
    read_vector(a);
    read_vector(b);

    string s;
    cin >> s;

    vector<int> prefsum(k);
    prefsum[0] = (s[0] == 'R') ? 1 : -1;
    for (int i = 1; i < k; i++)
    {
        prefsum[i] = prefsum[i - 1] + ((s[i] == 'R') ? 1 : -1);
    }

    sort(all(a));
    sort(all(b));

    vector<int> dtime(n, InF);

    map<int, int> fpos;
    for (int i = 0; i < k; i++)
    {
        if (!fpos.count(prefsum[i]))
            fpos[prefsum[i]] = i;
    }

    for (int i = 0; i < n; i++)
    {
        int pos = a[i];
        int idx = lower_bound(all(b), pos) - b.begin();

        if (idx < m)
        {
            int d = b[idx] - pos;
            if (fpos.count(d))
                dtime[i] = min(dtime[i], fpos[d]);
        }

        if (idx > 0)
        {
            int d = b[idx - 1] - pos;
            if (fpos.count(d))
                dtime[i] = min(dtime[i], fpos[d]);
        }
    }

    vector<int> times(k, 0);
    for (int i = 0; i < n; i++)
    {
        if (dtime[i] < k)
            times[dtime[i]]++;
    }

    vector<int> ans(k);

    int curr = n;
    for (int i = 0; i < k; i++)
    {
        curr -= times[i];
        ans[i] = curr;
    }

    print_vector(ans);
}

void r6()
{
    int n, q;
    cin >> n >> q;

    int m = 1 << n;
    vector<int> v(m);
    read_vector(v);

    vector<int> prefxor(m + 1, 0);
    for (int i = 0; i < m; i++)
        prefxor[i + 1] = prefxor[i] ^ v[i];

    map<pair<int, int>, int> xorval;

    for (int i = 0; i < n; i++)
    {
        int grpsize = 1 << i, cnt = m / grpsize;

        for (int s = 0; s < cnt; s++)
        {
            int l = s * grpsize;
            int r = l + grpsize;
            xorval[{i, s}] = prefxor[r] ^ prefxor[l];
        }
    }

    fl(i, q)
    {
        int b, c;
        cin >> b >> c;
        --b;

        int old = v[b];
        int ans = 0;

        for (int i = 0; i < n; i++)
        {
            int grpsize = 1 << i;
            int seg = b / grpsize;
            int p = (seg / 2) * 2;

            int x1 = xorval[{i, p}];
            int x2 = xorval[{i, p + 1}];

            if (seg == p)
                x1 = x1 ^ old ^ c;
            else
                x2 = x2 ^ old ^ c;

            if (x1 < x2)
            {
                if (seg == p)
                    ans += grpsize;
            }
            else
            {
                if (seg == p + 1)
                    ans += grpsize;
            }
        }

        cout << ans << '\n';
    }
}

void t1()
{
    int n, x;
    cin >> n >> x;

    fl(i, n)
    {
        int num;
        cin >> num;
        if (num < x)
        {
            cout << 1 << endl;
            x = num;
        }
        else
        {
            cout << 0 << endl;
        }
    }
}

void t2()
{
    double d;
    cin >> d;
    double r = d / 2;
    const double pi = 3.141592653589793;
    double area = (double)pi * r * r;
    cout << std::setprecision(10) << area << endl;
}

void t3()
{
    int n, m, q;
    cin >> n >> m >> q;

    fl(i, q)
    {
        int type, val;
        cin >> type >> val;

        if (type == 1)
        {
            cout << m * val << endl;
            n -= val;
        }
        else
        {
            cout << n * val << endl;
            m -= val;
        }
    }
}

void t4()
{
    int n, l, r;
    cin >> n >> l >> r;

    string s;
    cin >> s;

    vector<vector<int>> freq(26);

    fl(i, n)
    {
        freq[s[i] - 'a'].push_back(i);
    }

    int ans = 0;
    fl(i, 26)
    {
        auto v = freq[i];
        int m = v.size();
        for (int j = 0; j < m; j++)
        {
            auto lb = lower_bound(all(v), v[j] + l);
            auto ub = upper_bound(all(v), v[j] + r);
            ans += (ub - lb);
        }
    }

    cout << ans << endl;
}

void t5()
{
    int l, r, d, u;
    cin >> l >> r >> d >> u;

    int ans = 0;
    for (int i = l; i <= r; i++)
    {
        if (abs(i) & 1)
            continue;
        ans += abs(min(i, d)) + abs(min(i, u));
    }

    cout << ans << ' ';

    for (int i = d; i <= u; i++)
    {
        if (abs(i) & 1)
            continue;
        if (i >= l)
            ans += (i - l + 1);
    }

    cout << ans << endl;
}

int dp[10][90][90][2];

int t6helper(string &s, int pos = 0, int oddsum = 0, int evensum = 0, bool istight = 1)
{
    int n = s.size();
    if (pos == n)
    {
        if ((n % 2) == 0)
        {
            swap(oddsum, evensum);
        }
        // cout << evensum << ' ' << oddsum << endl;
        int diff = evensum - oddsum;
        return (diff == 1);
    }
    int &memvalue = dp[pos][oddsum][evensum][istight];

    if (memvalue != -1)
    {
        return memvalue;
    }

    int upperlimit = istight ? (s[pos] - '0') : 9;
    int ans = 0;
    for (int digit = 0; digit <= upperlimit; digit++)
    {
        // 1-based positioning
        int newOdd = oddsum;
        int newEven = evensum;

        if ((pos + 1) & 1)
            newOdd += digit;
        else
            newEven += digit;

        ans += t6helper(
            s,
            pos + 1,
            newOdd,
            newEven,
            istight && (digit == upperlimit));
    }
    return memvalue = ans;
}

// https://www.spoj.com/problems/RAONE/
void t6()
{
    int l, r;
    cin >> l >> r;

    string ls = to_string(l - 1);
    string rs = to_string(r);

    memset(dp, -1, sizeof(dp));
    int lessthanr = t6helper(rs);

    memset(dp, -1, sizeof(dp));
    int lessthanl = (l == 0) ? 0 : t6helper(ls);

    int ans = lessthanr - lessthanl;
    cout << ans << endl;
}

void p1()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    fl(i, n)
    {
        cin >> a[i + 1];
    }
    for (int i = k; i <= n; i += k)
    {
        cout << a[i] << ' ';
    }
}

void p2()
{
    int n, k;
    cin >> n >> k;

    int asum = 0, bsum = 0;
    fl(i, n)
    {
        int e;
        cin >> e;
        if (asum + e <= k)
        {
            asum += e;
        }
        else
        {
            bsum += e;
        }
    }
    if (asum > bsum)
    {
        cout << "Takahashi" << endl;
    }
    else if (asum < bsum)
    {
        cout << "Aoki" << endl;
    }
    else
    {
        cout << "Draw" << endl;
    }
}

void p3()
{
    int n, t, e;
    cin >> n >> t >> e;
    vector<int> p(n);
    read_vector(p);
    sort(all(p));

    int ans = 0;

    int sum = 0;
    for (auto i : p)
    {
        sum += (i * 1ll * t);
        if (sum <= e)
        {
            ++ans;
        }
        else
        {
            break;
        }
    }

    cout << ans << endl;
}

void p4()
{
    int n, k;
    cin >> n >> k;

    map<int, int> mp;

    fl(i, n)
    {
        int l, r;
        cin >> l >> r;
        mp[l]++;
        mp[r]--;
    }

    int ans = 0;
    int pref = 0, prev = 0;
    bool first = true;

    for (auto &[pos, val] : mp)
    {
        if (!first && pref >= k)
            ans += pos - prev;

        pref += val;
        prev = pos;
        first = false;
    }

    cout << ans << endl;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;

    while (t--)
    {
        p4();
    }

    khalaas
}