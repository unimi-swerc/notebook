/// Source: Dariost (booklet SWERC 2019-2020 LaStatale Blue)
/// https://github.com/dariost/swerc/blob/master/src/Data_Structures/persistent_segment_tree.cpp
/// Verification:
/// https://evaluator.hsin.hr/tasks/HONI202167index/ (submission #1)
// tested with $n\leq 2e5, q\leq 2e5\log{2e5}$ (1.145 sec)
int segcnt = 0;
struct segment {
  int l, r, lid, rid, sum;
} segs[HUGE_VAL];
int build(int l, int r) { //$\mathcal{O}(n)$
  if(l > r)
    return -1;
  int id = segcnt++;
  segs[id].l = l;
  segs[id].r = r;
  if(l == r)
    segs[id].lid = -1, segs[id].rid = -1;
  else {
    int m = (l + r) / 2;
    segs[id].lid = build(l, m);
    segs[id].rid = build(m + 1, r);
  }
  segs[id].sum = 0; //initial array has only zeroes
  return id; //return the id of the new root
}
int update(int idx, int v, int id) { //$\mathcal{O}(\log{n})$
  if(id == -1)
    return -1;
  if(idx < segs[id].l || idx > segs[id].r)
    return id;
  int nid = segcnt++;
  segs[nid].l = segs[id].l;
  segs[nid].r = segs[id].r;
  segs[nid].lid = update(idx, v, segs[id].lid);
  segs[nid].rid = update(idx, v, segs[id].rid);
  segs[nid].sum = segs[id].sum + v; // point update
  return nid; //return the id of the new root
}
int query(int id, int l, int r) { //$\mathcal{O}(\log{n})$
  if(r < segs[id].l || segs[id].r < l)
    return 0;
  if(l <= segs[id].l && segs[id].r <= r)
    return segs[id].sum;
  return query(segs[id].lid, l, r) +
         query(segs[id].rid, l, r); // sum query
}
