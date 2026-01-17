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

// finding the centroid of the tree

// =============== Centroid of the tree ==================
// A node of the tree is said to be centroid, if deleting this node,
// all the remaining connected components have size <= half of the
// original tree size before deletion of the centroid.

map<pair<int, int>, int> memo;
vector<bool> isNodeValid;

int dfs(vector<vector<int>> &adj, int node, int parent)
{
    // if (memo.count({node, parent}))
    // {
    //     return memo[{node, parent}];
    // }
    int ans = 1;
    for (auto i : adj[node])
    {
        if (i != parent and isNodeValid[i])
        {
            ans = max(ans, 1 + dfs(adj, i, node));
        }
    }
    return memo[{node, parent}] = ans;
}

int getCentroidOfTree(vector<vector<int>> &adj, vector<int> &degree, int numNodes)
{
    int inf = numNodes * 2;
    vector<int> minComponentSize(numNodes + 1, inf);

    int centroid = -1, maxSize = 0;

    for (int node = 1; node <= numNodes; node++)
    {
        if (!isNodeValid[node])
        {
            continue;
        }
        if (degree[node] <= 1)
        {
            minComponentSize[node] = 0;
        }
        for (auto neighbor : adj[node])
        {
            if (isNodeValid[neighbor])
            {
                minComponentSize[node] = min(minComponentSize[node], dfs(adj, neighbor, node));
            }
        }
        // cout << node << "-> " << degree[node] << ' ' << minComponentSize[node] << endl;
        if (minComponentSize[node] != inf && minComponentSize[node] > maxSize)
        {
            maxSize = minComponentSize[node];
            centroid = node;
        }
    }

    return centroid;
}

void removeNodes(vector<vector<int>> &adj, int node, int parent)
{
    isNodeValid[node] = false;
    for (auto neighbor : adj[node])
    {
        if (neighbor != parent && isNodeValid[neighbor])
        {
            removeNodes(adj, neighbor, node);
        }
    }
}

int query1(int k, vector<int> &nodes, int singleNode = -1)
{
    cout << "? 1 " << k << ' ';
    if (!nodes.empty())
    {
        for (auto i : nodes)
        {
            cout << i << ' ';
        }
    }
    else
    {
        cout << singleNode;
    }

    cout << endl;
    int ans;
    cin >> ans;
    return ans;
}

void query2(int u)
{
    cout << "? 2 " << u << endl;
}

void solve()
{
    int n;
    cin >> n;
    vector<int> degree(n + 1, 0ll);
    vector<vector<int>> adj(n + 1);

    fl(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }

    isNodeValid = vector<bool>(n + 1, true);

    int rootOfTreee = -1;

    while (true)
    {
        int currCentroid = getCentroidOfTree(adj, degree, n);
        // cout<<currCentroid<<endl;

        vector<int> neighbors;
        for (auto i : adj[currCentroid])
        {
            if (isNodeValid[i])
            {
                neighbors.push_back(i);
            }
        }

        if ((int)neighbors.size() == 0)
        {
            rootOfTreee = currCentroid;
            break;
        }

        sort(all(neighbors));
        // print_vector(neighbors);

        int sz = neighbors.size();

        // binary search to find parent of the centorid
        int low = 0, high = sz - 1, mid, ans = -1;

        while (low <= high)
        {
            mid = (low + high) / 2;
            vector<int> prefix = vector<int>(neighbors.begin(), neighbors.begin() + mid + 1);
            int prevsum = query1(mid + 1, prefix);
            query2(currCentroid);
            int newsum = query1(mid + 1, prefix);
            int assumeddiff = 2 * (mid + 1);

            if (abs(newsum - prevsum) != assumeddiff)
            {
                ans = mid;
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }

        // root is found if ans==-1
        if (ans == -1)
        {
            rootOfTreee = currCentroid;
            break;
        }
        else
        {
            // cout<<"parent: "<<neighbors[ans]<<' ';
            // remove non-essential nodes
            isNodeValid[currCentroid] = false;
            for (size_t i = 0; i < sz; i++)
            {
                if (i != ans)
                {
                    removeNodes(adj, neighbors[i], currCentroid);
                }
            }
        }
    }

    // cout << "Root node: " << rootOfTreee << endl;

    vector<bool> vis(n + 1, 0);
    vector<int> ans(n + 1, -1);

    vis[rootOfTreee] = 1;
    vector<int> emptyArr;

    vector<int> queryvalue(n + 1);
    queryvalue[rootOfTreee] = query1(1, emptyArr, rootOfTreee);

    ans[rootOfTreee] = queryvalue[rootOfTreee];

    queue<int> q;
    q.push(rootOfTreee);

    while (!q.empty())
    {
        auto fr = q.front();
        q.pop();
        for (auto j : adj[fr])
        {
            if (!vis[j])
            {
                vis[j] = 1;
                queryvalue[j] = query1(1, emptyArr, j);
                ans[j] = queryvalue[j] - queryvalue[fr];
                q.push(j);
            }
        }
    }

    cout << "! ";

    for (int i = 0; i < n; i++)
    {
        cout << ans[i + 1] << ' ';
    }

    cout << endl;
}

int32_t main()
{
    int t = 1;
    cin >> t;

    while (t--)
    {
        memo.clear();
        solve();
    }

    khalaas
}