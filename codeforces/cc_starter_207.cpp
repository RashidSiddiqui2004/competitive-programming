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
    isPrime[0] = isPrime[1] = false;
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
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;

    int a = 0, b = 0;
    for (auto i : s)
    {
        if (i == '1')
        {
            a++;
        }
        else
        {
            b++;
        }
    }
    int alpha = abs(a - b);
    int t = n - m - alpha;
    cout << t << " ";
    if (t > 0 and t % 2 == 0)
    {
        cout << "Yes\n";
    }
    else
    {
        cout << "No\n";
    }
}

void s2()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    int first = n, last = -1;
    fl(i, n)
    {
        if (s[i] == '1')
        {
            first = min(first, i);
            last = max(last, i);
        }
    }

    if (first == n)
    {
        cout << 0 << endl;
    }
    else
    {
        int ans = 0;
        for (int i = first; i <= last; i++)
        {
            if (s[i] == '0')
                ans++;
        }
        cout << ans << endl;
    }
}

void s3()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    vector<pair<int, int>> vp;
    bool alleq = true;

    for (int i = 0; i < n; i++)
    {
        if (v[i] != v[0])
            alleq = false;
        vp.push_back({v[i], i});
    }

    if (alleq)
    {
        cout << n << "\n";
        cout << n << " ";
        for (int i = 1; i < n; i++)
            cout << i << " ";
        cout << "\n";
        return;
    }

    sort(vp.begin(), vp.end());

    vector<int> p(n);
    int i = 0;

    while (i < n)
    {
        int e = vp[i].first;
        list<int> ind;
        while (i < n && vp[i].first == e)
        {
            ind.push_back(vp[i].second);
            i++;
        }

        if (ind.size() == 1)
        {
            ind.push_back(vp[i].second);
            i++;
        }

        vector<int> t(ind.begin(), ind.end());
        int m = t.size();
        for (int j = 0; j < m; ++j)
        {
            int from = t[j];
            int to = t[(j + 1) % m];
            p[from] = to;
        }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        if (p[i] != i && v[p[i]] <= v[i])
            ++ans;
    }

    cout << ans << "\n";
    for (int i = 0; i < n; ++i)
    {
        cout << p[i] + 1 << " ";
    }
    cout << "\n";
}

void s4()
{
    string s;
    cin >> s;
    int n = s.size();
    int ans = s[0] == '?' ? 9 : 1;

    for (int i = 1; i < n; i++)
    {
        if (s[i] == '?')
            ans *= 10;
    }

    if (s[0] == '0')
    {
        ans = 0;
    }

    cout << ans << endl;
}

bool checkPossibility(vector<int> &a, vector<int> &b, int l, int r)
{
    int n = a.size();
    for (int i = 0; i < l; i++)
    {
        if (a[i] != b[i])
        {
            return false;
        }
    }
    for (int i = r + 1; i < n; i++)
    {
        if (a[i] != b[i])
        {
            return false;
        }
    }
    return true;
}

void s5()
{
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    read_vector(a);
    read_vector(b);

    int p1 = 0, p2 = n - 1;
    // it is only possible for a given subarray to be our answer
    // if rest of the array elements match

    while (p1 < p2)
    {
        if (a[p1] == b[p1])
            p1++;
        else
            break;
    }

    while (p2 > p1)
    {
        if (a[p2] == b[p2])
            p2--;
        else
            break;
    }

    while (p1 > 0 and b[p1] >= b[p1 - 1])
    {
        p1--;
    }

    while (p2 < n - 1 and b[p2] <= b[p2 + 1])
    {
        p2++;
    }

    cout << p1 + 1 << " " << p2 + 1 << endl;
}

int getval(int n)
{
    int ans = 0;
    while (n > 0)
    {
        ans++;
        n /= 2;
    }
    return ans;
}

void s6()
{
    string s;
    cin >> s;
    int n = s.size();
    vector<vector<int>> pos(26);
    fl(i, n)
    {
        pos[s[i] - 'a'].push_back(i);
    }

    // codeforces
    // e = {3, 8}

    int minopers = INT_MAX;
    for (int i = 0; i < 26; i++)
    {
        int m = pos[i].size();
        if (m == 0)
            continue;
        int curr = getval(pos[i].front());
        curr = max(curr, getval(n - 1 - pos[i].back()));

        for (int j = 1; j < m; j++)
        {
            int gap = pos[i][j] - pos[i][j - 1] - 1;
            if (gap == 0)
                continue;
            curr = max(curr, getval(gap));
        }
        minopers = min(minopers, curr);
    }
    cout << minopers << endl;
}

