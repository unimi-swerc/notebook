#include<bits/stdc++.h>
using namespace std;

const int MAXN=100005, LOGN=18;

struct SegmentTree{
	long long _l,_r,lvl;
	long long sum,lazy;
	SegmentTree *left,*right;
	
	static SegmentTree* newSeg();
	static SegmentTree* newSeg(int l,int r);
	
	void build(long long *v,int l,int r){
		if(_r<l || _l>r)return;
		
		if(_l==_r){
			sum=v[_l];
			return;
		}
		
		left->build(v,l,r);
		right->build(v,l,r);
		
		sum=left->sum+right->sum;
	}
	
	SegmentTree* copy(int x){
		SegmentTree *res = newSeg();
		
		*res = *this;
		res->lvl=x;
		
		return res;
	}
	
	void checkcopy(){
		
		if(left->lvl != lvl){
			left = left->copy(lvl);
		}
		
		if(right->lvl != lvl){
			right = right->copy(lvl);
		}
	}
	
	void checklazy(){
		if(lazy!=0){
			left->lazy+=lazy;
			left->sum+=lazy*(left->_r-left->_l+1);
			
			right->lazy+=lazy;
			right->sum+=lazy*(right->_r-right->_l+1);
			
			lazy=0;
		}
	}
	
	
	void update(int l,int r,int val){
		if(l>r || r<_l || l>_r)return;
		
		if(_l>=l && _r<=r){
			lazy+=val;
			sum+=val*(_r-_l+1);
			return;
		}
		
		checkcopy();
		checklazy();
		
		left->update(l,r,val);
		right->update(l,r,val);
		sum=left->sum+right->sum;
	}
	
	long long query(int l,int r){
		if(_r<l || _l>r)return 0;
		if(_l>=l && _r<=r)return sum;
		
		checkcopy();
		checklazy();
		
		return left->query(l,r)+right->query(l,r);
	}
};

SegmentTree vett[4*MAXN*(LOGN+4)];
int cc=0;

SegmentTree* SegmentTree::newSeg(){
	return &vett[cc++];
}

SegmentTree* SegmentTree::newSeg(int l,int r){
	int ind=cc++;
	
	vett[ind]._l=l;
	vett[ind]._r=r;
	vett[ind].sum=0;
	vett[ind].lazy=0;
	vett[ind].lvl=0;
	vett[ind].left=nullptr;
	vett[ind].right=nullptr;
	
	if(l==r)return &vett[ind];
	
	vett[ind].left = newSeg(l,(l+r)/2);
	vett[ind].right = newSeg((l+r)/2+1,r);
	
	return &vett[ind];
}

struct que{
	int id,tempo,l,r;
};

SegmentTree *rt[MAXN];

long long t,n,q,v[MAXN],cont,cont1,ans[MAXN];
vector<que> off;

int main(){

	ios::sync_with_stdio(false);
	cin.tie(0);

	cin>>t;

	while(t--){
		off.clear();
		cin>>n;
		
		cc=0;
		rt[0] = SegmentTree::newSeg(1,n);
		cont=1;
		cont1=0;
		
		cin>>q;
		for(int i=0;i<q;i++){
			int a;
			cin>>a;
			
			if(a==0){
				int b,c,d;
				cin>>b>>c>>d;
				
				rt[cont]=rt[cont-1]->copy(cont);
				rt[cont]->update(b,c,d);
				cont++;
			}else{
				int p,q;
				cin>>p>>q;
				off.push_back({cont1,cont-1,p,q});
				cont1++;
			}
			
			
			if(off.size()>20){
				random_shuffle(off.begin(),off.end());
				for(auto &[id,tempo,l,r] : off){
					ans[id]=rt[tempo]->query(l,r);
				}
				off.clear();
			}
		}
		
		random_shuffle(off.begin(),off.end());
		for(auto &[id,tempo,l,r] : off){
			ans[id]=rt[tempo]->query(l,r);
		}
		
		for(int i=0;i<cont1;i++)cout<<ans[i]<<"\n";
	}

	return 0;
}

