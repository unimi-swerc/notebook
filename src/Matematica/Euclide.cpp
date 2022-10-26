/// Source: Bortoz
/// Verification:
/// https://codeforces.com/contest/1728/submission/171410592
/// https://open.kattis.com/submissions/8824728 (come subroutine di CRT)
// Soluzione: $\left( x + k b / \gcd (a,b), \ y - k a / \gcd (a,b) \right)$
// restituisce $\left( x, \ y, \ \gcd(a,b) \right)$
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
