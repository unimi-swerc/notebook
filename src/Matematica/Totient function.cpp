/// Source: Dariost (booklet SWERC 2019-2020 LaStatale Blue)
/// https://github.com/dariost/swerc/blob/master/src/Extra/totient.cpp
/// Verification:
/// https://www.spoj.com/problems/ETF/ (id: 29454799) (fino a 10^6)
// It took less than 0.5s to calculate with MAX=10^7
#define MAX 10000000
int phi[MAX];
bool pr[MAX];
void totient() {
  for (int i = 0; i < MAX; i++) {
    phi[i] = i;
    pr[i] = true;
  }
  for (int i = 2; i < MAX; i++)
    if (pr[i]) {
      for (int j = i; j < MAX; j += i) {
        pr[j] = false;
        phi[j] = phi[j] - (phi[j] / i);
      }
      pr[i] = true;
    }
}
