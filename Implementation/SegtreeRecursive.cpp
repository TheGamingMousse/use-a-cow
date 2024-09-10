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
    void apply(int v, int len, const Tag &x) {
        t[v].apply(x, len);
        lz[v].apply(x, len);
    }
    void pushdown(int v, int l, int r) {
        int m = (l + r) >> 1;
        apply(2 * v, m - l + 1, lz[v]);
        apply(2 * v + 1, r - m, lz[v]);
        lz[v] = Tag();
    }
    void upd(int v, int l, int r, int ql, int qr, const Tag &x) {
        if (qr < l || ql > r) { return; }
        if (ql <= l && r <= qr) {
            apply(v, r - l + 1, x);
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

    template<class F> 
    int walk(int v, int l, int r, Info cur, const F &func) {
        if (l == r) {
            return l;
        } else {
            int m = (l + r) / 2;
            pushdown(v, l, r);
            Info x = cur + t[2 * v];
            return func(x) ? walk(2 * v, l, m, cur, func) 
                           : walk(2 * v + 1, m + 1, r, x, func);
        }
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

    void upd(int ql, int qr, const Tag &x) {
        upd(1, 0, n - 1, ql, qr, x);
    }

    Info qry(int ql, int qr) {
        return qry(1, 0, n - 1, ql, qr);
    }

    template<class F>
    int walk(const F &func) {
        return walk(1, 0, n - 1, Info(), func);
    }
};

struct Tag {
    // tree values, and also set the default values

    /** apply this new tag to this lazy tag */
    void apply(const Tag &t, int len) {
        
    }
};

struct Info {
    // lazy tag values, and also set the default tag values 
    
    /** apply the lazy tag to this tree value */
    void apply(const Tag &t, int len) {
        
    }
};

/** @return result of joining a amd b together */
Info operator+(const Info &a, const Info &b) {

}