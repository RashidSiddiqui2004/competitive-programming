#include <iostream>
#include <string>
using namespace std;

string convertToBase(long long num, int base)
{
    if (num == 0)
        return "0";

    string digits = "0123456789ABCDEF"; // supports bases up to 16
    string result = "";

    bool isNegative = num < 0;
    if (isNegative)
        num = -num;

    while (num > 0)
    {
        result = digits[num % base] + result;
        num /= base;
    }

    if (isNegative)
        result = "-" + result;
    return result;
}

int main()
{
    long long l, r;
    int base;
    cin >> l >> r;
    cin >> base;

    for (int i = l; i <= r; i++)
    {
        cout << convertToBase(i, base) << " ";
    }

    return 0;
}
