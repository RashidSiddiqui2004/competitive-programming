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

void s1()
{
    string s;
    cin >> s;
    sort(all(s));
    cout << s[0] << endl;
}

void s2()
{
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    read_vector(v);

    int i = 0;
    int ans = 0;
    while (i < n)
    {
        while (i < n and v[i] == 1)
        {
            ++i;
        }
        int hikelen = 0;
        while (i < n and v[i] == 0 and hikelen < k)
        {
            ++i;
            hikelen++;
        }
        if (hikelen == k)
        {
            ans++;
            ++i;
        }
    }
    cout << ans << endl;
}

void s3()
{
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    read_vector(v);
    int curr_level = v[k - 1];
    set<int> st(v.begin(), v.end());
    v = vector<int>(st.begin(), st.end());
    int waterlevel = 0;

    int i = 0;
    while (i < n and v[i] <= curr_level)
    {
        ++i;
    }

    if (i == n)
    {
        yes;
    }

    n = v.size();

    while (i < n)
    {
        int height_diff = v[i] - curr_level;
        waterlevel += height_diff;
        if ((waterlevel - 1) >= curr_level)
        {
            no;
        }
        curr_level = v[i++];
    }

    yes;
}

void s4()
{
    int n, k;
    cin >> n >> k;

    vector<vector<int>> v(n);

    fl(i, n)
    {
        int l, r, real;
        cin >> l >> r >> real;
        v[i] = {l, r, real};
    }

    sort(v.begin(), v.end(), [](vector<int> &v1, vector<int> &v2)
         {
        if(v1[1]==v2[1]){
            return v1[0]<=v2[0];
        }
        return v1[1] <= v2[1]; });

    vector<vector<int>> finalarr;
    finalarr.push_back(v[0]);

    for (int i = 1; i < n; i++)
    {
        auto last = finalarr.back();

        if (last[1] >= v[i][0] and last[1] <= v[i][1])
        {
            finalarr.pop_back();
            if (last[0] >= v[i][0] and last[0] <= v[i][1])
            {
                finalarr.push_back({v[i][0], v[i][1], max(last[2], v[i][2])});
            }
            else
            {
                finalarr.push_back({last[0], v[i][1], max(last[2], v[i][2])});
            }
        }
        else
        {
            finalarr.push_back(v[i]);
        }
    }

    ll ans = k;

    for (auto i : finalarr)
    {
        if (i[0] <= k and k <= i[1])
        {
            ans = max(ans, i[2]);
        }
        else if (k < i[0])
        {
            break;
        }
    }

    cout << ans << endl;
}

void s5()
{
    vector<int> myprimes = sieve(2 * 1e5 + 2);
    int prod = 1;
    for (int i = 0;; i++)
    {
        prod *= myprimes[i];
        if (prod > 2 * 1e5)
        {
            cout << i << " primes are required!";
            break;
        }
    }
}

void s6()
{
    int n;
    cin >> n;

    vector<int> p(n);
    read_vector(p);

    int adjlist[n][n];

    for (int i = 0; i < n; i++)
    {
        adjlist[i][i] = p[i];
    }

    priority_queue<vector<int>, vector<vector<int>>, greater<>> pq;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            adjlist[i][j] = gcd(adjlist[i][j - 1], p[j]);
            pq.push({adjlist[i][j], i, j});
        }
    }

    // MST algo (Prim's algo / Kruskal's algo)
    vector<int> visited(n, 0);

    ll mstCost = 0;

    while (!pq.empty())
    {
        vector<int> top = pq.top();
        int cost = top[0], u = top[1], v = top[2];
        pq.pop();

        if (!visited[u])
        {
        }
    }
}

void r1()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> bal;
    int balanceval = 0;
    for (auto i : s)
    {
        if (i == '(')
            balanceval++;
        else
            balanceval--;
        bal.push_back(balanceval);
    }
    if (balanceval != 0)
    {
        cout << -1 << endl;
    }
    else
    {
        int ans = 0;
        bool isfirstpos = bal[0] >= 0;
        int curr = 1;
        vector<int> v;
        for (int i = 0; i < n; i++)
        {
            v.push_back(curr);
            if (bal[i] == 0)
            {

                if (i + 1 < n)
                {
                    bool isnextpos = bal[i + 1] >= 0;
                    if (isfirstpos == isnextpos)
                        curr = 1;
                    else
                        curr = 2;
                }
            }
        }
        set<int> st(all(v));
        cout << st.size() << endl;
        print_vector(v);
    }
}

void r2()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    for (int i = 0; i < n - 1; i++)
    {
        if (i % 2 == 0)
        {
            if (v[i] < v[i + 1])
            {
                v[i + 1] = -abs(v[i + 1]);
            }
        }
        else
        {
            if (v[i] > v[i + 1])
            {
                v[i + 1] = abs(v[i + 1]);
            }
        }
    }

    print_vector(v);
}

void g1()
{
    int n, a, b;
    cin >> n >> a >> b;
    set<int> st;
    int ans = a;
    while (true)
    {
        a = (a + b) % n;
        ans = max(ans, a);
        if (!st.count(a))
        {
            st.insert(a);
        }
        else
            break;
    }
    cout << ans << endl;
}

