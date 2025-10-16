#include <iostream>
#include <map>
#include <vector>

using namespace std;

class ExamTracker {
    using ll = long long;
    map<int, int> mp;
    vector<int> v;
    int size;

public:
    ExamTracker() {
        mp.clear();
        size = 0;
    }

    void record(int time, int score) {
        if (size == 0) {
            v.push_back(score);
        } else {
            v.push_back(v.back() + score);
        }
        mp[time] = size++;
    }

    ll totalScore(int startTime, int endTime) {
        // int l = mp[startTime], r = mp[endTime];
        int l = 0, r = size - 1;

        if (mp.lower_bound(startTime) != mp.end()) {
            l = (mp.lower_bound(startTime))->second;
        }

        auto t = mp.upper_bound(endTime);

        if(t==mp.end()){
        }
        else{
            --t;
            r = t->second;
        }

        cout << l << " " << r << endl;
        // sum[l....r] inclusive
        // sum[l, r] = sum[0, r] - sum[0, l-1]
        ll sum0r = v[r];
        ll sum0lminus1 = l == 0 ? 0 : v[l - 1];
        return sum0r - sum0lminus1;
    }
};

/**
 * Your ExamTracker object will be instantiated and called as such:
 * ExamTracker* obj = new ExamTracker();
 * obj->record(time,score);
 * long long param_2 = obj->totalScore(startTime,endTime);
 */