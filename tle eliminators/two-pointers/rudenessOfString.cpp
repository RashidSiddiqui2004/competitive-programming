#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

int main()
{
    ll n, maxRudenessAllowed;
    cin >> n >> maxRudenessAllowed;

    string s;
    cin >> s;

    ll maxlength = 0ll;
    ll l = 0, r = 0;
    ll countAs = 0ll, countBs = 0ll, currRudeness = 0ll;

    for (; r < n; r++)
    {
        if (s[r] == 'a')
        {
            countAs++;
        }
        else if(s[r]=='b')
        {
            currRudeness += countAs;
            countBs++;
        }
        while (l <= r and currRudeness > maxRudenessAllowed)
        {
            if (s[l] == 'a')
            {
                countAs--;
                currRudeness = max(0ll, currRudeness - countBs);
            }
            else if(s[l]=='b')
            {
                countBs--;
            }
            ++l;
        }
        if (currRudeness <= maxRudenessAllowed)
            maxlength = max(maxlength, r - l + 1);
    }

    cout << maxlength << endl;

    return 0;
}