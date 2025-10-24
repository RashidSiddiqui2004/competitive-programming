#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    vector<int> divisors;
    int query_count = 0;

    for (int p : primes) {
        cout << p << endl;
        query_count++;
        string response;
        cin >> response;
        if (response == "yes") {
            divisors.push_back(p);
            if (p * p <= 100) {  
                cout << p * p << endl;
                fflush(stdout);
                query_count++;
                cin >> response;
                if (response == "yes") {
                    cout << "composite" << endl;
                    return 0;
                }
            }
        }
        if (query_count >= 20) break;
    }
    
    if (divisors.size() > 1) {
        cout << "composite" << endl;
        fflush(stdout);
        
    } else {
        cout << "prime" << endl;
        fflush(stdout);
    }
    
    return 0;
}