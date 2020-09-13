#include <bits/stdc++.h>
using namespace std;

int lhs_count(const int k, const vector<int> &xs, const int i) {
    const int n = xs.size();
    assert(i >= 0);
    assert(i < n);

    const auto is_covered = [&](const int j) {
        assert(j >= 0);
        assert(j < n);
        assert(j <= i);
        return xs[i] - k <= xs[j];
    };

    if (is_covered(0)) return i + 1;

    int lo = 1;
    int hi = i + 1;

    while (lo < hi) {
        assert(is_covered(i - lo + 1));
        if (lo + 1 == hi) return is_covered(i - hi + 1) ? hi : lo;

        const int mid = lo + (hi - lo) / 2;
        // cout << "lo:" << lo << " mid:" << mid << " hi:" << hi << endl;

        if (is_covered(i - mid + 1))
            lo = mid;
        else
            hi = mid - 1;

        // cout << "lo:" << lo << " mid:" << mid << " hi:" << hi << endl;
    }

    return lo;
}

int rhs_count(const int k, const vector<int> &xs, const int i) {
    const int n = xs.size();
    assert(i >= 0);
    assert(i < n);

    const auto is_covered = [&](const int j) {
        assert(j >= 0);
        assert(j < n);
        assert(i <= j);
        return xs[i] + k >= xs[j];
    };

    if (is_covered(n - 1)) return n - i;

    int lo = 1;
    int hi = n - i;

    while (lo < hi) {
        assert(is_covered(i + lo - 1));
        if (lo + 1 == hi) return is_covered(i + hi - 1) ? hi : lo;

        const int mid = lo + (hi - lo) / 2;
        // cout << "lo:" << lo << " mid:" << mid << " hi:" << hi << endl;

        if (is_covered(i + mid - 1))
            lo = mid;
        else
            hi = mid - 1;

        // cout << "lo:" << lo << " mid:" << mid << " hi:" << hi << endl;
    }

    return lo;
}

vector<int> gather_pref(const int k, const vector<int> &xs) {
    const int n = xs.size();
    vector<int> ans(n, 1);
    for (int i = 1; i < n; ++i) ans[i] = max(ans[i - 1], lhs_count(k, xs, i));
    return ans;
}

vector<int> gather_suff(const int k, const vector<int> &xs) {
    const int n = xs.size();
    vector<int> ans(n, 1);
    for (int i = n - 2; i >= 0; --i)
        ans[i] = max(ans[i + 1], rhs_count(k, xs, i));
    return ans;
}

int max_saved(const int k, const vector<int> &xs) {
    const int n = xs.size();
    const auto pref = gather_pref(k, xs);
    const auto suff = gather_suff(k, xs);
    int ans = suff[0];
    for (int i = 1; i < n; ++i) ans = max(ans, pref[i - 1] + suff[i]);
    return ans;
}

void test_stuff() {
    vector<int> xs{1, 1, 2, 3, 4, 5, 5, 10};
    // const int res = rhs_count(1, xs, 0);
    // cout << "→ " << res << endl;
    assert(lhs_count(1, xs, 0) == 1);
    assert(lhs_count(1, xs, 1) == 2);
    assert(lhs_count(1, xs, 2) == 3);
    assert(lhs_count(1, xs, 3) == 2);
    assert(lhs_count(1, xs, 4) == 2);
    assert(lhs_count(1, xs, 5) == 2);
    assert(lhs_count(1, xs, 6) == 3);
    assert(lhs_count(1, xs, 7) == 1);

    assert(rhs_count(1, xs, 0) == 3);
    assert(rhs_count(1, xs, 1) == 2);
    assert(rhs_count(1, xs, 2) == 2);
    assert(rhs_count(1, xs, 3) == 2);
    assert(rhs_count(1, xs, 4) == 3);
    assert(rhs_count(1, xs, 5) == 2);
    assert(rhs_count(1, xs, 6) == 1);
    assert(rhs_count(1, xs, 7) == 1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> xs(n, 0);
        for (auto &x : xs) cin >> x;
        sort(begin(xs), end(xs));

        for (int i = 0; i < n; ++i) {
            int y;
            cin >> y;
        }

        cout << max_saved(k, xs) << '\n';
    }

    // test_stuff();
    return 0;
}
