/// Source:
/// https://judge.yosupo.jp/submission/67748 (modificato da MrBrionix sostituendo gli array con vector>
/// Verification:
/// https://judge.yosupo.jp/submission/104549
//a è 1-based (f invece va da 0 a n)
using ll = long long;
constexpr int N=105, p=1e9+7ll;
void inc(int &x,const int y){
	if ((x+=y)>=p) x-=p;
}
void dec(int &x,const int y){
	if ((x-=y)<0) x+=p;
}
int ksm(int x,int y){
	int r=1;
	while(y){if(y&1) r=(ll)r*x%p;x=(ll)x*x%p;y>>=1;}
	return r;
}
void calpoly(vector<vector<ll> > a,int n,vector<long long> &f){
	int i,j,k,r,rr;
	for (i=2;i<=n;i++){
		for (j=i;j<=n&&!a[j][i-1];j++);
		if (j>n) continue;
		if (j>i){
			swap(a[i],a[j]);
			for (k=1;k<=n;k++)swap(a[k][j],a[k][i]);
		}
		r=a[i][i-1];
		for (j=1;j<=n;j++)a[j][i]=(ll)a[j][i]*r%p;
		r=ksm(r,p-2);
		for (j=i-1;j<=n;j++)a[i][j]=(ll)a[i][j]*r%p;
		for (j=i+1;j<=n;j++){
			r=a[j][i-1];
			for(k=1;k<=n;k++)a[k][i]=(a[k][i]+(ll)a[k][j]*r)%p;
			r=p-r;
			for(k=i-1;k<=n;k++)a[j][k]=(a[j][k]+(ll)a[i][k]*r)%p;
		}
	}	
	static int g[N][N];memset(g,0,sizeof(g));
	g[0][0]=1;
	for (i=1;i<=n;i++){
		r=p-1;
		for (j=i;j;j--){
			rr=(ll)r*a[j][i]%p;
			for(k=0;k<j;k++)g[i][k]=(g[i][k]+(ll)rr*g[j-1][k])%p;
			r=(ll)r*a[j][j-1]%p;
		}
		for (k=1;k<=i;k++)inc(g[i][k],g[i-1][k-1]);
	}
	for(int i=0;i<n+1;i++)f[i]=g[n][i];
}
/*	
	calpoly(tt,n,tot);
	reverse(tot.begin(),tot.end());
	tot.erase(tot.begin());
	for(auto &i : tot)i=(-i+mod)%mod;
*/
