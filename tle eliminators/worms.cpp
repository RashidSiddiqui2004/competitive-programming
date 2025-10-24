#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> v;
    int start = 1;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        v.push_back({start, start + a - 1});
        start += a;
        // cout<<v.back().first<<" "<<v.back().second<<endl;
    }

    int k;
    cin >> k;

    for (int i = 0; i < k; i++)
    {
        int label;
        cin >> label;
        int it = std::upper_bound(v.begin(), v.end(), make_pair(label+1, -1)) - v.begin();
        cout << std::max(1, it) << endl;
    }

    return 0;
}