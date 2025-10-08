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
#include <fstream> // For file handling
#include <cfloat>
#include <bitset>
#include <cassert>
#include <random>
#include <chrono>

using namespace std;
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

// using namespace __gnu_pbds;
// typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

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

// it returns the logarithm of n to the base k
// @param(long long n) the value
// @param(long long k) the base for the logarithm

int lognk(ll n, ll k)
{
    int ans = 0;
    if (k == 1)
    {
        // Logarithm base 1 is undefined, return special value
        return n - 1; // Subtracting one repeatedly in this case
    }

    int currnum = 1;
    while ((currnum * k) <= n)
    {
        if (currnum > n / k) // Prevent multiplication overflow
            break;
        currnum *= k;
        ans++;
    }
    return ans;
}

// vector<ll> primes, isPrime;
// bool calc = false;
// const ll MAXN = 1e7 + 2;

// void precompute()
// {
//     if (calc)
//         return;
//     calc = true;
//     isPrime.resize(MAXN, 1);
//     isPrime[0] = isPrime[1] = 0;
//     for (ll i = 2; i < MAXN; i++)
//     {
//         if (isPrime[i])
//         {
//             primes.push_back(i);
//             for (ll j = i * i; j < MAXN; j += i)
//             {
//                 isPrime[j] = 0;
//             }
//         }
//     }
// }

void solve1(int casenum, std::ifstream &inFile, std::ofstream &outFile)
{
    int n, k;
    inFile >> n >> k;

    vector<int> v(110, 0);

    fl(i, n)
    {
        int e;
        inFile >> e;
        v[e]++;
    }

    outFile << "Case #" << casenum << ": ";
    if (2ll * k < n)
    {
        outFile << "NO\n";
    }
    else
    {
        for (auto i : v)
        {
            if (i > 2)
            {
                outFile << "NO\n";
                return;
            }
        }
        outFile << "YES\n";
    }
}

void solve2(int casenum, std::ifstream &inFile, std::ofstream &outFile)
{
    int n, m;
    inFile >> n >> m;

    vector<string> v(n);

    fl(i, n)
    {
        inFile >> v[i];
    }

    bool hastree = false;
    for (auto i : v)
    {
        for (auto j : i)
        {
            if (j == '^')
            {
                hastree = true;
                break;
            }
        }
    }

    outFile << "Case #" << casenum << ": ";

    // no tree case
    if (!hastree)
    {
        outFile << "Possible\n";
        for (auto i : v)
        {
            outFile << i << endl;
        }
        return;
    }

    if (n == 1 || m == 1)
    {
        outFile << "Impossible\n";
        return;
    }

    outFile << "Possible\n";
    fl(i, n)
    {
        string s = string(m, '^');
        outFile << s << endl;
    }
}

vector<int> dx = {0, 0, 1, -1};
vector<int> dy = {1, -1, 0, 0};

void solve3(int casenum, std::ifstream &inFile, std::ofstream &outFile)
{
    int n, m;
    inFile >> n >> m;

    vector<string> v(n);

    fl(i, n)
    {
        inFile >> v[i];
    }

    vector<string> res = v;

    bool hastree = false;
    for (auto &i : res)
    {
        fl(j, m)
        {
            if (i[j] == '^')
            {
                hastree = true;
            }
        }
    }

    outFile << "Case #" << casenum << ": ";

    // no tree case
    if (!hastree)
    {
        outFile << "Possible\n";
        for (auto i : v)
        {
            outFile << i << endl;
        }
        return;
    }

    if (n == 1 || m == 1)
    {
        outFile << "Impossible\n";
        return;
    }

    bool poss = true;

    fl(i, n)
    {
        fl(j, m)
        {
            if (res[i][j] == '.')
            {
                // check 4 dirs
                int cnt = 0;
                for (int l = 0; l < 4; l++)
                {
                    int newx = i + dx[l], newy = j + dy[l];
                    if (newx >= 0 and newx < n and newy >= 0 and newy < m and res[newx][newy] != '#')
                    {
                        cnt++;
                    }
                }
                if (cnt >= 2)
                {
                    res[i][j] = '^';
                }
            }
        }
    }
    fl(i, n)
    {
        fl(j, m)
        {
            if (res[i][j] == '^')
            {
                // check 4 dirs
                int cnt = 0;
                for (int l = 0; l < 4; l++)
                {
                    int newx = i + dx[l], newy = j + dy[l];
                    if (newx >= 0 and newx < n and newy >= 0 and newy < m and res[newx][newy] != '#')
                    {
                        cnt++;
                    }
                }
                if (cnt < 2)
                {
                    poss = false;
                    break;
                }
            }
        }
    }

    if (poss)
    {
        outFile << "Possible\n";
        for (auto i : res)
        {
            outFile << i << endl;
        }
    }
    else
    {
        outFile << "Possible\n";
    }
}

