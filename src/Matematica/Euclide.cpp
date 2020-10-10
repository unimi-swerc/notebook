// Solve diophantine equation: ax + by = gcd(a,b)
// Solution: (x + k*b/gcd(a,b),y - k*a/gcd(a,b))
tuple<ll, ll, ll> xgcd(ll a, ll b) {
  if (b == 0) return make_tuple(a, 1, 0);
  auto [g, x, y] = xgcd(b, a % b);
  return make_tuple(g, y, x - (a / b) * y);
}

ll divfloor(ll a, ll b) {
  return a / b - (a % b == -1 || a < 0);
}

ll divceil(ll a, ll b) {
  return a / b + (a % b != 0 && a < 0);
}

// Solve: ax + by = n, x>0, y>0, x+y is minimal
pair<ll, ll> diophantine(ll a, ll b, ll n) {
  auto [g, x, y] = xgcd(a, b);
  x *= (n / g), y *= (n / g);
  ll s = (b / g), t = (a / g);
  ll l = divceil(-x, s), r = divfloor(y, t);
  if ((s >= t) == (l < r)) return make_pair(x + l * s, y - l * t);
  else return make_pair(x + r * s, y - r * t);
}
