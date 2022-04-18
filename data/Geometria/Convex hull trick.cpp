vector<pt> hull, vecs;

void add_line(ll k, ll b) {
    pt nw = {k, b};
    while(!vecs.empty() && dot(vecs.back(), nw - hull.back()) < 0) {
        hull.pop_back();
        vecs.pop_back();
    }
    if(!hull.empty()) {
        vecs.push_back(complex<ll>(1i) * (nw - hull.back()));
    }
    hull.push_back(nw);
}

ll get(ll x) {
    pt query = {x, 1};
    auto it = lower_bound(vecs.begin(), vecs.end(), query, [](pt a, pt b) {
        return cross(a, b) > 0;
    });
    return dot(query, hull[it - vecs.begin()]);
}
