#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;
using vs = vector<string>;
using vvs = vector<vs>;
using Graph = unordered_multimap<int, int>;

template <typename T> int index_of(const vector<T> &xs, const T &x) {
    const auto it = find(xs.cbegin(), xs.cend(), x);
    return it == xs.cend() ? -1 : distance(xs.cbegin(), it);
}

bool are_adjacent(const string &x, const string &y) {
    assert(x.size() == y.size());
}

vvs all_paths(const vs &dict, const int s, const int t) { return {}; }

struct Solution final {
    vvs findLadders(const string &s, const string &t, vs dict) const {
        const int t_idx = index_of(dict, t);
        if (t_idx == -1) return {};
        dict.push_back(s);
        return all_paths(dict, dict.size() - 1, t_idx);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 1") {
        const vs dict{"hot","dot","dog","lot","log","cog"};
        auto actual = Solution{}.findLadders("hit", "cog", dict);
        sort(actual.begin(), actual.end());
        const vvs expected{{"hit","hot","dot","dog","cog"},{"hit","hot","lot","log","cog"}};
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const vs dict{"hot","dot","dog","lot","log"};
        const auto actual = Solution{}.findLadders("hit", "cog", dict);
        const vvs expected{};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
