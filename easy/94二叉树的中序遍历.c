/*
给定一个二叉树的根节点 root ，返回 它的 中序 遍历 。

示例 1：
    输入：root = [1,null,2,3]
    输出：[1,3,2]
示例 2：
    输入：root = []
    输出：[]
示例 3：
    输入：root = [1]
    输出：[1]

提示：
    树中节点数目在范围 [0, 100] 内
    -100 <= Node.val <= 100
 
进阶: 递归算法很简单，你可以通过迭代算法完成吗？
*/


#include<stdio.h>
struct TreeNode {
    int val;
     struct TreeNode *left;
     struct TreeNode *right;
};

int* traversal(struct TreeNode *curr,int * ret,int *returnSize){
    if(curr == NULL){
        return ret;
    }
    traversal(curr->left,ret,returnSize);
    ret[(*returnSize)++] = curr->val;
    traversal(curr->right,ret,returnSize);
    return ret;
}
int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    int *ret = (int *)malloc(100 * sizeof(int));
    *returnSize = 0;
    return traversal(root,ret,returnSize);
}

/*
ret[returnSize++] = curr->val;  // ❌ 两个错误
错误1：ret[returnSize] 应该解引用，returnSize 是指针不是下标：
错误2：returnSize++ 是对指针本身做自增（指针移位），不是对它指向的值自增：

-> 就是 (*p). 的简写，已经包含解引用。([]也包含解引用)
指针用 ->
变量（非指针）用 .
*/


//代码优化
//Morris 遍历算法是另一种遍历二叉树的方法，它能将非递归的中序遍历空间复杂度降为 O(1)。
int* inorderTraversal(struct TreeNode* root, int* returnSize){
    int *ret = (int *)malloc(100 * sizeof(int));
    *returnSize = 0;
    struct TreeNode *predecessor = NULL;

    while(root != NULL){
        if(root->left != NULL){
            predecessor = root->left;
            while (predecessor->right != NULL && predecessor->right != root){
                predecessor = predecessor->right;
            }

            if(predecessor->right == NULL){
                predecessor->right == root;
                root = root->left;
            }else{
                ret[(*returnSize)++] = root->val;
                predecessor->right = NULL;
                root = root->right;
            }
            
        }else{
            ret[(*returnSize)++] = root->val;
            root = root->right;
        }
    }

    return ret;
}