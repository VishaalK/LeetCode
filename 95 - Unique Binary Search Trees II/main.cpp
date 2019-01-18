#include <iostream>
#include <vector>
#include <numeric>
#include <queue>
using namespace std;

/**
 * Definition for a binary tree node. */
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

void printVector(const vector<int>& v) {
    cout << "[";
    for (int i = 0; i < v.size(); i++) {
        auto t = v[i];
        cout << t << (i != v.size() - 1 ? "," : "");
    }
    cout << "]" << endl;
}

vector<int> inorder(TreeNode* root) {
    if (!root) {
        return vector<int>();
    }

    auto l = inorder(root->left);
    l.push_back(root->val);
    auto r = inorder(root->right);
    l.insert(l.end(), r.begin(), r.end());

    return l;
}

vector<int> bfs(TreeNode* root) {
    queue<TreeNode*> q;
    // add current, then iterate through children
    vector<int> ret;

    q.push(root);

    while (!q.empty()) {
        auto elt = q.front(); q.pop();

        if (!elt) {
            continue;
        }

        ret.push_back(elt->val);

        q.push(elt->left); 
        q.push(elt->right);
    }

    return ret;
}

class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if (n == 0) {
            return vector<TreeNode*>();
        }
        // backtracking, if n == 1, just return the element that is left
        // choose roots that are left in the set
        vector<int> candidates;
        candidates.resize(n);
        iota(candidates.begin(), candidates.end(), 1);
        
        return generateTreesHelper(candidates);
    }
    
    vector<TreeNode*> generateTreesHelper(const vector<int>& candidates) {
        // cout << "candidates: "; printVector(candidates);
        if (candidates.size() == 0) {
            // cout << "returning empty" << endl;
            return vector<TreeNode*>{nullptr};
        }

        // if (candidates.size() == 1) {
        //     cout << "returning singleton" << endl;
        //     TreeNode* x = new TreeNode(candidates.front());
        //     return vector<TreeNode*>{x};
        // }

        
        vector<TreeNode*> ret;
        for (int i = 0; i < candidates.size(); i++) {
            // if (candidates.size() == 2) {
            //     cout << "top level: " << candidates[i] << endl;
            // }
            auto l = vector<int>(candidates.begin(), candidates.begin() + i);
            auto r = vector<int>(candidates.begin() + i + 1, candidates.end());
            
            // cout << "l: "; printVector(l);
            // cout << "r: "; printVector(r);

            auto leftTrees = generateTreesHelper(l);
            auto rightTrees = generateTreesHelper(r);

            // cout << "size of leftTrees: " << leftTrees.size() << endl;
            // cout << "size of rightTrees: " << rightTrees.size() << endl;
            
            for (auto leftTree : leftTrees) {
                for (auto rightTree : rightTrees) {
                    auto cur = new TreeNode(candidates[i]);
                    cur->left = leftTree;
                    cur->right = rightTree;
                    
                    ret.push_back(cur);
                }
            }

            // cout << "cartesian:\n";
            // // for (auto t : ret) {
            // //     printVector(inorder(t));
            // // }
            // cout << "\n";
            // get the cartesian product of the left and right  elements
            // possibly cache these values as well, dp will hold a list of eligible trees
        }
        
        return ret;
    }
};


void testInorder() {
    TreeNode* tree = new TreeNode(2);
    tree->left = new TreeNode(1);
    tree->right = new TreeNode(3);

    auto traversal = inorder(tree);
    printVector(traversal);
}

void testInorder2() {
    TreeNode* tree = new TreeNode(1);
    tree->right = new TreeNode(3);
    tree->right->left = new TreeNode(2);

    auto traversal = inorder(tree);
    printVector(traversal);
}

void testBfs1() {
    TreeNode* tree = new TreeNode(2);
    tree->left = new TreeNode(1);
    tree->right = new TreeNode(3);

    auto traversal = bfs(tree);
    printVector(traversal);
}

void testBfs2() {
    TreeNode* tree = new TreeNode(1);
    tree->right = new TreeNode(3);
    tree->right->left = new TreeNode(2);

    auto traversal = bfs(tree);
    printVector(traversal);
}

void test1() {
    auto trees = Solution().generateTrees(3);

    cout << "answers\n";
    for (auto t : trees) {
        printVector(bfs(t));
    }
}

int main() {
    // testInorder();
    // testInorder2();
    // testBfs1();
    // testBfs2();

    test1();
}