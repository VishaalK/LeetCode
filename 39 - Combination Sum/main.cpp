#include <iostream>
#include <utility>
#include <vector>
using namespace std;

void printVector(const vector<int>&);

void printMe(const vector<vector<int>>&);

template<typename T>
vector<pair<T,T>> cartesian(const vector<T>& left, const vector<T>& right);


vector<int> merge(const vector<int>& a, const vector<int>& b) {
    vector<int> ret;
    ret.reserve(a.size() + b.size());

    ret.insert(ret.end(), a.begin(), a.end());
    ret.insert(ret.end(), b.begin(), b.end());

    return ret;
}

// 2SUM is solved in O(n) time by using a hash table
// 3SUM is solved in O(n^2) time by using a hash table and checking pairs (i,j) in the sorted input vector

// Is this DP, or backtracking?
// In DP, we could do a bottom up solution,
//  DP[i] = for all (j, k) s.t j + k = i, DP[i] = U(DP[j] X DP[k]

// candidates = [2,3,6,7], target = 7,
// A solution set is:
// [
    // [7],
    // [2,2,3]
// ]

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ret;

        // each entry holds a vector of vectors
        vector<vector<vector<int>>> dp;
        dp.resize(target+1);

        // initialize all the candidates
        // cout << "Before initialize" << endl;
        for (int c : candidates) {
            dp[c].push_back(vector<int>{c});
        }
        // cout << "After initialize" << endl;

        for (int i = 0; i < dp.size(); i++) {
            auto sols = dp[i];

            // cout << "Solutions for i == " << i << endl;;
            printMe(dp[i]);
        }

        // now bottom up initialize
        // enumerate all i,j s.t i+j = target
        for (int curTarget = 2; curTarget <= target; curTarget++) {
            vector<vector<int>> mergedSols = dp[curTarget];
            for (int i = 1; i <= curTarget/2; i++) {
                int j = curTarget - i;
                auto sols = cartesian(dp[i], dp[j]);
                for (auto p : sols) {
                    auto merged = merge(p.first, p.second);
                    std::sort(merged.begin(), merged.end());
                    mergedSols.push_back(merged);
                }
            }
            dp[curTarget] = mergedSols;
        }
        
        // I want DP[1] which is DP[1]
        // I want DP[2] (2/2 = 1) which is DP[1] + DP[1]
        // I want DP[3] (3/2 = 1) which is DP[1] + DP[2]
        // I want DP[4] (4/2 = 2) which is DP[1] + DP[3], DP[2] + DP[2]
        // I want DP[5] (5/2 = 2) which is DP[1] + DP[4], DP[2] + DP[3]
        // I want DP[6] (6/2 = 3) which is DP[1] + DP[5], DP[2] + DP[4], DP[3] + DP[3]
        // I want DP[7] (7/2 = 3) which is DP[1] + DP[6], DP[2] + DP[5], DP[3] + DP[4]
        // so it is 1,2,3 -> 6,5,4 for (int i = 1; i <= curTarget/2; i++) { j = curTarget - i; }
        // If I go bottom up, I want to do DP[1], DP[2], DP[3], ..
        // which is for (int curTarget = 1; curTarget <= target; curTarget++)

        // only have to iterate up to floor(n/2) 4/2 = 5/2 = 2 + 3
        // dp[2] = dp[1] + dp[1]
        // dp[3] = dp[1] + dp[2]
        // dp[4] = dp[2] + dp[2] + dp[3] + dp[1]

        return dp[target];
    }
};

// (a, b, c), (d, e, f) = 
// {{2, 2}, {1, 1, 1, 1}, {1, 3}}, {{1}} -> there are 3 total, and they have to be merged
template<typename T>
vector<pair<T,T>> cartesian(const vector<T>& left, const vector<T>& right) {
    vector<pair<T,T>> ret;

    for (auto leftElt : left) {
        for (auto rightElt: right) {
            // emplace?
            ret.push_back(make_pair(leftElt, rightElt));
        }
    }

    return ret;
}

void testMerge() {
    Solution s;

    vector<int> a = {2,2,3};
    vector<int> b = {1,2,3};

    auto ret = merge(a,b);
    printVector(ret);

    cout << endl;
}

void printVector(const vector<int>& p) {
    for (auto elt : p) {
        cout << elt << ",";
    }
    cout << endl;
}

void testCartesian() {
    vector<vector<int>> a = {
        {1, 2},
        {3, 4}
    };

    vector<vector<int>> b = { 
        {5, 6},
        {7, 8}
    };

    auto ret = cartesian(a, b);
    for (auto p : ret) {
        cout << "{";
        for (auto l : p.first) {
            cout << l << ",";
        }
        for (auto r : p.second) {
            cout << r << ",";
        }
        cout << "}, ";
    }
    cout << endl;
}

void testMergeAndCartesian() {
    vector<vector<int>> a = {
        {1, 2},
        {3, 4}
    };

    vector<vector<int>> b = { 
        {5, 6},
        {7, 8}
    };

    auto ret = cartesian(a, b);
    vector<vector<int>> newRet;

    for (auto p : ret) {
        auto merged = merge(p.first, p.second);
        newRet.push_back(merged);
    }

    printMe(newRet);
}

void test0() {
    cout << "Begin test 0" << endl;
    vector<int> candidates = {1, 2};
    const int target = 2;

    cout << "Before call" << endl;
    auto sols = Solution().combinationSum(candidates, target);
    cout << "After call" << endl;

    printMe(sols);
    cout << "End test 0" << endl;
}


void test1() {
    cout << "Begin test 1" << endl;
    // candidates = [2,3,6,7], target = 7,
    // A solution set is:
    // [
    // [7],
    // [2,2,3]
    // ]
    vector<int> candidates = {2, 3, 6, 7};
    const int target = 7;

    cout << "Before call" << endl;
    auto sols = Solution().combinationSum(candidates, target);
    cout << "After call" << endl;

    printMe(sols);
    // check sols
    cout << "End test1" << endl;
}

int main() {
    // testMerge();
    // testCartesian();
    // testMergeAndCartesian();

    test0();
    test1();
}

void printMe(const vector<vector<int>>& v) {
    for (auto sol : v) {
        cout << "[";
        for (auto elt : sol) {
            cout << elt << ",";
        }
        cout << "]\n";
    }
}
