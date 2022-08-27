// Soluzione: $\left( x + k\cdot b / \gcd (a,b), y - k\cdot a / \gcd (a,b) \right)$
// restituisce $\left( x, y, \gcd(a,b) \right)$
tuple<ll, ll, ll> xgcd(ll a, ll b) {
  ll s = 0, s2 = 1, t = 1, t2 = 0;
  while (a != 0) {
    ll q = b / a; b -= q * a;
    s -= q * s2; t -= q * t2;
    swap(a, b);
    swap(s, s2); swap(t, t2);
  }
  return {s, t, b};
}
