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
    vector<int> months = {1, 3, 5, 7, 9};
    vector<int> days = {7, 3, 5, 7, 9};

    int m, d;
    cin >> m >> d;

    fl(i, 5)
    {
        if (m == months[i] && d == days[i])
        {
            cout << "Yes";
            return;
        }
    }
    cout << "No";
}

void s2()
{
    int n, m;
    cin >> n >> m;

    vector<vector<char>> ans(n, vector<char>(m, '.'));

    for (int i = 0; i < n; i++)
    {
        ans[i][0] = '#';
        ans[i][m - 1] = '#';
    }

    for (int i = 0; i < m; i++)
    {
        ans[0][i] = '#';
        ans[n - 1][i] = '#';
    }

    for (auto i : ans)
    {
        for (auto j : i)
        {
            cout << j;
        }
        cout << endl;
    }
}

void s3()
{
    int n;
    cin >> n;
    vector<pair<int, int>> v(n);

    fl(i, n)
    {
        cin >> v[i].first >> v[i].second;
    }

    int m;
    cin >> m;

    vector<string> words(m);
    map<pair<int, char>, vector<int>> mapping;

    fl(i, m)
    {
        cin >> words[i];
        string s = words[i];
        int t = s.size();
        for (int j = 0; j < t; j++)
        {
            mapping[{j + 1, s[j]}].push_back(i);
        }
    }

    for (auto i : words)
    {
        if ((int)i.size() != n)
        {
            cout << "No\n";
            continue;
        }

        bool check = true;

        for (int j = 0; j < n; j++)
        {
            int len = v[j].first, pos = v[j].second;
            bool found = false;
            for (auto k : mapping[{pos, i[j]}])
            {
                if ((int)words[k].size() == len)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                check = false;
                break;
            }
        }
        if (check)
        {
            cout << "Yes\n";
        }
        else
        {
            cout << "No\n";
        }
    }
}

void s4()
{
    string s, t;
    cin >> s >> t;

    int n = s.size(), m = t.size();
    int ans = 0;

    fl(i, n)
    {
        int ptr = 0;
        for (int j = i; j < n; j++)
        {
            if (s[j] == t[ptr])
            {
                ++ptr;
                if (ptr == m)
                {
                    break;
                }
            }
            ++ans;
        }
    }

    cout << ans << endl;
}

void s5()
{
    int n, m;
    cin >> n >> m;

    vector<int> a(n), b(m);
    read_vector(a);
    read_vector(b);
    sort(all(b));
    int b1 = b.front(), b2 = b.back();

    a[0] = min({a.front(), b1 - a.front(), b2 - a.front()});

    auto check = [&]()
    {
        vector<int> ac = a;
        for (int i = 1; i < n; i++)
        {
            int mini = min({ac[i], b1 - ac[i], b2 - ac[i]});
            int maxi = max({ac[i], b1 - ac[i], b2 - ac[i]});
            if (mini >= ac[i - 1])
            {
                ac[i] = mini;
            }
            else if (maxi >= ac[i - 1])
            {
                ac[i] = maxi;
            }
            else
            {
                return false;
            }
        }

        return true;
    };

    if (check())
    {
        cout << "YES\n";
        return;
    }
    else
    {
        cout << "NO\n";
    }
}

void p1()
{
    int x;
    cin >> x;

    cout << x << endl;
}

void p2()
{
    vector<int> v(7);
    read_vector(v);

    sort(all(v));

    int sum = 0;

    fl(i, 6)
    {
        sum += (-v[i]);
    }

    sum += v.back();

    cout << sum << endl;
}

void p3()
{
    int n;
    cin >> n;

    vector<int> a(3 * n);

    int p = 3 * n - 1;
    int st = 1;
    fl(i, n)
    {
        a[i * 3] = p;
        a[i * 3 + 1] = p + 1;
        a[i * 3 + 2] = st++;
        p -= 2;
    }

    print_vector(a);
}

void p4()
{
    int n;
    cin >> n;

    vector<int> ans;

    vector<int> primes = sieve(1e5);

    int ptr = 0, st = primes[ptr++];
    int curr = st;
    while (n > 0)
    {
        while (curr * st <= 1e13)
        {
            ans.push_back(curr);
            --n;
            if (n == 0)
            {
                break;
            }
            curr = curr * st;
        }
        if (n == 0)
        {
            break;
        }
        st = primes[ptr++];
        curr *= st;
        ans.push_back(curr);
        curr = st * st;
        --n;
    }

    int m = ans.size();

    // for (int i = 1; i < m; i++)
    // {
    //     cout << gcd(ans[i], ans[i - 1]) << ' ';
    // }
    // cout<<endl;
    print_vector(ans);
}

// Binary Trie template
// Author: Rashid Siddiqui