void g2()
{
    int n;
    cin >> n;
    vector<string> v(n);
    read_vector(v);

    string ans = v[0];

    for (size_t i = 1; i < n; i++)
    {
        if (v[i] < ans)
        {
            ans = v[i] + ans;
        }
        else
        {
            ans += v[i];
        }
    }

    cout << ans << endl;
}

void g3()
{
    int n, k;
    cin >> n >> k;
    if (k == 1)
    {
        cout << n << endl;
    }
    else
    {
        int lim = k % 2 == 0 ? k - 2 : k - 1;
        for (int i = 0; i < lim; i++)
        {
            cout << n << " ";
        }
        if (k % 2 == 0)
        {
            int num1 = 0, num2 = 0;
            int i = 31;
            for (; i >= 0; i--)
            {
                if (((1 << i) & n) != 0)
                {
                    num1 += (1 << i);
                    i--;
                    break;
                }
            }
            // cout<<num1<<' ';
            // cout<<i<<' ';
            for (; i >= 0; i--)
            {
                if (((1 << i) & n) != 0)
                {
                    num2 += (1 << i);
                }
                else if ((num1 + (1 << i)) <= n)
                {
                    num2 += (1 << i);
                    num1 += (1 << i);
                }
            }
            cout << num1 << ' ' << num2 << endl;
        }
        else
        {
            cout << n << endl;
        }
    }
}

void g4()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);
    sort(all(v));

    int ans = 0;
    int maxnegodd = INT_MIN, minposodd = INT_MAX;
    for (auto i : v)
    {
        if (i > 0)
            ans += i;

        if (i & 1)
        {
            if (i > 0)
                minposodd = min(minposodd, i);
            else
                maxnegodd = i;
        }
    }

    if ((ans & 1) == 0)
    {
        ans -= min(-maxnegodd, minposodd);
    }

    cout << ans << endl;
}

#define INT_SIZE 9

// A Trie Node
struct TrieNode
{
    int value; // Only used in leaf nodes
    TrieNode *arr[2];
};

// Utility function to create a Trie node
TrieNode *newNode()
{
    TrieNode *temp = new TrieNode;
    temp->value = 0;
    temp->arr[0] = temp->arr[1] = nullptr;
    return temp;
}

// Inserts pre_xor to trie with given root
void insert(TrieNode *root, int pre_xor)
{
    TrieNode *temp = root;

    // Start from the msb, insert all bits of
    // pre_xor into Trie
    for (int i = INT_SIZE - 1; i >= 0; i--)
    {
        // Find current bit in given prefix
        bool val = pre_xor & (1 << i);

        // Create a new node if needed
        if (temp->arr[val] == nullptr)
            temp->arr[val] = newNode();

        temp = temp->arr[val];
    }

    // Store value at leaf node
    temp->value = pre_xor;
}

// Finds the maximum XOR ending with last number in
// prefix XOR 'pre_xor' and returns the XOR of this maximum
// with pre_xor which is maximum XOR ending with last element
// of pre_xor.
int query(TrieNode *root, int pre_xor)
{
    TrieNode *temp = root;
    for (int i = INT_SIZE - 1; i >= 0; i--)
    {
        // Find current bit in given prefix
        bool val = pre_xor & (1 << i);

        // Traverse Trie, first look for a
        // prefix that has opposite bit
        if (temp->arr[1 - val] != NULL)
            temp = temp->arr[1 - val];

        // If there is no prefix with opposite
        // bit, then look for same bit.
        else if (temp->arr[val] != NULL)
            temp = temp->arr[val];
    }
    return pre_xor ^ (temp->value);
}

// Returns maximum XOR value of a subarray in arr[0..n-1]
int maxSubarrayXOR(vector<int> &arr)
{
    int n = arr.size();

    TrieNode *root = newNode();
    insert(root, 0);

    int result = INT_MIN, pre_xor = 0;
    for (int i = 0; i < n; i++)
    {
        pre_xor = pre_xor ^ arr[i];
        insert(root, pre_xor);
        result = max(result, query(root, pre_xor));
    }
    return result;
}

void g5()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    int maxxor = maxSubarrayXOR(v);
    cout << maxxor << endl;
    // fl(i, n)
    // {
    //     int currxor = 0;
    //     for (size_t j = i; j < n; j++)
    //     {
    //         currxor ^= v[j];
    //         maxxor = max(maxxor, currxor);
    //     }
    // }
}

void g6()
{
    string s;
    cin >> s;

    int n = s.size();
    vector<int> nextsmallest(n);

    char smalleschar = 'z';
    int smallestpos = n;
    for (int i = n - 1; i >= 0; i--)
    {
        if (s[i] <= smalleschar)
        {
            smalleschar = s[i];
            smallestpos = i;
        }
        nextsmallest[i] = smallestpos;
    }

    string ans = "";

    set<int> st;
    for (auto i : nextsmallest)
    {
        st.insert(i);
    }
    for (auto i : st)
    {
        ans += s[i];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        if (!st.count(i))
            ans += s[i];
    }

    cout << ans << endl;
}

