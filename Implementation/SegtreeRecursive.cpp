#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <class Info, class Tag> 
class LazySegtree {
  private:
    const int n;
    vector<Info> t;
    vector<Tag> lz;
       
    void build(int v, int l, int r, const vector<Info> &a) {
        if (l == r) {
            t[v] = a[l];
        } else {
            int m = (l + r) >> 1;
            build(2 * v, l, m, a);
            build(2 * v + 1, m + 1, r, a);
            t[v] = t[2 * v] + t[2 * v + 1];
        }
    }

    void apply(int v, int l, int r, const Tag &x) {
        t[v].apply(x, l, r);
        lz[v].apply(x, l, r);
    }

    void pushdown(int v, int l, int r) {
        int m = (l + r) >> 1;
        apply(2 * v, l, m, lz[v]);
        apply(2 * v + 1, m + 1, r, lz[v]);
        lz[v] = Tag();
    }

    void upd(int v, int l, int r, int ql, int qr, const Tag &x) {
        if (qr < l || ql > r) { return; }
        if (ql <= l && r <= qr) {
            apply(v, l, r, x);
        } else {
            pushdown(v, l, r);
            int m = (l + r) >> 1;
            upd(2 * v, l, m, ql, qr, x);
            upd(2 * v + 1, m + 1, r, ql, qr, x);
            t[v] = t[2 * v] + t[2 * v + 1];
        }
    }
    
    Info qry(int v, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return Info();
        if (l >= ql && r <= qr) return t[v];
        pushdown(v, l, r);
        int m = (l + r) >> 1;
        return qry(2 * v, l, m, ql, qr) + qry(2 * v + 1, m + 1, r, ql, qr);
    }

  public:
    LazySegtree(int n) : n(n) {
        t.assign(4 << __lg(n), Info());
        lz.assign(4 << __lg(n), Tag());
    }

    LazySegtree(const vector<Info> &a) : n(a.size()) {
        t.assign(4 << __lg(n), Info());
        lz.assign(4 << __lg(n), Tag());
        build(1, 0, n - 1, a);
    }

    /** updates [ql, qr] with the arbitrary update chosen */
    void upd(int ql, int qr, const Tag &x) {
        upd(1, 0, n - 1, ql, qr, x);
    }

    /** @return result of range query on [ql, qr] */
    Info qry(int ql, int qr) {
        return qry(1, 0, n - 1, ql, qr);
    }
};

struct Tag {
    // lazy tag values
    void apply(const Tag &t, int l, int r) {
        // tag to tag code
    }
};

struct Info {
    // tree values
    void apply(const Tag &t, int l, int r) {
        // tag to tree value code
    }
};

/** @return result of joining nodes a and b together */
Info operator+(const Info &a, const Info &b) {

}