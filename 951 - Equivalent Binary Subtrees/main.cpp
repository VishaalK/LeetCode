#include <iostream>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        if (root1 && !root2 || !root1 && root2) {
            return false;
        }
        
        if (!root1 && !root2) {
            return true;
        }
        
        if (root1->val != root2->val) {
            return false;
        }
        
        // same subtree
        bool sameSubtree = flipEquiv(root1->left, root2->left) && flipEquiv(root1->right, root2->right);
        bool oppSubtree = flipEquiv(root1->left, root2->right) && flipEquiv(root1->right, root2->left);
        
        return oppSubtree || sameSubtree;
    }
    
    // recurse through the tree, and look at its children
    // if the root value is not the same, it cannot be made flip equivalent
    // if the root value is the same, then it can be made flip equivalent
    //  if the left subtree is flip equivalent 
    // you only ever compare root, and the two children values
    //  if (root1->left->val == root2->right->val && vice-versa) and the subtrees are flip equivalent
    // I AM flip equivalent if my values are the same
    // AND my sub trees are flip equivalent to both of my friend's subtrees
    // OR my sub trees are flip equivalents to the reverse counterpart of my friend's subtrees
};

int main() {
    cout << "hi" << endl;
}