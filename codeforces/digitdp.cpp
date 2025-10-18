#include <iostream>
using namespace std;

// A number is called a “classy number” if its decimal representation
//  contains not more than three non-zero digits.

// We are given a segment [L, R]. "L" and "R" are the given endpoints
// of a segment. Here, "L" is the left endpoint, and "R" is the right
// endpoint. We need to find the count of classy numbers present between
// "L" and "R," inclusive.

int mod = 1e9 + 7;

int dp[19][4][2][2];

int count(string &lower_bound, string &upper_bound, int cnt = 0,
          int pos = 0, bool ltight = 1, bool utight = 1)
{
    int n = lower_bound.size();
    if (pos == n)
    {
        return 1;
    }
    if (dp[pos][cnt][ltight][utight] != -1)
    {
        return dp[pos][cnt][ltight][utight];
    }
    int llim = ltight ? lower_bound[pos] - '0' : 0;
    int ulim = utight ? upper_bound[pos] - '0' : 9;
    int ans = 0;
    for (int i = llim; i <= ulim; i++)
    {
        bool cantake = i != 0 ? (cnt < 3) : 1;

        if (cantake)
            ans = (ans + count(lower_bound, upper_bound, cnt + (i != 0),
                               pos + 1, ltight && i == llim,
                               utight && i == ulim)) %
                  mod;
    }
    return dp[pos][cnt][ltight][utight] = ans % mod;
}

int main()
{
    memset(dp, -1, sizeof(dp));
    string l, r;
    cin >> l >> r;

    int zerocnt = (int)r.size() - (int)l.size();
    string trailingzeros = string(zerocnt, '0');
    l = trailingzeros + l;

    cout << count(l, r) << endl;

    return 0;
}