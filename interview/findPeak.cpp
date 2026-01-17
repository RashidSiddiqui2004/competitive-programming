#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();
        for (int i = 1; i < n - 1; i++) {
            if (nums[i] > nums[i - 1] &&
                nums[i] > nums[i + 1]) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    ifstream fin("input.txt");
    ifstream fout("output.txt");

    if (!fin.is_open() || !fout.is_open()) {
        cout << "Error opening input/output file\n";
        return 1;
    }

    Solution sol;

    int t;
    fin >> t;

    while (t--) {
        int n;
        fin >> n;

        vector<int> nums(n);
        for (int i = 0; i < n; i++) {
            fin >> nums[i];
        }

        bool result = sol.find132pattern(nums);

        string expected;
        fout >> expected;

        string actual = result ? "True" : "False";

        if (actual != expected) {
            cout << "FAIL (Expected: " << expected
                 << ", Got: " << actual << ")\n";
        }
    }

    fin.close();
    fout.close();
    return 0;
}
