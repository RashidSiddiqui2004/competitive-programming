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

// bool a1(unsigned long long n)
// {
//     if (n <= 4)
//     {
//         return 1;
//     }

//     if (n & 1ll)
//     {
//         return 0;
//     }

//     int setbits = 0;
//     for (int i = 0; i < 64; i++)
//     {
//         if ((n & (1 << i)) != 0)
//         {
//             setbits++;
//             if (setbits == 2)
//             {
//                 break;
//             }
//         }
//     }

//     if (setbits == 1)
//     {
//         return 1;
//     }

//     if (((3 ^ n) + 1ll) == n)
//     {
//         return a1(n / 2);
//     }

//     return a1(n / 2) || a1((3 ^ n) + 1ll);
// }

unsigned int nextPowerOf2(unsigned int n)
{
    if (n == 0)
        return 1;

    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;

    return n + 1;
}

const int ulim = 1e6;
unordered_map<int, int> dp;

int a1(unsigned long long n)
{
    if (n == 1)
    {
        return 0;
    }
    if (n <= 3)
    {
        return 1;
    }

    if (dp.count(n))
    {
        return dp[n];
    }

    if (n & 1ll)
    {
        return dp[n] = ulim;
    }

    int setbits = 0;
    int lastsetbit = -1;

    for (int i = 0; i < 32; i++)
    {
        if ((n & (1ll << i)) != 0)
        {
            setbits++;
            lastsetbit = i;
            if (setbits == 2)
            {
                break;
            }
        }
    }

    if (setbits == 1)
    {
        return dp[n] = lastsetbit;
    }

    int val1 = a1(n / 2);

    if ((n & 2) != 0)
    {
        if (val1 == ulim)
        {
            return dp[n] = ulim;
        }
        return dp[n] = 1 + val1;
    }

    int nextpower = nextPowerOf2(n);
    int diff = nextpower - n;

    int val2 = ulim;

    if (diff % 4 == 0)
    {
        val2 = (diff / 4) + a1(nextpower);
    }

    return dp[n] = (min(val1, val2) == ulim) ? ulim : 1 + min(val1, val2);
}

void a2()
{
    int n;
    cin >> n;

    vector<int> v(n);
    read_vector(v);

    vector<vector<int>> positions(n + 1);

    fl(i, n)
    {
        positions[v[i]].push_back(i);
    }

    vector<int> ans;
    int start = 0;

    while (start < n)
    {
        int maximumIndex = start;
        int currentmex = 0;

        for (; currentmex <= n; currentmex++)
        {
            vector<int> myPositions = positions[currentmex];
            int index = lower_bound(myPositions.begin(), myPositions.end(), start) - myPositions.begin();
            // check if the element is not found
            if (index == myPositions.size())
            {
                myPositions.clear();
                positions[currentmex] = myPositions;
                break;
            }
            else
            {
                maximumIndex = max(maximumIndex, myPositions[index]);
                myPositions = vector<int>(myPositions.begin() + index, myPositions.end());
                positions[currentmex] = myPositions;
            }
        }

        start = maximumIndex + 1;
        ans.push_back(currentmex);
    }

    cout << ans.size() << endl;
    print_vector(ans);
}

void a3()
{
    // int n = 10;
    // vector<int> v = {0, 0, 2, 1, 1, 1, 0, 0, 1, 1};

    int n;
    cin >> n;

    vector<int> v(n);
    read_vector(v);

    vector<int> suffixmex(n);

    vector<bool> ismarked(n, 0);
    int currmex = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        ismarked[v[i]] = 1;
        while (ismarked[currmex])
        {
            currmex++;
        }
        suffixmex[i] = currmex;
    }

    vector<int> ans;
    int start = 0;

    while (start < n)
    {
        int requiredmex = suffixmex[start];
        int currentmex = 0;

        vector<bool> isPresent(n, 0);
        isPresent[v[start++]] = 1;
        while (isPresent[currentmex])
        {
            currentmex++;
        }

        for (; currentmex < requiredmex and start < n;)
        {
            isPresent[v[start++]] = 1;
            while (isPresent[currentmex])
            {
                currentmex++;
            }
        }
        ans.push_back(requiredmex);
    }

    cout << ans.size() << endl;
    print_vector(ans);
}

