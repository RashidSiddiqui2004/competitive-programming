void s3()
{
    int n;
    cin >> n;

    vector<int> a(n), b(n), c(n);
    read_vector(a);
    read_vector(b);
    read_vector(c);

    vector<int> validbc(n, 0), validab(n, 0);

    // ---------- b < c ----------
    vector<int> d(n), d2(2 * n), prefMin(2 * n);

    for (int i = 0; i < n; i++)
        d[i] = c[i] - b[i];

    for (int i = 0; i < 2 * n; i++)
        d2[i] = d[i % n];

    prefMin[0] = d2[0];
    for (int i = 1; i < 2 * n; i++)
        prefMin[i] = min(prefMin[i - 1], d2[i]);

    for (int s = 0; s < n; s++)
    {
        int mn;
        if (s == 0)
            mn = prefMin[n - 1];
        else
            mn = prefMin[s + n - 1] - prefMin[s - 1];

        if (mn > 0)
            validBC[s] = 1;
    }

    // ---------- a < b ----------
    for (int i = 0; i < n; i++)
        d[i] = b[i] - a[i];

    for (int i = 0; i < 2 * n; i++)
        d2[i] = d[i % n];

    prefMin[0] = d2[0];
    for (int i = 1; i < 2 * n; i++)
        prefMin[i] = min(prefMin[i - 1], d2[i]);

    for (int s = 0; s < n; s++)
    {
        int mn;
        if (s == 0)
            mn = prefMin[n - 1];
        else
            mn = prefMin[s + n - 1] - prefMin[s - 1];

        if (mn > 0)
            validAB[s] = 1;
    }

    // ---------- final answer ----------
    int sumBC = 0;
    for (int i = 0; i < n; i++)
        sumBC += validBC[i];

    int ans = 0;
    for (int i = 0; i < n; i++)
        if (validAB[i])
            ans += sumBC;

    cout << ans << '\n';
}
