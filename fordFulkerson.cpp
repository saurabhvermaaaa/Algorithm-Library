const int N = 512;
typedef long long ll;
ll capacity[N][N];
bool edge[N][N];
vector<int> adj[N];
struct fordFulkerson{
    int n;
    vector<vector<int>> adj;
    fordFulkerson(int _n) : n(_n) {
        memset(capacity, 0, sizeof(capacity));
        memset(edge, false, sizeof edge);
        for(int i = 1; i <= n; ++i)
            adj[i].clear();
    }

    void addEdge(int from, int to, ll cap){
        adj[from].push_back(to);
        capacity[from][to] += cap;
        edge[from][to] = 1;
    }

    const ll inf = 1e18;
    ll pfs(int src, int sink){
        priority_queue<pair<ll, pair<int, int>>> q;
        q.push({inf, {src, -1}});
        vector<int> prev(n + 1, -1);
        vector<bool> vis(n + 1, false);
        ll cap = inf;
        while(!q.empty())
        {
            ll cost = q.top().first;
            int v = q.top().second.first, pre = q.top().second.second;
            q.pop();
            if(vis[v])
                continue;
            prev[v] = pre;
            vis[v] = true;
            if(v == sink){
                cap = cost;
                break;
            }
            for(int u : adj[v]){
                ll wt = capacity[v][u];
                if(!vis[u] && wt > 0)
                    q.push({min(cost, wt), {u, v}});
            }
        }
        for(int v = sink; prev[v] > -1; v = prev[v]){
            capacity[prev[v]][v] -= cap, capacity[v][prev[v]] += cap;
            if(!edge[v][prev[v]])
                adj[v].push_back(prev[v]), edge[v][prev[v]] = 1;
            if(prev[v] == src)
                return cap;
        }
        return 0;
    }

    ll bfs(int src,int sink){
        queue<int> Q;
        vector<int> prev(n + 1, -1);
        vector<bool> vis(n + 1, false);
        Q.push(src);
        vis[src] = true;
        bool cont = true;
        while(!Q.empty()){
            int v = Q.front();
            Q.pop();
            for(int u : adj[v]){
                if(vis[u] || capacity[v][u] <= 0)
                    continue;
                Q.push(u);
                vis[u] = true;
                prev[u] = v;
                if(u == sink){
                    cont=false;
                    break;
                }
            }
            if(!cont)
                break;
        }
        ll cap = inf;
        for(int v = sink; prev[v] > -1; v = prev[v])
            cap = min(cap, capacity[prev[v]][v]);

        for(int v = sink; prev[v] > -1; v = prev[v]){
            capacity[prev[v]][v] -= cap, capacity[v][prev[v]] += cap;
            if(!edge[v][prev[v]])
                adj[v].push_back(prev[v]), edge[v][prev[v]] = 1;
            if(prev[v] == src)
                return cap;
        }

        if(cap == inf)
            return 0;
        else
            return cap;
    }

    ll maxflow(int src, int sink){
        ll ret = 0;
        while(1){
            ll cap = bfs(src, sink);
            ret += cap;
            if(!cap)
                return ret;
        }
    }
};
