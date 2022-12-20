/// Source: Bortoz (suffix array)
/// https://cp-algorithms.com/string/suffix-array.html#on-log-n-approach (lcp array) 
/// Verification:
/// https://oj.uz/submission/648808
/// https://codeforces.com/gym/102428/submission/185955879
int sa[MAXN], rnk[2*MAXN], lcp[MAXN], tmp[MAXN];
// build suffix array of $S_0,\cdots,S_{N-1}$
void suffix_array(int N, const string& S){//$\mathcal{O}(N\log^2N)$
  //se usi suffix_array() più di una volta azzera rnk qua
  for (int i = 0; i < N; i++) {
    sa[i] = i, rnk[i] = S[i];
  }
  for (int k = 1; k < N; k *= 2) {
    sort(sa, sa + N, [&](int a, int b) {
      return tie(rnk[a],rnk[a+k]) < tie(rnk[b],rnk[b+k]);
    });
    tmp[sa[0]] = 1;
    for (int i = 1; i < N; i++) {
      tmp[sa[i]] = tmp[sa[i-1]] + (rnk[sa[i]] !=
        rnk[sa[i-1]] || rnk[sa[i]+k] != rnk[sa[i-1]+k]);
    }
    copy(tmp, tmp + N, rnk);
    if (rnk[sa[N - 1]] == N) break;
  }
} //sa[i]= indice di inizio i-esimo prefisso più piccolo
void lcp_array(int N, const string& S) { //$\mathcal{O}(N)$
  for (int i = 0, k = 0; i < N; i++) {
    int j = sa[rnk[i]];
    while (i+k < N && j+k < N && S[i+k] == S[j+k]) k++;
    lcp[rnk[i] - 1] = k;
    k = max(k - 1, 0);
  }
} //lcp[i]= lcp tra sa[i] e sa[i+1] ($0\leq i \leq N-2$)