void t1()
{
    int a, b;
    cin >> a >> b;
    cout << (a * 12 + b) << endl;
}

void t2()
{
    int h, w, n;
    cin >> h >> w >> n;
    vector<vector<int>> grid(h, vector<int>(w));

    fl(i, h)
    {
        read_vector(grid[i]);
    }

    set<int> st;
    fl(i, n)
    {
        int e;
        cin >> e;
        st.insert(e);
    }

    int ans = 0;
    fl(i, h)
    {
        int cnt = 0;
        fl(j, w)
        {
            if (st.count(grid[i][j]))
                cnt++;
        }
        ans = max(ans, cnt);
    }
    cout << ans << endl;
}

using pii = pair<int, int>;

void t3()
{
    int n;
    cin >> n;

    vector<pair<int, int>> v(n);

    fl(i, n)
    {
        int w, p;
        cin >> w >> p;
        v.push_back({w, p});
    }

    sort(all(v), [](pii p1, pii p2)
         {
        if(p1.second == p2.second){
            return p1.first < p2.first;
        }
        return p1.first > p2.first; });

    int ans = 0;

    int p1 = 0, p2 = n - 1;
    int weight = 0, stregth = 0;

    while (p1 < p2)
    {
        stregth += v[p1++].second;
        while (p2 >= p1 and (weight + v[p2].first) <= stregth)
        {
            weight += v[p2--].first;
            ++ans;
        }
    }

    cout << ans << endl;
}

void t4()
{
    int n, m;
    cin >> n >> m;

    vector<int> a(n), b(m);
    read_vector(a);
    read_vector(b);

    sort(all(a));
    sort(all(b));

    ll mod = 998244353;
    ll sum = 0;

    vector<ll> prefb(m);
    prefb[0] = b[0] % mod;

    for (int i = 1; i < m; i++)
        prefb[i] = (prefb[i - 1] + b[i]) % mod;

    ll totalB = prefb.back();

    for (int x : a)
    {
        int it = upper_bound(all(b), x) - b.begin();

        ll prevcnt = it;
        ll nextcnt = m - it;

        ll prefsum = (it == 0 ? 0 : prefb[it - 1]);
        ll suffsum = (totalB - prefsum + mod) % mod;

        sum = (sum + (prevcnt * x) % mod - prefsum + mod) % mod;

        sum = (sum + suffsum - (nextcnt * x) % mod + mod) % mod;
    }

    cout << sum % mod << endl;
}

void t5()
{
    string year;
    cin >> year;

    int yearinint = 0;

    for (auto i : year)
    {
        yearinint *= 10;
        yearinint += (i - '0');
    }

    for (int x = 0; x <= 200; x++)
    {
        for (int y = 0; y <= 200; y++)
        {
            int result = (x + y) * (x + y);
            if (result == yearinint)
            {
                cout << x << ' ' << y << endl;
                return;
            }
        }
    }

    cout << -1 << endl;
}

void t6()
{
    int k, x;
    cin >> k >> x;

    int val = 1 + (k * x);
    cout << val << endl;
}

void t7()
{
    int n;
    cin >> n;

    vector<int> v(n);
    read_vector(v);

    int total = 0ll;

    for (int i = 0; i < n - 1; i++)
    {
        total += abs(v[i] - v[i + 1]);
    }

    int minans = total;

    for (int i = 0; i < n; i++)
    {
        int curr = total;
        if (i - 1 >= 0)
        {
            curr -= abs(v[i] - v[i - 1]);
        }
        if (i + 1 < n)
        {
            curr -= abs(v[i] - v[i + 1]);
        }
        if (i > 0 and i < n - 1)
        {
            curr += abs(v[i + 1] - v[i - 1]);
        }
        minans = min(minans, curr);
        // cout<<minans<<' ';
    }

    cout << minans << endl;
}

void t8()
{
    int n;
    cin >> n;

    vector<int> v(n);
    read_vector(v);

    sort(all(v));

    bool check = true;

    int diff = v[1] - v[0];

    if (diff >= v[0])
    {
        cout << diff << endl;
    }
    else
    {
        cout << v.front() << endl;
    }
}

void t9()
{
    int n;
    cin >> n;

    int maxi = (1 << n) - 1;
    vector<bool> used(maxi + 1, false);

    for (int i = n; i > 0; i--)
    {
        int fixpart = (1 << i) - 1;
        int rembits = n - i;
        for (int j = 0; j < (1 << rembits); j++)
        {
            int temp = fixpart + (j << i);
            if (!used[temp])
            {
                cout << temp << ' ';
                used[temp] = 1;
            }
        }
    }

    for (int i = 0; i <= maxi; i++)
    {
        if (!used[i])
            cout << i << ' ';
    }
    cout << endl;
}

void r3()
{
    
}

int32_t main()
{
    int t = 1;
    cin >> t;

    while (t--)
    {
        r3();
    }

    khalaas;

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