#include <iostream>
#include <random>
using namespace std;

bool istesting = false;
vector<int> v = {5, 4, 2, 1, 3};

int judge(int index)
{
    return v[index - 1];
}

int n;

int query(int index)
{
    if (index == 0 || index == n + 1)
    {
        return 1e9;
    }
    cout << "? " << index << endl;
    if (istesting)
    {
        return judge(index);
    }
    int res;
    cin >> res;
    return res;
}

int main()
{
    cin >> n;

    int low = 1, high = n, ans, mid;

    while (low <= high)
    {
        mid = (low + high) / 2;
        int prev = query(mid - 1), currval = query(mid), nextval = query(mid + 1);
        if (currval > nextval)
        {
            low = mid + 1;
        }
        else if (currval > prev)
        {
            high = mid - 1;
        }
        else
        {
            ans = mid;
            break;
        }
    }

    cout << "! " << ans << endl;
    return 0;
}