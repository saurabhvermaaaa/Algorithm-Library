#include<bits/stdc++.h>
using namespace std;

const double eps = 1e-9, pi = acos(-1.0);

struct point
{
   double x, y;
   point(double _x, double _y) : x(_x), y(_y) {};
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
double dist(point p1, point p2)
{
   return hypot(p1.x - p2.x, p1.y - p2.y);
}
point rotate(point p, double theta)
{
   double rad = theta * pi / 180.0;
   return point(p.x * cos(rad) - p.y * sin(rad), p.x * sin(rad) + p.y * cos(rad));
}
//keep b = 1 or 0. b = 1 means y = mx + c. b = 0 means x = c
struct line
{
   double a, b, c;
};
void pointsToLine(point p1, point p2, line &l)
{
   if(fabs(p1.x - p2.x) < eps)
   {
      l.a = 1.0, l.b = 0, l.c = -p1.x;
   }
   else
   {
      l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
      l.b = 1.0;
      l.c = -(double)(l.a * p1.x) - p1.y;
   }
}
bool areParallel(line l1, line l2)
{
   return fabs(l1.a - l2.a) < eps && fabs(l1.b < l2.b) < eps;
}
bool areSame(line l1, line l2)
{
   return areParallel(l1, l2) && fabs(l1.c - l2.c) < eps;
}
bool intersection(line l1, line l2, point &p)
{
   if(areParallel(l1, l2))
      return false;
   p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
   if(fabs(l1.b) > eps)
      p.y = -(l1.a * p.x + l1.c);
   else
      p.y = -(l2.a * p.x + l2.c);
   return true;
}
struct vec
{
   double x, y;
   vec(double _x, double _y) : x(_x), y(_y) {}
};
vec toVec(point p1, point p2)
{
   return vec(p2.x - p1.x, p2.y - p1.y);
}
vec scale(vec v, double s)
{
   return vec(v.x * s, v.y * s);
}
point translate(point p, vec v)
{
   return point(p.x + v.x, p.y + v.y);
}
double dot(vec a, vec b)
{
   return (a.x * b.x + a.y * b.y);
}
double normSq(vec a)
{
   return dot(a, a);
}
//returns Euclidean distance from p to the line defined by a and b(distinct). The closest point is c.
double distToLine(point p, point a, point b, point &c)
{
   vec ap = toVec(a, p), ab = toVec(a, b);
   double u = dot(ap, ab) / normSq(ab);
   //c = a + u * ab
   c = translate(a, scale(ab, u));
   return dist(p, c);
}
double distToLineSegment(point p, point a, point b, point &c)
{
   vec ap = toVec(a, p), ab = toVec(a, b);
   double u = dot(ap, ab) / normSq(ab);
   if(u < 0.0) {
      c = point(a.x, a.y);
      return dist(p, c);
   } else if(u > 1.0) {
      c = point(b.x, b.y);
      return dist(p, c);
   } else {
      return distToLine(p, a, b, c);
   }
}
//returns angle AOB in rad
double angle(point a, point o, point b)
{
   vec oa = toVec(o, a), ob = toVec(o, b);
   return acos(dot(oa, ob) / sqrt(normSq(oa) * normSq(ob)));
}
double cross(vec a, vec b)
{
   return (a.x * b.y - a.y * b.x);
}
bool collinear(point p, point q, point r)
{
   return fabs(cross(toVec(p, q), toVec(p, r))) < eps;
}
bool ccw(point p, point q, point r)
{
   //returns true if r is on left side of line pq or on line pq.
   return ((cross(toVec(p, q), toVec(p, r)) > 0) || collinear(p, q, r));
}
int inside(point p, point c, double r)
{
   return ((dist(p, c) < r - eps) ? 1 : ((dist(p, c) < r + eps) ? 2 : 0));
}
//cos(theta) = 2 * cos^2(theta / 2) - 1
bool ptsToCircle(point p1, point p2, double r, point &c)
{
   double d = dist(p1, p2);
   double det = (r * r) / (d * d) - 0.25;
   if(det < 0.0)
      return false;
   double h = sqrt(det);
   c.x = (p1.x + p2.x) * 0.5 + (p1.y - p2.y) * h;
   c.y = (p1.y + p2.y) * 0.5 + (p2.x - p1.x) * h;
   //other centre by exchanging p1 and p2
   return true;
}
//TRIANGLES
double area(double a, double b, double c)
{
   double s = (a + b + c) * 0.5;
   return sqrt(s * (s - a) * (s - b) * (s - c));
}
double radiusIncircle(double a, double b, double c)
{
   return area(a, b, c) / (0.5 * (a + b + c));//r = A / s
}
double radiusIncircle(point a, point b, point c)
{
   return radiusIncircle(dist(a, b), dist(b, c), dist(c, a));
}
bool incircle(point p1, point p2, point p3, point &c, double &r)
{
   r = radiusIncircle(p1, p2, p3);
   if(fabs(r) < eps)
      return false;
   line l1, l2;
   double ratio = dist(p1, p2) / dist(p1, p3);
   point p = translate(p2, scale(toVec(p2, p3), ratio / (1 + ratio)));
   pointsToLine(p1, p, l1);

   ratio = dist(p2, p1) / dist(p2, p3);
   p = translate(p1, scale(toVec(p1, p3), ratio / (1 + ratio)));
   pointsToLine(p2, p, l2);

   return intersection(l1, l2, c);
}
double radiusCircumcircle(double a, double b, double c)
{
   return (a * b * c) / (4 * area(a, b, c)); //R = abc / 4A
}
double radiusCircumcircle(point a, point b, point c)
{
   return radiusCircumcircle(dist(a, b), dist(b, c), dist(c, a));
}
/*
incentre is intersection of angle bisectors
circumcentre is meeting point of perpendicular bisectors

Cosine Law :- c^2 = a^2 + b^2 - 2 * a * b * cosC

Sine Law :- a / sinA = b / sinB = c / sinC = 2R(circumradius)
*/
//QUADRILATERALS
/*
Area of Trapezium : 0.5 * (w1 + w2) * h
w1 and w2 are parallel edges and h is height

Area of kite : 0.5 * d1 * d2
*/
//POLYGON
double perimeter(const vector<point> &p)
{
   double ans = 0.0;
   for(int i = 0; i < (int)p.size() - 1; ++i)
      ans += dist(p[i], p[i + 1]);
   ans += dist(p[0], p.back());
   return ans;
}
double area(const vector<point> &p)
{
   double ans = 0.0;
   for(int i = 2; i < (int)p.size(); ++i)
   {
      ans += cross(toVec(p[0], p[i - 1]), toVec(p[0], p[i]));
   }
   return fabs(ans / 2.0);
}
/*
double area(const vector<point> &P)
{
   double result = 0.0, x1, y1, x2, y2;
   for (int i = 0; i < (int)P.size()-1; i++)
   {
      double x1 = P[i].x, x2 = P[i+1].x, y1 = P[i].y, y2 = P[i+1].y;
      result += (x1 * y2 - x2 * y1);
   }
   return fabs(result) / 2.0;
}
*/
bool isConvex(const vector<point> &p)
{
   //check all ccw
   if(p.size() < 3)
      return false;
   bool first = ccw(p[p.size() - 2], p[p.size() - 1], p[0]);
   if(ccw(p.back(), p[0], p[1]) != first)
      return false;
   for(int i = 2; i < p.size(); ++i)
   {
      //allow collinearity if required
      if(ccw(p[i - 2], p[i - 1], p[i]) != first)
         return false;
   }
   return true;
}
//works for both convex and concave polygon
bool inPolygon(point pt, const vector<point> &p)
{
   int n = p.size();
   double sum = 0;
   for(int i = 0; i < p.size(); ++i)
   {
      if(ccw(pt, p[i], p[(i + 1) % n]))
         sum += angle(p[i], pt, p[(i + 1) % n]);
      else
         sum -= angle(p[i], pt, p[(i + 1) % n]);
   }
   return fabs(fabs(sum) - 2 * pi) < eps;
}
//line segment p-q intersect with line a-b
point lineIntersectSeg(point p, point q, point A, point B)
{
   double a = B.y - A.y;
   double b = A.x - B.x;
   double c = B.x * A.y - A.x * B.y;
   double u = fabs(a * p.x + b * p.y + c);
   double v = fabs(a * q.x + b * q.y + c);
   return point((p.x * v + q.x * u) / (u + v), (p.y * v + q.y * u) / (u + v));
}
//cuts polygon q along the line a-b
vector<point> cutPolygon(point a, point b, vector<point> &q)
{
   vector<point> p;
   q.push_back(q.front());
   for(int i = 0; i < q.size(); ++i)
   {
      double left1 = cross(toVec(a, b), toVec(a, q[i])), left2 = 0;
      if(i < q.size() - 1)
         left2 = cross(toVec(a, b), toVec(a, q[i + 1]));
      if(left1 > -eps)//point on left
         p.push_back(q[i]);
      if(left2 * left1 < -eps) //line cutting edge
         p.push_back(lineIntersectSeg(q[i], q[i + 1], a, b));
   }
   q.pop_back();
   return p;
}
//Convex HUll
point pivot(0, 0);
bool angleCmp(point a, point b)
{
   if(collinear(pivot, a, b))
      return dist(pivot, a) < dist(pivot, b);
   double x1 = a.x - pivot.x, y1 = a.y - pivot.y;
   double x2 = b.x - pivot.x, y2 = b.y - pivot.y;
   return (atan2(y1, x1) - atan2(y2, x2)) < 0;
}
vector<point> convexHull(vector<point> &p)
{
   if(p.size() <= 3)
      return p;
   int cur = 0;
   for(int i = 1; i < p.size(); ++i)
   {
      if(p[i].y < p[cur].y || (fabs(p[i].y - p[cur].y) < eps && p[i].x > p[cur].x))
         cur = i;
   }
   swap(p[cur], p[0]);
   pivot = p[0];
   sort(++p.begin(), p.end());
   vector<point> s;
   s.push_back(p.back()), s.push_back(p[0]), s.push_back(p[1]);
   int i = 2;
   while(i < p.size())
   {
      int j = s.size() - 1;
      if(ccw(s[j - 1], s[j], p[i]))
         s.push_back(p[i++]);
      else
         s.pop_back();
   }
   return s;
}
