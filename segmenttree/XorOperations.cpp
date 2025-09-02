#include <iostream>
using namespace std;

struct Node
{
    vector<int> bitCount; // bitCount[b] = count of numbers with bit b set
    int size;
    Node(int sz = 0)
    {
        size = sz;
        bitCount.assign(32, 0);
    }
};

class SegmentTree
{
    int n;
    vector<Node> tree;
    vector<int> lazy; // stores XOR mask to apply

public:
    SegmentTree(vector<int> &arr)
    {
        n = arr.size();
        tree.resize(4 * n);
        lazy.assign(4 * n, 0);
        build(1, 0, n - 1, arr);
    }

    void build(int node, int start, int end, vector<int> &arr)
    {
        if (start == end)
        {
            tree[node] = Node(1);
            for (int b = 0; b < 32; b++)
            {
                if (arr[start] & (1 << b))
                    tree[node].bitCount[b] = 1;
            }
            return;
        }
        int mid = (start + end) / 2;
        build(2 * node, start, mid, arr);
        build(2 * node + 1, mid + 1, end, arr);
        pull(node);
    }

    void pull(int node)
    {
        for (int b = 0; b < 32; b++)
        {
            tree[node].bitCount[b] = tree[2 * node].bitCount[b] + tree[2 * node + 1].bitCount[b];
        }
        tree[node].size = tree[2 * node].size + tree[2 * node + 1].size;
    }

    void applyXor(int node, int mask)
    {
        for (int b = 0; b < 32; b++)
        {
            if (mask & (1 << b))
            {
                tree[node].bitCount[b] = tree[node].size - tree[node].bitCount[b]; // flip counts
            }
        }
        lazy[node] ^= mask;
    }

    void push(int node)
    {
        if (lazy[node])
        {
            applyXor(2 * node, lazy[node]);
            applyXor(2 * node + 1, lazy[node]);
            lazy[node] = 0;
        }
    }

    void update(int l, int r, int val)
    {
        update(1, 0, n - 1, l, r, val);
    }

    void update(int node, int start, int end, int l, int r, int val)
    {
        if (start > r || end < l)
            return;
        if (l <= start && end <= r)
        {
            applyXor(node, val);
            return;
        }
        push(node);
        int mid = (start + end) / 2;
        update(2 * node, start, mid, l, r, val);
        update(2 * node + 1, mid + 1, end, l, r, val);
        pull(node);
    }

    long long query(int l, int r)
    {
        return query(1, 0, n - 1, l, r);
    }

    long long query(int node, int start, int end, int l, int r)
    {
        if (start > r || end < l)
            return 0;
        if (l <= start && end <= r)
        {
            long long sum = 0;
            for (int b = 0; b < 32; b++)
            {
                sum += 1LL * tree[node].bitCount[b] * (1LL << b);
            }
            return sum;
        }
        push(node);
        int mid = (start + end) / 2;
        return query(2 * node, start, mid, l, r) +
               query(2 * node + 1, mid + 1, end, l, r);
    }
};

int main()
{
    vector<int> arr = {1, 5, 2, 4};
    SegmentTree st(arr);

    cout << st.query(0, 3) << "\n";

    st.update(1, 2, 4);
    cout << st.query(0, 3) << "\n";

    st.update(0, 4, 10);
    cout << st.query(2, 4) << "\n";

    return 0;
}
