/// Source: Handbook of geometry for competitive programmers (Victor Lecomte)
/// Verification:
/// https://acm.timus.ru/problem.aspx?space=1&num=1520 (circleLine e circumCenter, ID: 10289483)
/// https://codeforces.com/contest/933/submission/206680402 (circleCircle)
/// https://www.acmicpc.net/source/61069469 (circleLine)
/// https://acm.timus.ru/problem.aspx?space=1&num=1909 (ID: 10289466, circleLine)
/// https://acm.timus.ru/problem.aspx?space=1&num=1163 (ID: 10319768, tangenti interne)
/// https://contest.ucup.ac/submission/196466 (circleLine)
int sgn(T xx) { return (xx > EPS) - (xx < -EPS); }
// centro della circonferenza per 3 punti
pt circumCenter(pt a, pt b, pt c) {
  b = b-a, c = c-a; assert(cross(b,c) != 0);
  return a + perp(b*norm(c) - c*norm(b))/cross(b,c)/T(2.0);
}  //tested with EPS < $10^{-5}$
// intersezione tra il cerchio (o,r) e la linea l
int circleLine(pt o, T r, line l, pair<pt,pt> &out) {
  T h2 = r*r - l.normDist(o);
  if (h2 > -EPS) { // the line touches the circle
    pt p = l.proj(o);
    pt h = l.v*T(sqrtl(h2))/abs(l.v);
    out = {p-h, p+h};
  }
  return 1 + sgn(h2);
}  //tested with EPS < ${10^-5}$
// intersezione tra due cerchi (o1,r1) e (o2,r2)
int circleCircle(pt o1, T r1, pt o2, T r2,
                                  pair<pt,pt> &out) {
  pt d=o2-o1; T d2=norm(d);
  if (d2 == 0) {assert(r1 != r2); return 0;}
  T pd = (d2 + r1*r1 - r2*r2)/2;
  T h2 = r1*r1 - pd*pd/d2;
  if (h2 >= 0) {
    pt p = o1 + d*pd/d2, h = perp(d)*T(sqrtl(h2/d2));
    out = {p-h, p+h};
  }
  return 1 + sgn(h2);
} //tested counting intersections of 3 circles
//tangenti tra due cerchi (o passante per un punto se r2=0)
int tangents(pt o1, T r1, pt o2, T r2,
              bool inner, vector<pair<pt,pt>> &out) {
  if (inner) r2 = -r2;
  pt d = o2-o1; T dr = r1-r2, d2 = norm(d), h2 = d2-dr*dr;
  if(abs(d2)<EPS||h2<-EPS){assert(abs(h2)>EPS);return 0;}
  for (T sign : {-1,1}) {
    pt v = (d*dr + perp(d)*T(sqrtl(h2))*sign)/d2;
    out.push_back({o1 + v*r1, o2 + v*r2});
  }
  return 1 + (h2 > EPS);
} //tested with EPS < $10^{-8}$
