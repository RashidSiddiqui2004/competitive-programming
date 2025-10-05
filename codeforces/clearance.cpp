#include <iostream>
using namespace std;

struct SegmentTree {
    struct Node {
        long long sum, minv, maxv;
    };

    int n;
    vector<Node> tree;
    vector<long long> lazy;

    SegmentTree(const vector<long long> &arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.assign(4 * n, 0);
        build(1, 0, n - 1, arr);
    }

    void build(int node, int start, int end, const vector<long long> &arr) {
        if (start == end) {
            tree[node] = {arr[start], arr[start], arr[start]};
            return;
        }
        int mid = (start + end) / 2;
        build(node * 2, start, mid, arr);
        build(node * 2 + 1, mid + 1, end, arr);
        pull(node);
    }

    void pull(int node) {
        tree[node].sum = tree[node * 2].sum + tree[node * 2 + 1].sum;
        tree[node].minv = min(tree[node * 2].minv, tree[node * 2 + 1].minv);
        tree[node].maxv = max(tree[node * 2].maxv, tree[node * 2 + 1].maxv);
    }

    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            long long val = lazy[node];
            tree[node].sum -= val * (end - start + 1);
            tree[node].minv -= val;
            tree[node].maxv -= val;

            if (start != end) {
                lazy[node * 2] += val;
                lazy[node * 2 + 1] += val;
            }
            lazy[node] = 0;
        }
    }

    long long buy(int l, int r, long long k) {
        return buy(1, 0, n - 1, l, r, k);
    }

    long long buy(int node, int start, int end, int l, int r, long long k) {
        push(node, start, end);

        if (start > r || end < l || tree[node].maxv <= 0)
            return 0; // No stock or no overlap

        if (l <= start && end <= r) {
            if (tree[node].minv >= k) {
                // All elements >= k → subtract k uniformly
                long long bought = k * (end - start + 1);
                lazy[node] += k;
                push(node, start, end);
                return bought;
            }

            if (tree[node].maxv <= k) {
                // All elements < k → buy all stock
                long long bought = tree[node].sum;
                tree[node].sum = 0;
                tree[node].minv = 0;
                tree[node].maxv = 0;
                if (start != end) {
                    lazy[node * 2] = 0;
                    lazy[node * 2 + 1] = 0;
                }
                return bought;
            }
        }

        // Partial overlap or mixed values
        if (start == end) {
            long long take = min(tree[node].sum, k);
            tree[node].sum -= take;
            tree[node].minv = tree[node].sum;
            tree[node].maxv = tree[node].sum;
            return take;
        }

        int mid = (start + end) / 2;
        long long left = buy(node * 2, start, mid, l, r, k);
        long long right = buy(node * 2 + 1, mid + 1, end, l, r, k);
        pull(node);
        return left + right;
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;
    vector<long long> A(n);
    for (auto &x : A) cin >> x;

    SegmentTree st(A);

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        long long k;
        cin >> l >> r >> k;
        --l, --r;
        cout << st.buy(l, r, k) << '\n';
    }
    return 0;
}
