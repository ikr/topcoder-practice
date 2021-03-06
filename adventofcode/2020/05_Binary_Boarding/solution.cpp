#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

enum class Half { LO, HI };

Half parse_half(const char c) {
    const map<char, Half> hs{
        {'F', Half::LO}, {'B', Half::HI}, {'L', Half::LO}, {'R', Half::HI}};
    assert(hs.count(c));
    return hs.at(c);
}

vector<Half> parse_path(const string &path) {
    vector<Half> ans(path.size());
    transform(cbegin(path), cend(path), begin(ans), parse_half);
    return ans;
}

constexpr int seat_id(const pi rc) { return rc.first * 8 + rc.second; }
string row_path(const string &seat_path) { return seat_path.substr(0, 7); }
string col_path(const string &seat_path) { return seat_path.substr(7); }

int zoom_down(const vector<Half> &hs) {
    int a = 0;
    int b = (1 << hs.size()) - 1;

    for (const auto h : hs) {
        const int mid = a + (b - a) / 2;

        if (h == Half::LO) {
            b = mid;
        } else {
            a = mid + 1;
        }
    }

    return hs.back() == Half::LO ? a : b;
}

set<pi> all_seats() {
    set<pi> ans;
    for (int r = 0; r < 128; ++r) {
        for (int c = 0; c < 8; ++c) {
            ans.emplace(r, c);
        }
    }
    return ans;
}

int main() {
    auto missing = all_seats();

    for (string line; getline(cin, line);) {
        const int r = zoom_down(parse_path(row_path(line)));
        const int c = zoom_down(parse_path(col_path(line)));
        missing.erase(pi{r, c});
    }

    for (const auto [r, c] : missing) {
        if (missing.count({r, c - 1}) || missing.count({r, c + 1})) continue;
        cout << seat_id({r, c}) << '\n';
        break;
    }

    return 0;
}
