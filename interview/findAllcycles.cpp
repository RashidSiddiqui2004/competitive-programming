#include<iostream>
#include<set>
using namespace std;

const int N = 100005;
int vis[N], parent[N];
vector<vector<int>> adj;
set<vector<int>> allCycles;

void dfs(int u, int p) {
    vis[u] = 1;
    parent[u] = p;

    for (int v : adj[u]) {
        if (v == p) continue; // ignore the edge to parent
        if (!vis[v]) {
            dfs(v, u);
        } else if (vis[v] == 1) {
            // Found a back edge (u -> v)
            vector<int> cycle;
            int x = u;
            cycle.push_back(v);
            while (x != v && x != -1) {
                cycle.push_back(x);
                x = parent[x];
            }
            if (x == v) {
                sort(cycle.begin(), cycle.end()); // canonical form
                allCycles.insert(cycle);
            }
        }
    }

    vis[u] = 2;
}

int main() {
    int n, m;
    cin >> n >> m;
    adj.assign(n, {});

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(vis, 0, sizeof(vis));
    memset(parent, -1, sizeof(parent));

    for (int i = 0; i < n; i++) {
        if (!vis[i]) dfs(i, -1);
    }

    int cycleId = 1;
    for (auto &cycle : allCycles) {
        cout << "Cycle " << cycleId++ << ": ";
        for (int x : cycle) cout << x + 1 << " ";
        cout << "\n";
    }

    if (allCycles.empty()) cout << "No cycles found\n";
}
