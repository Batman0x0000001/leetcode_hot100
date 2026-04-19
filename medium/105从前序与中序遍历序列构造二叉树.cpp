/*
给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。

示例 1:
    输入: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
    输出: [3,9,20,null,null,15,7]
示例 2:
    输入: preorder = [-1], inorder = [-1]
    输出: [-1]

提示:
    1 <= preorder.length <= 3000
    inorder.length == preorder.length
    -3000 <= preorder[i], inorder[i] <= 3000
    preorder 和 inorder 均 无重复 元素
    inorder 均出现在 preorder
    preorder 保证 为二叉树的前序遍历序列
    inorder 保证 为二叉树的中序遍历序列
*/

//背背递归
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
    TreeNode* build(vector<int>& preorder, int preStart, int preEnd, vector<int>& inorder,  int inStart, int inEnd){
        if(preStart > preEnd) 
            return nullptr;

        // 前序第一个是根
        int rootVal = preorder[preStart];
        TreeNode* root = new TreeNode(rootVal);

        // 在中序中找根的位置
        int index = inStart;
        while(inorder[index] != rootVal) index++;

        // 左子树的节点数
        int leftSize = index-inStart;
        
        //前序定根，中序定边
        root->left  = build(preorder, preStart+1, preStart+leftSize, inorder, inStart, index-1);
        root->right = build(preorder, preStart+leftSize+1, preEnd, inorder, index+1, inEnd);

        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return build(preorder,0,preorder.size()-1,inorder,0,inorder.size()-1);
    }
};