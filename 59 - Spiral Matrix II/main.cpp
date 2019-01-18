#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        vector<pair<int, int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        auto end = n*n;
        int sideLength = n-1;
        int sideLengthLeft = sideLength;
        int curDirection = 0;
        int x = 0, y = 0;
        for (int cur = 1; cur <= end; cur++) {
            matrix[x][y] = cur;
            
            auto directionToGoIn = directions[curDirection];
            x += directionToGoIn.first;
            y += directionToGoIn.second;
            
            sideLengthLeft -= 1;
            
            if (sideLengthLeft == 0) {
                curDirection += 1;
                
                if (curDirection == 4) {
                    curDirection = 0;
                    sideLength -= 2;
                    x += 1;
                    y += 1;
                }
            
                sideLengthLeft = sideLength;
            }
        }
     
        return matrix;
    }
};

int main() {
    int n = 3;

    Solution s;
    auto ret = s.generateMatrix(n);

    for (auto row : ret) {
        cout << "[";
        for (auto col : row) {
            cout << col << ",";
        }
        cout << "]" << endl;
    }
}