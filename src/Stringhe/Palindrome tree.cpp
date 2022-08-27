constexpr long long MOD = 1e9+7ll; //inf
struct PalTree {
	static const int ASZ = 26;
	struct node {
		array<int,ASZ> to = array<int,ASZ>();
		int len, link, oc = 0; //length and # occurrences of pal
		int slink = 0, diff = 0;
		array<int,2> seriesAns;
		node(int _len, int _link) : len(_len), link(_link) {}
	};
	string s = "@"; V<array<int,2>> ans = {{0,MOD}};
	V<node> d = {{0,1},{-1,0}}; // dummy pals of len 0,-1
	int last = 1;
	int getLink(int v) {
		while (s[sz(s)-d[v].len-2] != s.bk) v = d[v].link;
		return v;
	}
	void updAns() { // serial path has O(log n) vertices
		ans.pb({MOD,MOD});
		for (int v = last; d[v].len > 0; v = d[v].slink) {
			d[v].seriesAns=ans[sz(s)-1-d[d[v].slink].len-d[v].diff];
			if (d[v].diff == d[d[v].link].diff) 
				F0R(i,2) ckmin(d[v].seriesAns[i],
							d[d[v].link].seriesAns[i]);
			// start of previous oc of link[v]=start of last oc of v
			F0R(i,2) ckmin(ans.bk[i],d[v].seriesAns[i^1]+1);
		}
	}
	void addChar(char C) {
		s += C; int c = C-'a'; last = getLink(last);
		if (!d[last].to[c]) {
			d.eb(d[last].len+2,d[getLink(d[last].link)].to[c]);
			d[last].to[c] = sz(d)-1;
			auto& z = d.bk; z.diff = z.len-d[z.link].len;
			z.slink = z.diff == d[z.link].diff 
				? d[z.link].slink : z.link;
		} // max suf with different dif
		last = d[last].to[c]; ++d[last].oc;
		updAns();
	}
	long long numOc() { //total # of palindromes (with repetitions)
		long long ans=0;
		for (int i = (sz(d))-1; i >= (2); --i){
			d[d[i].link].oc += d[i].oc;
			ans += d[i].oc;
		}
		return ans;
	}
};