#define INT_SIZE 32

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
    temp->arr[0] = temp->arr[1] = NULL;
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
        if (temp->arr[val] == NULL)
            temp->arr[val] = newNode();

        temp = temp->arr[val];
    }

    // Store value at leaf node
    temp->value = pre_xor;
}

// Finds the maximum XOR ending with last number
int query(TrieNode *root, int num)
{
    TrieNode *temp = root;
    for (int i = INT_SIZE - 1; i >= 0; i--)
    {
        // Find current bit in given number
        bool val = num & (1 << i);

        // Traverse Trie, first look for a
        // number that has opposite bit
        if (temp->arr[1 - val] != NULL)
            temp = temp->arr[1 - val];

        // If there is no number with opposite
        // bit, then look for same bit.
        else if (temp->arr[val] != NULL)
            temp = temp->arr[val];
    }
    return num ^ (temp->value);
}

void p5()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    TrieNode *root = newNode();
    int ans = 0;
    insert(root, v[0]);

    for (int i = 1; i < n; ++i)
    {
        ans = max(ans, query(root, v[i]));
        insert(root, v[i]);
    }

    cout << ans << endl;
}

void p6()
{
    int x, y;
    cin >> x >> y;

    int n = x + y;

    if (n % 2 == 0 && x == 0)
    {
        cout << "NO\n";
        return;
    }

    int len = 2 * x;
    len += (n & 1);

    if (len > n)
    {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";

    for (int i = 1; i < len; i++)
    {
        cout << i << ' ' << i + 1 << endl;
    }

    for (int i = len + 1; i <= n; i++)
    {
        cout << len << ' ' << i << endl;
    }
}

// DIV-2
// https://codeforces.com/contest/2118
void p7()
{
    int n, k;
    cin >> n >> k;
    fl(i, k)
    {
        cout << 1;
    }
    fl(i, n - k)
    {
        cout << 0;
    }
    cout << endl;
}

void p8()
{
    int n;
    cin >> n;

    cout << 1 + (2 * (n - 1)) << endl;
    cout << 1 << ' ' << 1 << ' ' << n << endl;
    for (int i = 1; i < n; i++)
    {
        cout << i + 1 << ' ' << 1 << ' ' << n - i << endl;
        cout << i + 1 << ' ' << n - i + 1 << ' ' << n << endl;
    }
}

// https://codeforces.com/contest/2118/problem/C
// Make it beautiful
void p9()
{
    ull n, k;
    cin >> n >> k;

    vector<ull> v(n);
    read_vector(v);

    int MAX_BITS = 64;

    for (int i = 0; i < MAX_BITS; i++)
    {
        ull reqvalue = 1ull << i;
        fl(j, n)
        {
            if (reqvalue > k)
            {
                break;
            }
            if ((v[j] & (1ull << i)) == 0)
            {
                v[j] += (1ull << i);
                k -= (1ull << i);
            }
        }
    }

    ull ans = 0;
    for (auto i : v)
    {
        for (int j = 0; j < MAX_BITS; j++)
        {
            if ((i & (1ull << j)) != 0)
            {
                ++ans;
            }
        }
    }

    cout << ans << endl;
}

// https://codeforces.com/contest/2118/problem/D1
// RED LIGHT, GREEN LIGHT (1700 rated)
void p10()
{
    int n, k;
    cin >> n >> k;
    vector<int> p(n), d(n);
    read_vector(p);
    read_vector(d);
    int q;
    cin >> q;

    fl(i, q)
    {
        int position;
        cin >> position;

        int currTime = 0, direction = +1;
        set<pair<int, int>> collisions;
        bool willPass = true;
        while ((position >= p.front() || direction == +1) && (position <= p.back() || direction == -1))
        {
            int lb = lower_bound(all(p), position) - p.begin();
            if (p[lb] == position)
            {
                if (currTime % k == d[lb])
                {
                    if (collisions.count({lb, direction}))
                    {
                        willPass = false;
                        break;
                    }
                    collisions.insert({lb, direction});
                    direction *= -1;
                }
                position += direction;
                ++currTime;
            }
            else
            {
                if (direction == +1)
                {
                    int dist = p[lb] - position;
                    currTime += dist;
                    position = p[lb];
                }
                else
                {
                    if (lb == 0)
                    {
                        break;
                    }
                    --lb;
                    int dist = position - p[lb];
                    currTime += dist;
                    position = p[lb];
                }
            }
        }

        if (willPass)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }
}

// HARD version
void p11()
{
    int n, k;
    cin >> n >> k;
    vector<int> p(n), d(n);
    read_vector(p);
    read_vector(d);

    map<int, int> delays;
    map<int, vector<int>> mpl, mpr;

    fl(i, n)
    {
        delays[p[i]] = d[i];
        mpl[(d[i] + p[i]) % k].push_back(p[i]);
        mpr[(((d[i] - p[i]) % k) + k) % k].push_back(p[i]);
    }

    auto get_next_left = [&](int pos, int time)
    {
        int val = (time + pos) % k;
        auto &v = mpl[val];
        auto lb = lower_bound(all(v), pos);
        if (lb == v.begin())
            return -1ll;
        --lb;
        return *lb;
    };

    auto get_next_right = [&](int pos, int time)
    {
        int val = (((time - pos) % k) + k) % k;
        auto &v = mpr[val];
        auto lb = lower_bound(all(v), pos + 1);
        if (lb == v.end())
            return -1ll;
        return *lb;
    };

    int q;
    cin >> q;

    map<pll, bool> dp;

    fl(l, q)
    {
        int pos;
        cin >> pos;

        set<pll> states;

        bool willpass = false;
        int direction = 1, time = 0;

        if (delays.count(pos) && delays[pos] == 0)
        {
            direction ^= 1;
        }

        for (int i = 0; i < 2 * n; i++)
        {
            ll y = direction ? get_next_right(pos, time) : get_next_left(pos, time);
            if (y == -1)
            {
                willpass = true;
                break;
            }
            else
            {
                time += abs(y - pos);
                pos = y;
                direction ^= 1;
            }

            if (states.count({pos, direction}))
            {
                break;
            }

            states.insert({pos, direction});

            if (dp.count({pos, direction}))
            {
                willpass = dp[{pos, direction}];
                break;
            }
        }

        for (auto &x : states)
        {
            dp[x] = willpass;
        }

        cout << (willpass ? "YES\n" : "NO\n");
    }
}

void p12()
{
    int n, a, b;
    cin >> n >> a >> b;

    if (n & 1)
    {
        if (a <= b)
        {
            cout << (b & 1 ? "YES" : "NO");
        }
        else
        {
            cout << ((b & 1 && a & 1) ? "YES" : "NO");
        }
    }
    else
    {
        if (a <= b)
        {
            cout << ((b & 1) ? "NO" : "YES");
        }
        else
        {
            cout << ((b & 1 || a & 1) ? "NO" : "YES");
        }
    }
    cout << endl;
}

void p13()
{
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    read_vector(a);

    fl(i, n)
    {
        cout << (a[i] + (a[i] % (k + 1) * k)) << ' ';
    }
    cout << endl;
}

// https://codeforces.com/contest/2134/problem/C
void p14()
{
    int n;
    cin >> n;

    vector<int> v(n + 1);
    fl(i, n)
    {
        cin >> v[i + 1];
    }

    ull ans = 0;

    for (int i = 1; i < n; i++)
    {
        int evensum = 0, oddsum = 0;
        if (i & 1)
        {
            // odd index
            oddsum = v[i];
            evensum = v[i + 1];
        }
        else
        {
            // even index
            evensum = v[i];
            oddsum = v[i + 1];
        }
        if (evensum < oddsum)
        {
            int diff = oddsum - evensum;
            ans += diff;
            if (i & 1)
            {
                v[i] -= diff;
            }
            else
            {
                v[i + 1] -= diff;
            }
        }
        if ((i + 1) == n)
        {
            break;
        }

        if (i & 1)
        {
            // odd index
            oddsum = v[i];
            evensum = v[i + 1];
            oddsum += v[i + 2];
        }
        else
        {
            // even index
            evensum = v[i];
            oddsum = v[i + 1];
            evensum += v[i + 2];
        }

        if (evensum < oddsum)
        {
            int diff = oddsum - evensum;
            ans += diff;
            if (i & 1)
            {
                v[i + 2] -= diff;
            }
            else
            {
                v[i + 1] -= diff;
            }
        }
    }

    cout << ans << endl;
}

vector<int> hiddenpowers = {2, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2};
// vector<int> hiddenpowers = {2, 2, 2, 2};

void swapSimulator(int x)
{
    --x;
    swap(hiddenpowers[x], hiddenpowers[x + 1]);
}

int throwSimulator(int x)
{
    --x;
    int n = hiddenpowers.size();
    int jumps = 0;
    while (x < n)
    {
        x += hiddenpowers[x];
        ++jumps;
    }
    return jumps;
}

void swap(int x)
{
    cout << "swap " << x << endl;
    fflush(stdout);
    // swapSimulator(x);
}

int throwBall(int x)
{
    cout << "throw " << x << endl;
    fflush(stdout);
    int swaps;
    // swaps = throwSimulator(x);
    cin >> swaps;
    return swaps;
}

void p15()
{
    int n;
    cin >> n;

    // -1 denotes unknown
    vector<int> powers(n + 10, -1), jumps(n + 10, -1);
    jumps[n + 1] = 0;
    jumps[n + 2] = 0;

    for (int i = n; i >= 1; i--)
    {
        if (jumps[i + 1] == jumps[i + 2])
        {
            jumps[i] = jumps[i + 1] + 1;
        }
        else
        {
            jumps[i] = throwBall(i);
            if (jumps[i] == (jumps[i + 1] + 1))
            {
                powers[i] = 1;
            }
            else
            {
                powers[i] = 2;
            }
        }
    }

    for (int i = 1; i < n; i++)
    {
        // if unknown
        if (powers[i] == -1)
        {
            swap(i);
            int currjumps = throwBall(i + 1);
            if (currjumps == jumps[i + 2] + 1)
            {
                powers[i] = 1;
            }
            else
            {
                powers[i] = 2;
            }
        }
    }

    swap(n - 1);
    int currjumps = throwBall(n - 1);
    if (currjumps == jumps[n] + 1)
    {
        powers[n] = 1;
    }
    else
    {
        powers[n] = 2;
    }

    cout << "! ";
    fflush(stdout);

    fl(i, n)
    {
        cout << powers[i + 1] << ' ';
        fflush(stdout);
    }

    cout << '\n';
    fflush(stdout);
}

void p16()
{
    int n;
    cin >> n;
    set<int> st;

    fl(i, n)
    {
        int b;
        cin >> b;
        st.insert(b);
    }

    int ans = st.size();
    cout << ans << endl;
}

void fillChoices(vector<string> &v, string &s)
{
    int n = s.size();
    if (n == 3)
    {
        v.push_back(s);
        return;
    }
    s.push_back('0');
    fillChoices(v, s);
    s.pop_back();
    s.push_back('1');
    fillChoices(v, s);
    s.pop_back();
}

void p17()
{
    int x, y, z;
    cin >> x >> y >> z;
    int a1 = 0, b1 = 0, c1 = 0;

    vector<string> choices;
    string s;
    fillChoices(choices, s);

    for (int i = 0; i <= 30; i++)
    {
        // check all cases
        // 000, 001, 010, 100, ...

        bool check = false;
        for (auto &s : choices)
        {
            int a = s[0] - '0', b = s[1] - '0', c = s[2] - '0';

            // check for x
            bool allvalid = true;
            if ((x & (1 << i)) == 0 && (a && b) == 1)
            {
                allvalid = false;
            }
            else if ((x & (1 << i)) != 0 && (a && b) == 0)
            {
                allvalid = false;
            }

            // check for y
            if ((y & (1 << i)) == 0 && (b && c) == 1)
            {
                allvalid = false;
            }
            else if ((y & (1 << i)) != 0 && (b && c) == 0)
            {
                allvalid = false;
            }

            // check for z
            if ((z & (1 << i)) == 0 && (a && c) == 1)
            {
                allvalid = false;
            }
            else if ((z & (1 << i)) != 0 && (a && c) == 0)
            {
                allvalid = false;
            }
            if (allvalid)
            {
                a1 += a ? (1 << i) : 0;
                b1 += b ? (1 << i) : 0;
                c1 += c ? (1 << i) : 0;
                check = true;
                break;
            }
        }

        if (!check)
        {
            cout << "NO\n";
            return;
        }
    }

    // cout<<a1<<' '<<b1<<' '<<c1<<endl;
    cout << "YES\n";
}

void p18()
{
    int n;
    cin >> n;

    vector<int> v;
    map<int, int> freq;
    fl(i, n)
    {
        int len;
        cin >> len;
        freq[len]++;
        v.push_back(len);
    }

    sort(all(v));
    int len3 = 0, lenn = 0;

    for (int i = n - 3; i >= 0; i--)
    {
        if (v[i] != v[i + 1])
        {
            continue;
        }
        if ((v[i] + v[i + 1]) > v[i + 2])
        {
            len3 = v[i] + v[i + 1] + v[i + 2];
            break;
        }
    }

    vector<int> t;
    int sides = 0;
    
    for (auto &[len, f] : freq)
    {
        if (f & 1)
        {
            lenn += len * (f - 1);
            sides += (f - 1);
            t.push_back(len);
        }
        else
        {
            lenn += len * f;
            sides += f;
        }
    }

    int res = len3;

    int m = t.size();

    if (sides > 2)
    {
        for (int i = 0; i < m; i++)
        {
            if (t[i] < lenn)
            {
                res = max(res, lenn + t[i]);
            }
        }
    }

    for (int i = 0; i < m - 1; i++)
    {
        if (t[i + 1] < (lenn + t[i]))
        {
            res = max(res, lenn + t[i] + t[i + 1]);
        }
    }

    cout << res << endl;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;

    while (t--)
    {
        p18();
    }

    khalaas
}