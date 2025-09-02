#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <array>
#include <deque>
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
    vector<int> blacks;

public:
    DSU(int n)
    {
        parent.resize(n);
        size.resize(n, 1);
        blacks.resize(n, 0);
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
            blacks[rootX] += blacks[rootY];
            size[rootX] += size[rootY];
        }
    }

    int getParentSize(int x)
    {
        return size[getParent(x)];
    }

    bool hasBlack(int x)
    {
        return blacks[getParent(x)] > 0;
    }

    void updateBlack(int x, int val)
    {
        // cout<<x<<" "<<val<<endl;
        blacks[getParent(x)] += val;
    }
};

void sol1()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> edges;
    fl(i, n)
    {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        edges.push_back({u, v, w});
    }
    DSU dsu = DSU(n);
    sort(edges.begin(), edges.end(), [](const auto &v1, const auto &v2)
         {
        if(v1[2] == v2[2]) return true;
        return v1[2] < v2[2]; });
    vector<pll> queries(m);
    vector<int> ans(m, 0);
    fl(i, m)
    {
        cin >> queries[i].first;
        queries[i].second = i;
    }
    sort(queries.begin(), queries.end(), [](pll &p1, pll &p2)
         {
        if(p1.first == p2.first) return true;
        return p1.first < p2.first; });
    int ptr = 0;
    int currPairCount = 0;
    for (auto i : queries)
    {
        while (ptr < m and edges[ptr][2] <= i.first)
        {
            int u = edges[ptr][0], v = edges[ptr][1];
            dsu.unionSets(u, v);
            int p1 = dsu.getParent(u), p2 = dsu.getParent(v);
            currPairCount += ncr(dsu.getParentSize(p1), 2);
            currPairCount += ncr(dsu.getParentSize(p1), 2);
            currPairCount -= ncr(dsu.getParentSize(p1) - 1, 2);
            currPairCount -= ncr(dsu.getParentSize(p2) - 1, 2);
            ptr++;
        }
        ans[i.second] = currPairCount;
    }

    print_vector(ans);
}

void sol2()
{
    int n;
    cin >> n;
    if (n & 1)
    {
        cout << "Odd";
    }
    else
    {
        cout << "Even";
    }
    cout << endl;
}

void sol3()
{
    int n, h, m;
    cin >> n >> h >> m;
    vector<pll> v(n);
    fl(i, n)
    {
        int a, b;
        cin >> a >> b;
        v[i] = {a, b};
    }
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    ll ans = 0;
    dp[0][m] = h;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            if (dp[i - 1][j] != -1)
            {
                // case 1: fight monster i without using magic
                if (dp[i - 1][j] - v[i - 1].first >= 0)
                    dp[i][j] = max(dp[i][j], dp[i - 1][j] - v[i - 1].first);
            }
            // case 2: use magic
            if (j + v[i - 1].second <= m && dp[i - 1][j + v[i - 1].second] != -1)
            {
                dp[i][j] = max(dp[i][j], dp[i - 1][j + v[i - 1].second]);
            }

            if (dp[i][j] >= 0)
                ans = i;
        }
    }
    cout << ans << endl;
}

void sol3spaceoptimized()
{
    int n, h, m;
    cin >> n >> h >> m;
    vector<pll> v(n);
    fl(i, n)
    {
        int a, b;
        cin >> a >> b;
        v[i] = {a, b};
    }
    vector<int> dp(m + 1, -1);
    ll ans = 0;
    dp[m] = h;

    for (int i = 1; i <= n; i++)
    {
        vector<int> newdp(m + 1, -1);
        for (int j = 0; j <= m; j++)
        {
            if (dp[j] != -1 && dp[j] - v[i - 1].first >= 0)
                newdp[j] = max(newdp[j], dp[j] - v[i - 1].first);

            if (j + v[i - 1].second <= m && dp[j + v[i - 1].second] != -1)
                newdp[j] = max(newdp[j], dp[j + v[i - 1].second]);

            if (newdp[j] >= 0)
                ans = i;
        }
        dp.swap(newdp);
    }

    cout << ans << endl;
}

