#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define F first
#define S second
#define sd(x) scanf("%d", &x)
#define sl(x) scanf("%lld", &x)
#define ss(x) scanf("%s", x)
#define sc(x) scanf(" %c", &x)
#define sz(x) x.size()
#define debug(X) cerr << " --> " << #X << " = " << X << endl
#define clr(x) memset(x, 0, sizeof x)
#define all(x) x.begin(), x.end()
#define rep(i, begin, end) for(__typeof(end) i =(begin)-((begin)>(end));i!=(end)-((begin)>(end));i+=1-2*((begin)>(end)))
#define endl "\n"
typedef long long ll; typedef pair<int, int> pii; typedef vector<int> vi;
const int N = 512345, LG = 21, mod = 1000000007, M = N;
const double eps = 1e-3, pi = acos(-1.0);
const ll INF = 1123456789123456789LL;
/*
freopen("in.txt", "r", stdin);
freopen("out.txt", "w", stdout);
*/
template<class T>

inline T add(T a, T b)
{
    a += b;
    while(a >= mod)
        a -= mod;
    return a;
}

inline int mul(int a, int b)
{
    ll c = a;
    c *= b;
    c %= mod;
    return c;
}

ll power(ll a, ll b, ll c = mod)
{
    ll r = 1;
    while(b > 0)
    {
        if(b & 1)
            r = (r * a) % c;
        a = (a * a) % c;
        b >>= 1;
    }
    return r;
}

/// BINARY INDEXED TREE
void update(int bit[N], int i, int v)
{
    while(i < N)
    {
        bit[i] = add(bit[i], v);
        i += (i & (-i));
    }
}

int query(int bit[N], int i)
{
    int r = 0;
    while(i > 0)
    {
        r = add(r, bit[i]);
        i -= (i & (-i));
    }
    return r;
}

ll lcm(ll a, ll b)
{
    return (a / __gcd(a, b)) * b;
}

/// a ^ -1 modulo b
ll inverse(ll a, ll b = mod)
{
    ll f = b, inv = 0, preinv = 1;
    while(b > 1)
    {
        ll quo = a / b;
        ll rem = a % b;

        a = b;
        b = rem;

        ll temp = inv;
        inv = preinv - quo * inv;
        preinv = temp;
    }
    if(inv < 0)
        inv += f;
    return inv;
}
///inv[i] = i ^ -1 modulo m
ll inv[N];
void inverses(int m)
{
    inv[1] = 1;
    for (int i = 2; i < m; ++i)
         inv[i] = (m - ((m / i) * inv[m % i]) % m) % m;
}
///DSU
int st[N];
int findset(int a)
{
    return st[a] = ((st[a] == a) ? a : findset(st[a]));
}
void merger(int x,int y)
{
	int a = findset(x), b = findset(y);
	st[b] = a;
}

vector<int> adj[N];
///DFS on a tree
int parent[N], start[N], endd[N], supreme = 0;
void dfs(int v)
{
    start[v] = supreme++;
    for(int i = 0; i < adj[v].size(); ++i)
    {
        int u = adj[v][i];
        if(u == parent[v])
            continue;
        parent[u] = v;
        dfs(u);

    }
    endd[v] = supreme++;
}

///BFS
bool vis[N];
void bfs(int start)
{
    queue<int> q;
    q.push(start);
    while(!q.empty())
    {
        int v = q.front();
        q.pop();
        for(int i = 0; i < adj[v].size(); ++i)
        {
            int u = adj[v][i];
            if(!vis[u])
                q.push(u), vis[u] = true;
        }
    }
}

///SIEVE
vector<int> primes, factors[M];
bool sieve[M];
void makesieve()
{
    sieve[0] = true, sieve[1] = true;
    for(int i = 2; i < M; ++i)
    {
        if(sieve[i])
            continue;
        for(int j = i; j < M; j += i)
        {
            sieve[j] = true;
            factors[j].push_back(i);
        }
        sieve[i] = false;
        primes.push_back(i);
    }
}

///FASTSIEVE
int lp[N];
vector<int> pr;
void fastsieve()
{
    for(int i = 2; i < N; ++i)
    {
        if(lp[i] == 0)
        {
            lp[i] = i;
            pr.push_back (i);
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i*pr[j] < N; ++j)
            lp[i * pr[j]] = pr[j];
    }
}

///SPARSE TABLE
int rmq[N][LG];
void precompute(int n, int A[N])
{
    for(int i = 1; i <= n; ++i)
        rmq[i][0] = i;
    for(int j = 1; j < LG; ++j)
    {
        for(int i = 1; i + (1 << j) - 1 <= n; ++i)
        {
            if(A[rmq[i][j - 1]] < A[rmq[i + (1 << (j - 1))][j - 1]])
                rmq[i][j] = rmq[i][j - 1];
            else
                rmq[i][j] = rmq[i + (1 << (j - 1))][j - 1];
        }
    }
}
int minimum(int start, int length, int A[N])
{
    int p;
    for(p = 0; (1 << p) <= length; ++p);
    --p;

    if(A[rmq[start][p]] < A[rmq[start + length - (1 << p)][p]])
        return rmq[start][p];
    else
        return rmq[start + length - (1 << p)][p];

}

///DIJKSTRA
vector<pair<int, ll>> adj[N];
vector<ll> dijkstra(int src, int n)
{
    vector<ll> dist(n + 1, INF);
    dist[src] = 0;
    set<pair<ll, int>> Q;
    Q.insert({0, src});
    while(!Q.empty())
    {
        ll w = Q.begin() -> F, v = Q.begin()->S;
        Q.erase(Q.begin());
        for(int i = 0; i < adj[v].size(); ++i)
        {
            int u = adj[v][i].F;
            ll wt = adj[v][i].second;
            if(w + wt < dist[u])
            {
                Q.erase({dist[u], u});
                dist[u] = w + wt;
                Q.insert({dist[u], u});
            }
        }
    }
    return dist;
}

///2D BIT
void update(int x, int y, int v)
{
	for(;x < N; x += (x & (-x)))
		for(int z = y; z < N; z += (z & (-z)))
			bit[x][z] += v;
}

int query(int x, int y)
{
	int ret = 0;
	for(;x > 0; x -= (x & (-x)))
		for(int z = y; z > 0; z -= (z & (-z)))
			ret += bit[x][z];
	return ret;
}

///DFS
int parent[N];
vector<int> adj[N];
void dfs(int v)
{
    for(int u : adj[v])
    {
        if(u == parent[v]){

        }
        parent[u] = v;
        dfs(u);
    }
}
///MEX
int mex(set<int>& s)
{
    int ans = 0;
    for(int z : s)
    {
        if(z < ans)
            continue;
        else if(z == ans)
            ++ans;
        else
            return ans;
    }
    return ans;
}
///KRUSKAL
