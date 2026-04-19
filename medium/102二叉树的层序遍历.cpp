/*
给你二叉树的根节点 root ，返回其节点值的 层序遍历 。 （即逐层地，从左到右访问所有节点）。

示例 1：
    输入：root = [3,9,20,null,null,15,7]
    输出：[[3],[9,20],[15,7]]
示例 2：
    输入：root = [1]
    输出：[[1]]
示例 3：
    输入：root = []
    输出：[]

提示：
    树中节点数目在范围 [0, 2000] 内
    -1000 <= Node.val <= 1000
*/

#include<vector>
using std::vector;

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
    void traversal(TreeNode* curr,vector<vector<int>>& ret,int i){
        if(curr == nullptr){
            return;
        }
        if(i >= ret.size()){
            ret.emplace_back();
        }
        ret[i].emplace_back(curr->val);
        traversal(curr->left,ret,i+1);
        traversal(curr->right,ret,i+1);
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ret;
        traversal(root,ret,0);
        return ret;
    }
};


//迭代
#include<queue>

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ret;
        if(!root) return ret;

        std::queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int size = q.size();
            ret.emplace_back();
            while(size--){
                auto node = q.front(); q.pop();
                ret.back().emplace_back(node->val);
                if(node->left)  q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
        return ret;
    }
};