void sol4()
{
    int n;
    cin >> n;
    vector<ll> v(n);
    read_vector(v);
    int fr = v[0], last = v[n - 1];
    vector<ll> rem;
    for (size_t i = 1; i < n - 1; i++)
    {
        rem.push_back(v[i]);
    }
    sort(rem.begin(), rem.end());
    int i = -1, ans = 1;
    n = rem.size();
    ll next;
    while (i < n)
    {
        next = i == -1 ? fr * 2ll : rem[i] * 2ll;
        ++ans;
        ll pot = rem[i++];
        while (i < n and rem[i] <= next)
        {
            pot = rem[i];
            ++i;
        }
        if (pot == -1)
        {
            cout << -1 << endl;
            return;
        }
        if (i == n)
        {
            if (pot * 2ll >= last)
            {
                ans++;
                cout << ans << endl;
                return;
            }
        }
        cout << i << " ";
    }
    if (i != n || (last > next))
    {
        cout << -1 << endl;
    }
    else
    {
        cout << ans << endl;
    }
}

void s1()
{
    int r;
    cin >> r;
    cout << "Division ";
    if (r <= 1399)
    {
        cout << 4 << endl;
    }
    else if (r <= 1599)
    {
        cout << 3 << endl;
    }
    else if (r <= 1899)
    {
        cout << 2 << endl;
    }
    else
    {
        cout << 1 << endl;
    }
}

