/*
给定一个二叉树 root ，返回其最大深度。
二叉树的 最大深度 是指从根节点到最远叶子节点的最长路径上的节点数。

示例 1：
    输入：root = [3,9,20,null,null,15,7]
    输出：3
示例 2：
    输入：root = [1,null,2]
    输出：2

提示：
    树中节点的数量在 [0, 104] 区间内。
    -100 <= Node.val <= 100
*/

#include<stdio.h>
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int maxDepth(struct TreeNode* root) {
    if(root == NULL){
        return 0;
    }
    int left = maxDepth(root->left);
    int right = maxDepth(root->right);
    return (left > right ? left : right) + 1; 
    //每层只关心自己的子树结果
}

/*
错误：
int dfs(struct TreeNode *curr,int *depth){
    if(curr == NULL){
        (*depth)--;
        return *depth;
    }
    (*depth)++;
    dfs(curr->left,depth);
    dfs(curr->right,depth);
    return *depth;
}
int maxDepth(struct TreeNode* root) {
    int i = 1;
    int *depth = &i;
    return dfs(root,depth);
}
每次到达叶子节点都会减两次depth
*/

//CPP
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int recursion(TreeNode* curr){
        if(curr == nullptr){
            return 0;
        }
        int left = recursion(curr->left) + 1;
        int right = recursion(curr->right) + 1;
        return left > right ? left : right;
    }
    int maxDepth(TreeNode* root) {
        return recursion(root);
    }
};