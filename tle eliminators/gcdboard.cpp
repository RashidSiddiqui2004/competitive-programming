#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

bool ispossible(vector<int> &v, int k, int mid){
    int n = v.size();

    for (int i = 0; i < n; i++)
    {
        int a = v[i];
        if(a >= 3*mid){
            
        }
        else{
            if(k==0) return false;
            k--;
        }
    }
    
    return true;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n, k;
        cin >> n >> k;
        vector<int> v(n);
        for (size_t i = 0; i < n; i++)
        {
            cin >> v[i];
        }

        // sort(v.begin(), v.end());
        int low=2, high =n, ans=1, mid;
        
        while (low<=high)
        {
            mid=(low+high)/2;
            if(ispossible(v, k, mid)){
                low=mid+1;
                ans=mid;
            }
            else{
                high=mid-1;
            }
        }
        
        cout<<ans<<endl;
    }

    return 0;
}