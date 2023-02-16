/// Source: Bortoz
/// Verification:
/// https://acm.timus.ru/problem.aspx?space=1&num=1520 (circleLine e circumCenter, ID: 10156658)
/// https://codeforces.com/contest/933/submission/191029359 (circleCircle)
/// https://www.acmicpc.net/source/55979832 (circleLine)
int sgn(double xx) { return (xx > 1e-10) - (xx < -1e-10); }
// centro della circonferenza per 3 punti
pt circumCenter(pt a, pt b, pt c) {
  b = b-a, c = c-a;
  assert(cross(b,c) != 0);
  return a + perp(b*norm(c) - c*norm(b))/cross(b,c)/2.0;
}  //tested with EPS < $10^{-5}$
// intersezione tra il cerchio (o,r) e la linea l
int circleLine(pt o, double r, line l, pair<pt,pt>& out){
  double h2 = r*r - l.normDist(o);
  if (h2 >= 0) {
    pt p = o - perp(l.v) * l.side(p) / norm(l.v);
    pt h = l.v * sqrt(h2) / abs(l.v);
    out = {p-h, p+h};
  }
  return 1 + sgn(h2);
}  //tested with EPS < ${10^-5}$
// intersezione tra due cerchi
int circleCircle(pt o1, double r1, pt o2, double r2,
                                  pair<pt,pt> &out) {
  pt d=o2-o1; double d2=norm(d);
  if (d2 == 0) {assert(r1 != r2); return 0;}
  double pd = (d2 + r1*r1 - r2*r2)/2;
  double h2 = r1*r1 - pd*pd/d2;
  if (h2 >= 0) {
    pt p = o1 + d*pd/d2, h = perp(d)*sqrt(h2/d2);
    out = {p-h, p+h};
  }
  return 1 + sgn(h2);
} //tested counting intersections of 3 circles
// tangenti tra due cerchi
int tangents(pt o1, double r1, pt o2, double r2,
              bool inner, vector<pair<pt,pt>> &out) {
  if (inner) r2 = -r2;
  pt d = o2-o1;
  double dr = r1-r2, d2 = norm(d), h2 = d2-dr*dr;
  if (d2 == 0 || h2 < 0) {assert(h2 != 0); return 0;}
  for (double sign : {-1,1}) {
    pt v = (d*dr + perp(d)*sqrt(h2)*sign)/d2;
    out.push_back({o1 + v*r1, o2 + v*r2});
  }
  return 1 + (h2 > 0);
} //untested :(
