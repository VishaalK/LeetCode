#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#include <algorithm>
#include <numeric>
using namespace std;

void printSolutions(const vector<vector<int>>& solution) {
    cout << "[\n";
    for (int j = 0; j < solution.size(); j++) {
        auto sol = solution[j];
        cout << "\t[";
        for (int i = 0; i < sol.size(); i++) {
            auto elt = sol[i];
            cout << elt << ((i != sol.size() - 1) ? "," : "");
        }
        cout << "]" << ((j != solution.size() - 1) ? "," : "") << "\n";
    }
    cout << "]\n";
}

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        std::sort(candidates.begin(), candidates.end());
        vector<vector<int>> ret;

        if (!candidates.size()) {
            return ret;
        }

        vector<int> current_solution;

        // dfs 
        stack<tuple<int, int>> dfs;
        for (int i = 0; i < candidates.size(); i++) {
            dfs.push(make_tuple(candidates[i], i+1));
        }

        while (!dfs.empty()) {
            auto item = dfs.top();

            auto candidate = std::get<0>(item);
            current_solution.push_back(candidate);

            // process
            auto candidatesLeft_idx = std::get<1>(item);
            auto sum = std::accumulate(current_solution.begin(), current_solution.end(), 0);
            cout << "popped off: " << "(" << candidate << "," << candidatesLeft_idx << "," << sum << ")" << endl;

            if (sum == target) {
                cout << "yay" << endl;
                // save this somehow
                for (auto c : current_solution) {
                    cout << c << ",";
                }
                cout << endl;
                ret.push_back(current_solution);
                current_solution.pop_back();
            } else if (sum > target) {
                current_solution.pop_back();
            } else {
                // enqueue next, if we haven't already returned
                for (int i = candidatesLeft_idx; i < candidates.size(); i++) {
                    auto cand = candidates[i];
                    cout << "pushing on : (" << cand << ", " << (candidatesLeft_idx + 1) << ")" << endl;
                    dfs.push(make_tuple(cand, candidatesLeft_idx + 1));
                }
            }

            dfs.pop();

        }

        return ret;
    }
};

// Input: candidates = [10,1,2,7,6,1,5], target = 8,
// A solution set is:
// [
//   [1, 7],
//   [1, 2, 5],
//   [2, 6],
//   [1, 1, 6]
// ]
void test1() {
    vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
    const int target = 8;
    auto ret = Solution().combinationSum2(candidates, target);

    printSolutions(ret);
}

void test0() {
    vector<int> candidates = {1, 1};
    const int target = 2;
    auto ret = Solution().combinationSum2(candidates, target);

    printSolutions(ret);
}

// Example 2:

// Input: candidates = [2,5,2,1,2], target = 5,
// A solution set is:
// [
//   [1,2,2],
//   [5]
// ]
void test2() {
    vector<int> candidates = {2, 5, 2, 1, 2};
    const int target = 5;
    auto ret = Solution().combinationSum2(candidates, target);

    printSolutions(ret);
}

int main() {
    // DFS after sorting? 
    // A partial solution is really easy to check
    // Analyze the runtimes of a backtracking algorithm
    // There are how many possible baths? 2^n?
    // test0();
    test1();
    // test2();
}