void solve4(int casenum, std::ifstream &inFile, std::ofstream &outFile)
{
    int n;
    inFile >> n;
    string s;
    inFile >> s;
    char first = '.', second = '-';
    if (s[0] == '.')
    {
        swap(first, second);
    }
    outFile << "Case #" << casenum << ": \n";
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            outFile << first;
        }
        outFile << second << endl;
    }
}

void solve5(int casenum, std::ifstream &inFile, std::ofstream &outFile)
{
    int n;
    inFile >> n;

    string t;
    inFile >> t;

    int len = t.size();

    string s = string(5, '-');
    s += string(5, '.');

    set<string> st;
    st.insert(t);
    outFile << "Case #" << casenum << ": \n";

    do
    {
        string substr = s.substr(0, len);

        if (substr == t)
        {
            continue;
        }

        if (!st.count(s))
        {
            outFile << s << endl;
            n--;
            st.insert(s);
        }
        if (n == 1)
        {
            break;
        }
    } while (next_permutation(s.begin(), s.end()));
}

void solve6(int casenum, std::ifstream &inFile, std::ofstream &outFile)
{
    outFile << "Case #" << casenum << ": ";

    int n, k;
    inFile >> n >> k;

    vector<int> a(n), b(n);
    fl(i, n)
    {
        inFile >> a[i];
    }
    fl(i, n)
    {
        inFile >> b[i];
    }

    int pos = 0;

    fl(i, n)
    {
        if (b[i] == a[0])
        {
            pos = i + 1;
            break;
        }
    }

    int j = pos - 1;

    for (int i = 0; i < n; i++)
    {
        if (b[j] == a[i])
        {
            j++;
            if (j == n)
            {
                j = 0;
            }
        }
        else
        {
            outFile << "NO\n";
            return;
        }
    }

    if (k == 0)
    {
        if (pos == 1)
        {
            outFile << "YES\n";
        }
        else
        {
            outFile << "NO\n";
        }
        return;
    }

    pos = n - pos + 1;

    if (k <= pos)
    {
        outFile << "YES\n";
    }
    else
    {
        if (abs(k - pos) % 2 == 1)
        {
            outFile << "YES\n";
        }
        else
        {
            outFile << "NO\n";
        }
    }
}

void solve7(int casenum, std::ifstream &inFile, std::ofstream &outFile)
{
    outFile << "Case #" << casenum << ": ";

    int n, q;
    inFile >> n;

    vector<pll> trees(n);

    fl(i, n)
    {
        inFile >> trees[i].first >> trees[i].second;
    }

    inFile >> q;
    vector<pll> wells(q);

    fl(i, q)
    {
        inFile >> wells[i].first >> wells[i].second;
    }

    int sumwx = 0, sumwy = 0;
    int sumtx = 0, sumty = 0;
    int sumsqwx = 0, sumsqwy = 0;
    int sumsqtx = 0, sumsqty = 0;

    for (auto i : trees)
    {
        sumtx = mod_add(sumtx, i.first);
        sumty = mod_add(sumty, i.second);
        sumsqtx = mod_add(sumsqtx, i.first * 1ll * i.first);
        sumsqty = mod_add(sumsqty, i.second * 1ll * i.second);
    }

    for (auto i : wells)
    {
        sumwx = mod_add(sumwx, i.first);
        sumwy = mod_add(sumwy, i.second);
        sumsqwx = mod_add(sumsqwx, i.first * 1ll * i.first);
        sumsqwy = mod_add(sumsqwy, i.second * 1ll * i.second);
    }

    int ans = mod_add(mod_mul(n, mod_add(sumsqwx, sumsqwy)), mod_mul(q, mod_add(sumsqtx, sumsqty)));
    int tosub = mod_mul(sumtx, sumwx);
    tosub = mod_mul(tosub, 2ll);

    ans = mod_sub(ans, tosub);

    tosub = mod_mul(sumty, sumwy);
    tosub = mod_mul(tosub, 2ll);

    ans = mod_sub(ans, tosub);

    outFile << 1ll * ans << endl;
}

signed main()
{
    // precompute();
    // precompute_factorials(maxn);
    // std::string inputfile = "input.txt";
    std::string inputfile = "watering_well_chapter_2_input.txt";
    std::string outputfile = "output.txt";

    std::ifstream inFile(inputfile);

    if (!inFile.is_open())
    {
        std::cerr << "Error: Could not open the input file " + inputfile + "!" << endl;
        return 1;
    }
    std::ofstream outFile(outputfile);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open the output file." << endl;
        return 1;
    }

    ll t;
    inFile >> t;

    for (int i = 1; i <= t; i++)
        solve7(i, inFile, outFile);

    outFile.close();
    std::cout << "Output successfully written to " + outputfile << endl;
    return 0;
}