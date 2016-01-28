const int N = 112345;
const double eps = 1e-9;
struct point
{
   double x, y;
   point(double _x, double _y) : x(_x), y(_y) {};
   point() : x(0), y(0) {};
	bool operator < (point other) const
	{
		if(fabs(x - other.x) > eps)
			return x < other.x;
		return y < other.y;
	}
	bool operator == (point other) const
	{
		return (fabs(x - other.x) < eps && fabs(y - other.y) < eps);
	}
};
struct line
{
	long long m, c;				// y = mx + c
	bool operator < (const line l2) const
	{
		return ((l2.m != m) ? m < l2.m : c < l2.c);
	}
};
bool intersection(line l1, line l2, point& p)
{
	if(l1.m == l2.m)
		return false;
   p.x = ((double)(l2.c - l1.c)) / (l1.m - l2.m);
   p.y = l1.m * p.x + l1.c;
   return true;
}
set<line> st;						// to keep a stack of lines
set<pair<double, line>> sr;	// to binary search on coordinate
map<line, double> lft;			// to keep left intersection of line
double inf = 1e200;
void insertLine(line l)
{
   if(st.empty())
   {
		lft[l] = -inf, st.insert(l), sr.insert({lft[l], l});
		return;
   }
   bool ins = true;				//whether to insert or not
   auto it = st.upper_bound(l);
   if(it != st.end())
   {
		line nxt = *it;
		if(it == st.begin())
		{
			ins = true;
		}
		else
		{
			--it;
			line pre = *it;
			point p1, p2;
			bool f1 = intersection(pre, nxt, p1);
			bool f2 = intersection(nxt, l, p2);
			if(!f2)
            ins = false;
			else if(!f1)
				ins = true;
			else
				ins = (p1 < p2);
			++it;
		}
   }
   if(!ins)
		return;
	if(it != st.end())
	{
		line nxt = *it; point p1;
		intersection(l, nxt, p1);
		sr.erase({lft[nxt], nxt});
		lft[nxt] = p1.x;
		sr.insert({lft[nxt], nxt});
	}
   if(it != st.begin())
   {
		--it;
      line pre = *it;
      if(it == st.begin())
      {
			point p1;
			bool f1 = intersection(pre, l, p1);
			if(!f1)
			{
				st.erase(pre), sr.erase({lft[pre], pre}), lft.erase(pre);
				lft[l] = -inf, st.insert(l), sr.insert({lft[l], l});
			}
			else
			{
				lft[l] = p1.x, st.insert(l), sr.insert({lft[l], l});
			}
      }
      else
      {
			do
			{
				--it;
				point p1, p2;
				line cur = *it;
				bool f1 = intersection(pre, l, p1);
				intersection(cur, l, p2);
				if(!f1)
				{
					st.erase(pre), sr.erase({lft[pre], pre}), lft.erase(pre);
					lft[l] = p2.x, st.insert(l), sr.insert({lft[l], l});
					break;
				}
				else if(p1 < p2)
				{
					st.erase(pre), sr.erase({lft[pre], pre}), lft.erase(pre);
               pre = cur;
				}
				else
				{
					lft[l] = p1.x, st.insert(l), sr.insert({lft[l], l});
					break;
				}
				if(it == st.begin())
				{
					lft[l] = p2.x, st.insert(l), sr.insert({lft[l], l});
				}
			}
			while(it != st.begin());
      }
   }
}
