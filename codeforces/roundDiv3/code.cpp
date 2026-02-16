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
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> freq(26, 0ll);

    for (auto i : s)
    {
        if (i >= 'a' && i <= 'z')
        {
            freq[i - 'a']++;
        }
        else
        {
            freq[i - 'A']++;
        }
    }

    sort(all(freq));

    int ans = freq[24] + freq[25];
    cout << ans << endl;
}

void s2()
{
    int n;
    cin >> n;
    int sum = 0;

    fl(i, n)
    {
        int e;
        cin >> e;
        sum += e;
    }

    if (sum & 1)
    {
        cout << "No\n";
    }
    else
    {
        cout << "Yes\n";
    }
}

void s3()
{
    int n;
    cin >> n;

    vector<vector<int>> a(n, vector<int>(3));

    fl(i, n)
    {
        int e;
        cin >> e;
        a[i][0] = e;
    }

    int mindiff = INT_MAX, minindex = -1;
    fl(i, n)
    {
        int e;
        cin >> e;
        a[i][1] = e;
        a[i][2] = a[i][0] - a[i][1];
        if (a[i][2] < mindiff)
        {
            mindiff = a[i][2];
            minindex = i;
        }
    }

    int ans = 0;
    fl(i, n)
    {
        if (i != minindex)
            ans += a[i][0];
        else
            ans += a[i][1];
    }

    cout << ans << endl;
}

void s4()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    fl(i, n)
    {
        if (abs(v[i]) != abs(v[0]))
        {
            cout << "No\n";
            return;
        }
    }

    int turns = 0;

    for (int i = 0; i < n - 1; i++)
    {
        int prod = v[i] * v[i + 1];
        if (prod < 0)
            turns++;
    }

    if (turns <= 1)
    {
        cout << "Yes\n";
    }
    else
    {
        cout << "No\n";
    }
}

void s5()
{
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    read_vector(a);

    vector<int> t = a;
    sort(all(t));

    int mini = t.front();
    int maxi = t.back();

    if (k == 2)
    {
    }
    else
    {
        int freqmini = 0;
        int secmini;
        for (auto i : t)
        {
            if (i == mini)
            {
                ++freqmini;
            }
            else
            {
                secmini = i;
                break;
            }
        }

        if (freqmini > 2)
        {
            cout << maxi - mini << endl;
            return;
        }

        for (size_t i = 0; i < n; i++)
        {
            if (a[i] == maxi)
            {
                if (i == 0)
                {
                    if (a[i + 1] != mini)
                    {
                        cout << maxi - mini << endl;
                        return;
                    }
                }
                else if (i == n - 1)
                {
                    if (a[i - 1] != mini)
                    {
                        cout << maxi - mini << endl;
                        return;
                    }
                }
                else
                {
                    if (a[i + 1] != mini)
                    {
                        cout << maxi - mini << endl;
                        return;
                    }
                }
            }
        }
    }
}

void s6()
{
    int n;
    cin >> n;
    vector<int> ans(n, 0);
    vector<bool> mark(n + 1, 0);
    ans[n - 1] = n;
    mark[n] = 1;
    for (int i = n - 1; i >= 1; i--)
    {
        int f1 = abs(ans[i] + i), f2 = abs(ans[i] - i);
        if (f1 <= n && !mark[f1])
        {
            ans[i - 1] = f1;
            mark[f1] = true;
        }
        else if (f2 >= 1 && !mark[f2])
        {
            ans[i - 1] = f2;
            mark[f2] = true;
        }
    }

    print_vector(ans);
}

void s7()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<bool> cantake(n, true);
    int ans = 0;

    for (int i = 0; i < n; i++)
    {
        if (s[i] == '1')
        {
            ++ans;
            cantake[i] = false;
            if (i > 0)
            {
                cantake[i - 1] = false;
            }
            if (i < n - 1)
            {
                cantake[i + 1] = false;
            }
        }
    }

    int i = 0;
    while (i < n)
    {
        while (i < n && !cantake[i])
        {
            ++i;
        }
        int len = 0;
        while (i < n && cantake[i])
        {
            ++i;
            ++len;
        }
        ans += (len + 2) / 3;
    }

    cout << ans << endl;
}

void s8()
{
    int n;
    cin >> n;

    vector<int> a(n);
    read_vector(a);

    DSU dsu = DSU(n);

    vector<int> sorteda = a;
    sort(all(sorteda));

    map<int, int> revMapping;

    fl(i, n)
    {
        if (revMapping.count(sorteda[i]))
        {
            continue;
        }
        revMapping[sorteda[i]] = i;
    }

    fl(i, n)
    {
        if (a[i] != sorteda[i])
        {
            dsu.unionSets(revMapping[a[i]], revMapping[sorteda[i]]);
        }
    }

    map<int, vector<int>> components;

    fl(i, n)
    {
        components[dsu.getParent(revMapping[a[i]])].push_back(a[i]);
    }

    int k = -1;
    vector<int> t;

    for (auto &[parent, tree] : components)
    {
        int m = tree.size();
        if (m != 1)
        {
            fl(i, m)
            {
                t.push_back(tree[i]);
            }
        }
    }

    int m = t.size();
    sort(all(t));

    fl(i, m - 1)
    {
        k = max(k, abs(t[i + 1] - t[i]));
    }

    if (k == 0)
        k = -1;

    cout << k << endl;
}

void r1()
{
    int n;
    cin >> n;

    if (n % 9 == 0)
    {
        cout << 10 << endl;
    }
    else
    {
        cout << 0 << endl;
    }
}

void r2()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);

    int i = 0;
    while (i < n && v[i] == (n - i))
    {
        ++i;
    }

    int j = i;
    while (j < n && v[j] != (n - i))
    {
        ++j;
    }

    vector<int> temp;
    for (int k = i; k <= j; k++)
    {
        temp.push_back(v[k]);
    }

    reverse(all(temp));
    for (auto t : temp)
    {
        v[i++] = t;
    }

    print_vector(v);
}

void r3()
{
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    read_vector(a);
    read_vector(b);
    sort(all(a));

    for (int i = 1; i < n; i++)
    {
        b[i] += b[i - 1];
    }

    int maxscore = 0;

    for (int i = 0; i < n; i++)
    {
        int swords = n - i;
        int ub = upper_bound(b.begin(), b.end(), swords) - b.begin();
        maxscore = max(maxscore, ub * a[i]);
    }

    cout << maxscore << endl;
}

void r4()
{
    int n;
    cin >> n;
    vector<int> mincost(n + 1, INT_MAX);

    fl(i, n)
    {
        int e;
        cin >> e;
        mincost[e] = 1;
    }

    for (int i = 1; i <= n; i++)
    {
        if (mincost[i] != INT_MAX)
        {
            for (int j = i; j <= n; j += i)
            {
                mincost[j] = min(mincost[j], mincost[i] + mincost[j / i]);
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (mincost[i] == INT_MAX)
        {
            cout << -1 << ' ';
        }
        else
        {
            cout << mincost[i] << ' ';
        }
    }

    cout << endl;
}

void r5(){
    int n, k;
    cin>>n>>k;
    int total =0;
    fl(i, n){
        int c;cin>>c;
        if(c % k == 0)
        total+=c;
    }
    cout<<total<<endl;
}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // sieve(maxn);
    int t = 1;
    // cin >> t;

    while (t--)
    {
        r5();
    }

    khalaas
}