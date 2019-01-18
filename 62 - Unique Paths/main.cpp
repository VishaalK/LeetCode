#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;

int choose(int n, int k) {
    if (k == 0) {
        return 1;
    }

    return (n * choose(n - 1, k - 1)) / k;
}

class Solution {
public:
    int uniquePaths(int m, int n) {
        return choose(m + n - 2, m-1);
    }
};

void test1() {
    assert(Solution().uniquePaths(3, 2) == 3);
}

void test2() {
    assert(Solution().uniquePaths(7, 3) == 28);
}

void testNChooseK() {
    assert(choose(7, 3) == 35);
}

int main() {
    testNChooseK();
    test1();
    test2();
}