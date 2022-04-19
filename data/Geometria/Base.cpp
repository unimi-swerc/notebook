typedef complex<ll> pt;
#define x real()
#define y imag()
 
// *** Punti ***
ll dot(pt v, pt w) { return (conj(v) * w).x; }
ll cross(pt v, pt w) { return (conj(v) * w).y; }
ll orient(pt a, pt b, pt c) { return cross(b - a, c - a); }
pt translate(pt v, pt p) { return p+v; }
pt perp(pt p) { return {-p.y, p.x}; }
bool isPerp(pt v, pt w) { return dot(v,w) == 0; }
pt scale(pt c, ll factor, pt p) { return c + (p-c)*factor; }
pt rotate(pt p, double a) {
  return {p.x*cos(a)-p.y*sin(a), p.x*sin(a)+p.y*cos(a)};
}
double angle(pt v, pt w) {
  return acos(clamp(dot(v,w) / abs(v) / abs(w), -1.0, 1.0));
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

// *** Segmenti ***
bool above(pt a, pt p) { return p.y >= a.y; }
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
  double oa = orient(c,d,a), ob = orient(c,d,b),
         oc = orient(a,b,c), od = orient(a,b,d);
  // Proper intersection exists iff opposite signs
  if (oa*ob < 0 && oc*od < 0) {
    out = (a*ob - b*oa) / (ob-oa); // requires floating-point
    return true;
  }
  return false;
}
// definire un struct comp per comparare i complessi
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
double segPointDistance(pt a, pt b, pt p) {
  if (a != b) {
    line l(a,b);
    // if closest to projection
    if(dot(l.v, a)<dot(l.v, p) && dot(l.v, p)<dot(l.v, b)){
      return l.dist(p);
    }
  }
  return min(abs(p-a), abs(p-b));
}
double segSegDistance(pt a, pt b, pt c, pt d) {
  pt dummy;
  if (properInter(a,b,c,d,dummy)) return 0;
  return min({segPointDistance(a,b,c), 
              segPointDistance(a,b,d),
              segPointDistance(c,d,a), 
              segPointDistance(c,d,b)});
}

// *** Poligoni
ll area(vector<pt> V) {
  ll area = 0;
  for (int i = 0; i < (int)V.size(); i++) {
    area += cross(V[i], V[(i + 1) % V.size()]);
  }
  return abs(area); // divide by 2
}
bool isConvex(vector<pt> p) {
  bool hasPos=false, hasNeg=false;
  for (int i=0, n=p.size(); i<n; i++) {
    int o = orient(p[i], p[(i+1)%n], p[(i+2)%n]);
    if (o > 0) hasPos = true;
    if (o < 0) hasNeg = true;
  }
  return !(hasPos && hasNeg);
}
int inPolygon(vector<pt> V, pt p) {
  int numCrossings = 0;
  for (int i = 0; i < V.size(); i++) {
    if (onSegment(V[i], V[(i + 1) % V.size()], p)) return 2;
    numCrossings+=crossesRay(p, V[i], V[(i + 1) % V.size()]);
  }
  return numCrossings % 2;
}
bool half(pt p) {
  assert(p.x != 0 || p.y != 0);
  return p.y > 0 || (p.y == 0 && p.x < 0);
}
void polarSort(vector<pt> &v) {
  sort(v.begin(), v.end(), [](pt v, pt w) {
    return make_tuple(half(v),0)<make_tuple(half(w),cross(v,w));
  });
}

// *** Linee ***
struct line {
  pt v; ll c;
  // From direction vector v and offset c
  line(pt v, ll c) : v(v), c(c) {}
  // From equation ax+by=c
  line(ll a, ll b, ll c) : v({b,-a}), c(c) {}
  // From points P and Q
  line(pt p, pt q) : v(q-p), c(cross(v,p)) {}

  ll side(pt p) { return cross(v,p)-c; }
  ll dist(pt p) {return abs(side(p)) / abs(v);}
  ll normDist(pt p) {return side(p)*side(p) / norm(v);}

  line perpThrough(pt p) {return {p, p + perp(v)};}
  line translate(pt t) {return {v, c + cross(v,t)};}
  line shiftLeft(ll dist) {return {v, c + dist*abs(v)};}
}

bool lineIntersection(line l1, line l2, pt &out) {
  ll d = cross(l1.v, l2.v);
  if (d == 0) return false;
  out = (l2.v*l1.c - l1.v*l2.c) / d; //requires floating-point
  return true;
}
