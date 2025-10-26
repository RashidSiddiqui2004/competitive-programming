#include <iostream>
#include <random>
using namespace std;

bool istesting = true;

vector<int> v = {1, 0, 0, 1, 0, 1, 1, 1, 1, 0};

int judge(int l, int r)
{
    --l, --r;
    int sum = 0;
    for (int i = l; i <= r; i++)
    {
        sum += v[i];
    }
    return sum;
}

int query(int x, int y)
{
    cout << "? " << x << ' ' << y << endl;
    if (istesting)
    {
        // cout << judge(x, y) << endl;
        return judge(x, y);
    }
    int res;
    cin >> res;
    return res;
}

void output(int ans)
{
    cout << "! " << ans << endl;
}

int main()
{
    int n, t, k;
    cin >> n >> t >> k;

    int low = 1, high = n, mid, ans;

    while (low <= high)
    {
        mid = (low + high) / 2;
        int sum = query(low, mid);
        int numzeros = (mid - low + 1) - sum;
        if (numzeros < k)
        {
            low = mid + 1;
            k -= numzeros;
        }
        else
        {
            ans = mid;
            high = mid - 1;
        }
    }

    output(ans);

    return 0;
}