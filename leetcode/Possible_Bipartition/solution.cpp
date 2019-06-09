#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

bool can_split_in_two_groups(unordered_set<int> ga, unordered_set<int> gb,
                             vector<vector<int>> dislikes) {
    while (dislikes.size()) {
        const vector<int> dl = dislikes.back();
        dislikes.pop_back();

        const int x = dl.front();
        const int y = dl.back();

        if (!ga.size()) {
            ga.insert(x);
            gb.insert(y);
        } else if (!ga.count(x) && !gb.count(y) && !ga.count(y) &&
                   !gb.count(x)) {
            ga.insert(x);
            gb.insert(y);
            if (can_split_in_two_groups(ga, gb, dislikes)) return true;

            ga.erase(x);
            gb.erase(y);
            ga.insert(y);
            gb.insert(x);
            return can_split_in_two_groups(ga, gb, dislikes);
        } else if (ga.count(x)) {
            if (ga.count(y)) return false;
            gb.insert(y);
        } else if (ga.count(y)) {
            if (ga.count(x)) return false;
            gb.insert(x);
        } else if (gb.count(x)) {
            if (gb.count(y)) return false;
            ga.insert(y);
        } else if (gb.count(y)) {
            if (gb.count(x)) return false;
            ga.insert(x);
        } else
            return false;
    }

    return true;
}

