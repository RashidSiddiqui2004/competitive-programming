#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <array>
#include <deque>
#include <cstring>
#include <queue>
#include <stack>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <numeric>    // accumulate, gcd, lcm
#include <functional> // function, greater, less
#include <utility>    // pair, make_pair
#include <tuple>
#include <cmath>
#include <climits>
#include <fstream> // For file handling
#include <cfloat>
#include <bitset>
#include <cassert>
#include <random>
#include <chrono>

using namespace std;

// Macros
#define fast_io                  \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);            \
    cout.tie(nullptr);
#define pb push_back
#define mp make_pair
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define fi first
#define se second
#define sz(x) (int)((x).size())
#define endl '\n'
#define fl(i, n) for (int i = 0; i < n; i++)
#define fr(i, n) for (int i = n - 1; i >= 0; i--)
#define khalaas return 0;

// Typedefs

#define int long long

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pll> vpll;

#define vvi vector<vector<int>>
// Constants
const int MOD = 1e9 + 7;
const ll InF = 1e18;
const double EPS = 1e-9;
const ll nEG = -1e18;

// Debugging
#ifndef OnLInE_JUDGE
#define debug(x) cerr << #x << " = " << (x) << endl;
#else
#define debug(x)
#endif

struct Edge
{
    int u, v;
};

inline ll contri(ll a, ll d)
{
    return a * 1ll * a + (d - a) * 1ll * (d - a);
}

ll find_delta(int u, int v, int eid, vector<int> &x,
              vector<int> &a, vector<int> &d)
{
    ll du = d[u], dv = d[v];
    ll au = a[u], av = a[v];

    if (x[eid] == 1)
    {
        return 2 * (du - 2 * au + 1) + 2 * (dv - 2 * av + 1);
    }

    return 2 * (2 * au - du + 1) + 2 * (2 * av - dv + 1);
}

pair<ll, vector<int>> run_local_search(vector<Edge> &edges,
                                       vector<vector<int>> &incident,
                                       vector<int> &d,
                                       vector<int> &xorig)
{
    int M = edges.size();
    int N = d.size();

    vector<int> a(N, 0);
    vector<int> x = xorig;

    for (int e = 0; e < M; ++e)
    {
        if (x[e] == 1)
        {
            a[edges[e].u]++;
            a[edges[e].v]++;
        }
    }

    ll total = 0;
    for (int v = 0; v < N; ++v)
        total += contri(a[v], d[v]);

    priority_queue<pair<ll, int>> pq;

    for (int e = 0; e < M; ++e)
    {
        ll delta = find_delta(edges[e].u, edges[e].v, e, x, a, d);
        if (delta < 0)
        {
            pq.push({-delta, e});
        }
    }

    while (!pq.empty())
    {
        auto top = pq.top();
        pq.pop();
        ll gain = top.first;
        int eid = top.second;

        ll delta_now = find_delta(edges[eid].u, edges[eid].v, eid, x, a, d);
        if (delta_now >= 0)
            continue; 
        ll gain_now = -delta_now;
        if (gain_now != gain)
        {
            pq.push({gain_now, eid});
            continue;
        }

        if (x[eid] == 1)
        {
            x[eid] = 0;
            a[edges[eid].u]--;
            a[edges[eid].v]--;
        }
        else
        {
            x[eid] = 1;
            a[edges[eid].u]++;
            a[edges[eid].v]++;
        }
        total += delta_now;  

        int u = edges[eid].u, v = edges[eid].v;
        for (int ee : incident[u])
        {
            ll delta = find_delta(edges[ee].u, edges[ee].v, ee, x, a, d);
            if (delta < 0)
            {
                pq.push({-delta, ee});
            }
        }
        for (int ee : incident[v])
            if (ee != eid)
            {
                ll delta = find_delta(edges[ee].u, edges[ee].v, ee, x, a, d);
                if (delta < 0)
                {
                    pq.push({-delta, ee});
                }
            }
    }

    return {total, x};
}

void solve5(int casenum, std::ifstream &inFile, std::ofstream &outFile)
{
    outFile << "Case #" << casenum << ": ";
    int N, M;
    inFile >> N >> M;

    vector<Edge> edges;
    edges.reserve(M);
    vector<int> d(N, 0);

    for (int i = 0; i < M; ++i)
    {
        int u, v;
        inFile >> u >> v;
        --u;
        --v;
        edges.push_back({u, v});
        d[u]++;
        d[v]++;
    }

    vector<vector<int>> incident(N);
    for (int e = 0; e < M; ++e)
    {
        incident[edges[e].u].push_back(e);
        incident[edges[e].v].push_back(e);
    }

    vector<int> x_greedy(M, 0);
    vector<int> a(N, 0);

    for (int e = 0; e < M; ++e)
    {
        ll du = d[edges[e].u], dv = d[edges[e].v];
        ll au = a[edges[e].u], av = a[edges[e].v];
        ll delta_if1 = 2 * (2 * au - du + 1) + 2 * (2 * av - dv + 1);
        if (delta_if1 < 0)
        {
            x_greedy[e] = 1;
            a[edges[e].u]++;
            a[edges[e].v]++;
        }
        else
        {
            x_greedy[e] = 0;
        }
    }

    std::mt19937_64 rng((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());
    vector<int> x_random(M, 0);

    for (int e = 0; e < M; ++e)
    {
        x_random[e] = (rng() & 1);
    }

    auto res_g = run_local_search(edges, incident, d, x_greedy);
    auto res_r = run_local_search(edges, incident, d, x_random);

    pair<ll, vector<int>> best = res_g.first <= res_r.first ? res_g : res_r;

    const int EXTRA_RANDOM = 1000;
    for (int it = 0; it < EXTRA_RANDOM; ++it)
    {
        for (int e = 0; e < M; ++e)
            x_random[e] = (rng() & 1);
        auto res = run_local_search(edges, incident, d, x_random);
        if (res.first < best.first)
            best = res;
    }

    ll ans = best.first;
    outFile << ans << " ";

    for (int e = 0; e < M; ++e)
    {
        outFile << best.second[e] + 1;
    }

    outFile << endl;
}

signed main()
{
    std::string inputfile = "plan_out_validation_input.txt";
    std::string outputfile = "output.txt";

    std::ifstream inFile(inputfile);

    if (!inFile.is_open())
    {
        std::cerr << "Error: Could not open the input file " + inputfile + "!" << endl;
        return 1;
    }
    std::ofstream outFile(outputfile);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open the output file." << endl;
        return 1;
    }

    ll t;
    inFile >> t;

    for (int i = 1; i <= t; i++)
        solve5(i, inFile, outFile);

    outFile.close();
    std::cout << "Output successfully written to " + outputfile << endl;
    return 0;
}
