#include<iostream>
using namespace std;

vector<vector<int>> result;

void generateUniquePermutationsWithoutRepeatingNumbersHelper(
    vector<int> &v, int pos){
    int n = v.size();
    if(pos==n){
        result.push_back(v);
        return;
    }
    for(int i=pos;i<n;i++){
        swap(v[pos], v[i]);
        generateUniquePermutationsWithoutRepeatingNumbersHelper(v, pos+1);
        swap(v[pos], v[i]);
    }
}
// v has no repetition
void generateUniquePermutationsWithoutRepeatingNumbers(vector<int> &v){
    int n = v.size();
    sort(v.begin(),v.end());
    generateUniquePermutationsWithoutRepeatingNumbersHelper(v, 0);
    for(auto t : result){
        for(auto i: t){
            cout<<i<<" ";
        }
        cout<<endl;
    }
}

void generateUniquePermutationsWithRepeatingNumbersHelper(
    vector<int> &v, int pos){
    int n = v.size();
    if(pos==n){
        result.push_back(v);
        return;
    }
    for(int i=pos;i<n;i++){
        if(i!=0 and i!=pos and v[i]==v[i-1]){
            continue;
        }
        swap(v[pos], v[i]);
        generateUniquePermutationsWithRepeatingNumbersHelper(v, pos+1);
        swap(v[pos], v[i]);
    }
}
// v may have repetition
void generateUniquePermutationsWithRepeatingNumbers(vector<int> &v){
    int n = v.size();
    sort(v.begin(),v.end());
    generateUniquePermutationsWithRepeatingNumbersHelper(v, 0);
    for(auto t : result){
        for(auto i: t){
            cout<<i<<" ";
        }
        cout<<endl;
    }
}

// Recursively remove adjacent duplicates – Example: "abbaca" → "ca".
string removeDuplicates(string s) {
        stack<char> st;
        string ans = "";

        for(auto i: s){
            if(st.empty()){
                st.push(i);
            }
            else{
                if(st.top() == i){
                    st.pop();
                }else{
                    st.push(i);
                }
            }
        }

        while(!st.empty()){
            ans += st.top();
            st.pop();
        }

        reverse(ans.begin(), ans.end());

        return ans;
    }

int main(){
    int n;
    cin>>n;
    vector<int> v(n);
    for (size_t i = 0; i < n; i++)
    {
        cin>>v[i];
    }
    generateUniquePermutationsWithRepeatingNumbers(v);
    return 0;
}