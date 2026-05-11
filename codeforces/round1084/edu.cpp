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

void s1()
{
    int n;
    cin >> n;

    string s;
    cin >> s;

    vector<int> mark(n + 1, 0);
    mark[0] = 1;
    int curr = 0, ans = 1;

    for (int i = 0; i < n; i++)
    {
        if (s[curr] == 'L')
        {
            curr--;
        }
        else
        {
            curr++;
        }
        if (!mark[curr])
        {
            ++ans;
            mark[curr] = 1;
        }
    }
    cout << ans << endl;
}

void s2()
{
    int n;
    cin >> n;
    vector<int> a(n);
    multiset<int, greater<int>> st;
    fl(i, n)
    {
        cin >> a[i];
        st.insert(a[i]);
    }

    int ans = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        int lastelem = *st.begin();
        if (a[i] == lastelem)
        {
            ++ans;
        }
        st.erase(st.find(a[i]));
    }

    cout << ans << endl;
}

void s3()
{
    int a, b, c, m;
    cin >> a >> b >> c >> m;

    int lcm_ab = lcm(a, b);
    int lcm_bc = lcm(b, c);
    int lcm_ac = lcm(a, c);
    int lcm_abc = lcm(a, lcm(b, c));

    int ptotal = m / a;
    int psingle = ptotal - ((m / lcm_ab) + (m / lcm_ac) - (m / lcm_abc));

    int p = 6ll * psingle;
    p += 2ll * (m / lcm_abc);
    p += 3ll * ((m / lcm_ab) + (m / lcm_ac) - 2ll * (m / lcm_abc));

    cout << p << ' ';

    ptotal = m / b;
    psingle = ptotal - ((m / lcm_ab) + (m / lcm_bc) - (m / lcm_abc));

    p = 6ll * psingle;
    p += 2ll * (m / lcm_abc);
    p += 3ll * ((m / lcm_ab) + (m / lcm_bc) - 2ll * (m / lcm_abc));

    cout << p << ' ';

    ptotal = m / c;
    psingle = ptotal - ((m / lcm_ac) + (m / lcm_bc) - (m / lcm_abc));

    p = 6ll * psingle;
    p += 2ll * (m / lcm_abc);
    p += 3ll * ((m / lcm_ac) + (m / lcm_bc) - 2ll * (m / lcm_abc));

    cout << p << ' ';
    cout << endl;
}

// Disjoint Set Union Template
// Author: Rashid Siddiqui
// Time: ~O(α(N)) per operation (almost constant)

class DSU
{
    vector<int> parent, rankv;

public:
    DSU(int n)
    {
        parent.resize(n);
        rankv.resize(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    // Find with Path Compression
    int findParent(int x)
    {
        if (parent[x] == x)
            return x;
        return parent[x] = findParent(parent[x]);
    }

    // Union by Rank
    void unionSet(int a, int b)
    {
        int pa = findParent(a);
        int pb = findParent(b);

        if (pa == pb)
            return;

        if (rankv[pa] < rankv[pb])
        {
            parent[pa] = pb;
        }
        else if (rankv[pb] < rankv[pa])
        {
            parent[pb] = pa;
        }
        else
        {
            parent[pb] = pa;
            rankv[pa]++;
        }
    }
};

void s4()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);

    fl(i, m)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> mark(n + 1, -1);
    int ans = 0;

    for (int s = 1; s <= n; ++s)
    {
        if (mark[s] != -1)
        {
            continue;
        }

        queue<int> q;
        q.push(s);
        mark[s] = 0;

        int cnt0 = 0, cnt1 = 0;
        bool check = true;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            if (mark[u] == 0)
            {
                ++cnt0;
            }
            else
            {
                ++cnt1;
            }

            for (int v : adj[u])
            {
                if (mark[v] == -1)
                {
                    mark[v] = mark[u] ^ 1;
                    q.push(v);
                }
                else if (mark[v] == mark[u])
                {
                    check = false;
                }
            }
        }
        if (check)
        {
            ans += max(cnt0, cnt1);
        }
    }

    cout << ans << endl;
}

string res;

pair<bool, string> helperfn(string curr, vector<int> remfreq, int remdigits)
{
    string t = "";
    while (true)
    {
        int sum = 0;
        for (char c : curr)
        {
            sum += c - '0';
        }

        string nxt = to_string(sum);
        t += nxt;

        vector<int> need(10, 0);
        for (char c : nxt)
        {
            need[c - '0']++;
        }

        for (int i = 0; i < 10; i++)
        {
            if (need[i] > remfreq[i])
            {
                return {false, ""};
            }
        }

        for (int i = 0; i < 10; i++)
        {
            remfreq[i] -= need[i];
            remdigits -= need[i];
        }

        if (sum <= 9)
        {
            break;
        }
        curr = nxt;
    }

    if (remdigits == 0)
    {
        return {true, t};
    }

    return {false, ""};
}

