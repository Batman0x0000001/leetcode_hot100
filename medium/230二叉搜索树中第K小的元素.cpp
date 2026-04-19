/*
给定一个二叉搜索树的根节点 root ，和一个整数 k ，请你设计一个算法查找其中第 k 小的元素（k 从 1 开始计数）。

示例 1：
    输入：root = [3,1,4,null,2], k = 1
    输出：1
示例 2：
    输入：root = [5,3,6,2,4,null,null,1], k = 3
    输出：3

提示：
    树中的节点数为 n 。
    1 <= k <= n <= 104
    0 <= Node.val <= 104
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
    //注意i需要引用，不然i++不会生效
    void inOrder(TreeNode* root,int& i,int& k,int& ret){
        if(ret > 0){
            return;
        }
        if(root == nullptr){
            return;
        }
        inOrder(root->left,i,k,ret);
        i++;
        if(i == k){
            ret = root->val;
            return;
        }
        inOrder(root->right,i,k,ret);
    }
    int kthSmallest(TreeNode* root, int k) {
        int ret = 0;
        int i = 0;
        inOrder(root,i,k,ret);
        return ret;
    }
};