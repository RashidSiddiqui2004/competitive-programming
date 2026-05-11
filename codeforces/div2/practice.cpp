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

    map<int, int> freq;

    fl(i, n)
    {
        int m;
        cin >> m;
        freq[m]++;
    }

    int maxpolygons = 0;

    for (auto [_, f] : freq)
    {
        maxpolygons += f / 3;
    }

    cout << maxpolygons << endl;
}

void s2()
{
    int n, k;
    cin >> n >> k;

    if (n == 1)
    {
        cout << k << endl;
        return;
    }

    vector<int> ans;

    int msb = 0;
    for (int i = 0; i < 31; i++)
    {
        if (k & (1 << i))
        {
            msb = i;
        }
    }
    ans.push_back((1 << msb) - 1);
    ans.push_back(k - ans[0]);
    n -= 2;

    if (n > 0)
    {
        fl(i, n)
        {
            ans.push_back(0);
        }
    }

    print_vector(ans);
}

const int Z = 30;
const int MAX_N = 1e5 + 3;
int pref[Z][MAX_N][2];
int suff[Z][MAX_N][2];

void s3()
{
    int n;
    cin >> n;

    vector<int> v(n + 1);

    fl(i, n)
    {
        cin >> v[i + 1];
    }

    for (int i = 0; i < Z; i++)
    {
        suff[i][n + 1][0] = 0;
        suff[i][n + 1][1] = 0;
    }

    for (int i = 0; i < Z; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int isithBitsetInAj = !!(v[j] & (1 << i));
            fl(k, 2)
            {
                pref[i][j][k] = (isithBitsetInAj == k) + pref[i][j - 1][k ^ isithBitsetInAj];
            }
        }
        for (int j = n; j >= 0; j--)
        {
            int isithBitsetInAj = !!(v[j] & (1 << i));
            fl(k, 2)
            {
                suff[i][j][k] = (isithBitsetInAj == k) + suff[i][j + 1][k ^ isithBitsetInAj];
            }
        }
    }

    int ans = 0;

    for (int y = 1; y <= n; y++)
    {
        int msb = 0;
        for (int k = 0; k < 31; k++)
        {
            if (v[y] & (1 << k))
                msb = k;
        }

        ans += 1ll * pref[msb][y - 1][1] * (1 + suff[msb][y + 1][0]);
        ans += 1ll * (pref[msb][y - 1][0] + 1) * suff[msb][y + 1][1];
    }

    cout << ans << endl;
}

void s4()
{
    int n;
    cin >> n;

    map<int, int> freq;
    map<int, int> freqoffreq;

    int ans = 0;

    fl(i, n)
    {
        int p;
        cin >> p;
        if (freq.count(p))
        {
            --freqoffreq[freq[p]];
            if (freqoffreq[freq[p]] == 0)
            {
                freqoffreq.erase(freq[p]);
            }
        }
        ++freq[p];
        ++freqoffreq[freq[p]];
        int m = freqoffreq.size();
        if (m == 1)
        {
            auto it = freqoffreq.begin();
            int freq = (*it).first, cnt = (*it).second;
            if (freq == 1 || cnt == 1)
            {
                ans = i + 1;
            }
        }
        if (m == 2)
        {
            auto it = freqoffreq.begin();
            vector<pair<int, int>> vp;
            vp.push_back({(*it).first, (*it).second});
            ++it;
            vp.push_back({(*it).first, (*it).second});
            int valuediff = vp[1].first - vp[0].first;
            if (vp[0].first == 1 && vp[0].second == 1)
            {
                ans = i + 1;
            }
            else if (valuediff == 1 && vp[1].second == 1)
            {
                ans = i + 1;
            }
        }
    }

    cout << ans << endl;
}

void s5()
{
    int n, k;
    cin >> n >> k;

    vector<int> v(n);
    read_vector(v);

    int sum = accumulate(all(v), 0ll);

    if ((sum & 1) || (((k * n) % 2) == 0))
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
    int n, k;
    cin >> n >> k;

    vector<char> s(n);
    fl(i, n)
    {
        cin >> s[i];
    }

    int p;
    cin >> p;
    --p;

    char req = s[p];
    int i = 0;

    while (i < p && s[i] == req)
    {
        ++i;
    }

    int left = 0;
    while (i < p)
    {
        ++left;
        char curr = s[i++];
        while (i < p && s[i] == curr)
        {
            ++i;
        }
    }

    i = n - 1;

    while (i > p && s[i] == req)
    {
        --i;
    }

    int right = 0;

    while (i > p)
    {
        ++right;
        char curr = s[i--];
        while (i > p && s[i] == curr)
        {
            --i;
        }
    }

    if (left & 1)
    {
        ++left;
    }
    if (right & 1)
    {
        ++right;
    }

    int ans = max(left, right);
    cout << ans << endl;
}