void a4()
{
    int n, k, q;
    cin >> n >> k >> q;

    vector<int> ans(n, 0);

    // {MIN, MEX}
    vector<pair<bool, bool>> constraint(n, {0, 0});

    fl(j, q)
    {
        int c, l, r;
        cin >> c >> l >> r;
        --l, --r;
        for (size_t i = l; i <= r; i++)
        {
            if (c == 1)
                constraint[i].first = 1;
            else
                constraint[i].second = 1;
        }
    }

    for (size_t i = 0; i < n; i++)
    {
        // both the constraints
        if (constraint[i].first && constraint[i].second)
        {
            ans[i] = k + 1;
        }
        // only MIN constraint
        else if (constraint[i].first)
        {
            ans[i] = k;
        }
        // only MEX constraint
        else if (constraint[i].second)
        {
            ans[i] = i % k;
        }
    }

    print_vector(ans);
}

void a5()
{
    int n;
    cin >> n;
    int neg1 = 0, zero = 0;

    fl(i, n)
    {
        int e;
        cin >> e;
        if (e == 0)
            zero++;
        else if (e == -1)
            neg1++;
    }

    int ans = zero + 2 * (neg1 & 1);
    cout << ans << endl;
}

void a6()
{
    int n, k;
    cin >> n >> k;

    vector<int> freq(n + 1, 0ll);

    fl(i, n)
    {
        int e;
        cin >> e;
        freq[e]++;
    }

    int ans = 0;

    for (size_t i = 0; i < k; i++)
    {
        if (freq[i] == 0)
        {
            ans++;
            freq[k] = max(0ll, freq[k] - 1);
        }
    }

    ans += freq[k];

    cout << ans << endl;
}

int solve7(vector<int> &v)
{
    int n = v.size();

    if (n == 0)
        return 0;

    int ans = 0;
    // odd length
    if (n & 1)
    {
        int medianIdx = n / 2;
        int medianVal = v[medianIdx];

        // Calculate distance for all elements relative to the median
        for (int i = 0; i < n; i++)
        {
            // The target value for index i is: medianVal + (i - medianIdx)
            ans += abs(v[i] - (medianVal + (i - medianIdx)));
        }
    }
    // even length
    else
    {
        // In even length, we typically use the left median: n/2 - 1
        int medianIdx = (n / 2) - 1;
        int medianVal = v[medianIdx];

        for (int i = 0; i < n; i++)
        {
            ans += abs(v[i] - (medianVal + (i - medianIdx)));
        }
    }
    return ans;
}

void a7()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> a, b;

    for (size_t i = 0; i < n; i++)
    {
        if (s[i] == 'a')
            a.push_back(i);
        else
            b.push_back(i);
    }

    int ans = min(solve7(a), solve7(b));

    cout << ans << endl;
}

int countAtMostK(int n, vector<int> &a, int K, int maxLen)
{
    map<int, int> freq;
    int res = 0;
    int left = 0;

    for (int right = 0; right < n; right++)
    {
        freq[a[right]]++;

        while ((int)freq.size() > K || right - left + 1 > maxLen)
        {
            freq[a[left]]--;
            if (freq[a[left]] == 0)
                freq.erase(a[left]);
            left++;
        }

        res += (right - left + 1);
    }
    return res;
}

void a8()
{
    int n, k, l, r;
    cin >> n >> k >> l >> r;

    vector<int> v(n);
    read_vector(v);

    int ans =
        (countAtMostK(n, v, k, r) - countAtMostK(n, v, k, l - 1)) - (countAtMostK(n, v, k - 1, r) - countAtMostK(n, v, k - 1, l - 1));

    cout << ans << endl;
}

