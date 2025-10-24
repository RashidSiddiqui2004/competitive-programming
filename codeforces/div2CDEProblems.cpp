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
    int x, y;
    cin >> x >> y;
    int maximumMatchingSuffix = 0;
    for (int i = 0; i < 32; i++)
    {
        bool isithbitofxset = x & (1 << i);
        bool isithbitofyset = y & (1 << i);
        if (isithbitofxset == isithbitofyset)
        {
            maximumMatchingSuffix++;
        }
        else
        {
            break;
        }
    }
    cout << (1 << maximumMatchingSuffix) << endl;
}

void s2()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);
    int __lcm = 1;
    fl(i, n)
    {
        __lcm = lcm(__lcm, v[i]);
    }
    int suma = 0;
    fl(i, n)
    {
        suma += __lcm / v[i];
    }

    if (suma < __lcm)
    {
        fl(i, n)
        {
            cout << __lcm / v[i] << " ";
        }
        cout << endl;
    }
    else
    {
        cout << -1 << endl;
    }
}

void s3()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    char ch = s[0];

    int i = n - 1;
    int last = s[i] - '0';
    while (i >= 0 and (s[i] == (last + '0')))
        i--;

    int pivot = n - 1;
    while (i >= 0)
    {
        bool areequal = (i > k);
        last = !last;
        for (int j = 0; j < k and (i - j) >= 0; j++)
        {
            if (s[i - j] != (last + '0'))
            {
                areequal = false;
                break;
            }
        }
        if (!areequal)
        {
            pivot = i;
            break;
        }
        else
        {
            i -= k;
        }
    }

    string updateds = s;

    reverse(s.begin(), s.begin() + pivot + 1);
    updateds = s.substr(pivot + 1);
    updateds += s.substr(0, pivot + 1);

    // check if k-proper string
    i = 0;
    while (i < n)
    {
        ch = updateds[i];
        bool areequal = true;
        for (int j = 0; j < k; j++)
        {
            if ((updateds[i + j] != ch) || ((i + j + k < n) and updateds[i + j] == updateds[i + j + k]))
            {
                areequal = false;
                break;
            }
        }
        i += k;
        if (!areequal)
        {
            cout << -1 << endl;
            return;
        }
    }
    cout << pivot + 1 << endl;
}

void s4()
{
    int n;
    cin >> n;
    vector<int> p(n), q(n);
    read_vector(p);
    read_vector(q);
    int maxp = 0, maxq = 0;
    int maxpind = 0, maxqind = 0;

    int pow2mod[200000];
    int MOD = 1e9 + 7;
    pow2mod[0] = 1;

    for (int i = 1; i < 200000; i++)
    {
        pow2mod[i] = (pow2mod[i - 1] * 1ll * 2) % MOD;
    }

    fl(i, n)
    {
        if (p[i] > maxp)
        {
            maxp = p[i];
            maxpind = i;
        }
        if (q[i] > maxq)
        {
            maxq = q[i];
            maxqind = i;
        }

        int maxval = max(pow2mod[p[maxpind]] + pow2mod[q[i - maxpind]], pow2mod[q[maxqind]] + pow2mod[p[i - maxqind]]);
        cout << maxval << " ";
    }
    cout << endl;
}

void s5()
{
    int a, b;
    cin >> a >> b;

    if (a > b)
    {
        swap(a, b);
    }

    if (a % 2 == 0)
    {
        int newa = a / 2, newb = 2 * b;
        if (newa > newb)
            swap(newa, newb);
        if (a != newa || b != newb)
        {
            yes;
        }
    }
    if (b % 2 == 0)
    {
        int newa = b / 2, newb = 2 * a;
        if (newa > newb)
            swap(newa, newb);
        if (a != newa || b != newb)
        {
            yes;
        }
    }

    no;
}

void s6()
{
    int n;
    cin >> n;
    vector<int> v(n);
    read_vector(v);
    set<int> st(v.begin(), v.end());
    vector<int> uniq(st.begin(), st.end());
    int ans = 1;
    int m = uniq.size();
    fl(i, m)
    {
        auto it = upper_bound(all(uniq), uniq[i] + n - 1);
        --it;
        int j = it - uniq.begin();
        ans = max(ans, j - i + 1);
    }
    cout << ans << endl;
}

