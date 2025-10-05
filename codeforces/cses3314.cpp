#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    vector<int> nextGreater(n, n), prevGreater(n, -1);
    stack<int> st;

    // Next greater or equal (to the right)
    for (int i = n - 1; i >= 0; i--)
    {
        while (!st.empty() && v[st.top()] < v[i])
        {
            st.pop();
        }
        if (!st.empty())
        {
            nextGreater[i] = st.top();
        }
        st.push(i);
    }

    while (!st.empty())
        st.pop();

    // Prev greater or equal (to the left)
    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && v[st.top()] < v[i])
        {
            st.pop();
        }
        if (!st.empty())
        {
            prevGreater[i] = st.top();
        }
        st.push(i);
    }

    int ans = 1;
    for (int i = 0; i < n; i++)
    {
        // Tour to the right
        int rightLen = nextGreater[i] - i;
        // Tour to the left
        int leftLen = i - prevGreater[i];
        ans = max(ans, max(leftLen, rightLen));
    }

    cout << ans << endl;

    return 0;
}
