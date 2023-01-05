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
T norm(p3 v) {return v|v;}
double abs(p3 v) {return sqrt(norm(v));}
p3 unit(p3 v) {return v/abs(v);}
double angle(p3 v, p3 w) {
  return acos(clamp(1.*(v|w)/abs(v)/abs(w), -1., 1.));
}
// positivo se s è sopra il piano tra p, q, r
T orient(p3 p, p3 q, p3 r, p3 s) {
  return (q-p )* (r-p) | (s-p);
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
  double dist(p3 p) {return abs(side(p))/abs(n);}
  plane translate(p3 t) {return {n, d+(n|t)};}
  // requires double
  plane shiftUp(double dist) {return {n, d+dist*abs(n)};}
  p3 proj(p3 p) {return p - n*side(p)/norm(n);}
  p3 refl(p3 p) {return p - n*2*side(p)/norm(n);}
};