unordered_set<int> getevendivisors(int n)
{
    unordered_set<int> st;
    for (int i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            if (i % 2 == 0)
            {
                st.insert(i);
            }
            if ((n / i) % 2 == 0)
            {
                st.insert(n / i);
            }
        }
    }
    unordered_set<int> res;
    for (auto i : st)
    {
        res.insert(1 + (i / 2));
    }
    return res;
}

void s7()
{
    int n, x;
    cin >> n >> x;
    unordered_set<int> st = getevendivisors(n - x);
    unordered_set<int> st1 = getevendivisors(n + x - 2);

    for (auto i : st1)
    {
        st.insert(i);
    }
    int total = 0;
    for (auto i : st)
    {
        // if i < x -> x will never appear in its sequence
        if (i >= x)
        {
            total++;
        }
    }
    cout << total << endl;
}

void s8()
{
    int q;
    cin >> q;
    int bal_value = 0;
    vector<int> a, b;
    a.push_back(0);
    b.push_back(0);
    fl(i, q)
    {
        int type;
        cin >> type;
        if (type == 2)
        {
            a.pop_back();
            b.pop_back();
        }
        else
        {
            char ch;
            cin >> ch;
            if (ch == '(')
            {
                a.push_back(a.back() + 1);
            }
            else
            {
                a.push_back(a.back() - 1);
            }
            b.push_back(min(a.back(), b.back()));
        }
        if (a.back() == 0 and b.back() == 0)
        {
            cout << "Yes\n";
        }
        else
        {
            cout << "No\n";
        }
    }
}

void p1()
{
    int n, m;
    cin >> n >> m;
    cout << n * (m / 2) << endl;
}

void p2()
{
    int n;
    cin >> n;
    vector<pair<int, int>> v(n);
    fl(i, n)
    {
        cin >> v[i].first;
    }
    fl(i, n)
    {
        cin >> v[i].second;
    }
    sort(all(v));
    for (auto i : v)
    {
        cout << i.first << " ";
    }
    cout << endl;
    for (auto i : v)
    {
        cout << i.second << " ";
    }
    cout << endl;
}

void t1()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '1')
        {
            bool ch = false;
            for (int j = max(0ll, i - k + 1); j < i; j++)
            {
                if (s[j] == '1')
                {
                    ch = true;
                    break;
                }
            }
            if (ch == false)
            {
                ans++;
            }
        }
    }

    cout << ans << endl;
}

void t2()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    fl(i, n)
    {
        cin >> a[i + 1];
    }

    int maxi = -1;

    fl(i, n)
    {
        maxi = max(maxi, a[i + 1]);
        if ((i + 1) % 2 == 0)
        {
            a[i + 1] = maxi;
        }
    }

    a[0] = INT_MAX;
    a.push_back(INT_MAX);

    int ans = 0;

    // for (auto i : a)
    // {
    //     cout << i << " ";
    // }
    // cout << endl;

    for (int i = 1; i <= n; i += 2)
    {
        int mini = min(a[i - 1], a[i + 1]);
        if (a[i] >= mini)
            ans += abs(a[i] - mini + 1);
    }

    cout << ans << endl;
}

void t3()
{
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    read_vector(a);
    read_vector(b);

    int ans = 2;
    sort(all(a));

    // ans=0
    map<int, int> p;
    for (auto i : a)
    {
        if (i != 1)
            p[i]++;
    }
    int mx = *max_element(all(a));
    for (auto i : p)
    {
        for (int j = 1;; j++)
        {
            int req = i.first * j;
            if (req > mx)
                break;
            if (p.count(req))
            {
                if (req == i.first and i.second > 1)
                {
                    ans = 0;
                    break;
                }
                else if (req != i.first)
                {
                    ans = 0;
                    break;
                }
            }
        }
        if (ans == 0)
            break;
    }

    if (ans != 0)
    {
        // ans=1
        // primes
        set<int> primesocc, st(all(a));
        for (auto num : a)
        {
            int i = num;

            for (auto j : primes)
            {
                if (i % j == 0)
                {
                    primesocc.insert(j);
                }
            }
        }
        for (auto i : primesocc)
        {
            for (int j = 1;; j++)
            {
                int req = i * j - 1;
                if (req > mx)
                    break;
                if (st.count(req))
                {
                    ans = 1;
                    break;
                }
            }
            if (ans == 1)
                break;
        }
    }

    cout << ans << endl;
}

