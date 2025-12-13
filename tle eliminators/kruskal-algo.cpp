#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

// Structure to represent an edge
struct Edge {
  int u, v, weight;
  bool operator<(const Edge &other) const { return weight < other.weight; }
};

// Disjoint Set Union (DSU) structure
class DSU {
  vector<int> parent;
  vector<int> rank;

public:
  DSU(int n) {
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);
    rank.assign(n, 0);
  }

  int find(int i) {
    if (parent[i] == i)
      return i;
    return parent[i] = find(parent[i]);
  }

  void unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);

    if (root_i != root_j) {
      if (rank[root_i] < rank[root_j])
        parent[root_i] = root_j;
      else {
        parent[root_j] = root_i;
        if (rank[root_i] == rank[root_j])
          rank[root_i]++;
      }
    }
  }
};

void solve(int t) {
  int N, M;
  cin >> N >> M;

  vector<Edge> edges;
  for (int i = 0; i < M; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    edges.push_back({u, v, w});
  }

  sort(edges.begin(), edges.end());

  DSU dsu(N);
  long long mst_weight = 0;
  vector<Edge> mst_edges;

  for (const auto &edge : edges) {
    if (dsu.find(edge.u) != dsu.find(edge.v)) {
      dsu.unite(edge.u, edge.v);
      mst_weight += edge.weight;
      mst_edges.push_back(edge);
    }
  }

  cout << "Test Case #" << t << ":" << endl;
  if (mst_edges.size() != N - 1 &&
      N > 1) { // Check if MST is possible (graph might be disconnected)
    // Note: For typical Kruskal's problems, we assume connected or find MST of
    // component. If strictly MST of a connected graph is required and edges <
    // N-1, it's impossible. However, usually we just output what we found or
    // the weight. Let's assume we just print the edges and weight of the
    // Minimum Spanning Forest if disconnected. But standard MST implies
    // connected. Let's stick to printing what we found.
  }

  cout << "MST Weight: " << mst_weight << endl;
  cout << "Edges in MST:" << endl;
  for (const auto &edge : mst_edges) {
    cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
  }
  cout << endl;
}

int main() {
  int T;
  if (cin >> T) {
    for (int i = 1; i <= T; ++i) {
      solve(i);
    }
  }
  return 0;
}
