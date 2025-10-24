#include <iostream>
#include <random>
#include <unordered_set>
#include <map>
using namespace std;

int smallspread(vector<int> &v){
    
}
 
int main()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for (size_t i = 0; i < n; i++)
    {
        cin>>v[i];
    }
    
    cout << smallspread(v);
    return 0;
}
