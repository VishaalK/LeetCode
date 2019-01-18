#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cassert>
using namespace std;

void printVector(const vector<int>& v) {
    cout << "[";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << (i != v.size() -1 ? "," : "");
    }
    cout << "]\n";
}


class Solution {
public:
    int numTrees(int n) {
        if (n == 1) {
            return 1;
        }
        
        vector<int> dp;
        dp.resize(n+1);
        dp[0] = 1;
        dp[1] = 1;
        
        for (int i = 2; i < n+1; i++) {
            int total = 0;
            for (int j = 0; j < i; j++) {
                int l = j;
                int r = i-j-1;
                total += dp[l] * dp[r];
            }
            
            dp[i] = total;
        }
        
        return dp[n];
    }
};

void testNumTrees1() {
    assert(Solution().numTrees(5) == 42);
}

int main() {
    testNumTrees1();
}

