#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int longestSelfSufficientSubstring(const string &s)
{
    // Conditions for self-sufficient substring
    // 1. substring ≠ s
    // 2. letters present in substring can't be present outside
    // the substring

    vector<pair<int, int>> pos(26, {-1, -1});
    int n = s.size();

    for (int i = 0; i < n; i++)
    {
        int index = s[i] - 'a';
        if (pos[index].first == -1)
        {
            pos[index].first = i;
        }
        pos[index].second = i;
    }

    int ans = 0;

    for (int i = 0; i < 26; i++)
    {
        // only if that character is present in the string
        if (pos[i].first != -1)
        {
            int startindex = pos[i].first;
            int j = pos[i].first + 1, lastindex = pos[i].second;
            int currMaxLength = 0;
            while (j < n)
            {
                int index = s[j] - 'a';
                startindex = min(startindex, pos[index].first);
                lastindex = max(lastindex, pos[index].second);
                if (j == lastindex)
                {
                    int length = lastindex - startindex + 1;
                    if (length != n)
                    {
                        currMaxLength = max(currMaxLength, length);
                    }
                }
                ++j;
            }
            ans = max(ans, currMaxLength);
        }
    }

    return ans;
}

int verifySumofDistinctElementinsubarrays(int n, vector<int> &v)
{
    int ans = 0;
    for (size_t i = 0; i < n; i++)
    {
        map<int, int> mp;
        for (size_t j = i; j < n; j++)
        {
            mp[v[j]]++;
            ans += mp.size();
        }
    }
    return ans;
}

int SumofDistinctElementinsubarrays(int n, vector<int> &v)
{
    map<int, vector<int>> positionsMap;

    for (int i = 0; i < n; i++)
    {
        positionsMap[v[i]].push_back(i);
    }

    int ans = 0;
    int totalSubarrays = (n * (n + 1)) / 2;

    for (auto& pair : positionsMap)
    {
        int element = pair.first;
        vector<int>& positionsVector = pair.second;
        int m = positionsVector.size();
        int totalAbsentSubarrays = (positionsVector[0] * (positionsVector[0] + 1)) / 2;
        for (int i = 0; i < m - 1; i++)
        {
            int l = positionsVector[i + 1] - positionsVector[i] - 1;
            totalAbsentSubarrays += (l * (l + 1)) / 2;
        }
        int lastOccurence = positionsVector.back();
        totalAbsentSubarrays += ((n - lastOccurence - 1) * (n - lastOccurence)) / 2;
        ans += (totalSubarrays - totalAbsentSubarrays);
    }

    return ans;
}

class Solution
{
public:
    bool validWordAbbreviation(string word, string abbr)
    {
        int n = word.size(), m = abbr.size();
        int i = 0, j = 0;

        while (i < n)
        {
            if (j == m)
            {
                return false;
            }
            while (i < n and j < m and word[i] == abbr[j])
            {
                ++i, ++j;
            }
            if (i == n)
            {
                break;
            }
            if (j < m and (abbr[j] >= '1' and abbr[j] <= '9'))
            {
                int len = abbr[j++] - '0';
                while (j < m and abbr[j] >= '0' and abbr[j] <= '9')
                {
                    len *= 10;
                    len += abbr[j++] - '0';
                }
                i += len;
            }
            else
            {
                return false;
            }
        }

        if (i != n || j != m)
        {
            return false;
        }

        return true;
    }
};

int main()
{

    Solution *sol = new Solution();
    cout << sol->validWordAbbreviation("apple", "a3e") << endl;

    // string s;
    // cin >> s;

    // cout << longestSelfSufficientSubstring(s);

    // int n;
    // cin >> n;

    // vector<int> v(n);

    // for (size_t i = 0; i < n; i++)
    // {
    //     cin >> v[i];
    // }

    // bool isvalid = SumofDistinctElementinsubarrays(n, v) == verifySumofDistinctElementinsubarrays(n, v);

    // if(isvalid){
    //     cout<<"✅ Test passed";
    // }
    // else{
    //     cout<<"❌ Test failed";
    // }

    return 0;
}