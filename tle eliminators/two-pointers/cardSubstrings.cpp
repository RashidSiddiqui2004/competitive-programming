// https://codeforces.com/edu/course/2/lesson/9/3/practice/contest/307094/problem/F

#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

int main()
{
    ll n, m;
    cin >> n >> m;

    string s, cards;
    cin >> s >> cards;

    vector<int> totalcnt(26, 0);
    for (auto i : cards)
    {
        totalcnt[i - 'a']++;
    }

    ll numsubstrings = 0ll;
    ll l = 0, r = 0;
    vector<int> currfreq(26, 0);

    for (; r < n; r++)
    {
        int currchar = s[r] - 'a';
        currfreq[currchar]++;
        while (l <= r and currfreq[currchar] > totalcnt[currchar])
        {
            --currfreq[s[l]-'a'];
            ++l;
        }
        numsubstrings += max(0ll, r - l + 1);
    }

    cout << numsubstrings << endl;

    return 0;
}