struct Solution final {
    bool possibleBipartition(const int sz, vector<vector<int>> &dislikes) {
        assert(sz);
        return can_split_in_two_groups(unordered_set<int>{},
                                       unordered_set<int>{}, dislikes);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("problem statement example 1") {
        vector<vector<int>> input{{1,2},{1,3},{2,4}};
        const auto actual = Solution().possibleBipartition(4, input);
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("problem statement example 2") {
        vector<vector<int>> input{{1,2},{1,3},{2,3}};
        const auto actual = Solution().possibleBipartition(3, input);
        const auto expected = false;
        EXPECT(actual == expected);
    },
    CASE("problem statement example 3") {
        vector<vector<int>> input{{1,2},{2,3},{3,4},{4,5},{1,5}};
        const auto actual = Solution().possibleBipartition(5, input);
        const auto expected = false;
        EXPECT(actual == expected);
    },
    CASE("my test 1") {
        vector<vector<int>> input{{1,2}};
        const auto actual = Solution().possibleBipartition(9, input);
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("my test 2") {
        vector<vector<int>> input{{1,2},{3,4},{5,6}};
        const auto actual = Solution().possibleBipartition(9, input);
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("my test 3") {
        vector<vector<int>> input{{2,3},{3,2}};
        const auto actual = Solution().possibleBipartition(9, input);
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("my test 4") {
        vector<vector<int>> input{{2,3},{3,4},{4,5},{5,6},{6,2}};
        const auto actual = Solution().possibleBipartition(9, input);
        const auto expected = false;
        EXPECT(actual == expected);
    },
    CASE("trivial") {
        vector<vector<int>> input{};
        const auto actual = Solution().possibleBipartition(9, input);
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("submission test 26") {
        vector<vector<int>> input{{32,54},{9,84},{36,68},{76,100},{27,68},{72,92},{18,45},{74,94},{5,74},{40,66},{7,68},{48,59},{45,61},{17,90},{13,20},{32,87},{14,43},{20,58},{18,86},{36,50},{45,78},{80,94},{3,40},{75,97},{6,23},{32,35},{39,83},{6,67},{12,50},{20,82},{5,93},{45,54},{21,90},{19,70},{24,59},{3,11},{15,43},{33,74},{20,47},{12,90},{9,40},{81,97},{72,97},{31,56},{48,90},{72,80},{29,52},{65,88},{18,57},{39,57},{44,68},{12,29},{8,69},{45,64},{25,37},{47,62},{80,98},{63,65},{17,43},{24,99},{6,87},{4,99},{41,74},{40,58},{3,31},{26,45},{32,72},{81,83},{54,56},{32,46},{61,74},{27,70},{24,68},{1,70},{52,70},{89,92},{40,68},{44,58},{21,95},{7,92},{68,94},{57,87},{27,57},{2,45},{22,40},{34,56},{44,97},{1,95},{2,71},{8,14},{78,95},{75,95},{44,49},{77,93},{38,59},{20,73},{45,52},{10,22},{41,91},{46,80},{67,97},{84,96},{48,96},{6,12},{82,85},{11,25},{24,82},{1,80},{17,30},{79,92},{27,74},{40,50},{1,74},{44,70},{69,90},{16,90},{70,78},{57,75},{80,100},{2,63},{29,53},{27,45},{33,50},{73,75},{32,41},{77,88},{28,93},{19,86},{59,77},{42,93},{15,59},{56,72},{85,96},{32,84},{33,90},{8,12},{68,81},{23,66},{3,39},{60,76},{86,94},{63,72},{24,70},{2,74},{7,51},{26,68},{40,73},{49,62},{21,93},{44,82},{41,80},{55,96},{23,91},{36,97},{56,62},{3,44},{9,65},{23,49},{6,11},{37,71},{2,43},{8,42},{30,62},{1,93},{8,48},{18,32},{36,51},{14,90},{66,89},{20,68},{24,63},{1,3},{28,29},{61,96},{3,21},{35,80},{32,62},{14,66},{62,88},{74,98},{10,43},{13,78},{26,86},{9,54},{75,86},{31,66},{7,76},{40,96},{68,78},{2,3},{34,51},{68,84},{66,100},{4,29},{8,94},{24,91},{40,59},{49,79},{74,81},{52,97},{45,62},{10,96},{22,64},{43,77},{20,57},{10,74},{62,74},{25,84},{32,34},{38,88},{26,88},{39,90},{58,72},{78,88},{75,90},{43,53},{8,17},{13,52},{41,76},{23,63},{16,74},{21,91},{41,86},{14,45},{18,80},{45,72},{80,84},{35,71},{53,56},{72,99},{86,87},{34,73},{30,60},{29,89},{25,26},{67,95},{20,70},{32,100},{72,93},{25,60},{43,81},{85,90},{70,75},{27,50},{25,38},{3,61},{24,86},{25,72},{6,26},{5,63},{18,25},{8,31},{7,57},{28,66},{11,58},{74,84},{22,85},{46,95},{30,98},{85,99},{3,28},{45,84},{22,62},{5,30},{9,20},{30,46},{54,59},{52,95},{63,79},{26,95},{9,61},{6,55},{10,58},{55,73},{58,100},{50,62},{83,84},{58,78},{39,96},{45,77},{2,50},{85,86},{13,100},{46,50},{10,82},{34,76},{15,82},{11,82},{60,63},{72,96},{7,47},{31,50},{37,43},{4,80},{40,80},{3,100},{45,53},{17,82},{22,89},{87,99},{2,13},{91,100},{16,30},{40,43},{30,34},{31,59},{15,45},{17,49},{30,77},{44,47},{9,27},{52,56},{39,56},{11,29},{47,72},{69,91},{44,99},{14,92},{33,51},{25,78},{37,86},{2,88},{48,82},{10,49},{18,49},{6,84},{53,68},{17,76},{54,76},{13,62},{29,100},{15,56},{33,91},{1,50},{4,25},{59,67},{81,82},{54,57},{2,83},{8,34},{34,45},{63,87},{30,65},{44,59},{19,66},{43,65},{33,96},{47,53},{29,34},{62,80},{16,25},{6,44},{78,92},{79,86},{9,14},{40,76},{3,64},{4,82},{8,21},{30,72},{38,56},{18,76},{7,97},{14,91},{70,84},{10,91},{48,71},{77,97},{40,45},{36,83},{17,29},{13,79},{5,50},{40,51},{53,95},{1,73},{49,87},{42,73},{1,99},{8,98},{39,58},{26,29},{18,71},{16,91},{67,88},{11,66},{81,95},{39,68},{28,47},{2,86},{8,61},{5,59},{38,80},{51,72},{49,72},{29,72},{55,86},{64,70},{29,98},{1,30},{58,89},{22,67},{19,63},{7,96},{18,88},{77,83},{17,58},{26,91},{50,81},{63,81},{65,90},{13,53},{20,80},{16,73},{44,83},{46,76},{25,52},{26,51},{58,61},{7,13},{11,86},{62,86},{35,51},{4,92},{13,46},{5,88},{51,98},{25,27},{28,96},{43,94},{48,99},{38,99},{22,38},{5,22},{6,33},{30,38},{36,99},{48,95},{9,53},{19,45},{38,95},{53,93},{49,85},{29,77},{9,31},{55,91},{1,97},{66,81},{20,76},{53,97},{66,75},{22,78},{34,96},{20,51},{10,59},{21,50},{28,51}};
        const auto actual = Solution().possibleBipartition(100, input);
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("submission test 34") {
        vector<vector<int>> input{{26,47},{24,30},{10,17},{25,31},{15,20},{20,42},{21,28},{26,28},{23,41},{31,44},{7,34},{14,46},{11,47},{25,43},{38,40},{44,45},{26,32},{39,45},{10,18},{25,26},{23,35},{22,41},{21,31},{44,50},{33,39},{7,28},{27,36},{35,36},{30,41},{17,36},{16,44},{12,34},{13,35},{27,50},{21,40},{2,32},{39,48},{22,35},{36,48},{12,22},{7,35},{24,49},{37,44},{18,36},{24,36},{7,33},{26,43},{47,50},{2,37},{48,50},{1,21},{22,23},{30,32},{29,40},{17,29},{14,50},{37,47},{24,33},{38,44},{4,31},{31,45},{26,44},{40,41},{29,49},{21,27},{8,32},{7,24},{40,42},{12,24},{41,45},{34,47},{17,45},{40,48},{17,32},{10,26},{14,28},{46,49},{20,44},{3,44},{9,20},{39,44},{7,18},{11,26},{26,30},{17,22},{22,29},{12,29},{11,45},{18,39},{17,40},{38,39},{42,48},{38,42},{37,50},{45,50},{2,44},{41,44},{22,30},{13,22},{23,31},{27,39},{34,48},{36,37},{18,37},{19,37},{27,48},{44,48},{3,38},{27,37},{1,42},{7,11},{22,33},{14,38},{38,49},{49,50},{12,20},{35,44},{41,47},{5,49},{3,10},{42,44},{31,49},{35,50},{8,29},{24,34},{12,48},{25,46},{26,45},{25,35},{47,48},{29,48},{3,37},{25,29},{6,18},{21,26},{9,36},{9,47},{35,43},{17,31},{30,49},{2,34},{14,35},{2,14},{43,50},{14,29},{38,46},{43,49},{39,47},{21,32},{28,34},{39,40},{15,21},{34,36},{33,37},{4,12},{18,33},{46,50},{20,34},{26,35},{5,19},{41,50},{8,40},{22,40},{30,37},{29,35},{6,47},{11,38},{27,29},{36,45},{7,46},{37,42},{5,12},{34,50},{18,49},{20,39},{44,49},{39,49},{28,33},{8,37},{31,42},{41,46},{42,45},{14,39},{4,14},{1,50},{12,49},{18,50},{25,34},{21,44},{48,49},{1,22},{23,42},{40,44},{4,50},{17,30},{14,45},{11,32},{34,45},{42,46},{40,50},{19,45},{35,48},{26,48},{24,32},{3,46}};
        const auto actual = Solution().possibleBipartition(50, input);
        const auto expected = false;
        EXPECT(actual == expected);
    },
    CASE("submission test 40") {
        vector<vector<int>> input{{4,7},{4,8},{2,8},{8,9},{1,6},{5,8},{1,2},{6,7},{3,10},{8,10},{1,5},{7,10},{1,10},{3,5},{3,6},{1,4},{3,9},{2,3},{1,9},{7,9},{2,7},{6,8},{5,7},{3,4}};
        const auto actual = Solution().possibleBipartition(10, input);
        const auto expected = true;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
