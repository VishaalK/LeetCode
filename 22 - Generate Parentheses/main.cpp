#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        // there is a DP way, or a backtracking way
        // if numLeft == numRight, you must place a left parenthesis
        // if numLeft < numRight, you can place a left or a right
        // if numLeft == 0 && numRight == 0, you have a solution, and mark it as so
        vector<string> solutions;
        string cursol;
        generateHelper(cursol, n, n, solutions);

        return solutions;
    }
    
    void generateHelper(string curSol, int numLeftParens, int numRightParens, vector<string>& solutions) {
        if (numLeftParens == 0 && numRightParens == 0) {
            solutions.push_back(curSol);
            return;
        }

        if (numLeftParens == numRightParens) {
            generateHelper(curSol + "(", numLeftParens - 1, numRightParens, solutions);
            return;
        }

        if (numLeftParens > 0) {
            generateHelper(curSol + "(", numLeftParens - 1, numRightParens, solutions);
        }
        generateHelper(curSol + ")", numLeftParens, numRightParens - 1, solutions);
        return;
    }
};

void printSolutions(const vector<string>& v) {
    cout << "[\n";
    for (auto s : v) {
        cout << "\t" << s << "\n";
    }
    cout << "]" << endl;
}

void test1() {
    auto ret = Solution().generateParenthesis(1);
    printSolutions(ret);
}

void test3() {
    auto ret = Solution().generateParenthesis(3);
    printSolutions(ret);
}

int main() {
    test1();
    test3();
}