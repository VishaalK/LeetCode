#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        if (!nums.size()) {
            return vector<int>();
        }
        
        auto subsetsOfAllOtherElts = subsets(vector<int>(num.begin() + 1, nums.end()));
        
        vector<int> subsetsWithMyElt(subsetsOfAllOtherElts);
        for_each(subsetsWithMyElt.begin(), subsetsWithMyElt.end(), [](vector<int>& v){ 
            v.push_back(nums.front()); 
        });
        
        subsetsOfAllOtherElts.insert(end(subsetsOfAllOtherElts), begin(subsetsWithMyElt), end(subsetsWithMyElt));
    }
};