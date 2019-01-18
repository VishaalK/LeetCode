#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// nums = [1, 2, 3]
// target = 4

// The possible combination ways are:
// (1, 1, 1, 1)
// (1, 1, 2)
// (1, 2, 1)
// (1, 3)
// (2, 1, 1)
// (2, 2)
// (3, 1)

// Note that different sequences are counted as different combinations.

// Therefore the output is 7.

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        int numSols = 0;
        combinationSumHelper(nums, 0, target, numSols);
        
        return numSols;
    }

    // Brute force, but must do DP as well?
    void combinationSumHelper(vector<int>& nums, const int sumSoFar, int target, int& numSols) {
        // iterate through each num and check 
        // if num[i] + sumSoFar == target, increment numSols
        // if num[i] + sumSoFar > target, do not recurse
        // if num[i] + sumSoFar < target, recurse
        for (int i = 0; i < nums.size(); i++) {
            int sum = nums[i] + sumSoFar;
            if (sum == target) { 
                numSols++;
                continue;
            } else if (sum < target) {
                combinationSumHelper(nums, sum, target, numSols);
            }
        }
    }

    // We can use DP, # of ways to make 32 from [2,4] is *DP[1]
    int combinationSum4DP(vector<int>& nums, int target) {
        vector<int> dp(target+1, 0);

        for (auto n : nums) { dp[n] = 1; }

        for (int i = 2; i < dp.size(); i++) {
            int sum = 0;
            for (int j = 1; j < i-1; j++) {
                sum += dp[j] + dp[i-1-j];
            }
            dp[i] += sum;
        }

        // for (int i = 2; i < dp.size(); i++) {
        //     int sum = 0;
        //     for (int j = 1; j < i; j++) {
        //         sum += dp[i-j];
        //     }
        //     dp[i] += sum;
        // }

        for (auto i : dp) { cout << i << ","; }
        cout << endl;
        return dp[target];
    }
};

// 0,1,2,4,7,13,24

void test1() {
    vector<int> a{1,2,3};
    const int target = 16;
    int ans = Solution().combinationSum4(a, target);
    // int ans = 181997601;

    int ans2 = Solution().combinationSum4DP(a, target);
    cout << ans << " " << ans2 << endl;
    assert(ans == ans2);
}

int main() {
    test1();
}