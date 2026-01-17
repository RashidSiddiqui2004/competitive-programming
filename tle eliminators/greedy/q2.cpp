#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <array>
#include <deque>
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
#include <cstdio>

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
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << (x) << endl;
#else
#define debug(x)
#endif

void sol1()
{
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    map<char, int> operations;

    char maxch = 'a';

    for (auto i : s)
    {
        if (i > maxch)
        {
            maxch = i;
            int reqoper = i - 'a';
            if (reqoper <= k)
            {
                operations.clear();
                operations[i] = reqoper;
                if (k == 0)
                {
                    break;
                }
            }
            else
            {
                if (operations.empty())
                {
                    operations[i] = k;
                }
                else
                {
                    operations[i] = k - operations.begin()->second;
                }

                break;
            }
        }
    }

    for (auto i : operations)
    {
        char ch = i.first;
        int oper = i.second;
        // cout << ch << " " << oper << endl;
        for (int j = 1; j <= oper; j++)
        {
            char prevch = 'a' + (ch - 'a' - 1);
            for (int t = 0; t < n; t++)
            {
                if (s[t] == ch)
                {
                    s[t] = prevch;
                }
            }
            ch = prevch;
        }
    }
    cout << s << endl;
}

using pcc = pair<char, char>;

void sol2()
{
    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;
    vector<pair<int, pcc>> vp;
    fl(i, n)
    {
        if (a[i] != b[i])
        {
            vp.push_back({i, {a[i], b[i]}});
        }
    }

    // for(auto i: vp){
    //     cout<<i.first<<" "<<i.second.first<<" "<<i.second.second<<endl;
    // }

    int hammingvalue = (int)vp.size();
    int pos1val = -2, pos2val = -2;
    int ans = hammingvalue;

    for (int i = 0; i < 26; i++)
    {
        char ch = 'a' + i;
        bool first = false, second = false;
        map<char, int> s1, s2;

        for (auto p : vp)
        {
            if (p.second.first == ch)
            {
                first = true;
                if (!s1.count(p.second.second))
                {
                    s1[p.second.second] = p.first;
                }
            }
        }

        for (auto p : vp)
        {
            if (p.second.second == ch)
            {
                second = true;
                if (!s2.count(p.second.first))
                {
                    s2[p.second.first] = p.first;
                }
            }
        }

        if (first && second)
        {
            for (int j = 0; j < 26; j++)
            {
                char t = 'a' + j;
                if (s1.count(t) && s2.count(t))
                {
                    ans = hammingvalue - 2;
                    pos1val = s1[t], pos2val = s2[t];
                    break;
                }
                else if (s1.count(t))
                {
                    ans = hammingvalue - 1;
                    pos1val = s1[t], pos2val = s2.begin()->second;
                }
                else if (s2.count(t))
                {
                    ans = hammingvalue - 1;
                    pos1val = s1.begin()->second, pos2val = s2[t];
                }
            }
        }

        if (hammingvalue - ans == 2)
        {
            break;
        }
    }

    cout << ans << endl;
    cout << min(pos1val, pos2val) + 1 << " " << max(pos1val, pos2val) + 1 << endl;
}

