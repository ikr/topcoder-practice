#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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

double score(const vector<double> &xs, vector<vector<double>> &memo,
             const int l, const int r) {
    const int n = xs.size();

    assert(l < r);
    assert(l >= 0);
    assert(l < n);
    assert(r >= 0);
    assert(r < n);

    if (memo[l][r] < 0) {
        double s = xs[l] + xs[l + 1];
        if (r - l > 1) s += xs[r - 1] + xs[r];

        // The line of the last merge
        for (int i = l + 1; i <= r - 2; ++i) {
            const double bef = score(xs, memo, l, i);
            const double aft = score(xs, memo, i + 1, r);
            s += bef + aft;
        }

        memo[l][r] = s / (r - l);
    }

    return memo[l][r];
}

double solve(const vector<double> &xs) {
    const int n = xs.size();
    vector<vector<double>> memo(n, vector<double>(n, -1));
    const auto ans = score(xs, memo, 0, n - 1);
    cout << '\n' << memo << '\n';
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << setprecision(7) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n;
        cin >> n;
        vector<double> xs(n, 0);
        for (auto &x : xs) cin >> x;

        cout << "Case #" << i << ": " << solve(xs) << '\n';
    }

    return 0;
}