void a9()
{
    map<int, int> xcord, ycord;

    int n;
    cin >> n;

    vector<pair<int, int>> monsters;
    fl(i, n)
    {
        int x, y;
        cin >> x >> y;

        monsters.push_back({x, y});
        xcord[x]++;
        ycord[y]++;
    }

    if (n == 1)
    {
        cout << 1 << endl;
        return;
    }

    int minCost = LLONG_MAX;

    fl(i, n)
    {
        int x = monsters[i].first, y = monsters[i].second;
        xcord[x]--;
        ycord[y]--;
        if (xcord[x] == 0)
        {
            xcord.erase(x);
        }
        if (ycord[y] == 0)
        {
            ycord.erase(y);
        }

        int xmin = xcord.begin()->first;
        int xmax = xcord.rbegin()->first;
        int ymin = ycord.begin()->first;
        int ymax = ycord.rbegin()->first;

        int xside = (xmax - xmin + 1);
        int yside = (ymax - ymin + 1);
        int currArea = xside * yside;
        if (currArea < n)
        {
            currArea = min((xside + 1) * yside, xside * (yside + 1));
        }
        minCost = min(minCost, currArea);
        xcord[x]++;
        ycord[y]++;
    }

    cout << minCost << endl;
}

void a10()
{
    int n;
    cin >> n;

    vector<int> a(n);
    read_vector(a);

    vector<vector<int>> adj(n);
    vector<int> degree(n, 0ll);

    fl(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }

    vector<int> leafnodes;

    fl(i, n)
    {
        if (degree[i] == 1)
        {
            leafnodes.push_back(i);
        }
    }
}

void s1()
{
    int n, t;
    cin >> n >> t;

    vector<int> a(2 * n);

    fl(i, n - 1)
    {
        int e;
        cin >> e;
        a[i + 1] = i + 1 + e;
    }

    vector<bool> vis(2 * n, false);
    queue<int> q;
    q.push(1);

    while (!q.empty() and !vis[t])
    {
        auto fr = q.front();
        q.pop();

        vis[fr] = true;

        if (!vis[a[fr]])
            q.push(a[fr]);
    }

    if (vis[t])
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

    vector<string> grid(n);
    read_vector(grid);

    DSU dsu = DSU(n);

    fl(i, n)
    {
        fl(j, n)
        {
            if (grid[i][j] == '1')
                dsu.unionSets(i, j);
        }
    }

    unordered_map<int, vector<int>> groups;

    fl(i, n)
    {
        groups[dsu.getParent(i)].push_back(i);
    }

    for (auto [id, grp] : groups)
    {
        vector<int> temp, pos;
        for (auto i : grp)
        {
            pos.push_back(i);
            temp.push_back(v[i]);
        }
        int m = grp.size();
        sort(all(temp));
        for (int i = 0; i < m; i++)
        {
            v[pos[i]] = temp[i];
        }
    }

    print_vector(v);
}

bool ispossibles3(vector<int> &v, int k, int mid)
{
    int n = v.size();
    vector<bool> mark(n + 1, 0);

    int i = 0, currmex = 0;
    while (i < n)
    {
        if (v[i] <= n)
            mark[v[i]] = 1;

        ++i;
        while (mark[currmex])
        {
            ++currmex;
        }
        if (currmex == mid)
        {
            currmex = 0;
            mark = vector<bool>(n + 1, 0);
            k--;
            if (k == 0)
            {
                return true;
            }
        }
    }

    return false;
}

