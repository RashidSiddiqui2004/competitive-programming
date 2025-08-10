#include <iostream>
#include <string>
using namespace std;

// A subsequence of a string s is considered a good palindromic subsequence if:

// It is a subsequence of s. 
// It is a palindrome (has the same value if reversed). 🎶
// It has an even length.
// No two consecutive characters are equal, except the two middle ones. ❤️

class Solution {
    int dp[250][250][27];
    int solve(string &s,int l,int r, int lastchar){
        // The middle characters must be same, and only even length palindromes
        // are considered good palindrome.
        int ind = s[l] - 'a';
        if(l+1 == r){
            if(ind!=lastchar){
                return s[l]==s[r] ? 2 : 0;
            }
            return 0;
        }
        if(l>=r){
            return 0;
        }
        if(dp[l][r][lastchar]!=-1){
            return dp[l][r][lastchar];
        }
        int ans = 0;
        if(s[l]==s[r]){
            if(ind!=lastchar){
                ans=2+solve(s,l+1,r-1,ind);
            }
        }
        else{
            ans=max(solve(s,l+1,r,lastchar),solve(s,l,r-1,lastchar)); 
        }
        return dp[l][r][lastchar] = ans;  
    }
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        memset(dp,-1,sizeof(dp));
        return solve(s,0,n-1,26);
    }
};

int main(){
    cout<<"Longest Palindromic Subsequence II\n";
    Solution object = Solution();
    
    cout<<object.longestPalindromeSubseq("abefebda")<<endl;
    cout<<object.longestPalindromeSubseq("bbabab")<<endl;
    cout<<object.longestPalindromeSubseq("dcbccacdb")<<endl;

    // extreme case -: long string
    string longString = "";
    for(int i=0;i<250;i++){
        int randomIndex = rand() % 26;
        longString+=('a' + randomIndex);
    } 
    cout<<object.longestPalindromeSubseq(longString)<<endl;
    return 0;
}