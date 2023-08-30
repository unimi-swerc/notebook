/// Source: Bortoz
/// Verification:
/// https://training.olinfo.it/#/task/vasi2/submissions (id: 825432)
/// https://tlx.toki.id/contests/osn-open-2023-day-2/submissions/430773
// $\mathcal{O}(\log{N})$ query/update, 0-based
class CompressedTree {
 private:
  struct Node {
    ll height, size;
    ll from, to;
    Node *left, *right;
    Node() : height(0), size(0), from(0), to(0),
                               left(0), right(0) {}
    Node(ll a, ll b, Node* l, Node* r) : from(a),
                         to(b), left(l), right(r) {
      update();
    }
    void update() {
      height = max(left->height, right->height) + 1;
      size = left->size + right->size + to - from;
    }
    ll factor() { return right->height-left->height; }
  };
  Node *root, *end;
  Node* rotateLeft(Node* p) {
    Node* q = p->right;
    p->right = q->left;
    q->left = p;
    p->update();
    q->update();
    return q;
  }
  Node* rotateRight(Node* p) {
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    p->update();
    q->update();
    return q;
  }
  Node* balance(Node* p) {
    p->update();
    if (p->factor() >= 2) {
      if (p->right->factor() < 0)
         p->right = rotateRight(p->right);
      p = rotateLeft(p);
    } else if (p->factor() <= -2) {
      if (p->left->factor() > 0)
         p->left = rotateLeft(p->left);
      p = rotateRight(p);
    }
    return p;
  }
  Node* insert(ll from, ll to, size_t pos, Node* r) {
    if (r == end) return new Node(from, to, end, end);
    ll excess = pos - r->left->size;
    if (excess <= 0) {
      r->left = insert(from, to, pos, r->left);
    } else if (excess >= r->to - r->from) {
      r->right = insert(from, to, excess-(r->to-r->from),
                        r->right);
    } else {
      r->left = insert(r->from, r->from+excess, pos,
                       r->left);
      r->right = insert(r->from + excess, r->to, 0,
                        r->right);
      r->from = from, r->to = to;
    }
    return balance(r);
  }
  pair<Node*, Node*> eraseLeft(Node* r) {
    if (r->left == end) {
      Node* q = r->right;
      return {q, r};
    }
    auto ret = eraseLeft(r->left);
    r->left = ret.first;
    return {balance(r), ret.second};
  }
  pair<Node*, ll> erase(size_t pos, Node* r) {
    ll excess = pos - r->left->size;
    if (excess < 0) {
      auto ret = erase(pos, r->left);
      r->left = ret.first;
      return {balance(r), ret.second};
    } else if (excess >= r->to - r->from) {
      auto ret = erase(excess - (r->to - r->from),
                       r->right);
      r->right = ret.first;
      return {balance(r), ret.second};
    } else if (excess == 0 && r->to - r->from == 1) {
      if (r->right == end) {
        return {r->left, r->from};
      } else {
        auto retLeft = eraseLeft(r->right);
        retLeft.second->left = r->left;
        retLeft.second->right = retLeft.first;
        return {balance(retLeft.second), r->from};
      }
    } else if (excess == 0) {
      r->from++;
      return {balance(r), r->from - 1};
    } else if (excess + 1 == r->to - r->from) {
      r->to--;
      return {balance(r), r->to};
    } else {
      r->right = insert(r->from + excess + 1, r->to,
                        0, r->right);
      r->to = r->from + excess;
      return {balance(r), r->to};
    }
  }
  ll find(size_t pos, Node* r) {
    ll excess = pos - r->left->size;
    if (excess < 0) {
      return find(pos, r->left);
    } else if (excess >= r->to - r->from) {
      return find(excess - (r->to - r->from),
                  r->right);
    } else {
      return r->from + excess;
    }
  }
 public:
  CompressedTree() { root = end = new Node(); }
  //gli elementi con indice >=pos scalano a dx (0-based)
  void insert(ll val, size_t pos) {
    insert(val, val + 1, pos);
  }
  void insert(ll from, ll to, size_t pos) {
    root = insert(from, to, pos, root);
  }
  ll erase(size_t pos) {
    auto res = erase(pos, root);
    root = res.first;
    return res.second;
  }
  ll find(size_t pos) { return find(pos, root); }
};