void s3()
{
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    read_vector(a);

    int low = 0, high = 2e7, mid, ans;

    while (low <= high)
    {
        mid = (low + high) / 2;
        if (ispossibles3(a, k, mid))
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

void r1()
{
    string s;
    cin >> s;

    int yescnt = 0;
    for (auto i : s)
    {
        if (i == 'Y')
            yescnt++;
    }

    if (yescnt <= 1)
    {
        yes;
    }
    else
    {
        no;
    }
}

void r2()
{
    // susuusuuus
    // susussusus

    string s;
    cin >> s;

    int n = s.size();

    int ans = 0;
    if (s[0] != 's')
        ans++;
    if (s.back() != 's')
        ans++;
    s[0] = 's';
    s[n - 1] = 's';

    for (int i = 1; i < n; i++)
    {
        if (s[i] == 'u' and s[i + 1] != 's')
        {
            ++ans;
            s[i + 1] = 's';
        }
    }

    cout << ans << endl;
}

void r3()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    // vector<int> prefsum(n);
    // prefsum[0] = v[0];

    // for (size_t i = 1; i < n; i++)
    // {
    //     prefsum[i] = prefsum[i - 1] + v[i];
    // }

    // int ans = max(prefsum[n - 2], -(prefsum.back() - prefsum[0]));

    // for (int i = 1; i < n - 1; i++)
    // {
    //     ans = max(ans, prefsum[i - 1] - (prefsum.back() - prefsum[i]));
    // }

    int k = v[0];
    int maxres = 0;

    for (int i = 1; i < n; ++i)
    {
        int currval = v[i] + k;

        if (currval > maxres)
        {
            maxres = currval;
        }

        int cand = currval + v[i];
        if (cand > k)
        {
            k = cand;
        }
    }

    int sum = accumulate(all(v), 0ll);
    int ans = maxres + (v[0] - sum);
    cout << ans << '\n';
}

// vector<int> a = {2, 2, 4, 4, 4, 8, 4, 4};
// vector<int> a = {2, 2, 2, 2, 4, 8};
vector<int> a = {16, 8, 8, 4, 8, 16, 8, 4, 4};

int getSum(int l, int r)
{
    --l, --r;
    int sum = 0;
    for (size_t i = l; i <= r; i++)
    {
        sum += a[i];
    }
    return sum;
}

int query(int l, int r)
{
    cout << "? " << l << " " << r << endl;
    fflush(stdout);
    int ans;
    // ans = getSum(l, r);
    cin >> ans;
    return ans;
}

bool helper(int n, int k, int total)
{
    int m = 1ll << k;

    if ((4ll * total) % m != 0)
        return false;

    int s = (4ll * total) / m;
    int rhs = s - n;
    if (rhs < 0)
        return false;

    for (int x = 0; x <= n; x++)
    {
        int y = rhs - 3 * x;
        if (y < 0)
            continue;

        if (x + y <= n)
            return true;
    }

    return false;
}

void r4()
{
    int n;
    cin >> n;

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    unordered_set<int> used;

    int total = query(1, n);

    vector<int> valid(31, 1);

    for (int k = 0; k < 31; k++)
    {
        if (!helper(n, k, total))
            valid[k] = 0;
    }

    int MAX_Q = min(n, 300ll);

    for (int i = 0; i < MAX_Q; i++)
    {
        int pos;
        do
        {
            pos = uniform_int_distribution<int>(1, n)(rng);
        } while (used.count(pos));
        used.insert(pos);

        int v = query(pos, pos);
        int t = __builtin_ctz(v);

        vector<int> allow(31, 0);
        for (int d = 0; d <= 2; d++)
        {
            if (t + d < 31)
                allow[t + d] = 1;
        }

        for (int k = 0; k < 31; k++)
        {
            if (!allow[k])
                valid[k] = 0;
        }

        int cnt = 0;
        for (int k = 0; k < 31; k++)
            cnt += valid[k];

        if (cnt == 1)
            break;
    }

    int ans = 0;
    for (int k = 0; k < 31; k++)
    {
        if (valid[k])
        {
            ans = 1 << k;
            break;
        }
    }

    cout << "! " << ans << endl;
    fflush(stdout);
}

void r5()
{
    int d, f;
    cin >> d >> f;

    int l = ((d - f) / 7);
    int remdays = d - (f + 7 * l);
    int ans = 7 - remdays;

    if (ans == 0)
        ans = 7;

    cout << ans << endl;
}

void r6()
{
    // int n = 4, m = 2;
    // string s= "2025", t = "91";

    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;

    int ans = LLONG_MAX;

    for (int i = 0; (i + m) <= n; i++)
    {
        string substr = s.substr(i, m);
        int curr_cost = 0;
        for (int j = 0; j < m; j++)
        {
            int currdigit = t[j] - '0', reqdigit = substr[j] - '0';
            curr_cost += (currdigit <= reqdigit) ? (reqdigit - currdigit) : (10 - currdigit + reqdigit);
        }
        ans = min(ans, curr_cost);
    }

    cout << ans << endl;
}

void r7()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    stack<pair<int, int>> q;

    for (auto i : v)
    {
        if (q.empty())
        {
            q.push({i, 1});
            continue;
        }
        auto [elem, freq] = q.top();
        if (i == elem)
        {
            q.pop();
            q.push({elem, freq + 1});
        }
        else
        {
            q.push({i, 1});
        }
        while (!q.empty())
        {
            auto [__, freq] = q.top();
            if (freq == 4)
            {
                q.pop();
            }
            else
            {
                break;
            }
        }
    }
    int remelemscnt = 0;
    while (!q.empty())
    {
        auto [__, freq] = q.top();
        q.pop();
        remelemscnt += freq;
    }
    cout << remelemscnt << endl;
}

