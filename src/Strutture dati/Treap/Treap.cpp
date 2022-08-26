mt19937 rng(time(nullptr));

struct node {
    T val, mi;
    int size, rot;
    size_t prior;
    node *left, *right;

    node(T v) : val(v), mi(v), size(1), rot(0),
             prior(rng()), left(0), right(0) {}

    node* fix() {
        mi = val, size = 1;
        if (left) {
            mi = min(mi, left->mi);
            size += left->size;
            left->rot ^= rot;
        }
        if (right) {
            mi = min(mi, right->mi);
            size += right->size;
            right->rot ^= rot;
        }
        if (rot) swap(left, right);
        rot = 0;
        return this;
    }
};

node* merge(node* a, node* b) {
    if (!a) return b; a->fix();
    if (!b) return a; b->fix();
    if (a->prior > b->prior) {
        a->right = merge(a->right, b);
        return a->fix();
    } else {
        b->left = merge(a, b->left);
        return b->fix();
    }
}

pair<node*, node*> split(node* p, int k) {
    if (!p) return {nullptr, nullptr};
    p->fix();
    int sl = p->left ? p->left->size : 0;
    if (k <= sl) {
        auto [a, b] = split(p->left, k);
        p->left = b;
        return {a, p->fix()};
    } else {
        auto [a, b] = split(p->right, k-sl-1);
        p->right = a;
        return {p->fix(), b};
    }
}

int min_pos(node* p) {
    p->fix();
    int sl = p->left ? p->left->size : 0;
    if (p->left && p->left->mi == p->mi) {
        return min_pos(p->left);
    } else if (p->right && p->right->mi==p->mi) {
        return sl + 1 + min_pos(p->right);
    } else {
        return sl;
    }
}

node* build(vector<T>& A, int l, int r) {
    if (l + 1 == r) return new node(A[l]);
    int m = (l + r) / 2;
    node* a = build(A, l, m);
    node* b = build(A, m, r);
    return merge(a, b);
}
