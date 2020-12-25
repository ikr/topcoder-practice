#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Rows = vector<string>;
static constexpr int SZ = 10;

template <typename Iter, typename R, typename Binop, typename Unaop>
R ttransform_reduce(Iter first, Iter last, R init, Binop binop, Unaop unaop) {
    R ans = init;

    for (auto it = first; it != last; ++it) {
        ans = binop(ans, unaop(*it));
    }

    return ans;
}

int seq_hash(const string &s) {
    return bitset<SZ>(s, 0, string::npos, '.', '#').to_ulong();
}

int side_hash(string side) {
    int direct = seq_hash(side);
    reverse(begin(side), end(side));
    int flipped = seq_hash(side);
    return min(direct, flipped);
}

string column(const Rows &rows, const int co) {
    int sz = rows.size();
    string ans(sz, ' ');
    for (int i = 0; i < sz; ++i) {
        ans[i] = rows[i][co];
    }
    return ans;
}

Rows rotate_rows(const Rows &rows) {
    const int sz = rows.size();
    Rows ans(sz, string(sz, ' '));

    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) {
            ans[j][sz - 1 - i] = rows[i][j];
        }
    }

    return ans;
}

vector<Rows> complete_group(const Rows &rows) {
    vector<Rows> ans{rows};
    return ans;
}

struct Tile final {
    Tile(const int id, const Rows &rows) : m_id{id}, m_rows{rows} {}
    Tile() : m_id{0}, m_rows{} {}
    int id() const { return m_id; }

    vector<int> side_hashes() const {
        return {side_hash(m_rows[0]), side_hash(column(m_rows, SZ - 1)),
                side_hash(m_rows[SZ - 1]), side_hash(column(m_rows, 0))};
    }

  private:
    int m_id;
    Rows m_rows;
};

multimap<int, Tile> gather_index(const vector<Tile> &tiles) {
    multimap<int, Tile> ans;

    for (const auto &t : tiles) {
        for (const auto h : t.side_hashes()) {
            ans.emplace(h, t);
        }
    }

    return ans;
}

Tile suggest_top_left_corner(const vector<Tile> &tiles,
                             const multimap<int, Tile> &index) {
    for (const auto &t : tiles) {
        const auto hs = t.side_hashes();

        const auto neighs = ttransform_reduce(
            cbegin(hs), cend(hs), 0, plus<int>{},
            [&index](const int h) { return index.count(h) - 1; });

        if (neighs == 2) return t;
    }

    assert(false && "/o\\");
    return {};
}

ll solve(const vector<Tile> &tiles) {
    const Rows t0{"#.#.#####.", ".#..######", "..#.......", "######....",
                  "####.#..#.", ".#...#.##.", "#.#####.##", "..#.###...",
                  "..#.......", "..#.###..."};

    const auto t1 = rotate_rows(t0);
    for (const auto &r : t1) {
        cout << r << '\n';
    }

    const auto index = gather_index(tiles);
    return suggest_top_left_corner(tiles, index).id();
}

int main() {
    vector<Tile> tiles;
    int id = 0;
    Rows rows;

    for (string line; getline(cin, line);) {
        const string header{"Tile "};
        if (line.find(header) == 0) {
            id = stoi(line.substr(header.size(), 4));
            continue;
        }

        if (line == "") {
            tiles.emplace_back(id, rows);
            id = 0;
            rows.clear();
            continue;
        }

        rows.push_back(line);
    }
    tiles.emplace_back(id, rows);

    cout << solve(tiles) << '\n';
    return 0;
}
