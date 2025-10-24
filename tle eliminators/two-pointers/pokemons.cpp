#include <iostream>
#include <random>
#include <unordered_set>
#include <map>
using namespace std;

int subarraySumLessthanEqualtoK(string s)
{
    int n = s.size();
    int currentSubarraySum = 0;
    unordered_set<char> st(s.begin(), s.end());
    int uniqCount = st.size();

    map<char, int> mp;
    int l = 0, r = 0;
    int res = n;

    for (; r < n; r++)
    {
        mp[s[r]]++;
        while (l <= r and (int)mp.size() == uniqCount and mp[s[l]] > 1)
        {
            if (--mp[s[l]] == 0)
            {
                mp.erase(s[l]);
            }
            l++;
        }
        if (mp.size() == uniqCount)
        {
            res = min(res, r - l + 1);
        }
    }
    return res;
}

int main()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    cout << subarraySumLessthanEqualtoK(s);
    return 0;
}
