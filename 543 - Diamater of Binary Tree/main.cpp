#include <iostream>
using namespace std;

/**
 * Definition for a binary tree node. */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        return diameterHelper(root).second;
    }
    
    pair<int, int> diameterHelper(TreeNode* root) {
        if (!root) {
            return make_pair(0, 0);
        }
        
        auto left = diameterHelper(root->left);
        auto right = diameterHelper(root->right);
        
        auto height = 1 + left.first + right.first;
        
        vector<int> elts{height-1, left.second, right.second};
        auto longestPath = max_element(begin(elts), end(elts));
        
        return make_pair(height, *longestPath);
    }
    
    // helper returns height of that tree, + longest path in that tree
    // the root node is connecting either 2 longest paths, or returning its height (or both)
    // if 1 + height(l) + height(right) > longest(path->left) && longest(path->right) then return (h=height, p=height)
    // else return (h=height,p=path)
    // base case is (0, 0)
    // 1 + 0 + 0 > 0 && 1 > 0
    // so 1 is fine
    
    int height(TreeNode* root) {
        if (!root) { 
            return 0;
        }
        
        return 1 + max(height(root->left), height(root->right));
    }
};

int main() {
    
}