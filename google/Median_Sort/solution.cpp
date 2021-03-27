#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

int query(const tuple<int, int, int> ijk, int &Q) {
    assert(Q > 0);
    const auto [i, j, k] = ijk;
    cout << i << ' ' << j << ' ' << k << endl;

    int ans;
    cin >> ans;
    --Q;
    return ans;
}

using Iter = vi::const_iterator;

bool is_first_edge(const Iter first, const Iter last, const Iter x, int &Q) {
    assert(x != last);
    assert(distance(first, last) > 2);

    for (auto it = first; next(it) != last; ++it) {
        for (auto jt = next(it); jt != last; ++jt) {
            if (it == x || jt == x) continue;

            const auto mid = query({*it, *x, *jt}, Q);
            if (mid == *x) return false;
        }
    }

    return true;
}

bool is_second_edge(const Iter first, const Iter last, const Iter x0,
                    const Iter x, int &Q) {
    assert(x != last);
    assert(x != x0);
    assert(distance(first, last) > 2);

    for (auto it = first; it != last; ++it) {
        if (it == x0 || it == x) continue;
        const auto mid = query({*x0, *x, *it}, Q);
        if (mid == *x) return false;
    }

    return true;
}

vi extract_edge(vi &xs, int &Q) {
    if (sz(xs) < 3) {
        vi ans = xs;
        xs.clear();
        return ans;
    }

    vector<Iter> its;
    for (auto it = cbegin(xs); it != cend(xs); ++it) {
        if (its.empty()) {
            if (is_first_edge(cbegin(xs), cend(xs), it, Q)) {
                its.push_back(it);
            }
        } else {
            if (is_second_edge(cbegin(xs), cend(xs), its[0], it, Q)) {
                its.push_back(it);
                break;
            }
        }
    }

    assert(sz(its) == 2);
    sort(begin(its), end(its));

    vi ans{*its[0], *its[1]};
    xs.erase(its[1]);
    xs.erase(its[0]);
    return ans;
}

vi one_to(const int N) {
    vi ans(N);
    iota(begin(ans), end(ans), 1);
    return ans;
}

vi join(vi head, vi tail) {
    head.insert(end(head), crbegin(tail), crend(tail));
    return head;
}

pii orient(const pii curr_edge, const pii new_edge, int &Q) {
    const auto [a, b] = curr_edge;
    const auto [c, d] = new_edge;

    return (query({a, c, d}, Q) == c) ? pii{c, d} : pii{d, c};
}

vi derive_order(const int N, int &Q) {
    vi head;
    vi tail;

    vi xs = one_to(N);
    while (!xs.empty()) {
        if (!Q) return one_to(N);
        const auto e = extract_edge(xs, Q);

        if (sz(e) == 1) {
            assert(!head.empty());
            head.push_back(e[0]);
        } else {
            if (head.empty()) {
                assert(tail.empty());
                head.push_back(e[0]);
                tail.push_back(e[1]);
            } else {
                if (!Q) return one_to(N);

                const auto [c, d] =
                    orient({head.back(), tail.back()}, {e[0], e[1]}, Q);
                head.push_back(c);
                tail.push_back(d);
            }
        }
    }

    return join(head, tail);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int T, N, Q;
    cin >> T >> N >> Q;

    while (T--) {
        cout << derive_order(N, Q) << endl;
        int verdict;
        cin >> verdict;
    }

    return 0;
}
