/// Source: Handbook of geometry for competitive programmers (Victor Lecomte)
/// Verification:
/// https://judge.yosupo.jp/submission/140837 (Solo polar sort e cross)
/// https://training.olinfo.it/#/task/pre_boi_cerchi (Solo polar sort, cross e perp, ID: 1025082)
/// Guarda Convex huT per la verification di orient
/// https://cses.fi/problemset/result/6102096/ (Point in Polygon)
/// https://cses.fi/problemset/result/6102101/ (Polygon Area)
/// https://codeforces.com/gym/102501/submission/206681789 (Polygon Area)
/// https://cses.fi/problemset/result/6102115/ (segIntersection)
/// https://cses.fi/problemset/result/6102119/ (Line.Side)
/// https://dmoj.ca/submission/5552046 (polar sort + cross)
/// https://acm.timus.ru/problem.aspx?space=1&num=1909 (ID: 10289466, Line.proj e un po di altra roba)
using T = long long; //o double o long double
typedef complex<T> pt;
const T EPS = 1e-10; //per i double o long double
#define X real()
#define Y imag()
#define M_PI acos(-1)
// *** Punti ***
T dot(pt v, pt w) { return (conj(v) * w).X; }
T cross(pt v, pt w) { return (conj(v) * w).Y; }
T orient(pt a, pt b, pt c) { return cross(b-a, c-a); }
pt translate(pt v, pt p) { return p+v; }
pt perp(pt p) { return {-p.Y, p.X}; }
bool isPerp(pt v, pt w) { return dot(v,w) == 0; }
pt scale(pt c, T factor, pt p) { return c+(p-c)*factor; }
pt rotate(pt p, T a) { return p * polar(T(1.0), a); }
double angle(pt v, pt w) {
  return acos(clamp(
    1.*dot(v,w)/abs(v)/abs(w),T(-1)*1.,T(1)*1.));
}
bool inAngle(pt a, pt b, pt c, pt p) {
  assert(orient(a,b,c) != 0);
  if (orient(a,b,c) < 0) swap(b,c);
  return orient(a,b,p) >= 0 && orient(a,c,p) <= 0;
}
double orientedAngle(pt a, pt b, pt c) {
  if (orient(a,b,c) >= 0) {
    return angle(b-a, c-a);
  } else {
    return 2*M_PI - angle(b-a, c-a);
  }
}
// *** Linee ***
struct line {
  pt v; T c;
  // From direction vector v and offset c
  line(pt v, T c) : v(v), c(c) {}
  // From equation ax+by=c
  line(T a, T b, T c) : v({b,-a}), c(c) {}
  // From points P and Q
  line(pt p, pt q) : v(q-p), c(cross(v,p)) {}
  T side(pt p) { return cross(v,p)-c; }
  T dist(pt p) {return abs(side(p)) / abs(v);}
  T normDist(pt p) {return side(p)*side(p) / norm(v);}
  line perpThrough(pt p) {return {p, p + perp(v)};}
  line translate(pt t) {return {v, c + cross(v,t)};}
  line shiftLeft(T dist) {return {v, c + dist*abs(v)};}
  pt proj(pt p) {return p - perp(v)*side(p)/norm(v);}
};
bool lineIntersection(line l1, line l2, pt &out) {
  T d = cross(l1.v, l2.v);
  if (d == 0) return false;
  //requires floating-point
  out = (l2.v*l1.c - l1.v*l2.c) / d;
  return true;
}
// *** Segmenti ***
bool above(pt a, pt p) { return p.Y >= a.Y; }
bool inDisk(pt a, pt b, pt p) { 
  return dot(a - p, b - p) <= 0;
}
bool onSegment(pt a, pt b, pt p) { 
  return orient(a, b, p) == 0 && inDisk(a, b, p);
}
bool crossesRay(pt a, pt p, pt q) { 
  return (above(a,q)-above(a,p))*orient(a, p, q)>0;
}
bool properInter(pt a, pt b, pt c, pt d, pt &out) {
  T oa = orient(c,d,a), ob = orient(c,d,b),
     oc = orient(a,b,c), od = orient(a,b,d);
  // Proper intersection exists iff opposite signs
  if (oa*ob < 0 && oc*od < 0) {
    out = (a*ob - b*oa) / (ob-oa); // requires floats
    return true;
  }
  return false;
}
struct comp{ //serve solo per il set di segIntersection
  bool operator()(pt a, pt b) const {
    return make_pair(a.X, a.Y) < make_pair(b.X, b.Y);
  }
};
set<pt, comp> segIntersection(pt a, pt b, pt c, pt d) {
  pt out;
  if (properInter(a,b,c,d,out)) return {out};
  set<pt, comp> s;
  if (onSegment(c,d,a)) s.insert(a);
  if (onSegment(c,d,b)) s.insert(b);
  if (onSegment(a,b,c)) s.insert(c);
  if (onSegment(a,b,d)) s.insert(d);
  return s;
}
T segPointDistance(pt a, pt b, pt p) {
  if (a != b) {
    line l(a,b);
    // if closest to projection
    if(dot(l.v, a)<dot(l.v, p) && dot(l.v, p)<dot(l.v, b)){
      return l.dist(p);
    }
  }
  return min(abs(p-a), abs(p-b));
}
T segSegDistance(pt a, pt b, pt c, pt d) {
  pt dummy;
  if (properInter(a,b,c,d,dummy)) return 0;
  return min({segPointDistance(a,b,c), 
              segPointDistance(a,b,d),
              segPointDistance(c,d,a), 
              segPointDistance(c,d,b)});
}
// *** Poligoni
T area(vector<pt> V) {
  T area = 0;
  for (int i = 0; i < (int)V.size(); i++) {
    area += cross(V[i], V[(i + 1) % V.size()]);
  }
  return abs(area); // divide by 2 for the real area
}
bool isConvex(vector<pt> p) {
  bool hasPos=false, hasNeg=false;
  for (int i=0, n=p.size(); i<n; i++) {
    T o = orient(p[i], p[(i+1)%n], p[(i+2)%n]);
    if (o > 0) hasPos = true;
    if (o < 0) hasNeg = true;
  }
  return !(hasPos && hasNeg);
}
int inPolygon(vector<pt> V, pt p) {
  int numCrossings = 0;
  for (int i = 0; i < V.size(); i++) {
    if (onSegment(V[i], V[(i+1) % V.size()], p)) return 2;
    numCrossings+=crossesRay(p, V[i], V[(i+1)%V.size()]);
  }
  return numCrossings % 2; //1=INSIDE,0=OUTSIZE,2=BOUNDARY
}
bool half(pt p) {
  assert(p.X != 0 || p.Y != 0);
  return p.Y > 0 || (p.Y == 0 && p.X < 0);
}
void polarSort(vector<pt> &v) {
  sort(v.begin(), v.end(), [](pt v, pt w) {
    v = (v!=pt{0,0} ? v : pt{1,0}); //atan2(0,0)=0
    w = (w!=pt{0,0} ? w : pt{1,0}); //atan2(0,0)=0
    return make_tuple(half(v),0)<
           make_tuple(half(w),cross(v,w));});
}
