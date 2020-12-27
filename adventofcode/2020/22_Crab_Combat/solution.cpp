#include <bits/stdc++.h>
using namespace std;

enum class Winner { X, Y };

int score(const deque<int> &xs) {
    const int n = xs.size();
    vector fs(n, 0);
    iota(begin(fs), end(fs), 1);
    reverse(begin(fs), end(fs));
    return inner_product(cbegin(xs), cend(xs), cbegin(fs), 0);
}

pair<Winner, deque<int>> play(deque<int> xs, deque<int> ys) {
    while (!xs.empty() && !ys.empty()) {
        const int x = xs.front();
        xs.pop_front();

        const int y = ys.front();
        ys.pop_front();

        if (x > y) {
            xs.push_back(x);
            xs.push_back(y);
        } else {
            ys.push_back(y);
            ys.push_back(x);
        }
    }

    return xs.empty() ? pair{Winner::Y, ys} : pair{Winner::X, xs};
}

int solve(const deque<int> &xs, const deque<int> &ys) {
    const auto [_, zs] = play(xs, ys);
    return score(zs);
}

int main() {
    deque<int> xs;
    deque<int> ys;

    bool one = true;
    for (string line; getline(cin, line);) {
        if (line == "Player 1:") continue;
        if (line == "") {
            continue;
        }
        if (line == "Player 2:") {
            one = false;
            continue;
        }

        const int n = stoi(line);
        if (one) {
            xs.push_back(n);
        } else {
            ys.push_back(n);
        }
    }

    cout << solve(xs, ys) << '\n';
    return 0;
}
