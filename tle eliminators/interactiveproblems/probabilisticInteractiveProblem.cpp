#include <iostream>
#include <iomanip>
#include <random>
using namespace std;

bool isTesting = false;

// endl use krte hain to, no need to flushout
int ask(int index)
{
    cout << "? " << index << endl;
    int ans;
    cin >> ans;
    return ans;
}

// find an index of the majority element of the array
// Majority element is an element which occurs >= n/2 times 
// in the array.
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Number of elements in array
    int n = 1e9;
    int min = 1;
    int max = n;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);

    int randomValue = distrib(gen);

    for (size_t i = 0; i < 100; i++)
    {
        int index = distrib(gen);
        int result = ask(index);

        if (result == 1)
        {
            cout << "! " << index << endl;
            return 0;
        }
    }

    return 0;
}