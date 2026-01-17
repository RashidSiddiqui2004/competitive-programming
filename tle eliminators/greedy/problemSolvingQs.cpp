
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <array>
#include <deque>
#include <queue>
#include <stack>
#include <list>
#include <cstring>
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
    int n;
    cin >> n;
    vector<int> v(n);

    int N = 1e6 + 2;
    int freq[N];
    memset(freq, 0, sizeof(freq));

    fl(i, n)
    {
        cin >> v[i];
        ++freq[v[i]];
    }

    int answer = 0;
    fl(i, N - 1)
    {
        freq[i + 1] += freq[i] / 2;
        freq[i] &= 1;
        answer += freq[i];
    }

    cout << answer << endl;
}

void sol2()
{
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    fl(i, n)
    {
        cin >> v[i];
    }

    int minfreq = n / m;
    int extrafreq = n - (m * minfreq);

    cout << minfreq << ' ';

    vector<int> freq(m + 1, 0ll);
    vector<int> vacant_spaces;

    fl(i, n)
    {
        if (v[i] <= m)
        {
            if (freq[v[i]] == minfreq)
            {
                if (extrafreq > 0)
                {
                    extrafreq--;
                }
                else
                {
                    vacant_spaces.push_back(i);
                }
            }
            else
            {
                freq[v[i]]++;
            }
        }
        else
        {
            vacant_spaces.push_back(i);
        }
    }

    int j = 0;
    int ans = 0;

    for (size_t i = 1; i <= m; i++)
    {
        int rem_elems = minfreq - freq[i];
        for (; rem_elems > 0; rem_elems--)
        {
            v[vacant_spaces[j++]] = i;
            ++ans;
        }
    }

    cout << ans << endl;

    for (auto i : v)
    {
        cout << i << ' ';
    }

    cout << endl;
}

// Print two space-separated integers:
// the length of the longest word outside the parentheses (print 0, if there is no word outside the parentheses),
// the number of words inside the parentheses (print 0, if there is no word inside the parentheses).
void sol3()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    int longestwordlen = 0, parenthesis_words = 0;

    int i = 0;

    while (i < n)
    {
        while (i < n and s[i] == '_')
        {
            ++i;
        }
        if (i == n)
        {
            break;
        }
        if (s[i] == '(')
        {
            ++i;
            // sequence inside parenthesis
            while (i < n and s[i] != ')')
            {
                while (i < n and s[i] == '_')
                {
                    ++i;
                }
                if (s[i] == ')')
                {
                    break;
                }
                while (i < n and s[i] != ')' and s[i] != '_')
                {
                    ++i;
                }
                ++parenthesis_words;
            }
            ++i;
        }
        else
        {
            // sequence outside parenthesis
            int currwordlen = 0;
            while (i < n and s[i] != '(' and s[i] != '_')
            {
                ++currwordlen;
                ++i;
            }
            if (currwordlen > longestwordlen)
                longestwordlen = currwordlen;
        }
    }

    cout << longestwordlen << ' ' << parenthesis_words << endl;
}

vector<int> dx = {0, 0, 1, -1};
vector<int> dy = {1, -1, 0, 0};

int dfs(vector<string> &grid, vector<vector<bool>> &vis, int x, int y, int id = 0)
{
    char symbol = 'A' + id;
    grid[x][y] = symbol;
    int n = grid.size(), m = grid[0].size();
    int ans = 1;
    for (int i = 0; i < 4; i++)
    {
        int newx = x + dx[i], newy = y + dy[i];
        if (newx >= 0 and newx < n and newy >= 0 and newy < m and
            !vis[newx][newy] and grid[newx][newy] == '.')
        {
            vis[newx][newy] = 1;
            ans += dfs(grid, vis, newx, newy, id);
        }
    }
    return ans;
}

void sol4()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<string> grid(n);

    fl(i, n)
    {
        cin >> grid[i];
    }

    vector<vector<bool>> vis(n, vector<bool>(m, false));

    int id = 0;

    for (int i = 0; i < m; i++)
    {
        if (grid[0][i] == '.')
        {
            vis[0][i] = 1;
            dfs(grid, vis, 0, i);
        }
        if (grid[n - 1][i] == '.')
        {
            vis[n - 1][i] = 1;
            dfs(grid, vis, n - 1, i);
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (grid[i][0] == '.')
        {
            vis[i][0] = 1;
            dfs(grid, vis, i, 0);
        }
        if (grid[i][m - 1] == '.')
        {
            vis[i][m - 1] = 1;
            dfs(grid, vis, i, m - 1);
        }
    }

    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<>> lakesizes;

    fl(i, n)
    {
        fl(j, m)
        {
            if (!vis[i][j] and grid[i][j] == '.')
            {
                ++id;
                vis[i][j] = 1;
                lakesizes.push({dfs(grid, vis, i, j, id), id});
            }
        }
    }

    for (auto i : grid)
    {
        cout << i << endl;
    }

    int currlakes = lakesizes.size();
    int extra = currlakes - k;
    int ans = 0;

    vector<bool> isLakeRemoved(51, 0);

    fl(i, extra)
    {
        ans += lakesizes.top().first;
        lakesizes.pop();
    }

    cout << ans << endl;
}

void sol5(){
 
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