void t4()
{
    ull a, b, r;
    cin >> a >> b >> r;

    if (a < b)
        swap(a, b);

    const int N = 63; // up to 2^63 > 1e18
    bitset<N> bita(a), bitb(b);

    int firstbit = -1;
    for (int i = N - 1; i >= 0; i--)
    {
        if (bita[i] != bitb[i])
        {
            firstbit = i;
            break;
        }
    }

    ull result = 0;

    if (firstbit != -1)
    {
        result += (1ULL << firstbit);
    }

    for (int i = firstbit - 1; i >= 0; i--)
    {
        ull mask = (1ULL << i);

        if (bita[i] == 1)
        {
            if (bitb[i] == 0)
            {
                if (r >= mask)
                {
                    r -= mask;
                    result -= mask;
                }
                else
                {
                    result += mask;
                }
            }
        }
        else
        {
            if (bitb[i] == 1)
            {
                result -= mask;
            }
        }
    }

    cout << result << "\n";
}

// wrong approach -> greedy fails
bool ispossible(int n, vector<int> &v, int maxSum)
{
    int blockedsum = 0ll;
    int i = 0;
    while (i < n)
    {
        int subarraysum = 0ll;
        while (i < n and subarraysum + v[i] <= maxSum)
        {
            subarraysum += v[i++];
        }
        if (i != n)
        {
            if (blockedsum + v[i] > maxSum)
            {
                return false;
            }
            blockedsum += v[i++];
        }
    }
    return true;
}

// right approrach -> DP based check
bool ispossibleDP(int n, const vector<int> &v, long long maxSum)
{
    if (v[0] > maxSum)
        return false;

    vector<long long> dp(n, LLONG_MAX);
    dp[0] = v[0];

    for (int i = 1; i < n; i++)
    {
        long long segmentSum = 0;
        for (int j = i; j >= 0; j--)
        {
            segmentSum += v[j];
            if (segmentSum > maxSum)
                break;

            long long prev = (j == 0) ? 0 : dp[j - 1];
            if (prev != LLONG_MAX && prev + segmentSum <= maxSum)
                dp[i] = min(dp[i], prev + segmentSum);
        }
    }

    return dp[n] <= maxSum;
}

void t5()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for (int &x : v)
        cin >> x;

    long long low = *max_element(v.begin(), v.end());
    long long high = accumulate(v.begin(), v.end(), 0LL);
    long long res = high;
    v.push_back(0);

    while (low <= high)
    {
        long long mid = (low + high) / 2;
        if (ispossibleDP(n, v, mid))
        {
            res = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    cout << res << endl;
}

char query(int index)
{
    cout << "? " << index << endl;
    char ch;
    cin >> ch;
    return ch;
    fflush(stdout);
}

void t6()
{
    int n;
    cin >> n;

    vector<int> v(n, 0);

    // query for all indices
    fl(i, n)
    {
        char ch;
        while ((ch = query(i + 1)) != '=')
        {
            v[i] += (ch=='<') ? -1 : 1;
        }
    }

    // take prefix sum
    for (int i = 1; i < n; i++)
    {
        v[i] += v[i-1];
    }
    
    // maintain sorted order according to values
    vector<pair<int,int>> vp;

    fl(i, n){
        vp.push_back({v[i], i});
    }
    sort(all(vp));

    // build answer from sorted array
    vector<int> ans(n);
    fl(i, n){
        ans[vp[i].second] = i+1; 
    }

    cout<<"! ";
    print_vector(ans);
    fflush(stdout);
}

int32_t main()
{
    sieve(2e5 + 1);
    int t = 1;
    cin >> t;

    while (t--)
    {
        t6();
    }

    return 0;
}