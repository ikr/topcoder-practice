#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

using vi = vector<int>;
using vvi = vector<vi>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vvi gather_children(const vi &parent) {
    vvi ans(sz(parent));
    for (int u = 1; u < sz(parent); ++u) {
        ans[parent[u]].push_back(u);
    }
    return ans;
}

vi gather_levels(const vvi &children) {
    vi ans(sz(children), 0);
    function<void(int, int)> recur;
    recur = [&](const int level, const int u) {
        ans[u] = level;
        for (const auto v : children[u]) {
            recur(level + 1, v);
        }
    };
    recur(1, 1);
    return ans;
}

constexpr int mlog2(const int x) {
    return 8 * inof(sizeof(int)) - __builtin_clz(x) - 1;
}

vvi gather_lifts(const vi &parent) {
    const int n = sz(parent) - 1;
    const int m = mlog2(n);
    vvi ans(n + 1, vi(m + 1, 0));
    for (int i = 1; i <= n; ++i) ans[i][0] = parent[i];

    for (int j = 1; j <= m; ++j) {
        for (int i = 1; i <= n; ++i) {
            ans[i][j] = ans[ans[i][j - 1]][j - 1];
        }
    }

    return ans;
}

int k_levels_up(const vvi &up, const int u, const int k) {
    int r = k;
    int ans = u;

    while (r) {
        const auto j = mlog2(r);
        r &= ~(1 << j);
        ans = up[ans][j];
    }

    return ans;
}

int lca_from_same_level(const vvi &up, int a, int b) {
    if (a == b) return a;
    const int m = sz(up[0]) - 1;

    int j = m;
    while (up[a][0] != up[b][0]) {
        while (j && up[a][j] == up[b][j]) j--;

        a = up[a][j];
        b = up[b][j];
    }

    return up[a][0];
}

int lca(const vi &lvl, const vvi &up, int a, int b) {
    if (lvl[a] != lvl[b]) {
        if (lvl[a] > lvl[b]) swap(a, b);
        assert(lvl[b] - lvl[a] > 0);
        b = k_levels_up(up, b, lvl[b] - lvl[a]);
    }

    return lca_from_same_level(up, a, b);
}

vi diagnose(const vi &phab_parent, const vi &ic, const vvi &diseases,
            const vvi &patients) {
    const auto ch = gather_children(phab_parent);
    const auto lvl = gather_levels(ch);
    const auto up = gather_lifts(phab_parent);

    const auto score_term = [&](const int pv, const vi &d) {
        int ans = 0;
        for (const auto dv : d) {
            ans = max(ans, ic[lca(lvl, up, pv, dv)]);
        }
        return ans;
    };

    const auto score = [&](const vi &p, const vi &d) {
        int ans = 0;
        for (const auto &pv : p) ans += score_term(pv, d);
        return ans;
    };

    vi ans(sz(patients), 0);

    for (int i = 0; i < sz(patients); ++i) {
        int best_ic = 0;
        int best_j = -1;

        for (int j = 0; j < sz(diseases); ++j) {
            const auto curr_ic = score(patients[i], diseases[j]);
            if (curr_ic > best_ic) {
                best_ic = curr_ic;
                best_j = j;
            }
        }

        ans[i] = best_j;
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vi phab_parent(n + 1, 0);
    for (int i = 2; i <= n; ++i) cin >> phab_parent[i];

    vi ic(n + 1, 0);
    for (int i = 1; i <= n; ++i) cin >> ic[i];

    int m;
    cin >> m;
    vvi diseases(m);
    for (auto &vs : diseases) {
        int cm;
        cin >> cm;
        vs.resize(cm);
        for (auto &v : vs) cin >> v;
    }

    int nq;
    cin >> nq;
    vvi patients(nq);
    for (auto &vs : patients) {
        int cq;
        cin >> cq;
        vs.resize(cq);
        for (auto &v : vs) cin >> v;
    }

    for (const auto x : diagnose(phab_parent, ic, diseases, patients)) {
        cout << x + 1 << '\n';
    }

    return 0;
}
