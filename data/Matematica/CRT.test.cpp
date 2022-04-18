#include"CRT.cpp"
//test: https://open.kattis.com/problems/generalchineseremainder
int main(){

	ll t,a,n,b,m;
	cin>>t;
	while(t--){
		cin>>a>>n>>b>>m;
		auto res = crt(a,n,b,m);
		
		if(res.first==-1)cout<<"no solution\n";
		else cout<<res.first<<" "<<res.second<<"\n";
	}
	return 0;
}
