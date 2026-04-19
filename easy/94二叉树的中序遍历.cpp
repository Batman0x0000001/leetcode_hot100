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
#include<stdlib.h>
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
#include<vector>
using std::vector;

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        TreeNode *predecessor = nullptr;

        while (root != nullptr) {
            if (root->left != nullptr) {
                // predecessor 节点就是当前 root 节点向左走一步，然后一直向右走至无法走为止
                predecessor = root->left;
                while (predecessor->right != nullptr && predecessor->right != root) {
                    predecessor = predecessor->right;
                }
                
                // 让 predecessor 的右指针指向 root，继续遍历左子树
                if (predecessor->right == nullptr) {
                    predecessor->right = root;
                    root = root->left;
                }
                // 说明左子树已经访问完了，我们需要断开链接
                else {
                    res.push_back(root->val);
                    predecessor->right = nullptr;
                    root = root->right;
                }
            }
            // 如果没有左孩子，则直接访问右孩子
            else {
                res.push_back(root->val);
                root = root->right;
            }
        }
        return res;
    }
};


//CPP
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
    vector<int> traversal(TreeNode* root,vector<int>& ret){
        if(root == nullptr){
            return ret;
        }
        traversal(root->left,ret);
        ret.emplace_back(root->val);
        traversal(root->right,ret);
        return ret;
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ret;
        return traversal(root,ret);
    }
};