using pii = pair<int, int>;
void sol3()
{
    int n, x;
    cin >> n >> x;

    priority_queue<pii, vector<pii>, greater<>> type1, type2;

    for (size_t i = 0; i < n; i++)
    {
        int type, h, m;
        cin >> type >> h >> m;
        if (type == 0)
        {
            type1.push({h, m});
        }
        else
        {
            type2.push({h, m});
        }
    }

    int ans = 0;

    {
        auto type1cpy = type1, type2cpy = type2;
        int curr_height = x, ans1 = 0;
        int nexttype1 = -1, nexttype2 = -1;

        while (!type1cpy.empty())
        {
            bool check = false;
            int toadd = 0;
            while (!type1cpy.empty())
            {
                auto b1 = type1cpy.top();
                type1cpy.pop();
                if (curr_height >= b1.first)
                {
                    check = true;
                    toadd = b1.second;
                    if (curr_height + b1.second >= nexttype2)
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }

            if (check)
            {
                curr_height += toadd;
                ++ans1;

                if (!type1cpy.empty())
                {
                    nexttype1 = type1cpy.top().first;
                }
                else
                {
                    nexttype1 = -1;
                }

                if (!type1cpy.empty())
                {
                    nexttype1 = type1cpy.top().first;
                }
                else
                {
                    nexttype1 = -1;
                }

                if (!type2cpy.empty())
                {
                    bool check2 = false;
                    while (!type2cpy.empty())
                    {
                        auto b2 = type2cpy.top();
                        type2cpy.pop();
                        if (curr_height >= b2.first)
                        {
                            check2 = true;
                            toadd = b2.second;
                            if (curr_height + b2.second >= nexttype1)
                            {
                                break;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }

                    if (check2)
                    {
                        ++ans1;
                        curr_height += toadd;

                        if (!type2cpy.empty())
                        {
                            nexttype2 = type2cpy.top().first;
                        }
                        else
                        {
                            nexttype2 = -1;
                        }
                    }
                }
                else
                {
                    break;
                }
            }
        }
        ans = max(ans, ans1);
    }

    {
        auto type1cpy = type2, type2cpy = type1;
        int curr_height = x, ans1 = 0;
        int nexttype1 = -1, nexttype2 = -1;

        while (!type1cpy.empty())
        {
            bool check = false;
            int toadd = 0;
            while (!type1cpy.empty())
            {
                auto b1 = type1cpy.top();
                type1cpy.pop();
                if (curr_height >= b1.first)
                {
                    check = true;
                    toadd = b1.second;
                    if (curr_height + b1.second >= nexttype2)
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }

            if (check)
            {
                curr_height += toadd;
                ++ans1;

                if (!type1cpy.empty())
                {
                    nexttype1 = type1cpy.top().first;
                }
                else
                {
                    nexttype1 = -1;
                }

                if (!type1cpy.empty())
                {
                    nexttype1 = type1cpy.top().first;
                }
                else
                {
                    nexttype1 = -1;
                }

                if (!type2cpy.empty())
                {
                    bool check2 = false;
                    while (!type2cpy.empty())
                    {
                        auto b2 = type2cpy.top();
                        type2cpy.pop();
                        if (curr_height >= b2.first)
                        {
                            check2 = true;
                            toadd = b2.second;
                            if (curr_height + b2.second >= nexttype1)
                            {
                                break;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }

                    if (check2)
                    {
                        ++ans1;
                        curr_height += toadd;

                        if (!type2cpy.empty())
                        {
                            nexttype2 = type2cpy.top().first;
                        }
                        else
                        {
                            nexttype2 = -1;
                        }
                    }
                }
                else
                {
                    break;
                }
            }
        }
        ans = max(ans, ans1);
    }

    cout << ans << endl;
}

// https://codeforces.com/problemset/problem/1520/E
void sol4()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> sheeps;
    int empty = 0;
    fl(i, n)
    {
        if (s[i] == '*')
            sheeps.push_back(empty);
        else
            empty++;
    }
    int numsheeps = sheeps.size();
    if (numsheeps == 0 || numsheeps == n)
    {
        cout << 0 << endl;
    }
    else
    {
        int ans = 0;
        int median = sheeps[(numsheeps - 1) / 2];
        for (auto i : sheeps)
        {
            ans += abs(i - median);
        }
        cout << ans << endl;
    }
}

// https://codeforces.com/problemset/problem/1644/C
void sol5()
{
    int n, x;
    cin >> n >> x;
    vector<int> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    // int n = 10, x = 2;
    // vector<int> v = {-6, -1, -2, 4, -6, -1, -4, 4, -5, -4};
    int maxsum = LLONG_MIN;
    int p1 = 0, p2 = 0;

    fl(i, n)
    {
        int currsum = 0;
        for (int j = i; j < n; j++)
        {
            currsum += v[j];
            if (maxsum < currsum)
            {
                p1 = i, p2 = j;
                maxsum = currsum;
            }
        }
    }
    // cout << p1 << " " << p2 << endl;

    ll ans = max(maxsum, 0ll), currsum = maxsum;
    cout << ans << ' ';

    int m = p2 - p1 + 1;

    fl(i, m)
    {
        currsum = currsum + x;
        ans = currsum;
        cout << ans << ' ';
    }

    --p1, ++p2;

    while (p1 >= 0 || p2 < n)
    {
        int prev = LLONG_MIN, next = LLONG_MIN;
        if (p1 >= 0)
        {
            prev = v[p1] + x;
        }
        if (p2 < n)
        {
            next = v[p2] + x;
        }
        if (prev > next)
        {
            currsum = currsum + prev;
            --p1;
        }
        else
        {
            currsum = currsum + next;
            ++p2;
        }
        ans = max(ans, currsum);
        cout << ans << ' ';
    }

    cout << endl;
}

int32_t main()
{
    int t = 1;
    cin >> t;

    while (t--)
    {
        sol5();
    }

    return 0;
}