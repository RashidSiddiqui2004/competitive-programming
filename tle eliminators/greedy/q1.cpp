#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>
using namespace std;

using ll = long long;

void sol1()
{

    ll n, k;
    cin >> n >> k;

    vector<ll> divisors;

    int m = sqrt(n);

    for (int i = 1; i <= m; i++)
    {
        if ((n % i) == 0)
        {
            divisors.push_back(i);
        }
    }

    int t = divisors.size();
    for (int i = 0; i < t - 1; i++)
    {
        divisors.push_back(n / divisors[i]);
    }

    if ((n / divisors[t - 1]) != divisors[t - 1])
    {
        divisors.push_back(n / divisors[t - 1]);
    }

    t = divisors.size();

    if (k > t)
    {
        cout << -1 << endl;
    }
    else
    {
        sort(divisors.begin(), divisors.end());

        cout << divisors[k - 1] << endl;
    }
}

pair<ll, ll> helper(ll a, ll b, ll c,
                    vector<ll> &usb, vector<ll> &ps,
                    bool ordering = true)
{
    ll maxComputers = 0, cost = 0;

    int p1 = 0, p2 = 0;
    int n_usb = usb.size(), n_ps = ps.size();

    if (ordering)
    {
        while ((c--) and ((p1 < n_usb) || (p2 < n_ps)))
        {
            maxComputers++;
            if (p1 == n_usb)
            {
                cost += ps[p2++];
            }
            else if (p2 == n_ps)
            {
                cost += ps[p2++];
            }
            else if (usb[p1] <= ps[p2])
            {
                cost += usb[p1++];
            }
            else
            {
                cost += ps[p2++];
            }
        }
    }

    while (a-- and (p1 < n_usb))
    {
        maxComputers++;
        cost += usb[p1++];
    }

    while (b-- and (p2 < n_ps))
    {
        maxComputers++;
        cost += ps[p2++];
    }

    if (!ordering)
    {
        if (p1 == n_usb)
        {
            cost += ps[p2++];
        }
        else if (p2 == n_ps)
        {
            cost += ps[p2++];
        }
        else if (usb[p1] <= ps[p2])
        {
            cost += usb[p1++];
        }
        else
        {
            cost += ps[p2++];
        }
    }

    return {maxComputers, cost};
}

void sol2()
{
    ll a, b, c;
    cin >> a >> b >> c;

    ll m;
    cin >> m;
    vector<ll> usb, ps;

    for (size_t i = 0; i < m; i++)
    {
        ll price;
        string type;
        cin >> price >> type;
        if (type == "USB")
        {
            usb.push_back(price);
        }
        else
        {
            ps.push_back(price);
        }
    }

    sort(usb.begin(), usb.end());
    sort(ps.begin(), ps.end());

    auto [maxcomputers, cost] = helper(a, b, c, usb, ps, true);
    auto [maxcomputers2, cost2] = helper(a, b, c, usb, ps, false);

    if (maxcomputers2 > maxcomputers)
    {
        cost = cost2;
    }
    else if(maxcomputers2 == maxcomputers){
        cost = min(cost, cost2);
    }

    cout << maxcomputers << " " << cost << endl;
}

int main()
{
    sol2();
    return 0;
}