void s7()
{
    int n, k;
    cin >> n >> k;
    vector<pll> v(n);

    fl(i, n)
    {
        cin >> v[i].first;
    }

    fl(i, n)
    {
        cin >> v[i].second;
    }

    vector<int> s(n), c(n);

    int len = v[0].second - v[0].first + 1;
    s[0] = len == 1 ? 0 : len;
    c[0] = len == 1;

    for (int i = 1; i < n; i++)
    {
        int len = v[i].second - v[i].first + 1;
        s[i] = s[i - 1] + (len == 1 ? 0 : len);
        c[i] = c[i - 1] + (len == 1);
    }

    int moves = INT_MAX;

    fl(i, n)
    {
        if (s[i] < k and (s[i] + c[i]) >= k)
            moves = min(moves, v[i].second + 2ll * ((i - c[i] + 1) + (k - s[i])));
        else if (s[i] >= k)
            moves = min(moves, v[i].second - (s[i] - k) + 2ll * (i - c[i] + 1));
    }

    if (moves == INT_MAX)
        moves = -1;

    cout << moves << endl;
}

// k = 3
// ((())()(()())((())))

// ()()()()()()((()))()
// (())()(()())((()))()

void s8()
{
    // find corresponding ending bracket position of each opening position
    int k;
    cin >> k;

    string s;
    cin >> s;
    int n = s.size();

    string result;

    while (k > 0)
    {
        k--;
        vector<int> closing(n, -1);
        stack<int> st;

        fl(i, n)
        {
            if (s[i] == '(')
            {
                st.push(i);
            }
            else
            {
                int pos = st.top();
                st.pop();
                closing[pos] = i;
            }
        }

        bool changed = false;
        fl(i, n)
        {
            if (s[i] == '(' && closing[i] != i + 1)
            {
                result = s.substr(0, i);
                result += s.substr(i + 1, closing[i] - i - 1);
                result += '(';
                result += s.substr(closing[i]);
                s = result;
                changed = true;
                break;
            }
        }

        if (!changed)
        {
            break;
        }
    }

    cout << s << endl;
    int ans = 0, i = 0;

    while (i < n)
    {
        int open = 0;
        while (i < n and s[i] == '(')
            ++i, ++open;

        while (i < n and s[i] == ')')
            ++i;
        ans += open - 1;
    }

    cout << ans << endl;
}

void s9()
{
    int n;
    cin >> n;
    vector<int> v(101, 0);
    fl(i, n)
    {
        int e;
        cin >> e;
        v[e]++;
    }
    int mex = 0;
    fl(i, 101)
    {
        if (v[i] == 0)
        {
            mex = i;
            break;
        }
    }
    cout << mex << endl;
}

void s10()
{
    int n;
    cin >> n;
    vector<int> b(n + 1);
    fl(i, n)
    {
        cin >> b[i + 1];
    }
    vector<int> a(n + 1, -1);
    a[1] = 1;

    int nextelem = 2;
    for (size_t i = 2; i <= n; i++)
    {
        int requiredInc = i;
        int actualInc = b[i] - b[i - 1];
        int diff = requiredInc - actualInc;
        if (diff == 0)
        {
            a[i] = nextelem++;
        }
        else
        {
            a[i] = a[diff];
        }
    }

    for (int i = 1; i <= n; i++)
    {
        cout << a[i] << " ";
    }

    cout << endl;
}

void r1()
{
    int n;
    cin >> n;

    cout << (n + 1) / 2 << endl;
}

void r2()
{
    int n, x, k;
    cin >> n >> x >> k;

    priority_queue<int> pq;

    fl(i, n)
    {
        int e;
        cin >> e;
        pq.push(e);
    }

    while (!pq.empty() and k > 0)
    {
        k--;
        auto top = pq.top();
        pq.pop();
        x += 100;
    }

    int rank = 1;

    while (!pq.empty())
    {
        if (pq.top() > x)
        {
            pq.pop();
            rank++;
        }
        else
        {
            break;
        }
    }

    cout << rank << endl;
}