void s2()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);
    for (int i = 2; i < n; i += 2)
    {
        if ((v[i] % 2) != (v[i - 2] % 2))
        {
            cout << "NO\n";
            return;
        }
    }
    for (int i = 3; i < n; i += 2)
    {
        if ((v[i] % 2) != (v[i - 2] % 2))
        {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

void s3()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int i = 0;

    while (i < n)
    {
        while (i < n and s[i] == 'W')
            i++;
        char hasr = 0, hasb = 0;
        if (i != n)
        {
            while (i < n and s[i] != 'W')
            {
                if (s[i] == 'R')
                {
                    hasr = 1;
                }
                else
                {
                    hasb = 1;
                }
                i++;
            }
            if (hasr and hasb)
            {
                continue;
            }
            else
            {
                no;
            }
        }
    }
    yes
}

void s4()
{
    int n;
    cin >> n;
    vector<int> fra(n, 0), frb(n, 0);
    unordered_map<string, int> fr;
    vector<string> v;
    fl(i, n)
    {
        string a, b;
        cin >> a >> b;
        fra[a[0] - 'a']++;
        frb[a[1] - 'a']++;
        fr[a]++;
        fr[b]++;
        v.push_back(a);
    }
    int m = fr.size();
    int torem = (m * (m - 1)) / 2;

    // fl(i,n){
    //     int t=fr[]
    // }
}

void s5()
{
    int x, y;
    cin >> x >> y;

    int ans = (x + y) % 12;
    if (ans == 0)
        ans = 12;
    cout << ans;
}

void s6()
{
    int n, m;
    cin >> n >> m;
    vector<int> scores(n, 0);
    vector<string> v(n);

    fl(i, n)
    {
        cin >> v[i];
    }

    fl(i, m)
    {
        int ones = 0, zeros = 0;
        fl(j, n)
        {
            if (v[j][i] == '0')
                zeros++;
            else
                ones++;
        }
        if (ones == zeros)
        {
            fl(j, n)
            {
                scores[j]++;
            }
        }
        else if (ones < zeros)
        {
            fl(j, n)
            {
                if (v[j][i] == '1')
                    scores[j]++;
            }
        }
        else
        {
            fl(j, n)
            {
                if (v[j][i] == '0')
                    scores[j]++;
            }
        }
    }

    int maxi = *max_element(scores.begin(), scores.end());
    fl(i, n)
    {
        if (scores[i] == maxi)
        {
            cout << i + 1 << " ";
        }
    }
}

void s7()
{
    int n, q;
    cin >> n >> q;
    vector<int> a(n), b(n);
    read_vector(a);
    read_vector(b);
    int sum = 0;
    fl(i, n)
    {
        if (a[i] < b[i])
        {
            sum += a[i];
        }
        else
        {
            sum += b[i];
        }
    }
    fl(i, q)
    {
        char ch;
        cin >> ch;
        int x, y;
        cin >> x >> y;
        --x;
        if (ch == 'A')
        {
            sum -= min(a[x], b[x]);
            a[x] = y;
            sum += min(a[x], b[x]);
        }
        else
        {
            sum -= min(a[x], b[x]);
            b[x] = y;
            sum += min(a[x], b[x]);
        }
        cout << sum << endl;
    }
}

using pii = pair<int, int>;

vector<int> dx = {0, 0, 1, -1};
vector<int> dy = {1, -1, 0, 0};

void s8()
{
    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    fl(i, n)
    {
        cin >> grid[i];
    }

    queue<vector<int>> q;
    pii src, dest;

    fl(i, n)
    {
        fl(j, m)
        {
            if (grid[i][j] == 'S')
            {
                src = {i, j};
            }
            else if (grid[i][j] == 'G')
            {
                dest = {i, j};
            }
        }
    }

    vector<vector<int>> vis(n, vector<int>(m, 0));
    q.push({src.first, src.second, 1});
    vis[src.first][src.second] = 1;
    int time = 0;

    while (!q.empty())
    {
        int s = q.size();
        for (int i = 0; i < s; i++)
        {
            auto fr = q.front();
            q.pop();
            auto x = fr[0], y = fr[1], mark = fr[2];
            // cout<<x<<" "<<y<<" "<<mark<<endl;

            if (x == dest.first and y == dest.second)
            {
                cout << time;
                return;
            }
            for (int j = 0; j < 4; j++)
            {
                int newx = x + dx[j], newy = y + dy[j];
                if (newx >= 0 and newx < n and newy >= 0 and newy < m and
                    grid[newx][newy] != '#' and vis[newx][newy] < 10)
                {
                    if ((grid[newx][newy] == 'o') and mark)
                    {
                        q.push({newx, newy, mark});
                        vis[newx][newy]++;
                    }
                    else if ((grid[newx][newy] == 'x') and !mark)
                    {
                        q.push({newx, newy, mark});
                        vis[newx][newy]++;
                    }
                    else if (grid[newx][newy] == '?')
                    {
                        q.push({newx, newy, !mark});
                        vis[newx][newy]++;
                    }
                    else if (grid[newx][newy] == '.' || grid[newx][newy] == 'G')
                    {
                        q.push({newx, newy, mark});
                        vis[newx][newy]++;
                    }
                }
            }
        }
        time++;
    }

    cout << -1 << endl;
}

void s9()
{
    int n, q;
    cin >> n >> q;
    DSU dsu = DSU(n);
    vector<bool> isblack(n, 0);

    fl(i, q)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int x, y;
            cin >> x >> y;
            dsu.unionSets(x - 1, y - 1);
        }
        else if (type == 2)
        {
            int x;
            cin >> x;
            --x;
            if (!isblack[x])
            {
                dsu.updateBlack(x, 1);
            }
            else
            {
                dsu.updateBlack(x, -1);
            }
            isblack[x] = !isblack[x];
        }
        else
        {
            int x;
            cin >> x;
            --x;
            if (dsu.hasBlack(x))
            {
                cout << "Yes\n";
            }
            else
            {
                cout << "No\n";
            }
        }
    }
}

void s10()
{
    int n, a, b;
    cin >> n >> a >> b;

    if (n % 2 != b % 2)
    {
        no;
    }

    if (a <= b)
    {
        yes;
    }
    else
    {
        if (n % 2 != a % 2)
        {
            no;
        }
        else
        {
            yes;
        }
    }
}

void s11()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    long long sum = 0;
    int count = 0;
    priority_queue<int, vector<int>, greater<int>> pq; // min-heap

    for (int x : v)
    {
        sum += x;
        pq.push(x);
        count++;

        if (sum < 0)
        {
            // remove the worst element picked so far
            sum -= pq.top();
            pq.pop();
            count--;
        }
    }

    cout << count << endl;
}

