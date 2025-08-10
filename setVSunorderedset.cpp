#include <iostream>
#include <set>
#include <unordered_set>
#include <random>
using namespace std;
using namespace chrono;

// Function to generate random strings
string random_string(size_t length) {
    static const string chars = "abcdefghijklmnopqrstuvwxyz";
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0, chars.size() - 1);

    string s;
    s.reserve(length);
    for (size_t i = 0; i < length; i++)
        s += chars[dis(gen)];
    return s;
}

int main() {
    const int N = 100000;  // number of strings
    const int LEN = 10;    // length of each string

    vector<string> data;
    data.reserve(N);
    for (int i = 0; i < N; i++)
        data.push_back(random_string(LEN));

    // -------------------- std::set --------------------
    {
        set<string> s;

        auto start = high_resolution_clock::now();
        for (auto &str : data)
            s.insert(str);
        auto mid = high_resolution_clock::now();
        for (auto &str : data)
            s.find(str);
        auto end = high_resolution_clock::now();

        cout << "std::set:\n";
        cout << "  Insert time: " 
             << duration_cast<milliseconds>(mid - start).count() << " ms\n";
        cout << "  Find time:   " 
             << duration_cast<milliseconds>(end - mid).count() << " ms\n\n";
    }

    // -------------------- std::unordered_set --------------------
    {
        unordered_set<string> us;
        us.reserve(N); // prevent rehashing

        auto start = high_resolution_clock::now();
        for (auto &str : data)
            us.insert(str);
        auto mid = high_resolution_clock::now();
        for (auto &str : data)
            us.find(str);
        auto end = high_resolution_clock::now();

        cout << "std::unordered_set:\n";
        cout << "  Insert time: " 
             << duration_cast<milliseconds>(mid - start).count() << " ms\n";
        cout << "  Find time:   " 
             << duration_cast<milliseconds>(end - mid).count() << " ms\n";
    }

    return 0;
}
