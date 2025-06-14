/// Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/geometry/FastDelaunay.h (+ refactor di Bortoz)
/// Verification:
/// https://acm.timus.ru/problem.aspx?space=1&num=1520 (ID: 10250755)
/* Fast Delaunay triangulation, it works also with cyclic
 * quadrilateral. Each circumcircle contains none of input
 * points. There must be no duplicate points (but collinear
 * point are ok). If all points are on a line, no triangles
 * will be returned. Should work for doubles as well,
 * though there may be precision issues in 'circ'.
 * Returns triangles in order {t[0][0], t[0][1], t[0][2],
 * t[1][0], ...}, all counter-clockwise. Time: $\mathcal{O}(n \log n)$.
 * Tested with: $N\leq 300,X_i^2+Y_i^2\leq 1000$. (using doubles) */
typedef struct Quad* Q;
typedef __int128_t lll; // (can be ll if coords are < 2e4)
pt arb(LLONG_MAX,LLONG_MAX);//not equal to any other point
struct Quad {
  Q rot, o; pt p = arb; bool mark;
  pt& F() { return r()->p; }
  Q& r() { return rot->rot; }
  Q prev() { return rot->o->rot; }
  Q next() { return r()->prev(); }
} *H;
// is p in the circumcircle?
bool circ(pt p, pt a, pt b, pt c) {
  lll p2 = norm(p), A = norm(a)-p2,
      B = norm(b)-p2, C = norm(c)-p2;
  return cross(a-p,b-p)*C + cross(b-p,c-p)*A
                    + cross(c-p,a-p)*B > 0;
}
Q makeEdge(pt orig, pt dest) {
  Q r = H ? H : new Quad{new Quad{new Quad{new Quad{0}}}};
  H = r->o; r->r()->r() = r;
  rep(i,0,4) {
    r = r->rot, r->p = arb, r->o = i & 1 ? r : r->r();
  }
  r->p = orig; r->F() = dest;
  return r;
}
void splice(Q a, Q b) {
  swap(a->o->rot->o, b->o->rot->o); swap(a->o, b->o);
}
Q connect(Q a, Q b) {
  Q q = makeEdge(a->F(), b->p);
  splice(q, a->next());
  splice(q->r(), b);
  return q;
}
pair<Q,Q> rec(const vector<pt>& s) {
  if (sz(s) <= 3) {
    Q a=makeEdge(s[0], s[1]), b=makeEdge(s[1], s.back());
    if (sz(s) == 2) return { a, a->r() };
    splice(a->r(), b);
    auto side = cross(s[1]-s[0], s[2]-s[0]);
    Q c = side ? connect(b, a) : 0;
    return {side<0 ? c->r() : a, side<0 ? c : b->r() };
  }
#define H(e) e->F(), e->p
#define valid(e) (cross(base->F()-e->F(), \
                  base->p-e->F()) > 0)
  Q A, B, ra, rb; int half = sz(s) / 2;
  tie(ra, A) = rec({all(s) - half});
  tie(B, rb) = rec({sz(s) - half + all(s)});
  while((cross(A->F()-B->p,A->p-B->p)<0 && (A=A->next()))
     || (cross(B->F()-A->p,B->p-A->p)>0 && (B=B->r()->o)));
  Q base = connect(B->r(), A);
  if (A->p == ra->p) ra = base->r();
  if (B->p == rb->p) rb = base;
#define DEL(e, init, dir) Q e = init->dir; if (valid(e)) \
    while (circ(e->dir->F(), H(base), e->F())) { \
      Q t = e->dir; \
      splice(e, e->prev()); \
      splice(e->r(), e->r()->prev()); \
      e->o = H; H = e; e = t; \
    }
  for (;;) {
    DEL(LC, base->r(), o);  DEL(RC, base, prev());
    if (!valid(LC) && !valid(RC)) break;
    if (!valid(LC) || (valid(RC) && circ(H(RC), H(LC))))
      base = connect(RC, base->r());
    else
      base = connect(base->r(), LC->r());
  }
  return { ra, rb };
}
bool comp(const pt& a,const pt& b){
  return pair(a.x,a.y) < pair(b.x,b.y);
}
vector<pt> triangulate(vector<pt> pts) {
  sort(all(pts),comp);
  assert(unique(all(pts)) == pts.end());
  if (sz(pts) < 2) return {};
  Q e = rec(pts).first;
  vector<Q> q = {e}; int qi = 0;
  while (cross(e->F()-e->o->F(),e->p-e->o->F())<0) e=e->o;
#define ADD { Q c = e; do { c->mark = 1; \
  pts.push_back(c->p);  q.push_back(c->r()); \
  c = c->next(); } while (c != e); }
  ADD; pts.clear();
  while (qi < sz(q)) if (!(e = q[qi++])->mark) ADD;
  return pts;
}
