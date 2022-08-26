typedef long long ll;
const int MAXN=100005, LOGN=42;
const long long GAP = 10000004;
struct SegmentTree{
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

SegmentTree vett[4*(MAXN*LOGN+MAXN*LOGN)];
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

struct que{
  int id,tempo,l,r;
};
SegmentTree *rt[MAXN];
long long t,n,q,v[MAXN],cont,cont1;
__int128 ans[MAXN];
vector<que> off;

signed main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin>>t;
  while(t--){
    off.clear();
    cin>>n;
    cc=0;
    rt[0] = SegmentTree::newSeg(1,(n+1)*GAP,0);
    rt[0]->build(v,1,n,1,(n+1)*GAP);
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
        rt[cont]->update(b*GAP,c*GAP+GAP,d,1,(n+1)*GAP);
        rt[cont]->pointupdate(c*GAP+GAP,-d,1,(n+1)*GAP);
        cont++;
      }else{
        int p,q;
        cin>>p>>q;
        off.push_back({cont1,cont-1,p,q});
        cont1++;
      }
    }
    random_shuffle(off.begin(),off.end());
    for(auto &[id,tempo,l,r] : off){
    ans[id]=rt[tempo]->query(l*GAP,r*GAP+GAP-1,1,(n+1)*GAP);
    }
    for(int i=0;i<cont1;i++)cout<<(ll)(ans[i]/GAP)<<"\n";
  }
  return 0;
}
