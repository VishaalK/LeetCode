#include <algorithm>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if (!nums.size()) {
            return nullptr;
        }
 
        auto maxIterator = max_element(nums.begin(), nums.end());
        auto max = *maxIterator;
        
        TreeNode* ret = new TreeNode(max);
        auto second = vector<int>(nums.begin(), maxIterator);
        auto third = vector<int>(maxIterator + 1, nums.end());

        ret->left = constructMaximumBinaryTree(second);
        ret->right = constructMaximumBinaryTree(third);  
                                                
        return ret;
    }
};
