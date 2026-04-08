/*
给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。
有效 二叉搜索树定义如下：
节点的左子树只包含 严格小于 当前节点的数。
节点的右子树只包含 严格大于 当前节点的数。
所有左子树和右子树自身必须也是二叉搜索树。

示例 1：
    输入：root = [2,1,3]
    输出：true
示例 2：
    输入：root = [5,1,4,null,null,3,6]
    输出：false
    解释：根节点的值是 5 ，但是右子节点的值是 4 。

提示：
    树中节点数目范围在[1, 104] 内
    -231 <= Node.val <= 231 - 1
*/

#include<vector>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    void preorderTraversal(TreeNode* curr,std::vector<int>& nums){
        if(curr == nullptr){
            return;
        }
        preorderTraversal(curr->left,nums);
        nums.emplace_back(curr->val);
        preorderTraversal(curr->right,nums);
    }
    bool isValidBST(TreeNode* root) {
        std::vector<int> nums;
        preorderTraversal(root,nums);
        if(nums.size() <= 1) return true;
        for(auto it = nums.begin();it != nums.end()-1;it++){
            if(*it >= *(it+1)){
                return false;
            }
        }
        return true;
    }
};