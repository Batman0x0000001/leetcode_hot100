/*
给你一个二叉树的根节点 root ， 检查它是否轴对称。

示例 1：
    输入：root = [1,2,2,3,4,4,3]
    输出：true
示例 2：
    输入：root = [1,2,2,null,3,null,3]
    输出：false

提示：
    树中节点数目在范围 [1, 1000] 内
    -100 <= Node.val <= 100
*/

#include<stdio.h>
#include<stdbool.h>
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool recursion(struct TreeNode *A,struct TreeNode *B){
    if(A == NULL && B == NULL){
        return true;
    }
    if(A == NULL || B == NULL){
        return false;
    }
    if(A->val != B->val){
        return false;
    }
    return recursion(A->left,B->right)&&recursion(A->right,B->left);
}
bool isSymmetric(struct TreeNode* root) {
    if(root == NULL){
        return true;
    }
    return recursion(root->left,root->right);
}

/*
递归中如果是bool类型的返回应该怎么设计？一旦false就整个递归都是false，但是true不一定
用短路特性，&& 连接递归调用
*/