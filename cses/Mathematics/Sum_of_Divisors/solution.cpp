#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr ll M = 1e9 + 7;

ll sum_of_sum_of_divisors(const ll x) {
    ll ans = 0;
    for (ll i = 1; i <= x; ++i) {
        ans = (ans + (x / i) * i) % M;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll x;
    cin >> x;
    cout << sum_of_sum_of_divisors(x) << '\n';

    return 0;
}