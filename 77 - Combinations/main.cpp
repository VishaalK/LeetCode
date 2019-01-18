#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        if (n == k || k == 0) {
            vector<int> all;
            for (int i = 0; i < k; i++) {
                all.push_back(i+1);
            }

            vector<vector<int>> yolo;
            yolo.push_back(all);
            return yolo;
        }

        // choose all combinations without my specific element, of which there C(n-1, k)
        auto l = combine(n-1, k);

        // choose all combinations of size k with my specific element, of which there are C(n-1, k-1)
        auto r = combine(n-1, k-1);

        for (auto& comb : r) {
            comb.push_back(n);
        }

        for (int i = 0; i < r.size(); i++) {
            l.push_back(r[i]);
        }

        return l;
    }

    // vector<vector<int>> combine(int n, int k) {
    //     if (k == 0 || n == k) {
    //         vector<int> combination(k);
    //         for (int i = 1; i <= k; ++i)
    //             combination[i - 1] = i;
    //         return vector<vector<int>>{ combination };
    //     }
    //     vector<vector<int>> combinations= combine(n - 1, k - 1);
    //     for (auto &combination : combinations)
    //         combination.push_back(n);
    //     auto subCombinations = combine(n - 1, k);
    //     combinations.insert(combinations.end(), subCombinations.begin(), subCombinations.end());
    // 	return combinations;
    // }
};

int main() {
    auto ret = Solution().combine(4, 2);

    for (auto v : ret) {
        cout << "[";
        for (int i = 0; i < v.size(); i++) {
            auto elt = v[i];
            cout << elt;
            if (i != v.size() - 1) {
                cout << ",";
            }
        }
        cout << "]";
    }
}

