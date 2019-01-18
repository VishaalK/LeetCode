#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

class Solution
{
  public:
    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        if (matrix.empty()) {
            return vector<int>();
        }

        vector<int> ret;
        int leftCol = 0;
        int rightCol = matrix[0].size();

        int topRow = 0;
        int bottomRow = matrix.size();

        for (int i = leftCol; i < rightCol; i++) {
            ret.push_back(matrix[topRow][i]);
        }
        topRow++;

        for (int i = topRow; i < bottomRow; i++) {
            ret.push_back(matrix[i][rightCol]);
        }
        rightCol--;

        for (int i = rightCol; i >= leftCol; i--) {
            ret.push_back(matrix[bottomRow][i]);
        }
        bottomRow--;

        for (int i = bottomRow; i >= topRight; i--) {
            ret.push_back(matrix[i][leftCol]);
        }
        leftCol++;
    }
};

void printVector(const vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v;
        if (i != v.size() - 1) {
            cout << ",";
        }
    }
    cout << endl;
}

int main()
{
    Solution s;

    vector<vector<int>> matrix{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
        };

    auto r = s.spiralOrder(matrix);
    printVector(r);
    // cout << s.spiralOrder(matrix) << endl;
}
