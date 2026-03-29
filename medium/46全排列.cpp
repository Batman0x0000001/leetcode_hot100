/*
给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。

示例 1：
    输入：nums = [1,2,3]
    输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
示例 2：
    输入：nums = [0,1]
    输出：[[0,1],[1,0]]
示例 3：
    输入：nums = [1]
    输出：[[1]]

提示：
    1 <= nums.length <= 6
    -10 <= nums[i] <= 10
    nums 中的所有整数 互不相同
*/


/*
模板：for循环横向遍历，递归纵向遍历，回溯不断调整结果集

    void backtracking(参数) {
        if (终止条件) {
            存放结果;
            return;
        }
        for (选择 : 本层集合中的元素) {
            处理节点;
            backtracking(路径, 选择列表); // 递归
            撤销处理; // 回溯
        }
    }
*/
#include<vector>
using std::vector;

class Solution {
public:
    void back_tracking(vector<vector<int>>& ret,vector<int>& nums,vector<int>& visited,vector<int>& path){
        if(path.size() == nums.size()){
            ret.emplace_back(path);            
        }
        for(int i = 0;i < nums.size();i++){
            if(visited[i] != 1){
                visited[i] = 1;
                path.emplace_back(nums[i]);
                back_tracking(ret,nums,visited,path);
                path.pop_back();
                visited[i] = 0;
            }
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ret;
        vector<int> visited(nums.size(),0);
        vector<int> path;
        back_tracking(ret,nums,visited,path);
        return ret;
    }
};