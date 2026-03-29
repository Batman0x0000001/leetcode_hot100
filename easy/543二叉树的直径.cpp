/*
给你一棵二叉树的根节点，返回该树的 直径 。
二叉树的 直径 是指树中任意两个节点之间最长路径的 长度 。这条路径可能经过也可能不经过根节点 root 。
两节点之间路径的 长度 由它们之间边数表示。

示例 1：
    输入：root = [1,2,3,4,5]
    输出：3
    解释：3 ，取路径 [4,2,1,3] 或 [5,2,1,3] 的长度。
示例 2：
    输入：root = [1,2]
    输出：1

提示：
    树中节点数目在范围 [1, 104] 内
    -100 <= Node.val <= 100
*/

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#include<stdio.h>
int max;
int depth(struct TreeNode *curr){
    if(curr == NULL){
        return 0;
    }
    int left = depth(curr->left);
    int right = depth(curr->right);
    max = max > (left+right+1) ? max : left+right+1;
    return (left > right ? left : right) + 1;
}
int diameterOfBinaryTree(struct TreeNode* root) {
    max = 0;
    depth(root);
    return max-1;
}

/*
想到了但没有完全想到，一直在想要是没有经过root节点该怎么处理，但是这种递归是直接先到叶子节点的。不用额外考虑！
使用static int max;主函数必须每次重新定义，不然max的值会是上一个实例的
*/


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
    int depth(TreeNode* curr,int& max){
        if(curr == nullptr){
            return 0;
        }
        int left = depth(curr->left,max);
        int right = depth(curr->right,max);
        max = (left + right) > max ? (left + right) : max;
        return (left > right ? left : right) + 1; 
    }
    int diameterOfBinaryTree(TreeNode* root) {
        int max = 0;
        depth(root,max);
        return max;
    }
};