void r3()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);
    int maxi = *max_element(all(v));
    int ans = maxi - 1;
    int maxfr = 0;
    for (auto i : v)
    {
        if (i != maxi and i % ans != 0)
        {
            cout << ans << endl;
            return;
        }
        if (i == maxi)
            maxfr++;
    }
    if (maxfr == 1)
        ans--;
    cout << ans << endl;
}

void r4()
{
    int n, c;
    cin >> n >> c;

    vector<int> b(n), d(n);

    read_vector(b);
    read_vector(d);

    int mincost = 0;
    fl(i, n)
    {
        mincost += b[i] * d[i];
    }

    fl(i, n)
    {
        int currcost = c + (b[(i + 1) % n] * d[(i + 1) % n]);

        fl(j, n)
        {
            if (j == i)
                continue;
            currcost += b[j] * d[(j + 1) % n];
        }

        mincost = min(mincost, currcost);
    }

    fl(k, n - 1)
    {
        fl(i, n)
        {
            int currcost = c * (k + 1);
            fl(j, n)
            {
                currcost += b[j] * d[(j + k + 1) % n];
            }
            mincost = min(mincost, currcost);
        }
    }

    cout << mincost << endl;
}

void r5()
{
    int n;
    cin >> n;
    int M = 1e5 + 2;

    vector<int> freq(M, 0);

    fl(i, n)
    {
        int e;
        cin >> e;
        freq[e]++;
    }
    vector<int> odd(M, 0), even(M, 0);
    int ans = 0;

    for (int i = 1; i <= 1e5; i++)
    {
        if (i & 1)
        {
            odd[i] = max((i - 2 >= 0) ? odd[i - 2] : 0, (i - 3 >= 0) ? even[i - 3] : 0) + (freq[i] * 1ll * i);
        }
        else
        {
            even[i] = max((i - 2 >= 0) ? even[i - 2] : 0, (i - 3 >= 0) ? odd[i - 3] : 0) + (freq[i] * 1ll * i);
        }

        ans = max({ans, odd[i], even[i]});
    }

    cout << ans << endl;
}

#define cutenode pair<int, int>

