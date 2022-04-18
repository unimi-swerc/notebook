pair<ll,ll> crt(ll a,ll m,ll b,ll n) {
	if (n > m) swap(a, b), swap(m, n);
	auto [x, y, g] = xgcd(m, n);
	
	if((a - b) % g != 0)return {-1,-1}; //no solution
	x = (b - a) % n * x % n / g * m + a;
	return {x < 0 ? x + m*n/g : x, m*n/g};
}
