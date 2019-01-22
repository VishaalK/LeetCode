#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& A) {
        int totalSolutions = 0;
        vector<int> partial;
        helper(A, partial, totalSolutions);
        return totalSolutions;
    }
    
    void helper(vector<int>& digits, vector<int>& partialSolution, int &totalSolutions) {
        // cout << "partial_solution" << endl;
        for (auto ps : partialSolution) {
            cout << ps << " ";
        }
        cout << endl;
        // cout << endl << "end_partial_solution" << endl;
        // if (partialSolution.size() > 5) {
        //     return;
        // }
        // cout << endl;
        // start with each digit, the right-most digit is the last root node
        // if we can divide by any digit remaining OR a digit that we were able to construct
        // then we can add that subtree and the new vertex
        // in this way it is a bottom up approach
        if (!partialSolution.empty()) totalSolutions++;
        // actually, if there are no valid moves, then we are done with this iteration
        auto validMoves = findAllValidMoves(digits, partialSolution);
        // cout << "validMoves" << endl;
        // for (auto moves: validMoves) {
            // cout << moves << " ";
        // }
        // cout << endl;

        if (validMoves.empty()) {
            return;
        }

        for (auto move : validMoves) {
            // we have to place the correct digits here
            // find all valid moves, and put them on one at a time
            // vector<int> findAllValidMoves(digits, partialSolution)
            // partialSolution.push_back(digit);
            // cout << "in loop" << endl;
            bool emptyPartialSolution = partialSolution.empty();

            if (!emptyPartialSolution) {
                auto back = partialSolution.back();
                partialSolution.push_back(move);
                partialSolution.push_back(move*back);
            } else {
                partialSolution.push_back(move);
            }

            helper(digits, partialSolution, totalSolutions);

            if (!emptyPartialSolution) {
                partialSolution.pop_back();
            }
            partialSolution.pop_back();
            // cout << "end loop" << endl;
        }
    }

    vector<int> findAllValidMoves(const vector<int>& digits, const vector<int>& partialSolution) {
        if (partialSolution.empty()) {
            return digits;
        }

        auto currentRoot = partialSolution.back();
        // cout << "currentRoot: " << currentRoot << endl;
        vector<int> ret;
        for (auto digit : digits) {
            auto digitToFind = digit * currentRoot;
            // cout << "digitToFind: " << digitToFind << endl;
            auto found = find(digits.begin(), digits.end(), digitToFind);
            if (found != digits.end()) {
                // cout << "found: " << *found << endl;
            } else {
                // cout << "not found" << endl;
            }
            if (find(digits.begin(), digits.end(), digitToFind) != digits.end()) {
                ret.push_back(digit);
            }
        }
        return ret;
    }

    bool valid(const vector<int>& digits, vector<int>& partialSolution) {
        if (partialSolution.empty()) {
            return true;
        }

        auto currentRoot = partialSolution.back();
        for (auto digit : digits) {
            auto digitToFind = digit * currentRoot;
            if (find(digits.begin(), digits.end(), digitToFind) != digits.end()) {
                return true;
            }
        }

        return false;
    }
};

void test_findAllValidMoves() {
    // cout << "test_findAllValidMoves()" << endl;
    auto moves = Solution().findAllValidMoves(vector<int>{2,4}, vector<int>{2});
    // cout << "moves" << endl;
    // for (auto m : moves) {
        // cout << m << ", ";
    // }
    // cout << endl;

    vector<int> ans{2};
}
// Input: A = [2, 4]
// Output: 3
// Explanation: We can make these trees: [2], [4], [4, 2, 2]
// Example 2:

// Input: A = [2, 4, 5, 10]
// Output: 7
// Explanation: We can make these trees: [2], [4], [5], [10], [4, 2, 2], [10, 2, 5], [10, 5, 2].
void test() {
    vector<int> A{2, 4};
    auto ans = Solution().numFactoredBinaryTrees(A);
    cout << ans << endl;
    assert(ans == 3);

    // vector<int> B{2, 4, 5, 10};
    // assert(Solution().numFactoredBinaryTrees(B) == 7);
}

void test2() {
    vector<int> A{2, 4, 5, 10};
    auto ans = Solution().numFactoredBinaryTrees(A);
    cout << "ans: " << ans << endl;
    assert(ans == 7);
}

void test3() {
    vector<int> A{18,3,6,2};
    auto ans = Solution().numFactoredBinaryTrees(A);

    cout << "ans: " << ans << endl;

    sort(A.begin(), A.end());
    ans = Solution().numFactoredBinaryTrees(A);

    cout << "ans: " << ans << endl;
}

int main() {
    // test();
    // test2();
    test3();
    test_findAllValidMoves();
}