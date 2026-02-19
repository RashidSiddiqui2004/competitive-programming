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

    if (n < 10)
    {
        no;
    }
    else
    {
        for (int i = 0; i < 12; i++)
        {
            if (n % 11 == 0)
            {
                yes;
            }
            if (n < 111)
            {
                no;
            }
            n -= 111;
        }
        no;
    }
}

// https://codeforces.com/contest/1526/problem/C1
void s2()
{
    int n;
    cin >> n;
    vector<int> v(n + 1);
    fl(i, n)
    {
        cin >> v[i + 1];
    }

    // dp[i][k] = max health using first i potions taking k of them
    vvi dp(n + 1, vi(n + 1, INT_MIN));
    // Initially, health = 0
    dp[0][0] = 0;

    int res = 0ll;
    for (int i = 1; i <= n; i++)
    {
        for (int k = 0; k <= i; k++)
        {
            // skip ith potion
            dp[i][k] = dp[i - 1][k];

            // take the ith potion
            if (k > 0 && dp[i - 1][k - 1] != INT_MIN)
            {
                if (dp[i - 1][k - 1] + v[i] >= 0)
                {
                    dp[i][k] = max(dp[i][k], dp[i - 1][k - 1] + v[i]);
                }
            }
            if (i == n && dp[i][k] >= 0)
            {
                res = max(res, k);
            }
        }
    }

    cout << res << endl;
}

// https://codeforces.com/contest/1526/problem/C1
void s2SpaceoPtimized()
{
    int n;
    cin >> n;
    vector<int> v(n + 1);
    fl(i, n)
    {
        cin >> v[i + 1];
    }

    vi dp = vi(n + 1, INT_MIN);
    dp[0] = 0;

    int res = 0ll;
    for (int i = 1; i <= n; i++)
    {
        vi newdp = dp;
        for (int k = 0; k <= i; k++)
        {
            // skip ith potion
            newdp[k] = dp[k];

            // take the ith potion
            if (k > 0 && dp[k - 1] != INT_MIN)
            {
                if (dp[k - 1] + v[i] >= 0)
                {
                    newdp[k] = max(dp[k], dp[k - 1] + v[i]);
                }
            }
            if (i == n && newdp[k] >= 0)
            {
                res = max(res, k);
            }
        }
        dp = newdp;
    }

    cout << res << endl;
}

// https://codeforces.com/contest/1526/problem/C2
void s2TimeOptimized()
{
    int n;
    cin >> n;
    vector<int> v(n + 1);
    fl(i, n)
    {
        cin >> v[i + 1];
    }

    priority_queue<int, vector<int>, greater<>> pq;

    int currentHealth = 0ll;
    for (int i = 1; i <= n; i++)
    {
        currentHealth += v[i];
        pq.push(v[i]);

        if (currentHealth < 0)
        {
            currentHealth -= pq.top();
            pq.pop();
        }
    }

    cout << (int)pq.size() << endl;
}

void s3()
{
    // ABVJHBA
    // AB, BAB
    string s;
    cin >> s;

    if (s.find("AB") == string::npos || s.find("BA") == string::npos)
    {
        no;
    }

    int n = s.size();
    int i = 0;

    while (i < n - 1)
    {
        // first occurence of AB
        if (s[i] == 'A' && s[i + 1] == 'B')
        {
            i += 2;
            while (i < n - 1)
            {
                if (s[i] == 'B' && s[i + 1] == 'A')
                {
                    yes;
                }
                ++i;
            }
            break;
        }
        ++i;
    }

    i = 0;

    while (i < n - 1)
    {
        // first occurence of BA
        if (s[i] == 'B' && s[i + 1] == 'A')
        {
            i += 2;
            while (i < n - 1)
            {
                if (s[i] == 'A' && s[i + 1] == 'B')
                {
                    yes;
                }
                ++i;
            }
            break;
        }
        ++i;
    }

    no;
}

