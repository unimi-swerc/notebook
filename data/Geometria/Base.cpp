typedef complex<ll> pt;
#define x real()
#define y imag()
 
ll dot(pt v, pt w) { return (conj(v) * w).x; }
ll cross(pt v, pt w) { return (conj(v) * w).y; }
ll orient(pt a, pt b, pt c) {return cross(b - a, c - a);}
bool above(pt a, pt p) { return p.y >= a.y; }
bool inDisk(pt a, pt b, pt p) { return dot(a - p, b - p) <= 0; }
bool onSegment(pt a, pt b, pt p) { return orient(a, b, p) == 0 && inDisk(a, b, p); }
bool crossesRay(pt a, pt p, pt q) { return (above(a, q) - above(a, p)) * orient(a, p, q) > 0; }
 
bool properInter(pt a, pt b, pt c, pt d) {
    ll oa = orient(c, d ,a);
    ll ob = orient(c, d, b);
    ll oc = orient(a, b, c);
    ll od = orient(a, b, d);
    return ((double)oa * ob < 0 && (double)oc * od < 0);
}
bool intersect(pt a, pt b, pt c, pt d) {
    if (properInter(a, b, c, d)) return true;
    if (onSegment(c, d, a)) return true;
    if (onSegment(c, d, b)) return true;
    if (onSegment(a, b, c)) return true;
    if (onSegment(a, b, d)) return true;
    return false;
}
ll area(vector<pt> V) {
    ll area = 0;
    for (int i = 0; i < (int)V.size(); i++) {
        area += cross(V[i], V[(i + 1) % V.size()]);
    }
    return abs(area); // divide by 2
}
int inPolygon(vector<pt> V, pt p) {
    int numCrossings = 0;
    for (int i = 0; i < V.size(); i++) {
        if (onSegment(V[i], V[(i + 1) % V.size()], p)) return 2;
        numCrossings += crossesRay(p, V[i], V[(i + 1) % V.size()]);
    }
    return numCrossings % 2;
}