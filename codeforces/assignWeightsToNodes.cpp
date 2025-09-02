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

#define int long long
using namespace std;

const int N = 100005;
int vis[N], parent[N];
vector<vector<int>> adj;
set<vector<int>> allCycles;

const int MOD = 998244353;

// black box
void dfs(int u, int p)
{
    vis[u] = 1;
    parent[u] = p;

    for (int v : adj[u])
    {
        if (v == p)
            continue; // ignore the edge to parent
        if (!vis[v])
        {
            dfs(v, u);
        }
        else if (vis[v] == 1)
        {
            // Found a back edge (u -> v)
            vector<int> cycle;
            int x = u;
            cycle.push_back(v);
            while (x != v && x != -1)
            {
                cycle.push_back(x);
                x = parent[x];
            }
            if (x == v)
            {
                sort(cycle.begin(), cycle.end()); // canonical form
                allCycles.insert(cycle);
            }
        }
    }

    vis[u] = 2;
}

void solve()
{
    int n, m, v;
    cin >> n >> m >> v;

    allCycles.clear();

    vector<int> weights(n);

    for (size_t i = 0; i < n; i++)
    {
        cin >> weights[i];
    }

    adj.assign(n, {});

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    for(int i=0;i<n;i++){
        vis[i]=0;
        parent[i]=-1;
    }

    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
            dfs(i, -1);
    }

    bool check = true;
    vector<bool> ispartofcycle(n, 0);

    for (auto &cycle : allCycles)
    {
        int fvalue = -1;
        for (int x : cycle)
        {
            if (weights[x] != -1)
            {
                if (fvalue == -1)
                {
                    fvalue = weights[x];
                }
                else if (fvalue != weights[x])
                {
                    check = false;
                    break;
                }
            }
            else
            {
                ispartofcycle[x] = 1;
            }
        }
        if (!check)
            break;
    }

    if (!check)
    {
        cout << 0 << endl;
        return;
    }

    int ans = 1;
    for (int i = 0; i < n; i++)
    {
        if (weights[i] == -1 and !ispartofcycle[i])
        {
            ans = (ans * v) % MOD;
        }
    }
    cout << ans << endl;
}

int32_t main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
