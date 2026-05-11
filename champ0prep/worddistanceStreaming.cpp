#include <iostream>
#include <set>
using namespace std;

class WordDistance
{
    int index = 0;
    unordered_map<string, set<int>> positions;

public:
    void add(const string &a)
    {
        positions[a].insert(index++);
    }

    int minDistance(const string &a, const string &b)
    {
        // Return -1, if one of the words don't appear in the dictionary.
        if (!positions.count(a) || !positions.count(b))
        {
            return -1;
        }
        vector<int> positionsA = vector<int>(positions[a].begin(), positions[a].end());
        vector<int> positionsB = vector<int>(positions[b].begin(), positions[b].end());
        int result = 1e9;
        int ptrA = 0, ptrB = 0;

        while (ptrA < (int)positionsA.size() && ptrB < (int)positionsB.size())
        {
            result = min(result, abs(positionsA[ptrA] - positionsB[ptrB]));

            if (positionsA[ptrA] < positionsB[ptrB])
            {
                ++ptrA;
            }
            else
            {
                ++ptrB;
            }
        }

        return result;
    }
};

int main()
{
    WordDistance wordDistance;

    int n;
    cout<<"Number of words in dictionary: ";
    cin >> n;

    while (n--)
    {
        string s;
        cin >> s;
        wordDistance.add(s);
    }

    int t;
    cout<<"Number of queries: ";
    cin >> t;

    while (t--)
    {
        string a, b;
        cin >> a >> b;
        cout << wordDistance.minDistance(a, b)<<endl;
    }
    return 0;
}