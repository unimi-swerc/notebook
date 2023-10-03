/// Source: Handbook of geometry for competitive programmers (Victor Lecomte)
/// Verification:
/// https://acm.timus.ru/problem.aspx?space=1&num=1520 (ID: 10289483, solo dot e cross product)
/// https://acm.timus.ru/problem.aspx?space=1&num=1477 (ID: 10289475, orient, cross product, norm)
/// https://acm.timus.ru/problem.aspx?space=1&num=2099 (ID: 10289469, orient, dot product)
/// https://acm.timus.ru/problem.aspx?space=1&num=1686 (ID: 10289468, dot product, cross product, unit, abs, plane(p,q,r), plane.side())
/// https://acm.timus.ru/problem.aspx?space=1&num=1909 (ID: 10289466, plane.proj(), plane.dist() e coords)
/// https://osijek2023s-d8.eolymp.io/problems/4 (cross, dot, plane.side, creazione di piani)
/// https://contest.ucup.ac/submission/196527 (dot, cross, norm, abs, creazione piani, plane.translate(), plane.side(), plane.dist())
struct p3 {
  T x,y,z;
  p3 operator+(p3 p) {return {x+p.x, y+p.y, z+p.z};}
  p3 operator-(p3 p) {return {x-p.x, y-p.y, z-p.z};}
  p3 operator*(T d) {return {x*d, y*d, z*d};}
  p3 operator/(T d) {return {x/d, y/d, z/d};}
  bool operator==(p3 p) {
    return tie(x,y,z) == tie(p.x,p.y,p.z);
  }
  bool operator!=(p3 p) {return !operator==(p);}
};
T operator|(p3 v, p3 w) { // dot product
  return v.x*w.x + v.y*w.y + v.z*w.z;
}
p3 operator*(p3 v, p3 w) { // cross product
  return {v.y*w.z - v.z*w.y,
          v.z*w.x - v.x*w.z,
          v.x*w.y - v.y*w.x};
}
T norm(p3 v) {return v|v;} //modulo^2
T abs(p3 v) {return sqrtl(norm(v));} //modulo
p3 unit(p3 v) {return v/abs(v);} //versore ($|v|\neq 0$)
double angle(p3 v, p3 w) { //return an angle in $[0,\pi]$
  return acos(clamp(
    1.*(v|w)/abs(v)/abs(w), T(-1)*1., T(1)*1.));
}
//>0 sse s è sopra il piano pqr, nella direzione di $\overrightarrow{PQ}\times\overrightarrow{PR}$
T orient(p3 p, p3 q, p3 r, p3 s) {
  return (q-p) * (r-p) | (s-p); //0 sse p,q,r,s coplanari
}
// orientamento 2D delle proiezioni di p, q, r
// rispetto al piano perpendicolare a n
T orientByNormal(p3 p, p3 q, p3 r, p3 n) {
  return (q-p) * (r-p) | n;
}
struct plane {
  p3 n; T d;
  // From normal n and offset d
  plane(p3 n, T d) : n(n), d(d) {}
  // From normal n and point P
  plane(p3 n, p3 p) : n(n), d(n|p) {}
  // From three non-collinear points P,Q,R
  plane(p3 p, p3 q, p3 r) : plane((q-p)*(r-p), p) {}
  T side(p3 p) {return (n|p)-d;}
  T dist(p3 p) {return abs(side(p))/abs(n);}
  plane translate(p3 t) {return {n, d+(n|t)};}
  // requires double
  plane shiftUp(T dist) {return {n, d+dist*abs(n)};}
  p3 proj(p3 p) {return p - n*side(p)/norm(n);}
  p3 refl(p3 p) {return p - n*2*side(p)/norm(n);}
};
struct coords {
  p3 o, dx, dy, dz;
  // From three points P,Q,R on the plane:
  // build an orthonormal 3D basis
  coords(p3 p, p3 q, p3 r) : o(p) {
    dx = unit(q-p);
    dz = unit(dx*(r-p));
    dy = dz*dx;
  }
  // From four points P,Q,R,S: take directions PQ, PR, PS
  // as is (represents a change of coordinate system)
  coords(p3 p, p3 q, p3 r, p3 s) : //not always orthonormal
    o(p), dx(q-p), dy(r-p), dz(s-p) {}
  pt pos2d(p3 p) {return {(p-o)|dx, (p-o)|dy};}
  p3 pos3d(p3 p) {return {(p-o)|dx, (p-o)|dy, (p-o)|dz};}
};
