#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

enum class Cov { NONE, X, H, V };

using CovRowsConcat = vector<Cov>;
using CovRows = vector<vector<Cov>>;

CovRows delinerize(const int h, const int w, const CovRowsConcat &xs) {
    CovRows ans(h, vector<Cov>(w, Cov::NONE));
    for (int ro = 0; ro < h; ++ro) {
        for (int co = 0; co < w; ++co) {
            ans[ro][co] = xs[w * ro + co];
        }
    }
    return ans;
}

vector<CovRowsConcat> all_b_type_layouts(const int h, const int w,
                                         const int b) {
    vector<CovRowsConcat> ans;

    CovRowsConcat curr(h * w, Cov::NONE);
    for (int i = 0; i < b; ++i) curr[i] = Cov::X;
    sort(begin(curr), end(curr));

    do {
        ans.push_back(curr);
    } while (next_permutation(begin(curr), end(curr)));

    return ans;
}

int backtrack_a_type_fills(const CovRows &rows, const int ro, const int co,
                           const int a) {
    const int h = sz(rows);
    const int w = sz(rows[0]);

    if (ro == h - 1 && co == w - 1 && rows[ro][co] != Cov::NONE) return 1;

    if (rows[ro][co] == Cov::NONE && a) {
        int ans = 0;

        if (co < w - 1 && rows[ro][co + 1] == Cov::NONE) {
            CovRows rows_ = rows;
            rows_[ro][co] = Cov::H;
            rows_[ro][co + 1] = Cov::H;
            ans += backtrack_a_type_fills(rows_, ro, co + 1, a - 1);
        }

        if (ro < h - 1 && rows[ro + 1][co] == Cov::NONE) {
            CovRows rows_ = rows;
            rows_[ro][co] = Cov::V;
            rows_[ro + 1][co] = Cov::V;
            ans += backtrack_a_type_fills(rows_, ro + 1, co, a - 1);
        }

        return ans;
    }

    if (co < w - 1) return backtrack_a_type_fills(rows, ro, co + 1, a);
    return backtrack_a_type_fills(rows, ro + 1, 0, a);
}

int ways_num(const int h, const int w, const int a, const int b) {
    int ans = 0;

    for (const auto &la : all_b_type_layouts(h, w, b)) {
        const auto rows = delinerize(h, w, la);
        ans += backtrack_a_type_fills(rows, 0, 0, a);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int h, w, a, b;
    cin >> h >> w >> a >> b;

    cout << ways_num(h, w, a, b) << '\n';
    return 0;
}
