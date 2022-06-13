template <typename Val>
class CompressedTree {
 private:
  typedef unsigned long size_t;
  typedef long diff_t;

  struct Node {
    size_t height, size;
    Val from, to;
    Node *left, *right;

    Node() : height(0), size(0), from(0), to(0),
                               left(0), right(0) {}
    Node(Val a, Val b, Node* l, Node* r) : from(a),
                         to(b), left(l), right(r) {
      update();
    }

    void update() {
      height = max(left->height, right->height) + 1;
      size = left->size + right->size + to - from;
    }

    diff_t factor() { return right->height-left->height; }
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
      if (p->right->factor() < 0) {
        p->right = rotateRight(p->right);
      }
      p = rotateLeft(p);
    } else if (p->factor() <= -2) {
      if (p->left->factor() > 0) {
        p->left = rotateLeft(p->left);
      }
      p = rotateRight(p);
    }
    return p;
  }

  Node* insert(Val from, Val to, size_t pos, Node* r) {
    if (r == end) return new Node(from, to, end, end);
    diff_t excess = pos - r->left->size;
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
      r->from = from;
      r->to = to;
    }
    return balance(r);
  }

  pair<Node*, Node*> eraseLeft(Node* r) {
    if (r->left == end) {
      Node* q = r->right;
      return make_pair(q, r);
    }
    auto ret = eraseLeft(r->left);
    r->left = ret.first;
    return make_pair(balance(r), ret.second);
  }

  pair<Node*, Val> erase(size_t pos, Node* r) {
    diff_t excess = pos - r->left->size;
    if (excess < 0) {
      auto ret = erase(pos, r->left);
      r->left = ret.first;
      return make_pair(balance(r), ret.second);
    } else if (excess >= r->to - r->from) {
      auto ret = erase(excess - (r->to - r->from),
                       r->right);
      r->right = ret.first;
      return make_pair(balance(r), ret.second);
    } else if (excess == 0 && r->to - r->from == 1) {
      if (r->right == end) {
        auto ret = make_pair(r->left, r->from);
        delete r;
        return ret;
      } else {
        auto retLeft = eraseLeft(r->right);
        retLeft.second->left = r->left;
        retLeft.second->right = retLeft.first;
        auto ret = make_pair(balance(retLeft.second),
                             r->from);
        delete r;
        return ret;
      }
    } else if (excess == 0) {
      r->from++;
      return make_pair(balance(r), r->from - 1);
    } else if (excess + 1 == r->to - r->from) {
      r->to--;
      return make_pair(balance(r), r->to);
    } else {
      r->right = insert(r->from + excess + 1, r->to,
                        0, r->right);
      r->to = r->from + excess;
      return make_pair(balance(r), r->to);
    }
  }

  Val find(size_t pos, Node* r) {
    diff_t excess = pos - r->left->size;
    if (excess < 0) {
      return find(pos, r->left);
    } else if (excess >= r->to - r->from) {
      return find(excess - (r->to - r->from),
                  r->right);
    } else {
      return r->from + excess;
    }
  }

  void destroy(Node* r) {
    if (r == end) return;
    destroy(r->left);
    destroy(r->right);
    delete r;
  }

 public:
  CompressedTree() { root = end = new Node(); }

  ~CompressedTree() {
    destroy(root);
    if (root != end) delete end;
  }

  void insert(Val val, size_t pos) {
    insert(val, val + 1, pos);
  }
  void insert(Val from, Val to, size_t pos) {
    root = insert(from, to, pos, root);
  }

  Val erase(size_t pos) {
    auto res = erase(pos, root);
    root = res.first;
    return res.second;
  }

  Val find(size_t pos) { return find(pos, root); }
};