void helper(string &ans, vector<int> &remfreq, string &currnum, int remdigits)
{
    if (!res.empty())
        return;

    if (!currnum.empty())
    {
        auto [check, remainingStr] = helperfn(currnum, remfreq, remdigits);
        if (check)
        {
            res = ans + remainingStr;
            return;
        }
    }

    for (int i = 0; i < 10; i++)
    {
        if (remfreq[i] == 0)
        {
            continue;
        }

        if (currnum.empty() && i == 0)
        {
            continue;
        }

        remfreq[i]--;
        ans.push_back('0' + i);
        currnum.push_back('0' + i);

        helper(ans, remfreq, currnum, remdigits - 1);

        currnum.pop_back();
        ans.pop_back();
        remfreq[i]++;

        if (!res.empty())
        {
            return;
        }
    }
}

void s5()
{
    string s;
    cin >> s;

    res = "";
    vector<int> freq(10, 0);

    for (auto i : s)
    {
        ++freq[i - '0'];
    }

    int n = s.size();

    if (n == 1)
    {
        cout << s << endl;
        return;
    }
    string temp = "", ans = "";
    helper(ans, freq, temp, n);

    cout << res << endl;
}

void r1()
{
    int n, c, k;
    cin >> n >> c >> k;

    vector<int> v(n);
    read_vector(v);

    sort(all(v));

    while (k > 0)
    {
        int reqval = max(0ll, c - k);
        auto lb = lower_bound(all(v), reqval);
        if (lb != v.end())
        {
            if (c >= v[*lb])
            {
                c = c * 2ll;
                k -= (c - v[*lb]);
            }
            else
            {
                break;
            }
        }
        else
        {
            --lb;
            if (c >= v[*lb])
            {
                c = c + v[*lb] + k;
            }
            k = 0;
        }
    }

    cout << c << endl;
}

void r2()
{
    int n;
    cin >> n;
    vector<int> a(n);
    read_vector(a);
    fl(i, n - 1)
    {
        if (abs(a[i] - a[i + 1]) <= 1)
        {
            cout << 0 << endl;
            return;
        }
    }
    if (n <= 2)
    {
        cout << -1 << endl;
        return;
    }
    else
    {
        for (int i = 0; i < n - 1; i++)
        {
            int mini = min(a[i], a[i + 1]);
            int maxi = max(a[i], a[i + 1]);
            if ((i - 1) >= 0)
            {
                if (a[i - 1] >= mini && a[i - 1] <= maxi)
                {
                    cout << 1 << endl;
                    return;
                }
            }
            if ((i + 2) < n)
            {
                if (a[i + 2] >= mini && a[i + 2] <= maxi)
                {
                    cout << 1 << endl;
                    return;
                }
            }
        }
        cout << -1 << endl;
        return;
    }
}

void r3()
{
    int n;
    cin >> n;

    vector<int> a(n);
    read_vector(a);

    int ans = 0;

    for (int y = 0; y < n; y++)
    {
        for (int z = y + 1; z < n; z++)
        {
            int lo = 0, high = y - 1, mid, x = -1;
            while (lo <= high)
            {
                mid = lo + (high - lo) / 2;
                int sum = a[mid] + a[y] + a[z];
                if (sum > max(2 * a[z], a.back()))
                {
                    x = mid;
                    high = mid - 1;
                }
                else
                {
                    lo = mid + 1;
                }
            }
            if (x >= 0)
                ans += (y - x);
        }
    }

    cout << ans << endl;
}

void printedge(int u, int v)
{
    cout << u << ' ' << v << endl;
}

void findedges(int node, vector<vector<int>> &adj, bool direction, vector<bool> &vis)
{
    vis[node] = true;
    for (auto i : adj[node])
    {
        if (vis[i])
            continue;
        vis[i] = true;
        if (direction)
        {
            printedge(node, i);
        }
        else
        {
            printedge(i, node);
        }
        findedges(i, adj, !direction, vis);
    }
}

