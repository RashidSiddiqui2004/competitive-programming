#include <iostream>
#include <vector>
#include <set>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll k;
    cin >> n >> k;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    deque<int> maxdq, mindq;
    ll ans = 0;
    int l = 0;

    for (int r = 0; r < n; r++) {
        // Maintain max deque (decreasing order)
        while (!maxdq.empty() && a[maxdq.back()] <= a[r])
            maxdq.pop_back();
        maxdq.push_back(r);

        // Maintain min deque (increasing order)
        while (!mindq.empty() && a[mindq.back()] >= a[r])
            mindq.pop_back();
        mindq.push_back(r);

        // Shrink window while condition breaks
        while (!maxdq.empty() && !mindq.empty() &&
               a[maxdq.front()] - a[mindq.front()] > k) {
            if (maxdq.front() == l) maxdq.pop_front();
            if (mindq.front() == l) mindq.pop_front();
            l++;
        }

        // All subarrays ending at r are valid
        ans += (r - l + 1);
    }

    cout << ans << "\n";
    return 0;
}
