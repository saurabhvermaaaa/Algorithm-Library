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
const int N = 112345, LG = 21, mod = 1000000007;
const long double eps = 1e-9, pi = acos(-1.0);
int a[N];
struct node
{
   int l, r, s, y[2], m[2]; ll c[2];
};
int n;
class SegTree
{
public:
	node tree[N * 4];
	void init(int root, int l, int r);
	void mul(int root, int l, int r, int x[2]);
	void change(int root, int l, int r, int s, int y[2]);
	pair<ll, ll> query(int root, int l, int r);
	void refresh(int root);
	void print()
	{
        printf("\n");
	    printf("TREE : ");
	    for(int i = 1; i <= n; ++i)
            printf("{%lld, %lld} ", query(1, i, i).F, query(1, i, i).S);
        printf("\n");
	    printf("NODES : ");
	    for(int i = 1; i <= 3 * n; ++i)
            printf("{%lld, %lld} ", tree[i].c[0], tree[i].c[1]);
        printf("\n");
	}
	void clearChange(int root);
}segtree;
int prime[2] = {2, 5};
int sum[N][2];
void SegTree :: clearChange(int root)
{
    if(tree[root].s > 0)
    {
        int s = tree[root].s;
        for(int i = 0; i < 2; ++i)
        {
            tree[root].c[i] = sum[tree[root].r - s + 1][i] - sum[tree[root].l - s][i] + (tree[root].r - tree[root].l + 1) * tree[root].y[i];
            if(tree[root].l != tree[root].r)
            {
                tree[root * 2].m[i] = 0, tree[root * 2].s = s, tree[root * 2].y[i] = tree[root].y[i];
                tree[root * 2 + 1].m[i] = 0, tree[root * 2 + 1].s = s, tree[root * 2 + 1].y[i] = tree[root].y[i];
            }
            tree[root].m[i] = 0, tree[root].y[i] = 0;
        }
        tree[root].s = 0;
    }
}
void SegTree :: refresh(int root)
{
	if(tree[root].s > 0)
    {
        clearChange(root);
    }
    else if(tree[root].m[0] > 0 || tree[root].m[1] > 0)
    {
        for(int i = 0; i < 2; ++i)
        {
            tree[root].c[i] += tree[root].m[i] * (tree[root].r - tree[root].l + 1);
            if(tree[root].l != tree[root].r)
            {
                clearChange(root * 2), clearChange(root * 2 + 1);
                tree[root * 2].m[i] += tree[root].m[i], tree[root * 2 + 1].m[i] += tree[root].m[i];
            }
            tree[root].m[i] = 0;
        }
    }
}
void SegTree :: init(int root = 1, int l = 1, int r = n)
{
	tree[root].l = l, tree[root].r = r, tree[root].m[0] = 0, tree[root].m[1] = 0, tree[root].s = 0, tree[root].y[0] = 0, tree[root].y[1] = 0;
	if(l != r)
	{
		int mid = (l + r) / 2;
        init(root * 2, l, mid);
        init(root * 2 + 1, mid + 1, r);
        for(int i = 0; i < 2; ++i)
            tree[root].c[i] = tree[root * 2].c[i] + tree[root * 2 + 1].c[i];
	}
	else
    {
        for(int i = 0; i < 2; ++i)
        {
            int c = 0, x = a[l];
            while(x % prime[i] == 0)
                x /= prime[i], ++c;
            tree[root].c[i] = c;
        }
    }
}
void SegTree :: mul(int root, int l, int r, int x[2])
{
	refresh(root);
	if(tree[root].l > r || tree[root].r < l)
		return;
	if(tree[root].l >= l && tree[root].r <= r)
    {
        for(int i = 0; i < 2; ++i)
            tree[root].m[i] += x[i];
        refresh(root);
    }
	else
	{
		mul(root * 2, l, r, x);
		mul(root * 2 + 1, l, r, x);
		for(int i = 0; i < 2; ++i)
            tree[root].c[i] = tree[root * 2].c[i] + tree[root * 2 + 1].c[i];
	}
}
void SegTree :: change(int root, int l, int r, int s, int y[2])
{
	refresh(root);
	if(tree[root].l > r || tree[root].r < l)
		return;
	if(tree[root].l >= l && tree[root].r <= r)
	{
		tree[root].s = s, tree[root].y[0] = y[0], tree[root].y[1] = y[1];
        refresh(root);
	}
	else
	{
		change(root * 2, l, r, s, y);
		change(root * 2 + 1, l, r, s, y);
		for(int i = 0; i < 2; ++i)
            tree[root].c[i] = tree[root * 2].c[i] + tree[root * 2 + 1].c[i];
	}
}
pair<ll, ll> SegTree :: query(int root, int l, int r)
{
	refresh(root);
	if(tree[root].l > r || tree[root].r < l)
		return {0, 0};
	if(tree[root].l >= l && tree[root].r <= r)
		return {tree[root].c[0], tree[root].c[1]};
	else
    {
        pair<ll, ll> q = query(root * 2, l, r) , qq = query(root * 2 + 1, l, r);
        for(int i = 0; i < 2; ++i)
            tree[root].c[i] = tree[root * 2].c[i] + tree[root * 2 + 1].c[i];
        return {q.F + qq.F, q.S + qq.S};
    }
}
void pre()
{
    sum[0][0] = 0, sum[0][1] = 0;
    for(int i = 1; i < N; ++i)
    {
        int z = i;
        for(int j = 0; j < 2; ++j)
        {
            int c = 0;
            while(z % prime[j] == 0)
                z /= prime[j], ++c;
            sum[i][j] = sum[i - 1][j] + c;
        }
    }
}
int main()
{
    int t = 5;
    sd(t);
    pre();
    while(t--)
    {
        int m; ll ans = 0;
        sd(n), sd(m);
        for(int i = 1; i <= n; ++i)
            sd(a[i]);
        segtree.init();
        while(m--)
        {
            int cc;
            sd(cc);
            if(cc == 1)
            {
                int l, r, y, c[2] = {0, 0};
                sd(l), sd(r), sd(y);
                for(int i = 0; i < 2; ++i)
                    while(y % prime[i] == 0)
                        y /= prime[i], ++c[i];
                segtree.mul(1, l, r, c);
            }
            else if(cc == 2)
            {
                int l, r, y, c[2] = {0, 0};
                sd(l), sd(r), sd(y);
                for(int i = 0; i < 2; ++i)
                    while(y % prime[i] == 0)
                        y /= prime[i], ++c[i];
                segtree.change(1, l, r, l, c);
            }
            else
            {
                int l, r;
                sd(l), sd(r);
                auto q = segtree.query(1, l, r);
                ans += min(q.F, q.S);
            }
        }
        printf("%lld\n", ans);
    }
	return 0;
}
