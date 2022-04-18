#include <bits/stdc++.h>
#include "CRT.cpp"
#include "NTT.cpp"
using namespace std;

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	signed n,m;
	cin>>n>>m;
	
	vector<int> a(n),b(m);
	for(int i=0;i<n;i++){
		signed x;
		cin>>x;
		a[i]=x;
	}
	for(int i=0;i<m;i++){
		signed x;
		cin>>x;
		b[i]=x;
	}
	
	MOD = MOD1;
	vector<int> res1 = multiply(a,b);
	reset();
	MOD = MOD2;
	vector<int> res2 = multiply(a,b);
	reset();
	MOD = MOD3;
	vector<int> res3 = multiply(a,b);
	
	long long mod = 1e9+7ll;
	for(int i=0;i<res2.size();i++){
		auto tmp1 = crt(res1[i],MOD1,res2[i],MOD2);
		auto tmp2 = crt(tmp1.first,tmp1.second,res3[i],MOD3);
		
		cout<<int(tmp2.first%mod)<<" "; 
	}
	cout<<"\n";
}