void r6()
{
    int n, k;
    cin >> n >> k;
    vector<int> hasCat(n);

    fl(i, n)
    {
        cin >> hasCat[i];
    }
    vector<vector<int>> adj(n);
    fl(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    queue<cutenode> q;
    q.push({0, hasCat[0]});

    vector<bool> vis(n, 0);

    int ans = 0;

    while (!q.empty())
    {
        auto fr = q.front();
        q.pop();
        vis[fr.first] = 1;

        bool isLeafnode = true;

        for (auto i : adj[fr.first])
        {
            if (!vis[i])
            {
                isLeafnode = false;
            }
            if (!vis[i] and (fr.second + hasCat[i]) <= k)
            {
                q.push({i, hasCat[i] ? fr.second + hasCat[i] : 0});
            }
        }

        if (isLeafnode)
        {
            ans++;
        }
    }

    cout << ans << endl;
}

void r7()
{
    int n, m;
    cin >> n >> m;

    vector<int> v(m + 1, 0ll);
    fl(i, n)
    {
        int e;
        cin >> e;
        v[e]++;
    }

    int ans = 0;
    int total = accumulate(all(v), 0ll);

    fl(i, m + 1)
    {
        ans += 1ll * v[i] * (total - v[i]);
    }

    cout << ans / 2 << endl;
}

void r8()
{
    int n, m, k, s;
    cin >> n >> m >> k >> s;
    vector<pair<int, int>> a(n), b(n);
    fl(i, n)
    {
        cin >> a[i].first;
    }
    fl(i, n)
    {
        cin >> b[i].first;
    }
    vector<pair<int, int>> typeD, typeP;
    int dtaken = -1, ptaken = -1;
    int daydtaken = -1, dayptaken = -1;

    fl(i, m)
    {
        int type, cost;
        cin >> type >> cost;
        if (type == 1)
            typeD.push_back({cost, i});
        else
            typeP.push_back({cost, i});
    }
    sort(all(typeD));
    sort(all(typeP));

    a[0].second = 0;
    b[0].second = 0;
    for (int i = 1; i < n; i++)
    {
        if (a[i].first >= a[i - 1].first)
        {
            a[i].first = a[i - 1].first;
            a[i].second = a[i - 1].second;
        }
        else
        {
            a[i].second = i;
        }
        if (b[i].first >= b[i - 1].first)
        {
            b[i].first = b[i - 1].first;
            b[i].second = b[i - 1].second;
        }
        else
        {
            b[i].second = i;
        }
    }

    for (int i = 1; i < typeD.size(); i++)
    {
        typeD[i].first += typeD[i - 1].first;
    }
    for (int i = 1; i < typeP.size(); i++)
    {
        typeP[i].first += typeP[i - 1].first;
    }

    int ans = n + 1;

    int dcount = typeD.size();
    int pcount = typeP.size();

    // mixture of both D and P
    if ((dcount + pcount) >= k)
    {
        int mind = INT_MAX, minp = INT_MIN;
        int low = 0, high = n - 1, mid;
        while (low <= high)
        {
            mid = (low + high) / 2;
            int mind = a[mid].first, minp = b[mid].first;
            bool possible = false;
            // j -> denotes number of toys of type dollars (D)
            fl(j, min(k + 1, dcount + 1))
            {
                int sumd = j == 0 ? 0 : typeD[j - 1].first;
                int requiredPcnt = k - j;
                if (requiredPcnt > pcount)
                    continue;
                int sump = (k - j == 0) ? 0 : typeP[k - j - 1].first;
                int reqmoney = sumd * mind + sump * minp;
                // cout << reqmoney << endl;
                if (reqmoney <= s)
                {
                    possible = true;
                    dtaken = j;
                    ptaken = requiredPcnt;
                    daydtaken = a[mid].second + 1;
                    dayptaken = b[mid].second + 1;
                    break;
                }
            }

            if (possible)
            {
                ans = min(ans, mid + 1);
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
    }

    if (ans == (n + 1))
    {
        ans = -1;
    }
    cout << ans << endl;

    if (ans != -1)
    {
        fl(i, dtaken)
        {
            cout << typeD[i].second + 1 << " " << daydtaken << endl;
        }
        fl(i, ptaken)
        {
            cout << typeP[i].second + 1 << " " << dayptaken << endl;
        }
    }
}

// 0-1 BFS
void bfs01()
{
    int n;
    // weighted adj list (node, weight (0-1))
    vector<vector<pair<int, int>>> adj(n);
    set<cutenode> st;
    int src = 0;
    st.insert({0, src});

    vector<int> dist(n, InF);

    while (!st.empty())
    {
        int v = st.begin()->second;
        st.erase(st.begin());
        for (auto edge : adj[v])
        {
            int u = edge.first;
            int w = edge.second;

            if (dist[v] + w < dist[u])
            {
                st.erase({dist[u], u});
                dist[u] = dist[v] + w;
                st.insert({dist[u], u});
            }
        }
    }

    // print the distance vector
    print_vector(dist);
}

void r9()
{
    sieve(1e5 + 2);
    vector<int> nums;
    int n = nums.size();
    map<int, int> suffix_map, prefix_map;
    for (auto i : nums)
    {
        if (isPrime[i])
        {
            ++suffix_map[i];
        }
    }
    int maxprimesum = 0, prefprimecnt = 0, suffixprimecnt = suffix_map.size();
    for (int i = 0; i < n - 1; i++)
    {
        if (isPrime[nums[i]])
        {
            if (prefix_map[nums[i]]++ == 0)
            {
                ++prefprimecnt;
            }
            if (--suffix_map[nums[i]] == 0)
            {
                suffix_map.erase(nums[i]);
                --suffixprimecnt;
            }
            maxprimesum = max(maxprimesum, prefprimecnt + suffixprimecnt);
        }
    }
}

void p1()
{
    int n;
    cin >> n;
    int ans = 0;
    vector<int> v(n);
    read_vector(v);

    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = i; j < n; j++)
        {
            sum += v[j];
            int avg = (sum) / (j - i + 1);
            ans = max(ans, avg);
        }
    }

    cout << ans << endl;
}

vector<int> ans;
bool possible = false;

void checkpossible(string &s, int i, set<int> &ind, bool cantake0 = true)
{
    if (possible)
    {
        return;
    }
    int n = s.size();

    if (i == n)
    {
        string curr = "";
        fl(i, n)
        {
            if (!ind.count(i))
            {
                curr += s[i];
            }
        }
        int p1 = 0, p2 = curr.size() - 1;
        bool ispal = true;
        while (p1 < p2)
        {
            if (curr[p1] != curr[p2])
            {
                ispal = false;
                break;
            }
            p1++, p2--;
        }
        if (ispal)
        {
            ans = vector<int>(ind.begin(), ind.end());
            possible = true;
        }
        return;
    }

    checkpossible(s, i + 1, ind, cantake0);

    if (s[i] == '1')
    {
        ind.insert(i);
        checkpossible(s, i + 1, ind, 0);
        ind.erase(i);
    }
    else if (cantake0)
    {
        ind.insert(i);
        checkpossible(s, i + 1, ind, 1);
        ind.erase(i);
    }
}

void p2()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    set<int> st;
    possible = false;
    // ans.clear();
    checkpossible(s, 0, st);

    if (possible)
    {
        cout << (int)ans.size() << endl;
        for (auto i : ans)
        {
            cout << i + 1 << " ";
        }
        cout << endl;
    }
    else
    {
        cout << -1 << endl;
    }
}

