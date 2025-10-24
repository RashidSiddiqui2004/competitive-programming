#include <iostream>
#include <iomanip>
using namespace std;

// absolute error doesn't exceed 1e-6
// precision = 1e-8

const int N = 1e5;
double speeds[N], positions[N];

bool isPossible(int n, double time)
{
    vector<pair<double, double>> vp;
    for (int i = 0; i < n; i++)
    {
        vp.push_back({positions[i] - (speeds[i] * time), positions[i] + (speeds[i] * time)});
    }

    double min_coordinate = max(vp[0].first, vp[1].first);
    double max_coordinate = min(vp[0].second, vp[1].second);

    if (min_coordinate > max_coordinate)
    {
        return 0;
    }

    for (int i = 2; i < n; i++)
    {
        min_coordinate = max(min_coordinate, vp[i].first);
        max_coordinate = min(max_coordinate, vp[i].second);

        if (min_coordinate > max_coordinate)
        {
            return 0;
        }
    }

    return 1;
}

int main()
{
    setprecision(10);

    int n;
    cin >> n;

    for (size_t i = 0; i < n; i++)
    {
        cin >> positions[i] >> speeds[i];
    }

    if (n == 1)
    {
        cout << 0 << endl;
    }
    else
    {
        double precision = 1e-8;
        double low = 0, high = 1e9, mid, ans;
        double iterations = 100;

        for (size_t i = 0; i < iterations; i++)
        {
            mid = (low + high) / 2;
            if (isPossible(n, mid))
            {
                ans = mid;
                high = mid - precision;
            }
            else
            {
                low = mid + precision;
            }
        }

        cout << ans << endl;
    }
    return 0;
}