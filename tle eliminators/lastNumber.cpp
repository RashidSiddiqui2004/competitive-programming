#include <iostream>
#include <vector>
#include <set>
using namespace std;

bool istesting = false;

vector<int> v = {3, 2, 4, 5, 6, 1, 9, 8, 7};

int judge(int index, int x)
{
    return (v[index - 1] & x) != 0;
}

int query(int x, int y)
{
    cout << "? " << x << ' ' << y << endl;
    if (istesting)
    {
        // cout << judge(x, y) << endl;
        return judge(x, y);
    }
    int res;
    cin >> res;
    return res;
}

void output(int ans)
{
    cout << "! " << ans << endl;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;
        set<int> values, indices;
        for (int i = 1; i < n; i++)
        {
            values.insert(i);
            indices.insert(i);
        }
        values.insert(n);

        for (int i = 0; i < 15; i++)
        {
            set<int> grp1indices;
            set<int> grp2indices;

            int b = 1 << i;
            for (auto i : indices)
            {
                if (query(i, b))
                {
                    grp1indices.insert(i);
                }
                else
                {
                    grp2indices.insert(i);
                }
            }

            int grp1cnt = grp1indices.size(), grp2cnt = grp2indices.size();
            int grp1actcnt = 0, grp2actcnt = 0;

            set<int> grp1values;
            set<int> grp2values;

            for (auto i : values)
            {
                if (i & b)
                {
                    grp1actcnt++;
                    grp1values.insert(i);
                }
                else
                {
                    grp2actcnt++;
                    grp2values.insert(i);
                }
            }

            if (grp1cnt != grp1actcnt)
            {
                values = grp1values;
                indices = grp1indices;
            }
            else
            {
                values = grp2values;
                indices = grp2indices;
            }
        }
   
        output(*values.begin());
    }

    return 0;
}