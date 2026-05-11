#include <iostream>
using namespace std;

class WordDistance
{
    unordered_map<string, vector<int>> positions;

public:
    WordDistance(const vector<string> &dictionary)
    {
        int n = dictionary.size();
        for (int i = 0; i < n; i++)
        {
            positions[dictionary[i]].push_back(i);
        }
    }

    int minDistance(const string &a, const string &b)
    {
        // Return -1, if one of the words don't appear in the dictionary.
        if (!positions.count(a) || !positions.count(b))
        {
            return -1;
        }
        vector<int> positionsA = positions[a];
        vector<int> positionsB = positions[b];

        int result = 1e9;
        int ptrA = 0, ptrB = 0;

        while (ptrA < (int)positionsA.size() && ptrB < (int)positionsB.size())
        {
            result = min(result, abs(positionsA[ptrA] - positionsB[ptrB]));

            if(positionsA[ptrA] < positionsB[ptrB]){
                ++ptrA;
            }
            else{
                ++ptrB;
            }
        }

        return result;
    }
};

int main()
{
    vector<string> dictionary = {"practice", "makes", "perfect", "coding", "nice", "makes"};
    WordDistance wordDistance = WordDistance(dictionary);
    string a, b;

    int t;
    cin>>t;

    while (t--)
    {   
        cin>>a>>b;
        cout<<wordDistance.minDistance(a, b);
    }
    return 0;
}