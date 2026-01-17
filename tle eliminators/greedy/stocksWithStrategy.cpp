#include <iostream>
#include <vector>

using namespace std;

class Solution {
    using ll = long long;

public:
    ll maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        int n = prices.size();
        vector<ll> prefprices(n), prefprofit(n);
        prefprices[0] = prices[0];
        for (int i = 1; i < n; i++) {
            prefprices[i] = prefprices[i - 1] + prices[i];
        }
        ll orig_profit = 0;
        for (int i = 0; i < n; i++) {
            orig_profit += prices[i] * strategy[i];
            prefprofit[i] = orig_profit;
        }

        ll max_profit = orig_profit;

        for (int end = k - 1; end < n; ++end) {
            int start = end - k + 1;
            ll subarray_profit = start == 0
                                     ? prefprofit[end]
                                     : prefprofit[end] - prefprofit[start - 1];
            ll subarray_prices = prefprices[end] - prefprices[start + (k / 2) - 1];
            max_profit = max(max_profit, orig_profit - subarray_profit + subarray_prices);
        }

        return max_profit;
    }
};

int main()
{
    Solution *sol = new Solution();
    int n=3, k=2;
    vector<int> prices = {4,2,8}, strategy = {-1,0,1};
    // for(int i=0;i<n;i++){
    //     cin>>prices[i];
    // }
    // for(int i=0;i<n;i++){
    //     cin>>strategy[i];
    // }
    cout<<sol->maxProfit(prices, strategy, k)<<endl;
    return 0;
}