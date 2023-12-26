/// Source: Dariost (booklet SWERC 2019-2020 LaStatale Blue)
/// https://github.com/dariost/swerc/blob/master/src/Extra/totient.cpp
/// Verification:
/// https://www.spoj.com/problems/ETF/ (id: 31464594) (totient fino a 10^6)
/// https://www.codechef.com/viewsolution/97924273 (factorization sieve fino a 10^7)
/// https://projecteuler.net/problem=869 (factorization sieve fino a 10^8 ma solo per cercare i primi)
#define MAX 10000000
bool pr[MAX];vector<int> phi(MAX),lp(MAX+1),primes;
void totient() { //It took less than 0.5s with MAX=$10^7$
  for (int i = 0; i < MAX; i++)
    phi[i] = i, pr[i] = true;
  for (int i = 2; i < MAX; i++)
    if (pr[i]) {
      for (int j = i; j < MAX; j += i)
        pr[j] = false, phi[j] = phi[j] - (phi[j] / i);
      pr[i] = true;
    }
}
void factorization_sieve() { //$\mathcal{O}(MAX)$
  for (int i=2; i <= MAX; ++i) {
    if (lp[i] == 0) primes.push_back(lp[i]=i);
    for (int j = 0; i * primes[j] <= MAX; ++j) {
      lp[i * primes[j]] = primes[j];
      if (primes[j] == lp[i]) break;
    }
  }
} // lp[i] = minimum prime factor of $i$
