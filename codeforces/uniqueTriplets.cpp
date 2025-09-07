#include <iostream>
#include <set>
using namespace std;

//  0 <= nums[i] <= 1e9
//  1 <= len(nums) <= 2e5

// O(n*n)
set<vector<int>> uniqueTriplets(vector<int> &nums, int target)
{
    int len = nums.size();
    
    // no triplets exist
    if (len < 3)
    {
        return {};
    }

    unordered_map<int, int> freq;
    for (auto i : nums)
    {
        ++freq[i];
    }

    vector<int> uniqueElems;
    for (auto i : freq)
    {
        uniqueElems.push_back(i.first);
    }
    sort(uniqueElems.begin(), uniqueElems.end());

    int n = uniqueElems.size();
    set<vector<int>> triplets;

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (i == j and freq[uniqueElems[i]] > 1)
            {
                int diff = target - (uniqueElems[i] + uniqueElems[j]);
                int extraCount = (uniqueElems[i] == diff);
                extraCount += (uniqueElems[j] == diff);

                if (freq.count(diff) and freq[diff] > extraCount)
                {
                    vector<int> triplet = {uniqueElems[i], uniqueElems[j], diff};
                    sort(triplet.begin(), triplet.end());
                    triplets.insert(triplet);
                }
            }
            else if (i != j)
            {
                int diff = target - (uniqueElems[i] + uniqueElems[j]);
                int extraCount = (uniqueElems[i] == diff);
                extraCount += (uniqueElems[j] == diff);

                if (freq.count(diff) and freq[diff] > extraCount)
                {
                    vector<int> triplet = {uniqueElems[i], uniqueElems[j], diff};
                    sort(triplet.begin(), triplet.end());
                    triplets.insert(triplet);
                }
            }
        }
    }
    return triplets;
}

int main()
{
    int n;
    cin >> n;
    vector<int> nums(n);
    for (size_t i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    int t;
    cin >> t;

    auto uniquetriplets = uniqueTriplets(nums, t);

    for (auto &triplet : uniquetriplets)
    {
        cout << triplet[0] << " " << triplet[1] << " " << triplet[2] << endl;
    }

    return 0;
}