#include <iostream>
#include <random>
#include <map>
using namespace std;

bool istesting = false;

// vector<int> v = {1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1};
vector<int> v = {0, 0};

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

map<pair<int, int>, int> cache;
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
    // comment this as n can be large in actual test cases
    // v[ans - 1] = 1;
}

void synccache(int pos, int L, int R)
{
    cache[{L, R}]--;

    if (L != R)
    {
        int M = (L + R) / 2;
        if (pos <= M)
            synccache(pos, L, M);
        else
            synccache(pos, M + 1, R);
    }
}

int main()
{
    int n, t, k;
    cin >> n >> t;

    while (t--)
    {
        cin >> k;
        int low = 1, high = n, ans;

        while (low <= high)
        {
            int mid = (low + high) / 2;
            pair<int, int> p = {low, mid};
            int numzeros;
            if (cache.count(p))
                numzeros = cache[p];
            else
            {
                int sum = query(low, mid);
                numzeros = (mid - low + 1) - sum;
                cache[p] = numzeros;
            }

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
        synccache(ans, 1, n);
    }

    return 0;
}