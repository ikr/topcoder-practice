struct Cmp final {
    bool operator()(const string &lhs, const string &rhs) {
        if (lhs.size() == rhs.size()) return lhs < rhs;
        return lhs.size() < rhs.size();
    }
};

struct Solution {
    string largestNumber(vector<int> cost, const int target) const {
        cost.insert(cost.cbegin(), -1);
        
        // answer using [up to digit i] [summing up to target j];
        vector<vector<string>> dp(10, vector<string>(target + 1, "0"));
        
        for (int j = 1; j <= target; ++j) {
            if (j % cost[1] == 0) {
                dp[1][j] = string(j / cost[1], '1');
            }
        }
        
        for (int i = 2; i <= 9; ++i) {
            for (int j = 1; j <= target; ++j) {
                const int c = cost[i];
                string s = dp[i - 1][j];
                
                for (int k = 1; k <= j / c; ++k) {
                    const int budget = j - k * c;
                    if (budget != 0 && dp[i - 1][budget] == "0") continue;
                    const string suff = dp[i - 1][budget] == "0" ? "" : dp[i - 1][budget];
                    s = max(s, string(k, '0' + i) + suff, Cmp{});
                }
                
                dp[i][j] = s;
            }
        }
        
        return dp.back().back();
    }
};