void constellationSum()
{
    int n, x;
    cin >> n >> x;

    vector<int> v(n);
    read_vector(v);

    if (x >= 0)
    {
        ll maxsum = 0, currsum = 0;
        fl(i, n)
        {
            currsum += v[i];
            maxsum = max(maxsum, currsum);
            if (currsum < 0)
            {
                currsum = 0;
            }
        }
        if (x == 0 || x == 1)
        {
            cout << maxsum << endl;
        }
        else
        {
            cout << maxsum * 1ll * x << endl;
        }
    }
    else
    {
        // --- find minimum sum subarray using Kadane’s variant ---
        ll minsum = LLONG_MAX, currsum = 0;
        int start = 0, bestL = 0, bestR = 0;

        for (int i = 0; i < n; i++)
        {
            if (currsum > 0)
            {
                currsum = v[i];
                start = i;
            }
            else
            {
                currsum += v[i];
            }

            if (currsum < minsum)
            {
                minsum = currsum;
                bestL = start;
                bestR = i;
            }
        }

        if (minsum < 0)
        {
            // scale that subarray by x if minsum < 0
            for (int i = bestL; i <= bestR; i++)
            {
                v[i] = 1ll * v[i] * x;
            }
        }

        // --- now find maximum subarray sum  ---
        ll maxsum = 0, ans = 0;
        for (int i = 0; i < n; i++)
        {
            maxsum += v[i];
            ans = max(ans, maxsum);
            if (maxsum < 0)
                maxsum = 0;
        }

        cout << ans << endl;
    }
}

void sol7()
{
    int n;
    cin >> n;
    int maxSum = 0;
    int num = n;
    for (int i = 1; i <= n; i++)
    {
        maxSum += abs(num - i);
        num--;
    }
    cout << (maxSum / 2) + 1 << endl;
}

void sol8()
{
    int n, x;
    cin >> n >> x;
    int bits = __builtin_popcountll(x);
    if (n <= bits)
    {
        cout << x;
        return;
    }
    if ((n - bits) % 2 == 0)
        cout << x + n - bits;
    else
    {
        if (x > 1)
        {
            cout << x + n - bits + 1;
            return;
        }
        if (x == 1)
        {
            cout << n + 3;
            return;
        }
        else
        {
            if (n == 1)
            {
                cout << -1;
                return;
            }
            else
                cout << n + 3;
        }
    }
}

void sol9()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    vector<pii> vp;
    fl(i, n)
    {
        vp.push_back({v[i], i});
    }
    sort(vp.begin(), vp.end());
    reverse(all(vp));
    unordered_set<int> comp;
    int oper = 0, ind = 0;
    while (ind < n)
    {
        int currval = vp[ind].first;
        vector<int> rem;
        while (ind < n and vp[ind].first == currval)
        {
            if (comp.count(vp[ind].second - 1) || comp.count(vp[ind].second + 1))
            {
                comp.insert(vp[ind].second);
            }
            else
            {
                rem.push_back(ind);
            }
            ++ind;
        }
        for (auto i : rem)
        {
            if (comp.count(vp[ind].second - 1) || comp.count(vp[ind].second + 1))
            {
                comp.insert(vp[ind].second);
            }
            else
            {
                comp.insert(vp[ind].second);
                ++oper;
            }
        }
    }
    cout << oper << endl;
}

void sol10(){
    int n;
    cin>>n;
    vector<int> v(n);
    read_vector(v);
    int size=0;
    vector<pii> opers;
    for(int i=0;i<n;i++){
        if(v[i]!=0){
            size++;
        }else{
            if(i!=(n-1)){
                opers.push_back({size,size+1});
                size++;
                i++;
            }else{
                opers.push_back({size-1,size});
            }
        }
    }
    opers.push_back({0, size-1});

    cout<<opers.size()<<endl;
    for(auto &[i, j] : opers){
        cout<<i+1<<" "<<j+1<<endl;
    }
}

int32_t main()
{
    int t = 1;
    cin >> t;

    while (t--)
    {
        sol10();
    }

    return 0;
}