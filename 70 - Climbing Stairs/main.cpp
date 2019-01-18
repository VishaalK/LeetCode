#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

int choose(int n, int k) {
    if (k == 0) {
        return 1;
    }

    return (n * choose(n - 1, k - 1)) / k;
}

class Solution {
public:
    int climbStairs(int n) {
        vector<int> dp(n, -1);
        dp[0] = 1;
        dp[1] = 2;

        for (int i = 2; i < n; i++) {
            dp[i] = dp[i-1] + dp[i-2];
        }

        return dp[n-1];
    }
};

void testNChooseK() {
    assert(choose(5,5) == 1);
    assert(choose(5, 1) == 5);
    assert(choose(5, 0) == 1);
    assert(choose(4,2) == 6);
}

void testClimbStairs() {
    assert(Solution().climbStairs(2) == 2);
    assert(Solution().climbStairs(3) == 3);
}

int main() {
    testNChooseK();
    testClimbStairs();
}