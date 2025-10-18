#include <iostream>
using namespace std;

#define fl(i, n) for (int i = 0; i < n; i++)

void solve1()
{
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n), origadj(n);

    fl(i, n - 1)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> values(n, 0), lazy(n, 0);

    vector<vector<int>> levelwisenode(n);
    vector<int> nodetolevel(n);
    queue<pair<int, int>> qu;
    qu.push({0, 0});

    vector<bool> vis(n, 0);

    while (!qu.empty())
    {
        auto fr = qu.front();
        qu.pop();
        int node = fr.first, level = fr.second;
        vis[node] = 1;

        levelwisenode[level].push_back(node);
        nodetolevel[node] = level;

        for (auto i : adj[node])
        {
            if (!vis[i])
            {
                origadj[node].push_back(i);
                qu.push({i, level + 1});
                vis[i] = 1;
            }
        }
    }

    fl(i, q)
    {
        string type;
        cin >> type;
        int x, y;
        cin >> x >> y;
        // adds a new node
        if (type == "Ro")
        {
            // update to children
            int par = x - 1, node = y - 1;
            values[par] += lazy[par];
            values.push_back(0);

            for (auto child : origadj[par])
            {
                lazy[child] += lazy[par];
            }
            lazy[par] = 0;
            origadj[par].push_back(node);
            origadj.push_back({});
            // update level
            int parentlevel = nodetolevel[par];
            nodetolevel.push_back(parentlevel + 1);
            if (levelwisenode.size() == (parentlevel - 1))
            {
                levelwisenode.push_back({node});
            }
            else
            {
                levelwisenode[parentlevel + 1].push_back(node);
            }
        }
        else
        {
            int level = x, val = y;
            for (auto node : levelwisenode[level])
            {
                lazy[node] += val;
            }
        }
    }

    qu.push({0, lazy[0]});
    while (!qu.empty())
    {
        auto fr = qu.front();
        qu.pop();

        auto node = fr.first, lazyvalue = fr.second;

        for (auto node : origadj[node])
        {
            lazy[node] += lazyvalue;
            qu.push({node, lazy[node]});
        }
    }

    int k = values.size();
    int ans = 0;

    for (int i = 0; i < k; i++)
    {
        ans += values[i] + lazy[i];;
    }

    cout << ans << endl;
}

int main()
{
    solve1();

    return 0;
}