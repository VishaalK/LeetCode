#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (!nums.size()) {
            return -1;
        }

        if (nums.size() == 1) {
            return nums.front () == target ? 0 : -1;
        }

        if (nums.size() == 2) {
            if (nums.front() == target) return 0;
            if (nums.back() == target) return 1;

            return -1;
        }

        int offset = findIndexOfSwap(nums);
        
        // now we can binary search with indicies
        int l = offset;
        int r = offset + nums.size() - 1;

        cout << "Starting: l: " << l << " , r: " << r << endl;
        
        while (l <= r) {
            int mid = (l + (r-l)/2);
            cout << "l: " << l << " , r: " << r << " , mid: " << mid << endl;
            if (nums[mid % nums.size()] == target) {
                return (mid) % nums.size();
            }
            
            if (nums[mid % nums.size()] < target) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        
        return -1;
    }
    
    int findIndexOfSwap(const vector<int>& nums) {
        int l = 0;
        int r = nums.size() - 1;
        while ((l + 1) != r) {
            int mid = l + (r-l)/2;
            cout << "Starting: l: " << l << " , r: " << r << endl;

            if  (nums[l] < nums[mid]) { // no swap here, must be in rhs
                l = mid;
            } else if (nums[l] > nums[mid]) {
                r = mid;
            }
        }
        
        return (nums[l] > nums[r]) ? r : 0;
    }
};

void test1() {
    vector<int> v{0,1,2,4,5,6,7};
    auto ans1 = Solution().findIndexOfSwap(v);
    cout << ans1 << endl;
    assert(ans1 == 0);

    vector<int> v2{4,5,6,7,0,1,2};
    auto ans2 = Solution().findIndexOfSwap(v2);
    cout << ans2 << endl;
    assert(ans2 == 4);

    vector<int> v3{0,1,2,4,5,6,7};
    auto ans3 = Solution().search(v3, 4);
    cout << ans3 << endl;
    assert(ans3 == 3);
}

void test2() {
    vector<int> v3{4,5,6,7,0,1,2};
    cout << Solution().search(v3, 4) << endl;

    cout << Solution().search(v3, 0) << endl;
}

void test3() {
    vector<int> v3{4,5,6,7,0,1,2};

    cout << Solution().search(v3, 3) << endl;
}

void test4() {
    vector<int> v3{0,1,2,4,6,7};

    cout << Solution().search(v3, 4) << endl;
    cout << Solution().search(v3, 3) << endl;
}

void test5() {
    vector<int> v;
    cout << Solution().search(v, 4) << endl;

}

void test6() {
    vector<int> v{1,2};
    cout << Solution().findIndexOfSwap(v) << endl;
    cout << Solution().search(v, 0) << endl;
    cout << Solution().search(v, 1) << endl;
    cout << Solution().search(v, 2) << endl;
}

void test7() {
    cout << "Test 7" << endl;
    vector<int> v{1,2,3};
    cout << Solution().findIndexOfSwap(v) << endl;
    cout << Solution().search(v, 0) << endl;
    cout << Solution().search(v, 1) << endl;
    cout << Solution().search(v, 2) << endl;
    cout << Solution().search(v, 3) << endl;
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
}