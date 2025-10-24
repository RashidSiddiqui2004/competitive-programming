#include <iostream>
#include <random>
#include <map>
using namespace std;

int subarraySum(vector<int> &nums, int k)
{
    int n = nums.size();
    int subarraysWithSumK = 0;
    map<int, int> sumMap;
    sumMap[0] = 1;
    int currentSubarraySum = 0;
    for (int i = 0; i < n; i++)
    {
        currentSubarraySum += nums[i];
        int requiredSum = currentSubarraySum - k;
        if (sumMap.count(requiredSum))
        {
            subarraysWithSumK += sumMap[requiredSum];
        }
        sumMap[currentSubarraySum]++;
    }
    return subarraysWithSumK;
}
