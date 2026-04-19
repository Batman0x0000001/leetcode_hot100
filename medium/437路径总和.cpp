/*
给定一个二叉树的根节点 root ，和一个整数 targetSum ，求该二叉树里节点值之和等于 targetSum 的 路径 的数目。
路径 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。

示例 1：
    输入：root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
    输出：3
    解释：和等于 8 的路径有 3 条，如图所示。
示例 2：
    输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
    输出：3

提示:
    二叉树的节点个数的范围是 [0,1000]
    -109 <= Node.val <= 109 
    -1000 <= targetSum <= 1000 
*/

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
    void dfs(TreeNode* root,long currentSum,int& count,int& targetSum){
        if(root == nullptr){
            return;
        }
        //先加值再判断，防止漏掉了根节点的值
        currentSum += root->val;
        if(currentSum == targetSum){
            count++;
        }
        dfs(root->left,currentSum,count,targetSum);
        dfs(root->right,currentSum,count,targetSum);
    }
    int pathSum(TreeNode* root, int targetSum) {
        if(root == nullptr) return 0;
        int count = 0;
        //路径可以从任意节点开始，需要对每个节点都作为起点枚举
        dfs(root,0,count,targetSum);
        count += pathSum(root->left, targetSum);
        count += pathSum(root->right, targetSum);
        return count;
    }
};