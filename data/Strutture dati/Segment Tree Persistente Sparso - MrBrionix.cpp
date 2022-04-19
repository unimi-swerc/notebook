#include<bits/stdc++.h>
using namespace std;

const int MAXN=100005, MAXM=5005, MAXA=2000000010;
const int LOGA=32, GAP = 1000000005;

struct SegmentTree{
	unsigned int sum,lvl;
	SegmentTree *left,*right;
	
	static SegmentTree* newSeg();
	static SegmentTree* newSeg(int lvl);
	
	SegmentTree* copy(int lvl){
		SegmentTree *res = newSeg();
		*res=*this;
		res->lvl=lvl;
		
		return res;
	}
	
	void checkcopy(){
		if(left==nullptr)
			left = newSeg(lvl);
		else if(left->lvl!=lvl)
			left = left->copy(lvl);
			
		if(right==nullptr)
			right = newSeg(lvl);
		else if(right->lvl!=lvl)
			right = right->copy(lvl);
	}
	
	void update(int pos,long long _l,long long _r){
		if(pos<_l || pos>_r)return;
		if(_l==_r){
			sum++;
			return;
		}
		
		checkcopy();
		
		left->update(pos,_l,(_l+_r)/2);
		right->update(pos,(_l+_r)/2+1,_r);
		sum = left->sum+right->sum;
	}
};

int cc=0;
SegmentTree vett[2*(MAXN+MAXM*2)*LOGA];

SegmentTree* SegmentTree::newSeg(){
	return &vett[cc++];
}

SegmentTree* SegmentTree::newSeg(int lvl){
	vett[cc]={0,lvl,nullptr,nullptr};
	
	return &vett[cc++];
}

int query(SegmentTree *a,SegmentTree *b,int k,
    long long _l,long long _r){
	if(_l==_r)return _l;
	
	a->checkcopy();
	b->checkcopy();
	
	int val=b->left->sum-a->left->sum;
	
	if(val>=k)
		return query(a->left,b->left,k,_l,(_l+_r)/2);
	else
		return query(a->right,b->right,k-val,(_l+_r)/2+1,_r);
}

SegmentTree *rt[MAXN];
int n,m,cont;

int main(){

	ios::sync_with_stdio(false);
	cin.tie(0);
	
	cin>>n>>m;
	rt[cont++] = SegmentTree::newSeg(0);
	
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		
		rt[cont]=rt[cont-1]->copy(cont);
		rt[cont]->update(x+GAP,1,MAXA);
		cont++;
	}
	
	for(int i=0;i<m;i++){
		int a,b,c;
		cin>>a>>b>>c;
		
		cout<<query(rt[a-1],rt[b],c,1,MAXA)-GAP<<"\n";
	}

	return 0;
}

