#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, k;
int a[MAXN];
int limitPos[MAXN];

vector<int> pos[MAXN];

struct Node {
    int sum;
    Node *l, *r;
    Node(int s=0) : sum(s), l(nullptr), r(nullptr) {}
};

Node* build(int l, int r) {
    Node* node = new Node();
    if (l == r) return node;
    int m = (l + r) / 2;
    node->l = build(l, m);
    node->r = build(m+1, r);
    return node;
}

Node* update(Node* prev, int l, int r, int pos, int val) {
    Node* node = new Node();
    if (l == r) {
        node->sum = prev->sum + val;
        return node;
    }
    int m = (l + r) / 2;
    if (pos <= m) {
        node->l = update(prev->l, l, m, pos, val);
        node->r = prev->r;
    } else {
        node->l = prev->l;
        node->r = update(prev->r, m+1, r, pos, val);
    }
    node->sum = node->l->sum + node->r->sum;
    return node;
}

int query(Node* node, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) return node->sum;
    int m = (l + r) / 2;
    return query(node->l, l, m, ql, qr) +
           query(node->r, m+1, r, ql, qr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }

    // compute limit
    for (int v = 1; v <= 100000; v++) {
        auto &vec = pos[v];
        for (int i = 0; i < vec.size(); i++) {
            if (i >= k)
                limitPos[vec[i]] = vec[i - k];
            else
                limitPos[vec[i]] = 0;
        }
    }

    vector<Node*> root(n+1);
    root[0] = build(1, n);

    for (int i = 1; i <= n; i++) {
        root[i] = update(root[i-1], 1, n, i, 1);
        if (limitPos[i] != 0) {
            root[i] = update(root[i], 1, n, limitPos[i], -1);
        }
    }

    int q;
    cin >> q;

    int last = 0;

    while (q--) {
        int x, y;
        cin >> x >> y;

        int l = (x + last) % n + 1;
        int r = (y + last) % n + 1;
        if (l > r) swap(l, r);

        int ans = query(root[r], 1, n, l, r);

        cout << ans << "\n";
        last = ans;
    }

    return 0;
}