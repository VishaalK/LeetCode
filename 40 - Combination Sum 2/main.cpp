#include <iostream>
#include <vector>
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
        vector<vector<int>> allSolutions;

        vector<int> curSol;
        recursionHelper(curSol, candidates, 0, target, allSolutions, 0);

        return allSolutions;
    }

    void recursionHelper(vector<int>& currentSolution, vector<int>& candidates, int sum, int target, vector<vector<int>>& allSolutions, int candidateIndex) {
        // cout << "current solution: ";
        // for (auto c : currentSolution) { cout << c << ","; }
        // cout << endl;
        // cout << "candidateIndex: " << candidateIndex << endl;
        // cout << "sum: " << sum << endl;
        if (sum == target) {
            // cout << "yay" << endl;
            vector<int> cp;
            for (auto c : currentSolution) {
                cp.push_back(c);
            }
            allSolutions.push_back(cp);
            // printSolutions(allSolutions);

            return;
        }
        // printSolutions(allSolutions);
        
        for (int i = candidateIndex; i < candidates.size(); i++) {
            auto candidate = candidates[i];
            // cout << "Candidate: " << candidate << endl;
            if (candidate + sum > target) {
                return;
            } else {
                currentSolution.push_back(candidate);
                recursionHelper(currentSolution, candidates, sum + candidate, target, allSolutions, i + 1);
                currentSolution.pop_back();
            }
        }
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
    vector<int> candidates = {1, 2, 2};
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

// Software Engineering Mnemonic + Checklsit
// Write tests first
// EDGE cases

// Algorithm Design Mnemonic
// Backtracking
// Branch and Bound
// Depth First Search
// Breadth First Search