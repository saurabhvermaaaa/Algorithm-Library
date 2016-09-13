#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define sd(x) scanf("%d", &x)
#define sl(x) scanf("%lld", &x)
#define debug(X) cerr << " --> " << #X << " = " << X << endl
#define rep(i, begin, end) for(__typeof(end) i =(begin)-((begin)>(end));i!=(end)-((begin)>(end));i+=1-2*((begin)>(end)))
#define endl "\n"
typedef long long ll; typedef pair<int, int> pii; typedef vector<int> vi;
const int N = 2000005, LG = 21, mod = 1000000007;
const double eps = 1e-3, pi = acos(-1.0);

struct node {
    char c;
    int next[26];
} total[N];

int supreme = 1;
ll ct[2][26];
inline void dfs(int root, int pp)
{
    int cc = total[root].c - 'a';
    if(cc >= 0)
        ct[pp][cc] += 1;
    for(int i = 0; i < 26; ++i) {
        int p = total[root].next[i];
        if(p > 0)
            dfs(p, pp);
    }
}

inline void insert(int root, int i, char s[N])
{
    if(s[i] == 0)
        return;
    int cc = s[i] - 'a';
    int p = total[root].next[cc];
    if(p <= 0)
        p = supreme++, total[root].next[cc] = p, total[p].c = s[i];
    insert(p, i + 1, s);
}
char s[N];
int main()
{
    while(1){
        int f = supreme++, sec = supreme++;
        memset(ct, 0, sizeof ct);
        int n, m;
        sd(n), sd(m);
        if(n == 0)
            break;
        for(int i = 0; i < n; ++i){
            scanf("%s", s);
            insert(f, 0, s);
        }
        for(int i = 0; i < m; ++i){
            scanf("%s", s);
            reverse(s, s + strlen(s));
            insert(sec, 0, s);
        }

        dfs(sec, 1);

        dfs(f, 0);

        ll ans = 0;
        for(int i = 0; i < 26; ++i) {
            for(int j = 0; j < 26; ++j) {
                ans += ct[0][i] * ct[1][j];
            }
        }

        for(int i = 0; i < 26; ++i)
            ct[0][i] -= (total[f].next[i] > 0);
        for(int i = 0; i < 26; ++i)
            ct[1][i] -= (total[sec].next[i] > 0);

        for(int i = 0; i < 26; ++i)
            ans -= ct[0][i] * ct[1][i];

        printf("%lld\n", ans);
    }
    return 0;
}
