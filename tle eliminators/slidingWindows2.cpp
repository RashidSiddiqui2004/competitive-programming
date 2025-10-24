#include <iostream>
#include <map>
using namespace std;

// fixed sized sliding window
// dynamic sized sliding window

// always use map as there is guaranteed worst case TC of O(log(sizeofmap))
// as there may be collisions in case of unordered_map -> O(sizeofmap) complexity

// return the maximum sum of a subarray of size k
// with all distinct elements, return 0 if no such subarray exists.
// v[i] belongs to [-1e9, 1e9]
int maximumSubarraySumofSizek(int n, vector<int> &v, int k)
{
    int ans = INT_MIN;
    int sum = 0;
    map<int,int> mp;

    for (int i = 0; i < n; i++)
    {
        sum += v[i];
        mp[v[i]]++; // O(logk)

        if (i >= k)
        {
            sum -= v[i - k];
            if(--mp[v[i-k]]==0){
                mp.erase(v[i-k]); // O(logk)
            }
        }

        if ((int)mp.size() == k)
        {
            ans = max(ans, sum);
        }
    }

    return (ans == INT_MIN) ? 0 : ans;
}

int main()
{
    int n, k;
    cin >> n>>k;
    vector<int> v(n);
    for (size_t i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    cout << maximumSubarraySumofSizek(n, v, k);
    return 0;
}