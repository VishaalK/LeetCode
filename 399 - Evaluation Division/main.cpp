#include <iostream>
#include <cassert>
#include <vector>
#include <set>
#include <map>
#include <utility>
using namespace std;

// TC 1
// equations = [ ["a", "b"], ["b", "c"] ],
// values = [2.0, 3.0],
// queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ]. 
// return [6.0, 0.5, -1.0, 1.0, -1.0 ].

class Solution {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        vector<double> ret;

        int curId = 0;
        set<string> seenSoFar;
        map<string, int> variableToIdMap;

        for (auto& eq: equations) {
            if (!seenSoFar.count(eq.first)) {
                seenSoFar.insert(eq.first);
                variableToIdMap[eq.first] = curId++;
            }

            if (!seenSoFar.count(eq.second)) {
                seenSoFar.insert(eq.second);
                variableToIdMap[eq.second] = curId++;
            }
        }
        
        // seenSoFar and variableToIdMap should have the same # of elements, which is equal to curId
        vector<vector<double>> matrix(curId, vector<double>(curId, -1));

        // now we can process each equation
        for (int i = 0; i < equations.size(); i++) {
            auto& eq = equations[i];
            // first, we update that specific entry first -> second, and second -> first
            // say we get a->B, then b->c, everything that points to b now has something that points to c
            // we also have c->b, b->a
            // we now have a -> c, which is a->b * b->c = matrixValue *= values[i];
            // let's see if we only have to traverse it once in a test case
            // and vice versa, everything that points to c now also points to b
            auto left = eq.first;
            auto right = eq.second;

            auto leftIndex = variableToIdMap[left];
            auto rightIndex = variableToIdMap[right];

            matrix[leftIndex][rightIndex] = values[i];
            matrix[rightIndex][leftIndex] = 1/values[i];

                        // quick check
            // for (int i = 0; i < matrix.size(); i++) {
            //     for (int j = 0; j < matrix.size(); j++) {
            //         cout << matrix[i][j] << " ";
            //     }
            //     cout << endl;
            // }
            // cout << "WHOO" << endl;

            // now go through and update anything pointing to left
            for (int j = 0; j < matrix.size(); j++) {
                if (j == leftIndex) {
                    continue;
                }

                if (matrix[j][leftIndex] != -1) {
                    matrix[j][rightIndex] = matrix[j][leftIndex] * values[i];
                    matrix[rightIndex][j] = 1/matrix[j][rightIndex];
                }
            }

            for (int j = 0; j < matrix.size(); j++) {
                if (j == rightIndex) {
                    continue;
                }

                if (matrix[j][rightIndex] != -1) {
                    matrix[j][leftIndex] = matrix[j][rightIndex] * 1/values[i];
                    matrix[leftIndex][j] = 1/matrix[j][leftIndex];
                }
            }

            void recurse(vector<vector<double>>& matrix, int leftIndex) {
                for (int j = 0; j < matrix.size(); j++) {
                    if (j == leftIndex) {
                        continue;
                    }

                    if (matrix[j][leftIndex] != -1) {
                        matrix[j][rightIndex] = matrix[j][leftIndex] * values[i];
                        matrix[rightIndex][j] = 1/matrix[j][rightIndex];
                    }
                }
            }
        }

        // // quick check
        // for (int i = 0; i < matrix.size(); i++) {
        //     for (int j = 0; j < matrix.size(); j++) {
        //         cout << matrix[i][j] << " ";
        //     }
        //     cout << endl;
        // }

        // now process my equations
        for (auto q: queries) {
            auto left = q.first;
            auto right = q.second;

            // if one of them isn't found, return -1
            if (!seenSoFar.count(left) || !seenSoFar.count(right)) {
                ret.push_back(-1);
                continue;
            }

            // else if they are the same return 1
            if (left == right) {
                ret.push_back(1);
                continue;
            }

            // otherwise get the value
            auto leftIndex = variableToIdMap[q.first];
            auto rightIndex = variableToIdMap[q.second];

            ret.push_back(matrix[leftIndex][rightIndex]);
        }

        return ret;

        // for each equation, we have variables
        // each variable represents a node in our graph
        // construct a 2d matrix representing each node, and update each along the way
        // this is essentially an adjacency matrix
        // once the matrix is constructed, we go through each equation
        // and update if forwards and backwards, b -> a is 1/(a -> b)
        // each string has an id
    }
};

void test1() {
    vector<pair<string, string>>  equations = {{"a", "b"}};
    vector<double> values = {2.0};
    vector<pair<string, string>> queries = {{"a", "b"}, {"b", "a"}, {"c", "a"}};

    // should return [2.0, .5, -1.0]
    auto res = Solution().calcEquation(equations, values, queries);
    for (int i = 0; i < res.size(); i++) {
        cout << res[i] << ",";
    }
    cout << endl;
}

void realTest() {
    // equations = [ ["a", "b"], ["b", "c"] ],
// values = [2.0, 3.0],
// queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ]. 
// return [6.0, 0.5, -1.0, 1.0, -1.0 ].

    vector<pair<string, string>>  equations = {{"a", "b"}, {"b", "c"}};
    vector<double> values = {2.0, 3.0};
    vector<pair<string, string>> queries = {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"c", "a"}, {"a", "a"}, {"x", "x"}};

    // should return [2.0, .5, -1.0]
    auto res = Solution().calcEquation(equations, values, queries);
    for (int i = 0; i < res.size(); i++) {
        cout << res[i] << ",";
    }
    cout << endl;
}

void secondTest() {
    vector<pair<string, string>> equations = {{"a","e"},{"b","e"}};
    vector<double> values = {4.0,3.0};
    vector<pair<string, string>> queries = {{"a","b"}, {"e","e"},{"x","x"}};

        // should return [2.0, .5, -1.0]
    auto res = Solution().calcEquation(equations, values, queries);
    for (int i = 0; i < res.size(); i++) {
        cout << res[i] << ",";
    }
    cout << endl;
}

int main() {
    // test1();
    // realTest();
    secondTest();
    return 0;
}