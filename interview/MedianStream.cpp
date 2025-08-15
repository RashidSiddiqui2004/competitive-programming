#include <iostream>
using namespace std;

class MedianFinder {
    priority_queue<int> left; // max heap
    priority_queue<int, vector<int>, greater<int>> right; // min heap
    // size(left) <= 1 + size(right)
public: 
    void addNum(int num) {
        // Step 1: Push into correct heap
        if (left.empty() || num <= left.top()) {
            left.push(num);
        } else {
            right.push(num);
        }

        // Step 2: Balance the heaps
        if (left.size() > right.size() + 1) {
            right.push(left.top());
            left.pop();
        } else if (right.size() > left.size()) {
            left.push(right.top());
            right.pop();
        }
    }

    double findMedian() { 
        if(left.size() == right.size()){
            return (left.top() + right.top()) / 2.0;
        }
        return left.top();
    }
};

int main() {
    MedianFinder mf;
    vector<int> stream = {5, 15, 1, 3};
    for (int num : stream) {
        mf.addNum(num);
        cout << "Median after inserting " << num << ": " << mf.findMedian() << "\n";
    }
}
