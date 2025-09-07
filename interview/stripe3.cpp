#include <iostream>
using namespace std;

bool isDirectConversionPossible(
    const vector<string> &conversions,
    string sourceCurrency,
    string targetCurrency,
    int amount)
{
    unordered_map<string, vector<pair<string, pair<string, int>>>> adjlist;

    for (auto &conversion : conversions)
    {
        // USD:CAD:DHL:5
        string temp = conversion;
        int pos = find(temp.begin(), temp.end(), ':') - temp.begin();
        string source = temp.substr(0, pos);
        temp = temp.substr(pos + 1);
        pos = find(temp.begin(), temp.end(), ':') - temp.begin();
        string target = temp.substr(0, pos);
        temp = temp.substr(pos + 1);
        pos = find(temp.begin(), temp.end(), ':') - temp.begin();
        string shippingMethod = temp.substr(0, pos);
        temp = temp.substr(pos + 1);
        pos = find(temp.begin(), temp.end(), ':') - temp.begin();
        string costStr = temp.substr(0, pos);
        int cost = 0;
        for (auto i : costStr)
        {
            cost *= 10;
            cost += (i - '0');
        }
        adjlist[source].push_back({target, {shippingMethod, cost}});
    }

    if (!adjlist.count(sourceCurrency))
    {
        return 0;
    }

    for (auto i : adjlist[sourceCurrency])
    {
        if (i.first == targetCurrency)
        {
            // print the shipping method
            cout << i.second.first << " " << i.second.second << endl;
            return 1;
        }
    }
}

bool isAtmostOneHopConversionPossible(
    const vector<string> &conversions,
    string sourceCurrency,
    string targetCurrency,
    int amount)
{
    unordered_map<string, vector<pair<string, pair<string, int>>>> adjlist;

    for (auto &conversion : conversions)
    {
        string temp = conversion;
        int pos = find(temp.begin(), temp.end(), ':') - temp.begin();
        string source = temp.substr(0, pos);
        temp = temp.substr(pos + 1);
        pos = find(temp.begin(), temp.end(), ':') - temp.begin();
        string target = temp.substr(0, pos);
        temp = temp.substr(pos + 1);
        pos = find(temp.begin(), temp.end(), ':') - temp.begin();
        string shippingMethod = temp.substr(0, pos);
        temp = temp.substr(pos + 1);
        pos = find(temp.begin(), temp.end(), ':') - temp.begin();
        string costStr = temp.substr(0, pos);
        int cost = 0;
        for (auto i : costStr)
        {
            cost *= 10;
            cost += (i - '0');
        }
        adjlist[source].push_back({target, {shippingMethod, cost}});
    }

    if (!adjlist.count(sourceCurrency))
    {
        return 0;
    }

    // O(N^2)
    for (auto i : adjlist[sourceCurrency])
    {
        for (auto j : adjlist[i.first])
        {
            if (j.first == targetCurrency)
            {
                cout << i.second.first << " " << j.second.first << endl;
                return 1;
            }
        }
    }
}

int minimumCostforConversion(
    const vector<string> &conversions,
    string sourceCurrency,
    string targetCurrency,
    int amount)
{
    unordered_map<string, vector<pair<string, pair<string, int>>>> adjlist;

    for (auto &conversion : conversions)
    {
        string temp = conversion;
        int pos = find(temp.begin(), temp.end(), ':') - temp.begin();
        string source = temp.substr(0, pos);
        temp = temp.substr(pos + 1);
        pos = find(temp.begin(), temp.end(), ':') - temp.begin();
        string target = temp.substr(0, pos);
        temp = temp.substr(pos + 1);
        pos = find(temp.begin(), temp.end(), ':') - temp.begin();
        string shippingMethod = temp.substr(0, pos);
        temp = temp.substr(pos + 1);
        pos = find(temp.begin(), temp.end(), ':') - temp.begin();
        string costStr = temp.substr(0, pos);
        int cost = 0;
        for (auto i : costStr)
        {
            cost *= 10;
            cost += (i - '0');
        }
        adjlist[source].push_back({target, {shippingMethod, cost}});
    }

    if (!adjlist.count(sourceCurrency))
    {
        return 0;
    }

    int minimumCost = INT_MAX;
    for (auto i : adjlist[sourceCurrency])
    {
        for (auto j : adjlist[i.first])
        {
            if (j.first == targetCurrency)
            {
                minimumCost = min(minimumCost, i.second.second + j.second.second);
            }
        }
    }
    return minimumCost;
}

int main()
{
    int n;
    cin >> n;
    vector<string> conversions(n);

    for (size_t i = 0; i < n; i++)
    {
        cin >> conversions[i];
    }

    string sourceCurrency;
    cin >> sourceCurrency;
    string targetCurrency;
    cin >> targetCurrency;

    int amount;
    cin >> amount;

    // cout << isDirectConversionPossible(conversions, sourceCurrency, targetCurrency, amount);
    // cout << isAtmostOneHopConversionPossible(conversions, sourceCurrency, targetCurrency, amount);
    cout << minimumCostforConversion(conversions, sourceCurrency, targetCurrency, amount);

    return 0;
}