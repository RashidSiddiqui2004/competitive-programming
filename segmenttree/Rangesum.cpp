#include <iostream>
using namespace std;

class SegmentTree {
    int n;
    vector<long long> tree, lazy;
    // parent (root) node -> 1

public:
    SegmentTree(int n) {
        this->n = n;
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
    }

    SegmentTree(vector<int> &arr) {
        n = arr.size();
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        build(1, 0, n - 1, arr);
    }

    void build(int node, int start, int end, vector<int> &arr) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = (start + end) / 2;
        build(2 * node, start, mid, arr);
        build(2 * node + 1, mid + 1, end, arr);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            // Apply the pending update
            tree[node] += (end - start + 1) * lazy[node];

            // Propagate to children if not a leaf
            if (start != end) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void update(int l, int r, int val) {
        update(1, 0, n - 1, l, r, val);
    }

    void update(int node, int start, int end, int l, int r, int val) {
        push(node, start, end);

        if (start > r || end < l) return; // no overlap

        // complete overlap
        if (l <= start && end <= r) {
            lazy[node] += val;
            push(node, start, end);
            return;
        }

        int mid = (start + end) / 2;
        update(2 * node, start, mid, l, r, val);
        update(2 * node + 1, mid + 1, end, l, r, val);

        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    long long query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    long long query(int node, int start, int end, int l, int r) {
        push(node, start, end);

        if (start > r || end < l) return 0; // no overlap
        if (l <= start && end <= r) return tree[node];

        int mid = (start + end) / 2;
        return query(2 * node, start, mid, l, r) +
               query(2 * node + 1, mid + 1, end, l, r);
    }
};


int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    SegmentTree st(arr);

    cout << st.query(0, 4) << "\n"; // sum of [0..4] = 15

    st.update(1, 3, 10); // add 10 to range [1..3]

    cout << st.query(0, 4) << "\n"; // updated sum = 15 + 30 = 45
    cout << st.query(2, 2) << "\n"; // single element [2] = 13

    return 0;
}