void s4()
{
    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    read_vector(v);

    sort(all(v));

    vector<int> cnt(n + 2, 0ll);

    fl(i, q)
    {
        int l, r;
        cin >> l >> r;
        cnt[l]++;
        cnt[r + 1]--;
    }

    vector<int> positiveCnts;

    for (int i = 1; i <= n; i++)
    {
        cnt[i] += cnt[i - 1];
        if (cnt[i] > 0)
        {
            positiveCnts.push_back(cnt[i]);
        }
    }

    sort(all(positiveCnts));

    int i = n - 1;

    int ans = 0;

    int m = positiveCnts.size();

    for (int j = m - 1; j >= 0; j--)
    {
        ans += (positiveCnts[j] * 1ll * v[i--]);
    }

    cout << ans << endl;
}

int strToint(string &s)
{
    int num = 0;
    for (auto i : s)
    {
        num *= 10;
        num += (i - '0');
    }
    return num;
}

int sumofdigits(int n)
{
    int sum = 0;
    while (n > 0)
    {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

void s5()
{
    int n, s;
    cin >> n >> s;

    int currsum = sumofdigits(n);
    if (currsum <= s)
    {
        cout << 0 << endl;
        return;
    }

    string curr = to_string(n);
    int m = curr.size(), ptr = m - 1;
    while (ptr >= 0)
    {
        curr[ptr--] = '0';
        while (ptr >= 0 && curr[ptr] == '9')
        {
            curr[ptr--] = '0';
        }

        if (ptr >= 0)
        {
            int dig = curr[ptr] - '0';
            curr[ptr] = '0' + (dig + 1);
            int currNumber = strToint(curr);
            if (sumofdigits(currNumber) <= s)
            {
                cout << currNumber - n << endl;
                return;
            }
        }
        else
        {
            curr = "1" + curr;
            int currNumber = strToint(curr);
            if (sumofdigits(currNumber) <= s)
            {
                cout << currNumber - n << endl;
                return;
            }
        }
    }
}

void s6()
{
    int n, k;
    cin >> n >> k;

    vector<int> x(n), y(n);
    read_vector(x);
    read_vector(y); // useless

    sort(all(x));

    vector<int> t(n);
    for (int i = n - 1; i >= 0; i--)
    {
        int ub = upper_bound(all(x), x[i] + k) - x.begin();
        --ub;
        int windowSize = ub - i + 1;
        t[i] = windowSize;
        if (i != (n - 1))
        {
            t[i] = max(t[i], t[i + 1]);
        }
    }

    int maxPoints = 0;
    for (int i = 0; i < n; i++)
    {
        int ub = upper_bound(all(x), x[i] + k) - x.begin();
        int windowSize1 = ub - i;
        int windowSize2 = (ub == n) ? 0 : t[ub];
        maxPoints = max(maxPoints, windowSize1 + windowSize2);
    }

    cout << maxPoints << endl;
}

int s7helper(vector<int> &a, vvi &dp, int pos = 0, int player = 0)
{
    int n = a.size();
    if (pos == n)
    {
        return 0;
    }
    int &memoval = dp[pos][player];
    if (memoval != -1)
    {
        return memoval;
    }
    int ans = INT_MAX;
    if (player == 0)
    {
        // 1 kill
        ans = min(ans, (a[pos] == 1) + s7helper(a, dp, pos + 1, !player));
        // 2 kills
        if (pos != (n - 1))
        {
            ans = min(ans, (a[pos] == 1) + (a[pos + 1] == 1) + s7helper(a, dp, pos + 2, !player));
        }
    }
    else
    {
        // 1 kill
        ans = min(ans, s7helper(a, dp, pos + 1, !player));
        // 2 kills
        if (pos != (n - 1))
        {
            ans = min(ans, s7helper(a, dp, pos + 2, !player));
        }
    }

    return memoval = ans;
}

void s7()
{
    int n;
    cin >> n;
    vector<int> a(n);
    read_vector(a);
    vvi dp(n, vi(2, -1));
    cout << s7helper(a, dp) << endl;
}

void s8()
{
    int n, q;
    cin >> n >> q;
    vector<int> v;
    set<int> st;
    multiset<int> gaps;

    for (int i = 0; i < n; i++)
    {
        int pt;
        cin >> pt;
        st.insert(pt);
        v.push_back(pt);
    }
    sort(all(v));
    for (int i = 0; i < n - 1; i++)
    {
        gaps.insert(v[i + 1] - v[i]);
    }
    // cout << "Gaps: ";
    // for (auto gap : gaps)
    // {
    //     cout << gap << ' ';
    // }
    // cout << endl;

    int ans = gaps.empty() ? 0 : *st.rbegin() - *st.begin() - *gaps.rbegin();
    cout << ans << '\n';
    fl(i, q)
    {
        int t, x;
        cin >> t >> x;
        if (t == 0)
        {
            auto it = st.lower_bound(x);
            ++it;
            int frontpile = -1, backpile = -1;
            if (it != st.end())
            {
                frontpile = *it;
                gaps.erase(gaps.find(abs(*it - x)));
            }
            --it;
            if (it != st.begin())
            {
                --it;
                backpile = *it;
                gaps.erase(gaps.find(abs(*it - x)));
            }
            if (frontpile != -1 && backpile != -1)
            {
                gaps.insert(frontpile - backpile);
            }

            // erase later
            st.erase(x);
        }
        else
        {
            if (st.empty())
            {
                st.insert(x);
            }
            else
            {
                auto it = st.lower_bound(x);
                if (it == st.end())
                {
                    gaps.insert(x - *st.rbegin());
                }
                else if (it == st.begin())
                {
                    gaps.insert(*st.begin() - x);
                }
                else
                {
                    int frontpile = *it, backpile = -1;
                    --it;
                    backpile = *it;
                    gaps.erase(gaps.find(frontpile - backpile));
                    gaps.insert(frontpile - x);
                    gaps.insert(x - backpile);
                }
            }

            st.insert(x);
        }
        // cout << "Gaps: ";
        // for (auto gap : gaps)
        // {
        //     cout << gap << ' ';
        // }
        // cout << endl;
        if (st.size() <= 2)
        {
            cout << 0 << '\n';
        }
        else
        {
            ans = *st.rbegin() - *st.begin() - *gaps.rbegin();
            cout << ans << '\n';
        }
    }
}

void s8CleanCode()
{
    int n, q;
    cin >> n >> q;

    set<int> st;
    multiset<int> gaps;

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        st.insert(x);
    }

    if (st.size() >= 2)
    {
        auto prev = st.begin();
        auto curr = prev;
        ++curr;

        while (curr != st.end())
        {
            gaps.insert(*curr - *prev);
            ++prev;
            ++curr;
        }
    }

    auto print_answer = [&]()
    {
        if (st.size() <= 2)
        {
            cout << 0 << '\n';
        }
        else
        {
            int ans = *st.rbegin() - *st.begin() - *gaps.rbegin();
            cout << ans << '\n';
        }
    };

    print_answer();

    while (q--)
    {
        int t, x;
        cin >> t >> x;

        if (t == 0) // DELETE
        {
            if (!st.count(x))
            {
                print_answer();
                continue;
            }

            if (st.size() == 1)
            {
                st.erase(x);
                gaps.clear();
                print_answer();
                continue;
            }

            auto it = st.find(x);

            int hasLeft = 0, hasRight = 0;
            int leftVal = 0, rightVal = 0;

            // check left neighbor
            if (it != st.begin())
            {
                auto left = it;
                --left;
                leftVal = *left;
                hasLeft = 1;

                auto git = gaps.find(x - leftVal);
                if (git != gaps.end())
                    gaps.erase(git);
            }

            // check right neighbor
            auto right = it;
            ++right;
            if (right != st.end())
            {
                rightVal = *right;
                hasRight = 1;

                auto git = gaps.find(rightVal - x);
                if (git != gaps.end())
                    gaps.erase(git);
            }

            // if both neighbors exist, connect them
            if (hasLeft && hasRight)
            {
                gaps.insert(rightVal - leftVal);
            }

            st.erase(it);
        }
        else // INSERT
        {
            if (st.count(x))
            {
                print_answer();
                continue;
            }

            if (st.empty())
            {
                st.insert(x);
                print_answer();
                continue;
            }

            auto it = st.lower_bound(x);

            int hasLeft = 0, hasRight = 0;
            int leftVal = 0, rightVal = 0;

            if (it != st.end())
            {
                rightVal = *it;
                hasRight = 1;
            }

            if (it != st.begin())
            {
                auto left = it;
                --left;
                leftVal = *left;
                hasLeft = 1;
            }

            // if x goes between two elements, remove old gap
            if (hasLeft && hasRight)
            {
                auto git = gaps.find(rightVal - leftVal);
                if (git != gaps.end())
                    gaps.erase(git);

                gaps.insert(x - leftVal);
                gaps.insert(rightVal - x);
            }
            else if (hasLeft)
            {
                gaps.insert(x - leftVal);
            }
            else if (hasRight)
            {
                gaps.insert(rightVal - x);
            }

            st.insert(x);
        }

        print_answer();
    }
}

void s9()
{
    int n;
    cin >> n;

    vector<int> v(n), unlockedpositions;
    read_vector(v);

    vector<int> values;

    fl(i, n)
    {
        int b;
        cin >> b;
        if (b == 0)
        {
            values.push_back(v[i]);
            unlockedpositions.push_back(i);
        }
    }

    sort(all(values));
    reverse(all(values));

    int m = values.size();
    for (int i = 0; i < m; i++)
    {
        v[unlockedpositions[i]] = values[i];
    }

    print_vector(v);
}

void s10()
{
    int n, a, b;
    cin >> n >> a >> b;
    if (a > b)
    {
        swap(a, b);
    }
    int diff = b - a;
    for (int i = n - 2; i >= 0; i--)
    {
        if (diff % (i + 1) == 0)
        {
            diff = diff / (i + 1);
            int remElems = (n - 2) - i;
            int minElem = a;
            while (remElems > 0 && a - diff > 0)
            {
                a -= diff;
                minElem = min(minElem, a);
                remElems--;
            }
            int maxElem = b + (diff * remElems);
            int start = minElem;
            while (start < maxElem)
            {
                cout << start << ' ';
                start += diff;
            }
            cout << maxElem << endl;
            return;
        }
    }
}

int numberOfSubsequences(string &s, char a, char b)
{
    int totalb = 0;
    for (auto i : s)
    {
        if (i == b)
            totalb++;
    }
    int countSequences = 0;
    for (auto i : s)
    {
        if (i == a)
        {
            countSequences += totalb;
        }
        if (i == b)
        {
            totalb--;
        }
    }
    return countSequences;
}

void s11()
{
    int n, k;
    cin >> n >> k;
    string s, t;
    cin >> s;
    cin >> t;
    char a = t.front(), b = t.back();

    int ans = numberOfSubsequences(s, a, b);
    for (int i = 0; i <= k; i++)
    {
        // use i moves to place a in front
        int ptr = 0, rema = i;
        string temp = s;
        while (ptr < n && rema > 0)
        {
            if (temp[ptr] != a)
            {
                temp[ptr] = a;
                rema--;
            }
            ++ptr;
        }
        int ptr2 = n - 1, remb = k - i;
        while (ptr2 > ptr && remb > 0)
        {
            if (temp[ptr2] != b)
            {
                temp[ptr2] = b;
                remb--;
            }
            ++ptr2;
        }
        ans = max(ans, numberOfSubsequences(temp, a, b));
    }

    cout<<ans<<endl;
}


void s12(){

}

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;

    while (t--)
    {
        s11();
    }

    khalaas
}