#include <iostream>
using namespace std;

int getIndexofElementAtmostK(vector<int> &v, int k)
{
    int n = v.size();
    int lo = 0, hi = n - 1, mid, index;

    while (lo <= hi)
    {
        mid = (lo + hi) / 2;
        if (v[mid] <= k)
        {
            index = mid;
            lo = mid + 1;
        }
        else
        {
            hi = mid - 1;
        }
    }
    return index;
}

int main()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    // find out number of indices i s.t  l <= a[i] <= r
    int l, r;
    cin >> l >> r;

    int lptr = getIndexofElementAtmostK(v, l - 1);
    int rptr = getIndexofElementAtmostK(v, r);
    int ans = rptr - lptr;

    cout << "Number of elements belonging to range: [" << l << ", " << r << "]: " << ans << endl;

    return 0;
}
