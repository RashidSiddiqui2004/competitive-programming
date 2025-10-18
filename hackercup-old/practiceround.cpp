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

void solve1(int casenum, std::ifstream &inFile, std::ofstream &outFile)
{
    int n;
    inFile >> n;

    vector<int> a(n, 0), b(n, 0);

    fl(i, n)
    {
        inFile >> a[i];
    }

    fl(i, n)
    {
        inFile >> b[i];
    }

    outFile << "Case #" << casenum << ": ";

    bool ispossible = true;

    fl(i, n)
    {
        if (a[i] > b[i])
        {
            ispossible = false;
            break;
        }
    }

    if (!ispossible)
    {
        outFile << -1 << endl;
    }
    else
    {
        map<int, int> pos;
        fl(i, n)
        {
            pos[a[i]] = i;
        }

        vector<pair<int, int>> vp;

        fl(i, n)
        {
            vp.push_back({b[i], i});
        }

        sort(vp.begin(), vp.end());

        vector<pair<int, int>> opers;

        fl(i, n)
        {
            if (a[vp[i].second] != vp[i].first)
            {
                if (!pos.count(vp[i].first))
                {
                    ispossible = false;
                    break;
                }
                else
                {
                    opers.push_back({vp[i].second, pos[vp[i].first]});
                }
            }
        }

        if (ispossible == false)
        {
            outFile << -1 << endl;
            return;
        }

        int ans = opers.size();
        outFile << ans << endl;

        for (auto i : opers)
        {
            outFile << i.second + 1 << " " << i.first + 1 << endl;
        }
    }
}

vector<int> dx = {0, 0, 1, -1};
vector<int> dy = {1, -1, 0, 0};

void solve2(int casenum, std::ifstream &inFile, std::ofstream &outFile)
{
    outFile << "Case #" << casenum << ": ";
    // outFile << endl;

    int n, m, c;
    inFile >> n >> m >> c;

    vector<string> grid(n);

    fl(i, n)
    {
        inFile >> grid[i];
    }

    fl(i, c)
    {
        fl(j, m)
        {
            if (i >= n)
            {
                break;
            }
            if (grid[i][j] == '.')
            {
                grid[i][j] = '*';
            }
            if (grid[n - 1 - i][j] == '.')
            {
                grid[n - 1 - i][j] = '*';
            }
        }
        fl(j, n)
        {
            if (i >= m)
            {
                break;
            }
            if (grid[j][i] == '.')
            {
                grid[j][i] = '*';
            }
            if (grid[j][m - 1 - i] == '.')
            {
                grid[j][m - 1 - i] = '*';
            }
        }
    }

    fl(i, n)
    {
        fl(j, m)
        {
            if (grid[i][j] == '#')
            {
                queue<pair<int, int>> q;
                q.push({i, j});

                for (int k = 1; k <= c; k++)
                {
                    if (q.empty())
                    {
                        break;
                    }
                    int len = q.size();
                    while (len--)
                    {
                        auto pr = q.front();
                        auto x = pr.first, y = pr.second;
                        q.pop();

                        fl(p, 4)
                        {
                            int newx = x + dx[p], newy = y + dy[p];
                            if (newx >= 0 and newx < n and newy >= 0 and newy < m and grid[newx][newy] != '#')
                            {
                                grid[newx][newy] = '*';
                                q.push({newx, newy});
                            }
                        }
                    }
                }
            }
        }
    }

    // for (auto i : grid)
    // {
    //     outFile << i << endl;
    // }

    int maxsize = 0;

    fl(i, n)
    {
        fl(j, m)
        {
            if (grid[i][j] == '.')
            {
                int currsize = 0;
                queue<pair<int, int>> q;
                q.push({i, j});

                grid[i][j] = '*';

                while (!q.empty())
                {
                    int len = q.size();
                    currsize += len;

                    while (len--)
                    {
                        auto pr = q.front();
                        auto x = pr.first, y = pr.second;
                        q.pop();

                        fl(p, 4)
                        {
                            int newx = x + dx[p], newy = y + dy[p];
                            if (newx >= 0 and newx < n and newy >= 0 and newy < m and grid[newx][newy] == '.')
                            {
                                grid[newx][newy] = '*';
                                q.push({newx, newy});
                            }
                        }
                    }
                }

                maxsize = max(maxsize, currsize);
            }
        }
    }

    outFile << maxsize << endl;
}