void s7()
{
    int n, k;
    cin >> n >> k;

    vector<int> v(n);
    read_vector(v);

    multiset<int> st(v.begin() + k, v.end());
    int mindiff = INT_MAX;

    for (int i = 0; i < n - k; i++)
    {
        auto it = st.lower_bound(v[i]);
        if (it != st.begin())
        {
            mindiff = min(mindiff, abs(v[i] - *prev(it)));
        }
        if (it != st.end())
        {
            mindiff = min(mindiff, abs(v[i] - *(it)));
        }
        st.erase(st.find(v[i + k]));
    }

    cout << mindiff << endl;
}

void s8()
{
    int n, c;
    cin >> n >> c;

    vector<int> a(n);
    read_vector(a);

    int cost = 0;
    priority_queue<ll> pq;

    for (auto &e : a)
    {
        if (e <= c)
            pq.push(e);
        else
            ++cost;
    }

    vector<ll> temp;
    while (!pq.empty())
    {
        ll top = pq.top();
        pq.pop();

        temp.resize(0);
        while (!pq.empty())
        {
            ll currtop = pq.top();
            pq.pop();
            if (currtop * 2ll > c)
            {
                ++cost;
            }
            else
            {
                temp.push_back(currtop * 2ll);
            }
        }
        for (ll &e : temp)
        {
            pq.push(e);
        }
    }

    cout << cost << endl;
}

void s9()
{
    int n;
    cin >> n;
    vector<int> a(n);
    read_vector(a);

    int l = 0, r = n - 1;
    string ans;

    bool turn = 1;
    while (l <= r)
    {
        if (turn & 1)
        {
            if (a[l] < a[r])
            {
                ans += 'L';
                ++l;
            }
            else
            {
                ans += 'R';
                --r;
            }
        }
        else
        {
            if (a[l] > a[r])
            {
                ans += 'L';
                ++l;
            }
            else
            {
                ans += 'R';
                --r;
            }
        }
        turn = !turn;
    }

    cout << ans << endl;
}

void p1()
{
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    int ans = 0;

    fl(i, n)
    {
        if (s[i] == '0')
        {
            continue;
        }
        int st = max(0ll, i - k + 1);
        bool has1 = false;
        for (int j = st; j < i; j++)
        {
            if (s[j] == '1')
            {
                has1 = true;
                break;
            }
        }
        if (!has1)
        {
            ++ans;
        }
    }

    cout << ans << endl;
}

void p2()
{
    int n;
    cin >> n;
    vector<int> a(n + 2);
    fl(i, n)
    {
        cin >> a[i + 1];
    }

    int prefmax = INT_MIN;
    for (int i = 1; i <= n; i++)
    {
        prefmax = max(prefmax, a[i]);
        if (i % 2 == 0)
        {
            a[i] = prefmax;
        }
    }

    int opers = 0;
    prefmax = INT_MIN;
    for (int i = 1; i < n; i++)
    {
        if (i & 1)
        {
            if (a[i] >= a[i + 1])
            {
                int reqOpers = (a[i] - a[i + 1] + 1);
                opers += reqOpers;
                a[i] -= reqOpers;
            }
        }
        else
        {
            if (a[i] <= a[i + 1])
            {
                int reqOpers = (a[i + 1] - a[i] + 1);
                opers += reqOpers;
                a[i + 1] -= reqOpers;
            }
        }

        if (a[i] > prefmax)
        {
            prefmax = a[i];
        }
    }

    cout << opers << endl;
}

const int MAXN = 2e5 + 10;
vector<vector<int>> primefactors(MAXN);

void p3()
{
    int n;
    cin >> n;

    vector<int> a(n), b(n);

    read_vector(a);
    read_vector(b);

    map<int, int> cnt;
    int ans = 2;

    for (auto &num : a)
    {
        for (auto pf : primefactors[num])
        {
            if (cnt[pf])
            {
                ans = 0;
            }
            ++cnt[pf];
        }
    }

    if (ans == 2)
    {
        for (auto &num : a)
        {
            for (auto pf : primefactors[num])
            {
                --cnt[pf];
            }
            for (auto pf : primefactors[num + 1])
            {
                if (cnt[pf])
                {
                    ans = 1;
                }
            }
            for (auto pf : primefactors[num])
            {
                ++cnt[pf];
            }
        }
    }

    cout << ans << endl;
}

const int N = 2e5 + 10;
int parent[N];

bool bfs(int node, int par, int dest, vector<vector<int>> &adj)
{
    if (node == dest)
    {
        parent[node] = par;
        return true;
    }

    for (int neig : adj[node])
    {
        if (neig != par && bfs(neig, node, dest, adj))
        {
            parent[node] = par;
            return true;
        }
    }

    return false;
}

void p4()
{
    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);

    fl(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(parent, -1, sizeof(parent));

    bfs(1, -1, n, adj);

    vector<int> path;
    int curr = n;
    while (curr != 1)
    {
        path.push_back(curr);
        curr = parent[curr];
    }
    path.push_back(1);

    reverse(all(path));
    // print_vector(path);

    vector<pair<int, int>> opers;

    int currnode = 1, index = 0;

    while (currnode != n)
    {
        currnode = path[index++];
        int nextnode = path[index];
        if (currnode == n)
        {
            break;
        }
        for (auto &i : adj[currnode])
        {
            if (i != nextnode)
            {
                opers.push_back({2, i});
            }
        }
        opers.push_back({1, -1});
    }

    cout << (int)opers.size() << endl;

    for (auto [f, s] : opers)
    {
        if (f == 1)
        {
            cout << 1 << endl;
        }
        else
        {
            cout << f << ' ' << s << endl;
        }
    }
}

