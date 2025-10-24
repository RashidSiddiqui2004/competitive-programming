#include <iostream>
#include <random>
#include <map>
using namespace std;

// nums[i]>=0
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

int subarraySumGreaterthanEqualtoK(vector<int> &nums, int k)
{
    int n = nums.size();
    int res = 0;
    int currentSubarraySum = 0;
    int l = 0, r = 0;
    for (; r < n; r++)
    {
        currentSubarraySum += nums[r];
        while (l <= r and currentSubarraySum - nums[l] >= k)
        {
            res += (n - r + 1);
            currentSubarraySum -= nums[l++];
        }
    }
    return res;
}

int main()
{
    vector<int> v = {1, 2, 3, 3, 2};
    int k = 5;
    int n = v.size();
    // first approach
   int valuebytype1 =  ((n * (n + 1)) / 2 - subarraySumLessthanEqualtoK(v, k - 1));
   int valuebytype2 =  subarraySumGreaterthanEqualtoK(v, k);

   cout<<(valuebytype1==valuebytype2)<<endl;
}