void p3()
{
    int x, y;
    cin >> x >> y;

    bitset<32 * sizeof(int)> bitx(x), bity(y);
    int f1, f2 = 0;

    for (int i = 32; i >= 0; i--)
    {
        if (bitx[i] == 1)
        {
            f1 = i;
            break;
        }
    }
    for (int i = 32; i >= 0; i--)
    {
        if (bity[i] == 1)
        {
            f2 = i;
            break;
        }
    }

    if (f2 > f1)
    {
        cout << -1 << endl;
        return;
    }

    vector<int> ans;

    if (bity[f1] == 0)
    {
        ans.push_back(1 << f1);
    }

    int num = 0;

    for (int i = f1 - 1; i >= 0; i--)
    {
        if (bitx[i] != bity[i])
        {
            num |= (1 << i);
        }
    }

    ans.push_back(num);

    sort(all(ans));

    int z = x;
    for (auto i : ans)
    {
        z ^= i;
    }

    if (z == y)
    {
        cout << ans.size() << endl;
        print_vector(ans);
    }
    else
    {
        cout << -1 << endl;
        return;
    }
}

map<pair<int, int>, int> queries;

int query(int type, int i, int n)
{
    if (i == 1 and type == 1)
    {
        return (n * (n + 1)) / 2;
    }

    if (queries.count({type, i}))
    {
        return queries[{type, i}];
    }

    cout << type << " " << i << " " << n << endl;
    fflush(stdout);

    int ans;
    cin >> ans;
    return queries[{type, i}] = ans;
}

void p4()
{
    queries.clear();

    int n;
    cin >> n;

    int low = 1, high = n, lval = 1, mid, rval;

    int finalsum;
    cout << 2 << " " << 1 << " " << n << endl;
    fflush(stdout);
    cin >> finalsum;

    int increment = finalsum - (n * (n + 1)) / 2;

    while (low <= high)
    {
        mid = (low + high) / 2;
        int orig = query(1, mid, n);
        int modified = query(2, mid, n);
        if (orig == modified)
        {
            low = mid + 1;
        }
        else
        {
            lval = max(lval, mid);
            high = mid - 1;
        }
    }

    rval = lval + increment - 1;

    cout << "! " << lval << " " << rval << endl;
    fflush(stdout);
}

void p5()
{
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    read_vector(v);

    vector<int> vis(n + 1, 1);
    vis[v[n - 1]] = 0;
    vis[v[n - 2]] = 0;

    for (int i = 1; i <= n and k > 0; i++)
    {
        if (vis[i])
        {
            cout << i << " ";
            v.push_back(i);
            k--;
        }
    }

    if (k == 2)
    {
        // we need 2 values
        int minpalindromes = INT_MAX;
        int res = -1;
        for (int i = 1; i <= n; i++)
        {
            // check all possible values with palindromic subarrays including last element
            v.push_back(i);

            v.pop_back();
        }
    }
    else if (k == 1)
    {
        int minpalindromes = INT_MAX;
        int res = -1;
        for (int i = 1; i <= n; i++)
        {
            // check all possible values with palindromic subarrays including last element
            v.push_back(i);

            v.pop_back();
        }
        cout << res << endl;
    }

    cout << endl;
}

int32_t main()
{

    int t = 1;
    cin >> t;

    while (t--)
    {
        p4();
    }

    khalaas
}