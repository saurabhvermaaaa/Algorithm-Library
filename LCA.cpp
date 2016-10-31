int parent[N], height[N], dp[N][LG];
void computeLCADP()
{
    for(int i = 1; i < N; ++i)
    {
        dp[i][0] = parent[i];
    }

    for(int j = 1; j < lgN; ++j)
    {
        for(int i = 1; i < N; ++i)
        {
            if(dp[i][j - 1] > 0)
                dp[i][j] = dp[dp[i][j - 1]][j - 1];
            else
                dp[i][j] = -1;
        }
    }
}
int lca(int u, int v)
{
    if(height[u] < height[v])
        swap(u, v);
    for(int i = lgN - 1; i >= 0; --i)
    {
        if(height[u] - (1 << i) >= height[v])
        {
            u = dp[u][i];
        }
    }

    if(u == v)
        return u;

    for(int i = lgN - 1; i >= 0; --i)
    {
        if(dp[u][i] != -1 && dp[u][i] != dp[v][i])
        {
            u = dp[u][i], v = dp[v][i];
        }
    }
    return parent[u];
}
