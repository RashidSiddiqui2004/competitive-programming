#include <iostream>
#include <random>
using namespace std;

bool istesting = false;

int mine1x = 3, mine1y = 8;
int mine2x = 2, mine2y = 3;

int judge(int x, int y)
{
    return min(abs(x - mine1x) + abs(y - mine1y), abs(x - mine2x) + abs(y - mine2y));
}

int n, m;

int query(int x, int y)
{
    cout << "? " << x << ' ' << y << endl;
    if (istesting)
    {
        return judge(x, y);
    }
    int res;
    cin >> res;
    return res;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        cin >> n >> m;
        int x = n, y = 1;
        int dist = query(x, y);
        if (dist == 0)
        {
            cout << "! " << x << " " << y << endl;
            continue;
        }
        else
        {
            int x1, y1, x2, y2;
            if (dist + 1 <= m)
            {
                x1 = n;
                y1 = dist + 1;
            }
            else
            {
                x1 = n + m - 1 - dist;
                y1 = m;
            }
            if (n - dist >= 1)
            {
                x2 = n - dist;
                y2 = 1;
            }
            else
            {
                x2 = 1;
                y2 = dist + 2 - n;
            }
            int dist2 = query(x1, y1);
            int dist3 = query(x2, y2);

            if (dist2 == 0)
            {
                cout << "! " << x1 << " " << y1 << endl;
                continue;
            }
            if (dist3 == 0)
            {
                cout << "! " << x2 << " " << y2 << endl;
                continue;
            }

            int potx1, poty1, potx2, poty2;
            potx1 = x1 - dist2 / 2;
            poty1 = y1 - dist2 / 2;

            potx2 = x2 + dist3 / 2;
            poty2 = y2 + dist3 / 2;

            int potdist = query(potx1, poty1);
            if (potdist == 0)
            {
                cout << "! " << potx1 << " " << poty1 << endl;
            }
            else
            {
                cout << "! " << potx2 << " " << poty2 << endl;
            }
        }
    }

    return 0;
}