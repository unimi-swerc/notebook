//link cut tree degli dei
#define fori(a,b) for(int i=(a);i<(b);i++)

//0.687 s con $n,q \leq 10^5$ (e ios_sync_with_stdio=false)
const int N=100010;
typedef struct node* sp; //sp=splay tree
struct lazy{
  int a,b;
  operator bool() const{return !a||b;}
};
lazy operator+=(lazy& a,lazy& b){
  a.a=a.a*b.a; a.b=a.b*b.a+b.b;
  return a;
}
struct Info{
  int sz,sum,mi,ma;
  Info(int v){
    sz=1; sum=mi=ma=v;
  }
  Info(){
    sz=sum=0; mi=0x3f3f3f3f; ma=-0x3f3f3f3f;
  }
};
Info& operator+=(Info& a,Info& b){
  a.sz+=b.sz; a.sum+=b.sum; a.mi=min(a.mi,b.mi); a.ma=max(a.ma,b.ma);
  return a;
}
Info operator+=(Info& a,lazy& b){
  if(!a.sz) return a;
  a.sum=a.sum*b.a+a.sz*b.b; a.mi=a.mi*b.a+b.b; a.ma=a.ma*b.a+b.b;
  return a;
}
int operator +=(int& a,lazy& b){
  a=a*b.a+b.b;
  return a;
}
struct node{
  int id,val;
  sp p,c[5];
  bool flip;
  Info info[2];
  lazy lz[2];
  node(int i, int v){
    id=i; val=v;
    lz[0]=lz[1]={1,0}; info[0]=Info(val);
    p=nullptr; fori(0,5) c[i]=nullptr;
    flip=0;
  }
  void upd(lazy l){
    lz[0]+=l; info[0]+=l; val+=l;
  }
  void upd2(lazy l){
    lz[1]+=l; info[1]+=l;
  }
  void push(){
    if(flip){
      swap(c[0],c[1]);
      fori(0,2) if(c[i]) c[i]->flip^=1;
      flip=0;
    }
    if(lz[1]){
      fori(0,5) if(c[i]){
        c[i]->upd2(lz[1]);
        if(i>=2) c[i]->upd(lz[1]);
      }
      lz[1]={1,0};
    }
    if(lz[0]){
      fori(0,2) if(c[i]) c[i]->upd(lz[0]);
      lz[0]={1,0};
    }
  }
  void pull(){
    info[0]=Info(val); info[1]=Info();
    fori(0,5) if(c[i]){
      info[1]+=c[i]->info[1];
      info[i>=2]+=c[i]->info[0];
    }
  }
  int dir(){
    if(!p) return 5;
    fori(0,5) if(p->c[i]==this) return i;
  }
  friend void connect(sp x,sp y,int d){
    if(y) y->p=x;
    if(d<5) x->c[d]=y;
  }
  void rot(){
    int d = dir(); sp x=p;
    connect(x->p,this,x->dir()); connect(x,c[d^1],d); connect(this,x,d^1);
    x->pull(); pull();
  }
};
void splay(sp x){
  if(!x) return;
  sp y;
  while(x->dir()<2&&x->p->dir()<2&&x->p->p->dir()<2){
    y=x->p; y->p->push(); y->push(); x->push();
    x->dir()==y->dir()? y->rot(): x->rot();
    x->rot();
  }
  if(x->dir()<2&&x->p->dir()<2) x->p->push(), x->push(), x->rot();
  if(x->dir()<2) {
    x->p->push(), x->push();
    fori(2,4) if(x->p->c[i]) connect(x,x->p->c[i],i), x->p->c[i]=nullptr;
    x->rot();
  }
  while(x->dir()<4){
    y=x->p; if(y->p) y->p->push(); y->push(); x->push();
    if(y->dir()<4) x->dir()==y->dir()? y->rot(): x->rot();
    x->rot();
  }
  x->push();
}
sp splayRight(sp x){
  while(x->c[3]) x=x->c[3];
  splay(x); return x;
}
sp join(sp a,sp b){
  if(!a) return b;
  splay(a); a=splayRight(a);
  connect(a,b,3); a->pull(); return a;
}
void access(sp x){
  for(sp v=x,last=nullptr;v;v=v->p){
    splay(v); auto c=v->c[1];
    if(c) c->p=nullptr;
    if(last){
      last->push();
      auto a=last->c[2],b=last->c[3];
      if(a) a->p=nullptr;
      if(b) b->p=nullptr;
      last->c[2]=last->c[3]=nullptr;
      connect(v,join(join(a,b),c),4);
    }
    else{
      if(v->c[4]) v->c[4]->p=nullptr;
      connect(v,join(c,v->c[4]),4);
    }
    v->c[1]=last; v->pull(); last=v;
  }
  splay(x);
}
void evert(sp x){
  access(x);
  x->flip^=1;
}
sp lca(sp x,sp y){
  if(x==y) return x;
  access(x); access(y);
  if(!x->p) return nullptr;
  splay(x); return x->p?:x;
}
void link(sp x,sp y){
  if(lca(x,y)) return; //!need to access y!!
  evert(x); connect(y,join(x,y->c[4]),4);
}
void cut(sp x){
  access(x);
  x->c[0]->p=nullptr; x->c[0]=nullptr;
}
sp lct[N];
int n,q,a,b,c,t,rt;
pair<int,int> e[N];
Info ans;

int main(){
  cin>>n>>q;
  fori(1,n) cin>>e[i].first>>e[i].second;
  fori(1,n+1){
    cin>>a; lct[i]=new node(i,a);
  }
  fori(1,n){
    tie(a,b)=e[i];
    link(lct[a],lct[b]);
  }
  cin>>rt;
  fori(0,q){
    cin>>t;
    if(t==1){
      cin>>a; rt=a;
    }
    else if(t==0||t==5){
      cin>>a>>b;
      evert(lct[rt]); access(lct[a]);
      lazy temp={t==5,b}; auto c=lct[a]->c[4];
      if(c) c->upd(temp), c->upd2(temp);
      lct[a]->val+=temp;
    }
    else if(t==3||t==4||t==11){
      cin>>a;
      evert(lct[rt]); access(lct[a]);
      ans=Info(lct[a]->val); auto c=lct[a]->c[4];
      if(c) ans+=c->info[0], ans+=c->info[1];
      if(t==3) cout<<ans.mi<<"\n";
      else if(t==4) cout<<ans.ma<<"\n";
      else if(t==11) cout<<ans.sum<<"\n";
    }
    else if(t==2||t==6){
      cin>>a>>b>>c;
      evert(lct[a]); access(lct[b]);
      lct[b]->upd({t==6,c});
    }
    else if(t==7||t==8||t==10){
      cin>>a>>b;
      evert(lct[a]); access(lct[b]); ans=lct[b]->info[0];
      if(t==7) cout<<ans.mi<<"\n";
      else if(t==8) cout<<ans.ma<<"\n";
      else if(t==10) cout<<ans.sum<<"\n";
    }
    else if(t==9){
      cin>>a>>b;
      evert(lct[rt]);
      if(lca(lct[a],lct[b])==lct[a]) continue;
      cut(lct[a]); link(lct[a],lct[b]);
    }
  }
  return 0;
}
