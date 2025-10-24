#include <iostream>
#include <iomanip>
using namespace std;

// how to update low and high in real search space
// ????

// we'll be given how many decimal places do we need correctly.
// or max. absolute error allowed

// if abs error <= 1e(-5) = 0.00001
// |actual- output| <= 0.00001

// If the relative error is equivalent is for y = 10^(-3)
// then if we print any answer which is correct upto 4 decimal places will work.

// correct = 12.944893
// accepted values = {12.9448, 12.94483939, ....}
// not accepted values = {13, 12.95, ...}

// we can deal with infinite candidate space
// by fixing the number of decimal places

// find the highest real number x, such that x^2 <= y
// correct upto 6 decimal places or abs error <= 1e-5
int main()
{
    double n;
    cin >> n;

    double low = 0, high = n, mid, ans;

    // use 1 extra decimal place precision to avoid
    // getting skipping on some candidate elements.

    // for upto 5 decimal places -> use 1e-6
    // for abs error upto 1e-8 -> use 1e-10
    double step_size = 1e-7; // number of decimal places ke equal
    
    // Number of iterations = log2(search space)
    // iterations can be max 100 for much precise values(1e-10), with high being 1e18
    int iterations = 100;
    for (int i = 1; i <= iterations; i++)
    {
        mid = (low + high) / 2;
        if ((mid * 1ll * mid) <= n)
        {
            ans = mid;
            low = mid + step_size;
        }
        else
        {
            high = mid - step_size;
        }
    }

    cout << setprecision(9);
    cout << ans << endl;

    return 0;
}