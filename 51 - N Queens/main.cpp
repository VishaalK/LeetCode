#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <utility>
using namespace std;

void printSolution(const vector<string>&);

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ret;

        vector<vector<pair<int, int>>> completeSolutions;
        vector<pair<int, int>> a;
        recurse(n, a, completeSolutions);

        for (auto pairSol : completeSolutions) {
            printPairSolution(pairSol);
            ret.push_back(convertPairToBoard(pairSol));
        }

        return ret;
    }

    void printPairSolution(const vector<pair<int, int>>& ps) {
        for (auto p : ps) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    }

    vector<string> convertPairToBoard(const vector<pair<int, int>>& sol) {
        auto size = sol.size();

        string base(size, '.');
        vector<string> ret(size, base);

        for (int i = 0; i < size; i++) {
            auto x = sol[i].first, y = sol[i].second;
            ret[x][y] = 'Q';
        }
    
        return ret;
    }
    
    void recurse(const int n, vector<pair<int, int>>& solutionSoFar, vector<vector<pair<int, int>>>& completeSolutions) {
        if (solutionSoFar.size() == n /* && !alreadyExists(solutionSoFar, completeSolutions)*/) {
            completeSolutions.push_back(solutionSoFar);
            return;
        }
        
        vector<int> inits;
        for (int i = 0; i < n; i++) {
            inits.push_back(i);
        }
        // set<int> candidateRows(inits.begin(), inits.end());
        set<int> candidateCols(inits.begin(), inits.end());
        
        // the row I want to start from is the maximum of those in the solution so far + 1
        int maxRowSoFar = -1;

        for (auto sol : solutionSoFar) {
            // candidateRows.erase(sol.first);
            if (sol.first > maxRowSoFar) {
                maxRowSoFar = sol.first;
            }
            candidateCols.erase(sol.second);
        }

        set<int> candidateRows;
        for (int i = maxRowSoFar + 1; i < n; i++) {
            candidateRows.insert(i);
        }

        for (auto row : candidateRows) {
            for (auto col: candidateCols) {
                auto candidateSolution = solutionSoFar;
                candidateSolution.push_back(make_pair(row, col));
                
                if (valid(candidateSolution)) {
                    recurse(n, candidateSolution, completeSolutions);
                } else {
                    candidateSolution.pop_back();
                }
            }
        }
        
        return;
    }
    
    bool valid(const vector<pair<int, int>>& placements) {
        // if any rows or columns are same or they are diagonally attacking, remove it
        for (int i = 0; i < placements.size(); i++) {
            for (int j = i+1; j < placements.size(); j++) {
                auto xAbs = abs(placements[j].first - placements[i].first);
                auto yAbs = abs(placements[j].second - placements[i].second);
                if (xAbs == yAbs) {
                    return false;
                }
            }
        }
        
        return true;
    }
    
};

void testDiagonal() {
    auto placements = {
        make_pair(0, 0),
        make_pair(1, 1)
    };

    string result = Solution().valid(placements) ? "false" : "true";
    cout << result << endl;
}

void testDiagonal2() {
    auto placements = {
        make_pair(0, 0),
        make_pair(1, 3)
    };

    string result = Solution().valid(placements) ? "true" : "false";
    cout << result << endl;
}

void testConvertPairToBoard() { 
    auto ret = Solution().convertPairToBoard(vector<pair<int, int>>());

    for (auto it : ret) {
        cout << it << ",";
    }

    cout << endl;
}


void testConvertPairToBoard2() { 
    auto ret = Solution().convertPairToBoard(vector<pair<int, int>>{
        make_pair(0, 0),
        make_pair(1, 1),
        make_pair(2, 2),
        make_pair(0, 1)
    });

    for (auto it : ret) {
        cout << it << "," << endl;
    }

    cout << endl;
}

void printSolution(const vector<string>& c) {
    for (auto line : c) {
        cout << "\"" << line << "\"," << endl;
    }
    cout << endl;
}

void test4Queens() {
    auto ret = Solution().solveNQueens(4);

    for (auto sol : ret) {
        printSolution(sol);
    }

    cout << "Number: " << ret.size() << endl;
}

void test8queens() {
    auto ret = Solution().solveNQueens(8);

    for (auto sol : ret) {
        printSolution(sol);
    }

    cout << "Number: " << ret.size() << endl;
}

int main() {
    // testDiagonal();
    // testDiagonal2();
    // testConvertPairToBoard();
    // testConvertPairToBoard2();

    test4Queens();
    test8queens();
}