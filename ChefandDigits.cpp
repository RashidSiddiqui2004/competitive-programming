#include <iostream>
#include <string.h>
using namespace std;

using ll = long long;

// A number is said to be a "good integer"
// if its digits frequency is not ugly.

// For handling large integers
const ll mod = 1e9 + 7;

vector<int> ugly_freq;
unordered_map<string, int> dp;

ll helper(string bound,
          int pos,
          bool istight,
          bool started,
          vector<int> &freq)
{
    // pos, istight, started, freq
    string key = to_string(pos) + "," + to_string(istight) + "," + to_string(started);
    for (int i = 0; i < 10; i++)
    {
        key += to_string(freq[i]);
        key += ",";
    }

    if (dp.count(key))
    {
        return dp[key];
    }

    if (pos == (int)bound.size())
    {
        if (!started)
            return 0;
        for (int i = 0; i < 10; i++)
        {
            if (freq[i] == ugly_freq[i])
            {
                return 0;
            }
        }
        return 1;
    }

    int limit = istight ? bound[pos] - '0' : 9;

    ll ans = 0;

    for (int dig = 0; dig <= limit; dig++)
    {
        bool nextTight = istight && (dig == limit);
        bool nextStarted = started || (dig != 0);

        if (!nextStarted)
        {
            ans = (ans + helper(bound, pos + 1, nextTight, false, freq)) % mod;
        }
        else
        {
            freq[dig]++;
            ans = (ans + helper(bound, pos + 1, nextTight, true, freq)) % mod;
            freq[dig]--;
        }
    }

    return dp[key] = ans % mod;
}

/// Find all the "good integers" in the range [lower_bound, upper_bound].
/// Reference -
// https://www.codechef.com/problems/DGTCNT
ll numberOfGoodIntegers(int lower_bound, int upper_bound)
{
    string upperbound = to_string(upper_bound);
    string lowerbound = to_string(lower_bound - 1);
    vector<int> freq(10);
    dp.clear();
    ll tillupperbound = helper(upperbound, 0, true, false, freq) % mod;
    dp.clear();
    ll tilllowerbound = helper(lowerbound, 0, true, false, freq) % mod;

    return ((tillupperbound - tilllowerbound) + mod) % mod;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int l, r;
        cin >> l >> r;

        ugly_freq = vector<int>(10);

        for (size_t i = 0; i < 10; i++)
        {
            cin >> ugly_freq[i];
        }

        cout << numberOfGoodIntegers(l, r) << endl;
    }

    return 0;
}