#include <iostream>
#include <random>
using namespace std;

bool istesting = false;

vector<int> v = {15, 5, 6, 40, 10};

int judge(int l, int r)
{
    // index of 2nd largest element in range l, r (1-based)
    --l, --r;
    int maxi = v[l], secmaxi = INT_MIN;
    int indexmaxi = l, indexsecmaxi = -1;
    for (int i = l + 1; i <= r; i++)
    {
        if (v[i] > maxi)
        {
            secmaxi = maxi;
            maxi = v[i];
            indexsecmaxi = indexmaxi;
            indexmaxi = i;
        }
        else if (v[i] >= secmaxi)
        {
            secmaxi = v[i];
            indexsecmaxi = i;
        }
    }
    return indexsecmaxi + 1;
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

int left(int l, int r)
{
    int pivot = r + 1;
    int ans = l;

    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (query(mid, pivot) == pivot)
        {
            ans = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }

    return ans;
}

int right(int l, int r)
{
    int pivot = l - 1;
    int ans = l;

    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (query(pivot, mid) == pivot)
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }

    return ans;
}

void output(int ans)
{
    cout << "! " << ans << endl;
}

int main()
{
    int n;
    cin >> n;

    int pivot = query(1, n);

    if (pivot == 1)
    {
        output(right(2, n));
    }
    else if (query(1, pivot) == pivot)
    {
        output(left(1, pivot - 1));
    }
    else
    {
        output(right(pivot + 1, n));
    }

    return 0;
}