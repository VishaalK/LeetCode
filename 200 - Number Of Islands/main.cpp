#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <cassert>
#include <fstream>
using namespace std;

struct Tile {
    bool seen;
    char value;
};

enum Direction {
    north,
    south, 
    east,
    west
};

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (!grid.size() || !grid[0].size()) {
            return 0;
        }

        vector<vector<bool>> seen(grid.size(), vector<bool>(grid[0].size(), false));

        int totalCount = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (!seen[i][j] && grid[i][j] == '1') {
                    markIslandsAsSeen(grid, seen, i, j);
                    totalCount++;
                }
            }
        }

        return totalCount;
    }

    void markIslandsAsSeen(vector<vector<char>>& grid, vector<vector<bool>>& seen, int i, int j) {
        // cout << "i: " << i << " grid.size(): " << grid.size() << ", j: " << j << endl;
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size()) {
            // cout << "out of bounds" << endl;
            return;
        }

        if (grid[i][j] != '1' || seen[i][j]) {
            return;
        }

        seen[i][j] = true;

        vector<Direction> ds{north, south, east, west};

        const map<Direction, pair<int, int>> directions{
            {north, make_pair(-1, 0)},
            {south, make_pair(1, 0)},
            {east, make_pair(0, 1)},
            {west, make_pair(0, -1)}
        };

        for (Direction d : ds) {
            // cout << "Direciton: " << d << endl;
            // for (pair<int, pair<int, int>> f : directions) {
            //     cout << f.second.first << " " << f.second.second << " ";
            // }
            // cout << endl;
            pair<int, int> nextDirection = directions.at(d);
            // cout << "nextDirection: " << nextDirection.first << " " << nextDirection.second << endl;
            markIslandsAsSeen(grid, seen, i + nextDirection.first, j + nextDirection.second);
        }

        return;
    }
};

bool compare_seen(const vector<vector<bool>>& actual, const vector<vector<bool>>& expected) {
    for (int i = 0; i < actual.size(); i++) {
        for (int j = 0; j < actual[i].size(); j++) {
            if (actual[i][j] != expected[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void test_markIslands() {
    vector<vector<char>> grid{
        {'1', '0', '1'},
        {'1', '0', '1'},
        {'0', '1', '1'}
    };

    vector<vector<bool>> seen(3, vector<bool>(3, false));

    vector<vector<bool>> ans1{
        {true, false, false},
        {true, false, false},
        {false, false, false}
    };

    Solution().markIslandsAsSeen(grid, seen, 0, 0);
    
    assert(compare_seen(seen, ans1));

    Solution().markIslandsAsSeen(grid, seen, 0, 2);

    vector<vector<bool>> ans2{
        {true, false, true},
        {true, false, true},
        {false, true, true}
    };

    assert(compare_seen(seen, ans2));
}


void basic_test() {
    auto dummy = vector<vector<char>>();
    assert(Solution().numIslands(dummy) == 0);
}

void test1() {
    ifstream file;
    file.open("test0.txt");
    string line;
    vector<vector<char>> grid;
    while (getline(file, line)) {
        grid.push_back(vector<char>());
        for (int j = 0; j < line.size(); j++) {
            grid[grid.size() - 1].push_back(line[j]);
        }
    }

    // check grid
    for (auto line : grid) {
        for (auto c : line) {
            cout << c;
        }
        cout << endl;
    }

    assert(Solution().numIslands(grid) == 1);
}

void test2() {
    ifstream file;
    file.open("test1.txt");
    string line;
    vector<vector<char>> grid;
    while (getline(file, line)) {
        grid.push_back(vector<char>());
        for (int j = 0; j < line.size(); j++) {
            grid[grid.size() - 1].push_back(line[j]);
        }
    }

    // check grid
    for (auto line : grid) {
        for (auto c : line) {
            cout << c;
        }
        cout << endl;
    }

    assert(Solution().numIslands(grid) == 3);
}

int main() {
    test_markIslands();
    basic_test();
    test1();
    test2();
    return 0;
}