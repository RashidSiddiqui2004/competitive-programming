#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
    struct Node {
        int count;   // count of 1s in this segment
        bool lazy;   // lazy flip flag
        Node(): count(0), lazy(false) {}
    };

    vector<Node> tree;
    int n;

public:
    SegmentTree(const vector<int> &arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(1, 0, n - 1, arr);
    }

    void build(int idx, int l, int r, const vector<int> &arr) {
        if (l == r) {
            tree[idx].count = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(idx * 2, l, mid, arr);
        build(idx * 2 + 1, mid + 1, r, arr);
        tree[idx].count = tree[idx * 2].count + tree[idx * 2 + 1].count;
    }

    void pushDown(int idx, int l, int r) {
        if (tree[idx].lazy) {
            int mid = (l + r) / 2;
            apply(idx * 2, l, mid);
            apply(idx * 2 + 1, mid + 1, r);
            tree[idx].lazy = false;
        }
    }

    void apply(int idx, int l, int r) {
        // flipping: ones -> zeros, zeros -> ones
        tree[idx].count = (r - l + 1) - tree[idx].count;
        tree[idx].lazy = !tree[idx].lazy;
    }

    void update(int idx, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return; // no overlap
        if (ql <= l && r <= qr) {
            apply(idx, l, r);
            return;
        }
        pushDown(idx, l, r);
        int mid = (l + r) / 2;
        update(idx * 2, l, mid, ql, qr);
        update(idx * 2 + 1, mid + 1, r, ql, qr);
        tree[idx].count = tree[idx * 2].count + tree[idx * 2 + 1].count;
    }

    int query(int idx, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return tree[idx].count;
        pushDown(idx, l, r);
        int mid = (l + r) / 2;
        return query(idx * 2, l, mid, ql, qr) + 
               query(idx * 2 + 1, mid + 1, r, ql, qr);
    }

    // Public functions
    void flipRange(int l, int r) {
        update(1, 0, n - 1, l, r);
    }

    int countOnes(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};

int main() {
    vector<int> arr = {1, 0, 1, 1, 0, 0, 1}; 
    SegmentTree st(arr);

    cout << st.countOnes(0, 6) << "\n"; // total 1s
    st.flipRange(1, 4);                  // flip [1,4]
    cout << st.countOnes(0, 6) << "\n"; // new total 1s
    cout << st.countOnes(2, 5) << "\n"; // query [2,5]

    return 0;
}
