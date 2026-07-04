/**
 * Definition for a binary tree node.
 * struct TreeNode {
 * int val;
 * TreeNode *left;
 * TreeNode *right;
 * TreeNode() : val(0), left(nullptr), right(nullptr) {}
 * TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        // Traverse the tree until we hit a null node or find the target val
        while (root != nullptr && root->val != val) {
            // If the target value is smaller, move to the left subtree
            if (val < root->val) {
                root = root->left;
            } 
            // If the target value is larger, move to the right subtree
            else {
                root = root->right;
            }
        }
        // Returns either the matching node or nullptr if not found
        return root;
    }
};