/*
给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

示例 1：
    输入：root = [1,2,3,null,5,null,4]
    输出：[1,3,4]
示例 2：
    输入：root = [1,2,3,4,null,null,null,5]
    输出：[1,3,4,5]
示例 3：
    输入：root = [1,null,3]
    输出：[1,3]
示例 4：
    输入：root = []
    输出：[]

提示:
    二叉树的节点个数的范围是 [0,100]
    -100 <= Node.val <= 100 
*/

#include<vector>
#include<queue>
using std::vector;
using std::queue;

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
    vector<int> rightSideView(TreeNode* root) {
        if(!root) return {};
        vector<int> ret;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int qSize = q.size();
            ret.emplace_back(q.front()->val);           
            while(qSize--){
                auto node = q.front();
                q.pop();
                if(node->right) q.push(node->right);
                if(node->left)  q.push(node->left);
            }
        }
        return ret;
    }
};