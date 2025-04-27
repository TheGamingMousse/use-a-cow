#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/**
 * Sparse segment tree.
 * Update: O(log n)
 * Query: O(log n)
 * Space: O(q log n)
 * 
 * Info = tree values
 * Tag = lazy updates
 */
template <class Info, class Tag>
class SparseSegtree {
  private:
    struct Node {
        Info info;
        Tag tag;
        Node *left = nullptr;
        Node *right = nullptr;
    };
    Node *root = new Node;
    const int n;

    void apply(Node *v, int l, int r, const Tag &x) {
        (v -> info).apply(x, l, r);
        (v -> tag).apply(x);
    }

    void pushdown(Node *v, int l, int r) {
        if ((v -> left) == nullptr) { (v -> left) = new Node; }
        if ((v -> right) == nullptr) { (v -> right) = new Node; }
        int m = (l + r) >> 1;
        apply(v -> left, l, m, v -> tag);
        apply(v -> right, m + 1, r, v -> tag);
        (v -> tag) = Tag();
    }

    void upd(Node *v, int l, int r, int ql, int qr, const Tag &x) {
        if (qr < l || ql > r) { return; }
        if (ql <= l && r <= qr) {
            apply(v, l, r, x);
        } else {
            pushdown(v, l, r);
            int m = (l + r) >> 1;
            upd(v -> left, l, m, ql, qr, x);
            upd(v -> right, m + 1, r, ql, qr, x);
            (v -> info) = ((v -> left) -> info) + ((v -> right) -> info);
        }
    }

    Info qry(Node *v, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) { return Info(); }
        if (ql <= l && r <= qr) { return v -> info; }
        pushdown(v, l, r);
        int m = (l + r) >> 1;
        return qry(v -> left, l, m, ql, qr) + qry(v -> right, m + 1, r, ql, qr);
    }

    template<typename F>
    int walk(Node *v, int l, int r, const Info &pf, const F &f) {
        if (l == r) { return l; }
        pushdown(v, l, r);
        int m = (l + r) >> 1;
        Info x = pf + ((v -> left) -> info);
        return f(x) ? walk(v -> left, l, m, pf, f)
                    : walk(v -> right, m + 1, r, x, f);
    }

  public:
    SparseSegtree() {}
    SparseSegtree(int n) : n(n) {}

    void upd(int ql, int qr, const Tag &x) {
        upd(root, 0, n - 1, ql, qr, x); 
    }

    Info qry(int ql, int qr) {
        return qry(root, 0, n - 1, ql, qr);
    }

    template<typename F>
    int walk(const F &fn) {
        return walk(root, 0, n - 1, Info(), fn);
    }
};

struct Tag {
    // tag values
    void apply(const Tag &t) {
        // make sure tag isn't the default value
    }
};

struct Info {
    // tree values
    void apply(const Tag &t, int l, int r) {
        // make sure tag isn't the default value
    }
};

/** @return result of joining two tree nodes */
Info operator+(const Info &a, const Info &b) {
    
}