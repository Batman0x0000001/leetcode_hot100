/*
二叉树中的 路径 被定义为一条节点序列，序列中每对相邻节点之间都存在一条边。同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。
路径和 是路径中各节点值的总和。
给你一个二叉树的根节点 root ，返回其 最大路径和 。

示例 1：
    输入：root = [1,2,3]
    输出：6
    解释：最优路径是 2 -> 1 -> 3 ，路径和为 2 + 1 + 3 = 6
示例 2：
    输入：root = [-10,9,20,null,null,15,7]
    输出：42
    解释：最优路径是 15 -> 20 -> 7 ，路径和为 15 + 20 + 7 = 42

提示：
    树中节点数目范围是 [1, 3 * 104]
    -1000 <= Node.val <= 1000
*/

#include<climits>
#include<algorithm>
using std::max;
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
    int dfs(TreeNode* root,int& ret){
        if(root == nullptr){
            return 0;
        }
        int leftMax = max(0,dfs(root->left,ret));
        int rightMax = max(0,dfs(root->right,ret));

        //以root为顶点的完整路径，记录到ret
        ret = max(ret,leftMax+rightMax+root->val);

        //故意只选一半，因为这个返回值的用途是给父节点用的。
        return max(leftMax,rightMax)+root->val;
    }
    int maxPathSum(TreeNode* root) {
        int ret = INT_MIN;
        dfs(root,ret);
        return ret;
    }
};