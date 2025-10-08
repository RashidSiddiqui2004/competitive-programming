#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

using pii = pair<int, int>;

int ac, dr;
using ll = long long;

long long f(int a, int b) {
    return max(0, a - ac) + max(0, b - dr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> ac >> dr >> n;
    vector<pii> v(n);
    for (int i = 0; i < n; i++) cin >> v[i].first;
    for (int i = 0; i < n; i++) cin >> v[i].second;

    tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> t;

    for (auto &p : v) t.insert(f(p.first, p.second));

    int m; cin >> m;
    while (m--) {
        int id, newa, newb;
        cin >> id >> newa >> newb;
        --id;

        t.erase(t.find(f(v[id].first, v[id].second)));
        v[id] = {newa, newb};
        t.insert(f(v[id].first, v[id].second));
        int p = 0;
        while (true) {
            int cnt = t.order_of_key(p + 1);
            if (cnt > p)
                p++;
            else
                break;
        }
        cout << p << "\n";
    }
}
