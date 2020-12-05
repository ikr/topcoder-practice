#include <bits/stdc++.h>
using namespace std;
using ll = long long;
static constexpr ll M = 1e9 + 7;

constexpr ll pow_mod(const ll base, const ll exp, const ll m) {
    if (!exp) return 1;
    if (exp % 2) return (base * pow_mod(base, exp - 1, m)) % m;
    const ll q = pow_mod(base, exp / 2, m);
    return (q * q) % m;
}

constexpr ll inv_mod(const ll x, const ll m) { return pow_mod(x, m - 2, m); }

constexpr ll sum_1_to_n_mod(const ll n, const ll m) {
    ll ans = n * (n + 1);
    ans %= m;
    ans *= inv_mod(2, m);
    ans %= m;
    return ans;
}

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
