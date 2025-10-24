#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int low = 0, high = 1e9, mid, ans;

    while (low <= high)
    {
        mid = (low + high) / 2;
        if ((mid * 1ll * mid) <= n)
        {
            ans = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    cout << ans << endl;
}