void r4()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    vector<int> degree(n + 1, 0);

    fl(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        ++degree[u];
        ++degree[v];
    }

    vector<bool> vis(n + 1, 0);

    int nodeWithDegree2 = -1;

    fl(i, n)
    {
        if (degree[i + 1] == 2)
        {
            nodeWithDegree2 = i + 1;
        }
    }

    if (nodeWithDegree2 == -1)
    {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";

    int u = adj[nodeWithDegree2].front(), v = adj[nodeWithDegree2].back();
    printedge(u, nodeWithDegree2);
    printedge(nodeWithDegree2, v);

    vis[nodeWithDegree2] = true;

    // recurse
    findedges(u, adj, 1, vis);
    findedges(v, adj, 0, vis);
}

bool isPossiblemex(int n, vector<int> &v, int mex, int k)
{
    int N = 2e5 + 3;
    vector<bool> pres(N, 0);
    int currmex = 0;

    for (auto i : v)
    {
        if (i < N)
            pres[i] = true;

        while (pres[currmex])
        {
            ++currmex;
        }

        if (currmex >= mex)
        {
            --k;
            if (k == 0)
                return true;
            currmex = 0;
            pres = vector<bool>(N, 0);
        }
    }
    return (k == 0);
}

void r5()
{
    int n, k;
    cin >> n >> k;

    vector<int> v(n);
    read_vector(v);

    int low = 0, high = 1e6, res = 0, mid;

    while (low <= high)
    {
        mid = low + (high - low) / 2;
        if (isPossiblemex(n, v, mid, k))
        {
            res = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    cout << res << endl;
}

void r6()
{
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    read_vector(a);
    read_vector(b);
    sort(all(a));
    sort(all(b));

    int res = 1ll * n * a.front() + accumulate(b.begin(), b.end(), 0ll);
    res = min(res, 1ll * n * b.front() + accumulate(a.begin(), a.end(), 0ll));

    cout << res << endl;
}

void r7()
{
    int q;
    cin >> q;

    priority_queue<int, vector<int>, greater<int>> trees;
    while (q--)
    {
        int type, h;
        cin >> type >> h;
        if (type == 1)
        {
            trees.push(h);
        }
        else
        {
            while (!trees.empty())
            {
                auto toph = trees.top();
                if (toph <= h)
                {
                    trees.pop();
                }
                else
                {
                    break;
                }
            }
        }
        int ans = trees.size();
        cout << ans << endl;
    }
}

void r8()
{
    int n;
    cin >> n;

    vector<vector<int>> actualdist(n + 1, vector<int>(n + 1, INT_MAX));
    vector<vector<pair<int, int>>> adj(n + 1);
    vector<vector<int>> edges;

    for (int i = 1; i <= n - 1; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            int w;
            cin >> w;
            edges.push_back({w, i, j});
            actualdist[i][j] = w;
        }
    }

    sort(all(edges));

    DSU dsu = DSU(n + 1);
    for (auto i : edges)
    {
        if (dsu.findParent(i[1]) != dsu.findParent(i[2]))
        {
            adj[i[1]].push_back({i[2], i[0]});
            adj[i[2]].push_back({i[1], i[0]});
            dsu.unionSet(i[1], i[2]);
        }
    }

    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INT_MAX));

    for (int i = 1; i < n; i++)
    {
        dist[i][i] = 0;
        queue<int> q;
        q.push(i);
        vector<bool> vis(n + 1, false);
        while (!q.empty())
        {
            auto node = q.front();
            q.pop();
            vis[node] = true;
            for (auto &[neighbor, w] : adj[node])
            {
                if (!vis[neighbor])
                {
                    dist[i][neighbor] = dist[i][node] + w;
                    q.push(neighbor);
                }
            }
        }

    }

    for (int i = 1; i <= n - 1; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            if (dist[i][j] != actualdist[i][j])
            {
                cout << "No\n";
                return;
            }
        }
        cout << endl;
    }

    cout << "Yes\n";
}

void r9(){  
    int n, k;
    cin>>n>>k;

    string s;
    cin>>s;

    bool islexsmaller=false;
    for(int i=0;i<n;i++){
        if(s[i]<s[n-i-1]){  
            islexsmaller=true;
        }
        else if(s[i] > s[n-i-1]){
            break;
        }
    }

    if(islexsmaller){
        yes;
    }
    else{
        bool allsame=true;
        fl(i, n-1){
            if(s[i]!=s[i+1]){
                allsame=false;
                break;
            }
        }

        if(allsame || k==0){
            no;
        }
        else{
            yes;
        }
    }
}

int32_t main()
{
    auto begin = std::chrono::high_resolution_clock::now();

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;

    while (t--)
    {
        r9();
    }
    // auto end = std::chrono::high_resolution_clock::now();
    // auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    // cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n";

    khalaas
}