#include <iostream>
#include <random>
#include <map>
using namespace std;

#define int long long

int subarraySumLessthanEqualtoK(vector<int> &nums, int k)
{
    int n = nums.size();
    int res = 0;
    int currentSubarraySum = 0;
    int l = 0, r = 0;
    for (; r < n; r++)
    {
        currentSubarraySum += nums[r];
        while (l <= r and currentSubarraySum > k)
        {
            currentSubarraySum -= nums[l++];
        }
        if (l <= r)
            res += (r - l + 1);
    }
    return res;
}

int32_t main()
{
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    cout << subarraySumLessthanEqualtoK(v, k);

    // vector<int> v = {1, 2, 3, 3, 2};
    // int k = 5;
    // cout << subarraySumLessthanEqualtoK(v, k);
}
