#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;
using mint = atcoder::modint998244353;

ostream &operator<<(ostream &os, const mint x) {
    os << x.val();
    return os;
}

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

mint transition_addition(const char l_cell, const mint l_ways,
                         const char u_cell, const mint u_ways) {
    const string x{l_cell, u_cell};

    if (x == "XX" || x == "XD" || x == "RX" || x == "RD") {
        return l_ways + u_ways;
    }

    if (x == "DX" || x == "DD") return u_ways;
    if (x == "XR" || x == "RR") return l_ways;
    assert(x == "DR");
    return 0;
}

mint transition_combo(const char l_cell, const mint l_ways, const char u_cell,
                      const mint u_ways) {
    const string ls = l_cell == ' ' ? "XDR" : string{l_cell};
    const string us = u_cell == ' ' ? "XDR" : string{u_cell};

    mint ans = 0;
    for (const auto l : ls) {
        for (const auto u : us) {
            ans += transition_addition(l, l_ways, u, u_ways);
        }
    }
    return ans;
}

mint count_ways(const vector<string> &rows) {
    const int H = rows.size();
    const int W = rows[0].size();

    vector<vector<mint>> dp(H, vector<mint>(W, 0));
    dp[0][0] = 1;

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (!ro && !co) continue;

            const char l = co > 0 ? rows[ro][co - 1] : 'D';
            const mint lw = co > 0 ? dp[ro][co - 1] : 0;

            const char u = ro > 0 ? rows[ro - 1][co] : 'R';
            const mint uw = ro > 0 ? dp[ro - 1][co] : 0;

            dp[ro][co] = transition_combo(l, lw, u, uw);
        }
    }

    cout << dp << '\n';

    return rows.back().back() == ' ' ? dp.back().back() * mint{3}
                                     : dp.back().back();
}

namespace oracle {
int solve(const vector<string> &s, const int K) {
    const int H = s.size();
    const int W = s[0].size();

    vector<vector<mint>> dp(H, vector<mint>(W));
    mint p = 2;
    p *= mint(3).inv();
    dp[0][0] = 1;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            mint res = 1;
            if (s[i][j] == ' ') {
                res = p;
            }
            if (s[i][j] != 'D' && j + 1 < W) {
                dp[i][j + 1] += dp[i][j] * res;
            }
            if (s[i][j] != 'R' && i + 1 < H) {
                dp[i + 1][j] += dp[i][j] * res;
            }
        }
    }
    return (dp[H - 1][W - 1] * mint(3).pow(H * W - K)).val();
}
} // namespace oracle

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int H, W, K;
    cin >> H >> W >> K;

    vector<string> rows(H, string(W, ' '));

    for (int i = 0; i < K; ++i) {
        int ro, co;
        char c;
        cin >> ro >> co >> c;
        rows[ro - 1][co - 1] = c;
    }

    cout << count_ways(rows).val() << '\n';
    cout << oracle::solve(rows, K) << '\n';
    return 0;
}
