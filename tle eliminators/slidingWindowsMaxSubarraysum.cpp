#include <iostream>
using namespace std;

// fixed sized sliding window
// dynamic sized sliding window

// find the maximum subarray sum of size k
// v[i] belongs to [-1e9, 1e9]
int maximumSubarraySumofSizek(int n, vector<int> &v, int k)
{
    int ans = INT_MIN;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += v[i];

        if (i >= k)
        {
            sum -= v[i - k];
        }

        if (i >= (k - 1))
        {
            ans = max(ans, sum);
        }
    }
    return ans;
}

int main()
{
    int n, k;
    cin >> n>>k;
    vector<int> v(n);
    for (size_t i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    cout << maximumSubarraySumofSizek(n, v, k);
    return 0;
}