void p5()
{
    int n;
    cin >> n;

    vector<int> v(n);
    read_vector(v);

    sort(all(v));
    reverse(all(v));

    fl(i, n - 1)
    {
        if (v[i] == v[i + 1])
        {
            cout << -1 << endl;
            return;
        }
    }

    print_vector(v);
}

bool ispalindrome(string &s)
{
    int n = s.size();
    int p1 = 0, p2 = n - 1;

    while (p1 < p2)
    {
        if (s[p1] == s[p2])
        {
            ++p1, --p2;
        }
        else
        {
            return false;
        }
    }

    return true;
}

void p6()
{
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    int ans = -1;
    if (k == 0)
    {
        ans = 1;
    }
    else if (ispalindrome(s))
    {
        ans = 1;
    }
    else
    {
        ans = 2;
    }

    cout << ans << endl;
}

void p7()
{
    // string s="codeforcesecrofedoc";
    // cout<<(int)s.size()<<endl;

    string s;
    cin >> s;

    int n = s.size();
    if (!ispalindrome(s))
    {
        cout << n << endl;
        return;
    }

    set<char> st(all(s));

    if ((int)st.size() == 1)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << n - 1 << endl;
    }
}

const int mxn = 2e5 + 5;
ll a[mxn];

void p8()
{
    ll n, m;
    cin >> n >> m;

    for (int i = 1; i <= n * m; ++i)
    {
        cin >> a[i];
    }

    sort(a + 1, a + n * m + 1);

    if (n > m)
    {
        swap(n, m);
    }

    if (n == 1)
    {
        cout << (m - 1) * (a[n * m] - a[1]) << '\n';
    }
    else
    {
        ll ans1 = (n * m - 1) * (a[n * m]) - a[1] * (n * (m - 1)) - a[2] * (n - 1);
        ll ans2 = a[n * m] * (n * (m - 1)) + a[n * m - 1] * (n - 1) - a[1] * (n * m - 1);
        cout << max(ans1, ans2) << '\n';
    }
}

void l1()
{
    int n;
    cin >> n;
    vector<int> a(n);
    read_vector(a);

    int ans = 0;

    fl(i, n - 1)
    {
        if (a[i] > a[i + 1])
        {
            int l = log2((a[i] + a[i + 1] - 1) / a[i + 1]);
            int updatedval = a[i + 1] * pow(2, l);
            if (a[i] <= updatedval)
            {
                ans += l;
                a[i + 1] = updatedval;
            }
            else
            {
                ans += l + 1;
                a[i + 1] = updatedval * 2ll;
            }
        }
    }

    cout << ans << endl;
}

void l2()
{
    int n;
    cin >> n;

    vector<int> v(n);
    read_vector(v);

    sort(all(v));
    reverse(all(v));

    int sum = 0, ans = 0;

    fl(i, n)
    {
        if (sum + v[i] < 0)
        {
            break;
        }
        sum += v[i];
        ++ans;
    }

    cout << ans << endl;
}

void l3()
{
    int n;
    cin >> n;

    int zeros = (n / 2);
    int ones = n - zeros;

    string ans = "0";

    fl(i, n - 2)
    {
        ans += '1';
    }

    if (n > 2)
    {
        ans += '0';
    }
    else
    {
        ans += '1';
    }

    cout << ans << endl;

    // 0101
    // 0011

    // {3, 5, 7}
    // 3, 4, 5, 6
}

void l4()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    map<int, int> fr;

    for (auto i : v)
    {
        fr[v[i]]++;
    }

    for (auto &e : v)
    {
        cout << fr[e] << ' ';
    }

    cout << endl;
}

void l5()
{
    int n;
    cin >> n;

    vector<int> v(n);
    read_vector(v);

    vector<pll> intervals;

    for (int i = 0; i < n; i++)
    {
        map<int, int> cnt;
        int countOfSingleFreqElems = 0;
        for (int j = i; j < n; j++)
        {
            if (++cnt[v[j]] == 1)
            {
                countOfSingleFreqElems++;
            }
            else if (cnt[v[j]] == 2)
            {
                --countOfSingleFreqElems;
            }
            if (countOfSingleFreqElems == 0)
            {
                intervals.push_back({j, i});
            }
        }
    }

    sort(all(intervals));

    int prevright = -1, ans = 0;
    for (auto &[right, left] : intervals)
    {
        if (prevright >= left)
        {
            continue;
        }
        else
        {
            ++ans;
            prevright = right;
        }
    }

    cout << ans << endl;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;

    while (t--)
    {
        l5();
    }

    khalaas
}