void solve3(int casenum, std::ifstream &inFile, std::ofstream &outFile)
{
    outFile << "Case #" << casenum << ": ";

    int n;
    inFile >> n;

    vector<int> v(n);
    fl(i, n)
    {
        inFile >> v[i];
    }

    vector<pair<int, int>> vp;
    int i = 0;

    while (i < n)
    {
        int k = 1;
        int pos1 = 1, opers = 0;
        if (v[i] == 1)
        {
            while ((i + 1) < n and v[i + 1] == (1 + v[i]))
            {
                ++i;
                k++;
            }
        }
        else
        {
            int mini = v[i];
            while (i < n and v[i] != 1)
            {
                ++pos1;
                ++i;
            }
            k = v[i - 1];
            while (i < n and v[i] != (mini - 1))
            {
                ++i;
            }
            opers = mini - 1;
        }
        ++i;
        vp.push_back({k, opers});
    }

    reverse(all(vp));

    vector<pair<int, int>> t;
    int curropers = 0;

    for (auto i : vp)
    {
        // outFile << i.first << " " << i.second << endl;
        int len = i.first, requiredOpers = i.second;
        int actual = (requiredOpers - (curropers % len) + len) % len;
        for (int j = 1; j <= actual; j++)
        {
            t.push_back({2, -1});
        }
        curropers += actual;
        t.push_back({1, len});
    }

    reverse(t.begin(), t.end());

    int ans = t.size();
    outFile << ans << endl;

    for (auto i : t)
    {
        if (i.first == 1)
        {
            outFile << i.first << " " << i.second << endl;
        }
        else
        {
            outFile << i.first << endl;
        }
    }
}

string result = "";
int minCost = LLONG_MAX;
vector<int> totalfreq;

void helper(int n, int m, vector<int> &day1, vector<pair<int, int>> &vp,
            int pos, string &res)
{
    if (pos == m)
    {
        int currcost = 0ll;
        for (int i = 1; i <= n; i++)
        {
            currcost += (1ll * day1[i] * day1[i]);
            currcost += (1ll * (totalfreq[i] - day1[i]) * (totalfreq[i] - day1[i]));
        }
        if (currcost < minCost)
        {
            minCost = currcost;
            result = res;
        }
        return;
    }

    int c1 = vp[pos].first, c2 = vp[pos].second;
    ++day1[c1];
    ++day1[c2];

    res.push_back('1');
    helper(n, m, day1, vp, pos + 1, res);
    --day1[c1];
    --day1[c2];
    res.pop_back();
    res.push_back('2');
    helper(n, m, day1, vp, pos + 1, res);
}

void solve4(int casenum, std::ifstream &inFile, std::ofstream &outFile)
{
    result = "";
    minCost = LLONG_MAX;

    outFile << "Case #" << casenum << ": ";
    int n, m;
    inFile >> n >> m;
    vector<int> day1(n + 1, 0);
    vector<pair<int, int>> vp(m);
    totalfreq = vector<int>(n + 1, 0);

    fl(i, m)
    {
        inFile >> vp[i].first >> vp[i].second;
        ++totalfreq[vp[i].first];
        ++totalfreq[vp[i].second];
    }

    string s = "";
    helper(n, m, day1, vp, 0, s);
    outFile << minCost << " " << result << endl;
}

void solve5(int casenum, std::ifstream &inFile, std::ofstream &outFile)
{
    outFile << "Case #" << casenum << ": ";
    int s, d, k;
    inFile >> s >> d >> k;

    int buns = 2 * (s + d), cheese = s + 2 * d;

    if (buns >= (k + 1) and cheese >= k)
    {
        outFile << "YES\n";
    }
    else
    {
        outFile << "NO\n";
    }
}

void solve6(int casenum, std::ifstream &inFile, std::ofstream &outFile)
{
    outFile << "Case #" << casenum << ": ";
    int a, b, c;
    inFile >> a >> b >> c;

    int maxdouble = c / b;
    int remc = c - (maxdouble * b);
    int maxsingle = remc / a;
    int maxdeck = min(maxsingle + 2 * maxdouble, 2ll * (maxsingle + maxdouble) - 1);

    if (maxdouble > 0)
    {
        maxdouble--;
        remc += b;
        maxsingle = remc / a;
        maxdeck = max(maxdeck, min(maxsingle + 2 * maxdouble, 2ll * (maxsingle + maxdouble) - 1));
    }

    {
        maxsingle = c / a;
        remc = c - (maxsingle * a);
        maxdouble = remc / b;
        maxdeck = max(maxdeck, min(maxsingle + 2 * maxdouble, 2ll * (maxsingle + maxdouble) - 1));
    }

    maxdeck = max(maxdeck, 0ll);
    outFile << maxdeck << endl;
}

void solve7(int casenum, std::ifstream &inFile, std::ofstream &outFile)
{
    outFile << "Case #" << casenum << ": ";
    int a, b, c, d;
    inFile >> a >> b;
    inFile >> c >> d;

    if (a > b)
    {
        outFile << "YES\n";
    }
    else
    {
        outFile << "NO\n";
    }
}

