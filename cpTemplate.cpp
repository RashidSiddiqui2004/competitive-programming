#include<bits/stdc++.h>
using namespace std;
using ll=long long;

void yes()
{
    cout<<"YES\n";
}
void no()
{
    cout<<"NO\n";
}
struct TreeNode 
{
    int val;
    TreeNode* parent;
    vector<TreeNode*> children;

    TreeNode(int v) : val(v), parent(nullptr) {}
};

void read_array(vector<ll>&arr)
{
	for(int i=0;i<arr.size();i++)
	{
		cin>>arr[i];
	}
}

void read_graph(vector<pair<ll,ll>>&arr,vector<vector<ll>>&brr)
{
    for(int i=0;i<arr.size();i++)
	{
		cin>>arr[i].first>>arr[i].second;
		arr[i].first--;arr[i].second--;
		brr[arr[i].first].push_back(arr[i].second);
		brr[arr[i].second].push_back(arr[i].first);
	}
}

void print_array(vector<ll>&arr)
{
	for(int i=0;i<arr.size();i++)
	{
		cout<<arr[i]<<' ';
	}
	cout<<endl;
}
vector<int> sieve(int n) 
{
    vector<bool> isPrime(n + 1, true);
    vector<int> primes;

    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= n; ++i) 
	{
        if (isPrime[i]) 
		{
            for (int j = i * i; j <= n; j += i)
                isPrime[j] = false;
        }
    }

    for (int i = 2; i <= n; ++i) 
	{
        if (isPrime[i]) 
			primes.push_back(i);
    }

    return primes;
}

bool isprime(long long n) 
{
    if (n <= 1) 
		return false;
    if (n <= 3)
		return true;
    if (n % 2 == 0 || n % 3 == 0) 
		return false;

    for (long long i = 5; i * i <= n; i += 6) 
	{
        if (n % i == 0 || n % (i + 2) == 0) 
			return false;
    }
    return true;
}

class SegmentTree 
{
    int n;
    vector<long long> tree;

    void build(int node, int start, int end, const vector<long long>& arr) 
	{
        if (start == end) 
		{
            tree[node] = arr[start];
            return;
        }
        int mid = (start + end) / 2;
        build(2 * node, start, mid, arr);
        build(2 * node + 1, mid + 1, end, arr);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    void update(int node, int start, int end, int idx, long long val) {
        if (start == end) 
		{
            tree[node] = val;
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid)
            update(2 * node, start, mid, idx, val);
        else
            update(2 * node + 1, mid + 1, end, idx, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    long long query(int node, int start, int end, int l, int r) 
	{
        if (r < start || end < l)
            return 0;
        if (l <= start && end <= r)
            return tree[node];
        int mid = (start + end) / 2;
        return query(2 * node, start, mid, l, r) +
               query(2 * node + 1, mid + 1, end, l, r);
    }



public:
    SegmentTree(const vector<long long>& arr) {
        n = arr.size();
        tree.assign(4 * n, 0);
        build(1, 0, n - 1, arr);
    }

    void update(int idx, long long val) {
        update(1, 0, n - 1, idx, val);
    }

    long long query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};

class DSU
{
public:
    vector<ll> parent, sz;

    DSU(ll n)
    {
        parent.resize(n+1);
        sz.resize(n+1,1);
        for(ll i=0;i<=n;i++)
            parent[i]=i;
    }

    ll find(ll x)
    {
        if(parent[x]==x)
            return x;
        return parent[x]=find(parent[x]); 
    }

    void unite(ll a, ll b)
    {
        a=find(a);
        b=find(b);
        if(a==b) return;

        if(sz[a]<sz[b])
            swap(a,b);

        parent[b]=a;
        sz[a]+=sz[b];
    }
};

class DSU_Skip
{
public:
    vector<ll> parent;

    DSU_Skip(ll n)
    {
        parent.resize(n+2);
        for(ll i=0;i<=n+1;i++)
            parent[i]=i;
    }

    ll find(ll x)
    {
        if(parent[x]==x)
            return x;
        return parent[x]=find(parent[x]);
    }

    void remove(ll x)
    {
        parent[x]=x+1; 
    }
};

class Tree {
public:
    unordered_map<int, TreeNode*> nodes;
    TreeNode* root = nullptr;

    void buildFromEdges(int n, const vector<pair<int, int>>& edges) 
	{
        for (int i = 1; i <= n; ++i) 
		{
            nodes[i] = new TreeNode(i);
        }

        vector<int> indegree(n + 1, 0);
        for (auto [u, v] : edges) 
		{
            nodes[v]->parent = nodes[u];
            nodes[u]->children.push_back(nodes[v]);
            indegree[v]++;
        }

        for (int i = 1; i <= n; ++i) 
		{
            if (indegree[i] == 0) 
			{
                root = nodes[i];
                break;
            }
        }
    }

    void printTree() 
	{
        printNode(root, 0);
    }

    void printNode(TreeNode* node, int level) 
	{
        if (!node) 
			return;
        cout << string(level * 2, ' ') << "Node " << node->val;
        if (node->parent) 
			cout << " (Parent: " << node->parent->val << ")";
        cout << "\n";
        for (auto child : node->children) 
		{
            printNode(child, level + 1);
        }
    }

    ~Tree() 
	{
        for (auto& [_, node] : nodes) 
		{
            delete node;
        }
    }
};

int main()
{
	ll cases;
	cin>>cases;
	while(cases--)
	{
		ll n;
		cin>>n;
// 		cout<<n<<endl;
		vector<ll>arr(n,0ll);
		read_array(arr);
		
		ll ans=0ll;
		ll counter=0ll;
		vector<pair<ll,ll>>brr;
		
		for(ll i=0;i<n;i++)
		{
		    map<ll,ll>mp;
		    for(ll j=i;j<n;j++)
		    {
		        mp[arr[j]]++;
		        if(mp[arr[j]]==1ll)
		        {
		            counter++;
		        }
		        else if(mp[arr[j]]==2ll)
		        counter--;
		        
		        if(counter==0ll)
		        {
		            brr.push_back({j,i});
		        }
		    }
		    counter=0;
		    
		}
		sort(brr.begin(),brr.end());
		ll prev=-1;
		for(ll i=0;i<brr.size();i++)
		{
		    ll righty=brr[i].first;
		    ll lefty=brr[i].second;
		    if(prev<lefty)
		    {
		        ans++;
		        prev=righty;
		    }
		}
		cout<<ans<<endl;
	}
}
