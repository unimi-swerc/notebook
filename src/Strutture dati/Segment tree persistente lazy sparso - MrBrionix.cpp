/// Source: MrBrionix
/// Verification:
/// https://www.spoj.com/problems/HORRIBLE/ (id: 29751795)
/// https://training.olinfo.it/#/task/ois_police7 (id: da cercare, cms non funziona ora)
typedef long long ll;//$n,q\leq 10^5$,t ignoto->0.89sec
const ll MAXN=100005, LOGN=42, GAP = 10000004;
struct SegmentTree{//$\mathcal{O}(\log{N})$ per query/update ovviamente
  __int128 sum;
  SegmentTree *left,*right;
  long long lazy;
  int lvl;
  static SegmentTree* newSeg();
  static SegmentTree* newSeg(ll l,ll r,int _lvl);
  
  void build(ll *v,ll l,ll r,ll _l,ll _r){
    if(_r<l || _l>r)return;  
    if(_l==_r){
      sum=v[_l];
      return;
    }
    checkcopy(_l,_r);
    left->build(v,l,r,_l,(_l+_r)/2);
    right->build(v,l,r,(_l+_r)/2+1,_r);   
    sum=left->sum+right->sum;
  }
  
  SegmentTree* copy(int x){
    SegmentTree *res = newSeg(); 
    *res = *this;
    res->lvl=x;
    return res;
  }
  
  void checkcopy(long long _l,long long _r){   
    if(left == nullptr){
      left = newSeg(_l,(_l+_r)/2,lvl);
    } else if(left->lvl != lvl){
      left = left->copy(lvl);
    }
	
    if(right == nullptr){
      right = newSeg((_l+_r)/2+1,_r,lvl);
    }else if(right->lvl != lvl){
      right = right->copy(lvl);
    }
  }
  
  void checklazy(long long _l,long long _r){
    if(lazy!=0){
      left->lazy+=lazy;
      left->sum+=lazy*((_l+_r)/2-_l+1);
      right->lazy+=lazy;
      right->sum+=lazy*(_r-((_l+_r)/2+1)+1);
      lazy=0;
    }
  }
  
  void update(ll l,ll r,ll val,ll _l,ll _r){
    if(l>r || r<_l || l>_r)return;
    if(_l>=l && _r<=r){
      lazy+=val;
      sum+=val*(_r-_l+1);
      return;
    }
    checkcopy(_l,_r);
    checklazy(_l,_r);
    left->update(l,r,val,_l,(_l+_r)/2);
    right->update(l,r,val,(_l+_r)/2+1,_r);
    sum=left->sum+right->sum;
  }
  
  void pointupdate(ll pos,ll val,ll _l,ll _r){
    if(pos<_l || pos>_r)return;
    if(_l==_r){
      sum+=val;
      return;
    }
    checkcopy(_l,_r);
    checklazy(_l,_r);
    left->pointupdate(pos,val,_l,(_l+_r)/2);
    right->pointupdate(pos,val,(_l+_r)/2+1,_r);
    sum = left->sum+right->sum;
  }
  
  __int128 query(ll l,ll r,ll _l,ll _r){
    if(_r<l || _l>r)return 0;
    if(_l>=l && _r<=r)return sum;
    checkcopy(_l,_r);
    checklazy(_l,_r);
    return left->query(l,r,_l,(_l+_r)/2)+
	  right->query(l,r,(_l+_r)/2+1,_r);
  }
};

SegmentTree vett[4*(MAXN*LOGN+MAXN*LOGN)]; //652M
int cc=0;
SegmentTree* SegmentTree::newSeg(){
  return &vett[cc++];
}
SegmentTree* SegmentTree::newSeg(ll l,ll r,int _lvl){
  int ind=cc++; 
  vett[ind].sum=0;
  vett[ind].lazy=0;
  vett[ind].lvl=_lvl;
  vett[ind].left=nullptr;
  vett[ind].right=nullptr; 
  return &vett[ind];
}
/* building:
  rt[0] = SegmentTree::newSeg(1,(n+1)*GAP,0);
  rt[0]->build(v,1,n,1,(n+1)*GAP);
  update:
  rt[cont]=rt[cont-1]->copy(cont);
  rt[cont]->update(b*GAP,c*GAP+GAP,d,1,(n+1)*GAP);
  rt[cont]->pointupdate(c*GAP+GAP,-d,1,(n+1)*GAP);
  query:
  ans[id]=rt[tempo]->query(l*GAP,r*GAP+GAP-1,1,(n+1)*GAP);*/