// EDU forces

void r8()
{
    string s;
    cin >> s;

    // int inf = 1e6;
    int ans = 0;

    int n = s.size();

    vector<string> majedarpattern = {"**", "><", "*<", ">*"};

    for (auto pattern : majedarpattern)
    {
        if (s.find(pattern) != string::npos)
        {
            cout << -1 << endl;
            return;
        }
    }

    int left = 0, right = 0;
    bool hasStar = 0;

    for (auto i : s)
    {
        if (i == '>')
            right++;
        else if (i == '<')
            left++;
        else
            hasStar = 1;
    }

    ans = max(left, right);
    if (hasStar)
        ++ans;

    cout << ans << endl;
}

void r9()
{
    int n;
    cin >> n;

    vector<int> v(n);
    read_vector(v);

    vector<int> prefsum(n + 1);
    prefsum[1] = v[0];

    for (size_t i = 2; i <= n; i++)
    {
        prefsum[i] = prefsum[i - 1] + v[i - 1];
    }

    // vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0ll));
    // // dp[i][j] = sum if we replace v[i...j]

    // int totalsum = prefsum.back();
    // int ans = totalsum;

    // for (int i = 1; i <= n; i++)
    // {
    //     for (int j = i; j <= n; j++)
    //     {
    //         dp[i][j] = totalsum - (prefsum[j] - prefsum[i - 1]) + (j - i + 1) * 1ll * (i + j);
    //         ans = max(ans, dp[i][j]);
    //     }
    // }

    vector<int> f(n + 1, 0ll);

    for (int i = 1; i <= n; i++)
    {
        f[i] = (i * 1ll * i) + i - prefsum[i];
    }

    // print_vector(f);

    vector<int> suffmaxf(n + 1, 0ll);
    suffmaxf[n] = f[n];

    for (int i = n - 1; i >= 0; i--)
    {
        suffmaxf[i] = max(suffmaxf[i + 1], f[i]);
    }

    int ans = prefsum.back();

    for (int i = 0; i <= n; i++)
    {
        ans = max(ans, prefsum.back() + suffmaxf[i] - f[i]);
    }

    cout << ans << endl;
}

void r10()
{
    int x, y, k;
    cin >> x >> y >> k;

    int low = 0, high = 1e12, mid, ans = -1;

    while (low <= high)
    {
        mid = (low + high) / 2;
        int p = mid;

        for (int i = 1; i <= x; i++)
        {
            p -= p / y;
            if (p == 0)
            {
                break;
            }
        }

        bool isvalid = p >= k;
        if (isvalid)
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

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;

    while (t--)
    {
        r10();
    }

    khalaas
}