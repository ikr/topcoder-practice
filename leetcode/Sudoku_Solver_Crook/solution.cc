#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <optional>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

struct Coord {
    constexpr Coord(int row, int col) : r{row}, c{col} {}

    constexpr int row() const { return r; }
    constexpr int col() const { return c; }

    constexpr bool operator==(const Coord &other) const {
        return r == other.r && c == other.c;
    }

    constexpr bool operator!=(const Coord &other) const {
        return r != other.r || c != other.c;
    }

  private:
    int r;
    int c;
};

template <char N> struct Potential {
    constexpr Potential() : impl{} {}
    constexpr explicit Potential(const char only_one)
        : impl{1UL << (only_one - '1')} {}

    vector<char> elements() const;
    char any() const;

    constexpr size_t size() const { return impl.count(); };
    void erase(const char el) { impl[el - '1'] = false; }
    void insert(const char el) { impl[el - '1'] = true; }
    static constexpr Potential full() { return bitset<N>{(1 << N) - 1}; }

  private:
    constexpr Potential(const bitset<N> &the_impl) : impl{the_impl} {}
    bitset<N> impl;
};

struct Solution {
    constexpr int answer() const { return 42; }
    using Rows = vector<vector<char>>;
    void solveSudoku(Rows &rows) const;

  private:
    static constexpr int bsize = 3;
    static constexpr int gsize = bsize * bsize;
    using CoordPotential = pair<Coord, Potential<gsize>>;

    static optional<CoordPotential>
    deduce_definite_return_variation(Rows &rows);

    static optional<CoordPotential> min_coord_potential(const Rows &rows);
    static Potential<gsize> potential(const Rows &rows, const Coord &coord);
    static vector<Coord> linked_coords(const Coord &x);
    static vector<Coord> row_coords(const Coord &x);
    static vector<Coord> col_coords(const Coord &x);
    static vector<Coord> box_coords(const Coord &x);
};

template <char N> vector<char> Potential<N>::elements() const {
    vector<char> result{};

    for (char i = 0; i != N; ++i)
        if (impl[i])
            result.push_back(static_cast<char>('1' + i));

    return result;
}

template <char N> char Potential<N>::any() const {
    for (char i = 0; i != N; ++i)
        if (impl[i])
            return static_cast<char>('1' + i);

    abort();
}

optional<Solution::CoordPotential>
Solution::deduce_definite_return_variation(Rows &rows) {
    for (;;) {
        auto cp = min_coord_potential(rows); // if 1 option, returns immediately
        if (!cp)
            return nullopt;

        if (cp->second.size() == 1)
            rows[cp->first.row()][cp->first.col()] = cp->second.any();
        else
            return cp;
    }
}

optional<Solution::CoordPotential>
Solution::min_coord_potential(const Rows &rows) {
    size_t min_size{gsize + 1};
    optional<CoordPotential> result{};

    for (int row = 0; row != gsize; ++row) {
        for (int col = 0; col != gsize; ++col) {
            if (rows[row][col] == '.') {
                const Coord x{row, col};
                const Potential<gsize> p = potential(rows, x);

                if (p.size() == 1)
                    return {{x, p}};

                if (p.size() < min_size) {
                    min_size = p.size();
                    result = {x, p};
                }
            }
        }
    }

    return result;
}

Potential<Solution::gsize> Solution::potential(const Rows &rows,
                                               const Coord &coord) {
    auto result = Potential<gsize>::full();

    for (const Coord &x : linked_coords(coord)) {
        const char el = rows[x.row()][x.col()];

        if (el != '.')
            result.erase(el);
    }

    return result;
}

vector<Coord> Solution::linked_coords(const Coord &x) {
    vector<Coord> result;

    for (auto xs : {row_coords(x), col_coords(x), box_coords(x)})
        result.insert(result.end(), make_move_iterator(xs.begin()),
                      make_move_iterator(xs.end()));

    return result;
}

vector<Coord> Solution::row_coords(const Coord &x) {
    vector<Coord> result;

    for (int i = 0; i != gsize; ++i) {
        if (x.col() != i)
            result.push_back({x.row(), i});
    }

    return result;
}

vector<Coord> Solution::col_coords(const Coord &x) {
    vector<Coord> result;

    for (int i = 0; i != gsize; ++i) {
        if (x.row() != i)
            result.push_back({i, x.col()});
    }

    return result;
}

vector<Coord> Solution::box_coords(const Coord &x) {
    vector<Coord> result;
    const Coord o = {bsize * (x.row() / bsize), bsize * (x.col() / bsize)};

    for (int row = 0; row != bsize; ++row) {
        for (int col = 0; col != bsize; ++col) {
            const Coord y{o.row() + row, o.col() + col};

            if (x != y)
                result.push_back(y);
        }
    }

    return result;
}

int main() {
    cout << Solution().answer() << endl;

    return 0;
}