void solve8(int casenum, std::ifstream &inFile, std::ofstream &outFile)
{
    outFile << "Case #" << casenum << ": ";
    int n;
    inFile >> n;

    int m = (2 * n) - 1;

    vector<int> v(m);

    fl(i, m)
    {
        inFile >> v[i];
    }

    sort(all(v));

    if (n == 1)
    {
        outFile << 1 << endl;
        return;
    }

    int lastelem = v[m - 1];
    int ans = INT_MAX;

    {
        int sum = v[1] + lastelem;
        int p1 = 1, p2 = m - 1;
        while (p1 < p2)
        {
            if (v[p1] + v[p2] != sum)
            {
                break;
            }
            ++p1, --p2;
        }
        if (p1 > p2 and sum > v[0])
        {
            ans = sum - v[0];
        }
    }

    {
        int sum = v[0] + v[m - 2];
        int p1 = 0, p2 = m - 2;
        while (p1 < p2)
        {
            if (v[p1] + v[p2] != sum)
            {
                break;
            }
            ++p1, --p2;
        }
        if (p1 > p2 and (sum > v[m - 1]))
        {
            ans = min(ans, sum - v[m - 1]);
        }
    }

    {
        int sum = v[0] + lastelem;
        int p1 = 0, p2 = m - 1;
        bool check = true;

        while (p1 <= p2)
        {
            if (p1 == p2)
            {
                if (check == false)
                {
                    break;
                }
                else
                {
                    if (sum > v[p1])
                        ans = min(ans, sum - v[p1]);
                }
            }

            if (v[p1] + v[p2] != sum)
            {
                if (check)
                {
                    check = false;
                    if (v[p1] + v[p2 - 1] == sum)
                    {
                        ans = min(ans, sum - v[p2]);
                        p2--;
                    }
                    else if (v[p1 + 1] + v[p2] == sum)
                    {
                        ans = min(ans, sum - v[p1]);
                        p1++;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            ++p1, --p2;
        }
    }

    if (ans == INT_MAX)
    {
        ans = -1;
    }
    else
    {
        v.push_back(ans);
        sort(all(v));
        int p1 = 0, p2 = (int)v.size() - 1;
        int currsum = v.front() + v.back();
        while (p1 < p2)
        {
            if (v[p1] + v[p2] != currsum)
            {
                ans = -1;
                break;
            }
            ++p1, --p2;
        }
    }

    outFile << ans << endl;
}

void solve9(int casenum, std::ifstream &inFile, std::ofstream &outFile)
{
    outFile << "Case #" << casenum << ": ";
    int p;
    inFile >> p;
    vector<int> freq(42, 0);
    for (auto i : primes)
    {
        if (p == 1)
            break;
        if (p % i == 0)
        {
            while (p > 1 and p % i == 0)
            {
                p /= i;
                freq[i]++;
            }
        }
        if (i == 41)
        {
            if (p > 1)
            {
                outFile << -1 << endl;
                return;
            }
            else
                break;
        }
    }
    vector<int> ans;

    for (int i = 2; i <= 41; i++)
    {
        int t = freq[i];
        while (t--)
        {
            ans.push_back(i);
        }
    }
    int sum = accumulate(all(ans), 0ll);

    if (sum <= 41)
    {
        priority_queue<int> pq;
        multiset<int> st;

        for (auto i : ans)
        {
            pq.push(i);
            st.insert(i);
        }

        while (!pq.empty())
        {
            int p1 = pq.top();
            pq.pop();

            if(freq[p1]==0){
                continue;
            }

            bool possible = false;
            int chosen = -1;
            int newsum = sum;

            for (auto it = st.rbegin(); it != st.rend(); ++it)
            {
                int val = *it; 

                if (val == p1 && freq[p1] == 1)
                    continue;

                int tmpSum = sum - (p1 + val) + (p1 * val);
                if (tmpSum <= 41)
                {
                    chosen = val;
                    newsum = tmpSum;
                    possible = true;
                    break;
                }
            }

            if (!possible)
                continue;

            pq.push(p1 * chosen);

            freq[p1]--;
            freq[chosen]--;
            freq[p1 * chosen]++;

            if (p1 == chosen)
            {
                auto it1 = st.find(p1);
                if (it1 != st.end())
                    st.erase(it1);
                it1 = st.find(p1);
                if (it1 != st.end())
                    st.erase(it1);
            }
            else
            {
                auto it1 = st.find(chosen);
                if (it1 != st.end())
                    st.erase(it1);

                auto it2 = st.find(p1);
                if (it2 != st.end())
                    st.erase(it2);
            }

            st.insert(p1 * chosen);
            sum = newsum;
        }

        vector<int> res;
        for (auto i : st)
        {
            res.push_back(i);
        }

        sum = accumulate(all(res), 0ll);

        if (sum > 41)
        {
            outFile << -1 << endl;
            return;
        }

        int diff = 41 - sum;

        while (diff--)
        {
            res.push_back(1);
        }

        sort(all(res));

        int m = (int)res.size();
        outFile << m << " ";

        fl(i, m)
        {
            outFile << res[i] << " ";
        }

        outFile << endl;
        return;
    }

    outFile << -1 << endl;
}

void s1(int casenum, std::ifstream &inFile, std::ofstream &outFile)
{
    
}

signed main()
{
    sieve(100);
    // precompute_factorials(maxn);
    std::string inputfile = "input.txt";
    // std::string inputfile = "sum_41_chapter_2_input.txt";
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
        s1(i, inFile, outFile);

    outFile.close();
    std::cout << "Output successfully written to " + outputfile << endl;
    return 0;
}