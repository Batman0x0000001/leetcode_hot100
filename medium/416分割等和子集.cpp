/*
给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

示例 1：
    输入：nums = [1,5,11,5]
    输出：true
    解释：数组可以分割成 [1, 5, 5] 和 [11] 。
示例 2：
    输入：nums = [1,2,3,5]
    输出：false
    解释：数组不能分割成两个元素和相等的子集。

提示：
    1 <= nums.length <= 200
    1 <= nums[i] <= 100
*/


//超时
#include<vector>
using std::vector;

class Solution {
public:
    void backTraking(int bag,vector<int>& nums,int index,int& sum,bool& flag){
        if(flag == true){
            return;
        }
        if(bag == sum){
            flag = true;
            return;
        }
        for(int i = index;i < nums.size();i++){
            if(bag + nums[i] <= sum){
                backTraking(bag+nums[i],nums,i+1,sum,flag);
            }
        }
    }
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for(int& it:nums){
            sum += it;
        }
        if(sum % 2 != 0){
            return false;
        }
        bool flag = false;
        sum = sum/2;
        backTraking(0,nums,0,sum,flag);
        return flag;
    }
};


//传统dp,可以简化为一维dp,多看看
#include<algorithm>
#include<numeric>

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) {
            return false;
        }
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        int maxNum = *max_element(nums.begin(), nums.end());
        if (sum & 1) {
            return false;
        }
        int target = sum / 2;
        if (maxNum > target) {
            return false;
        }
        //dp[i][j] = 从前i个数中能否选出若干数字，使其和恰好为j
        vector<vector<bool>> dp(n, vector<bool>(target + 1, false));
        for (int i = 0; i < n; i++) {
            dp[i][0] = true;
        }
        dp[0][nums[0]] = true;//只有第0个数时，只能凑出nums[0]
        for (int i = 1; i < n; i++) {
            int num = nums[i];
            for (int j = 1; j <= target; j++) {
                /*
                对于第i个数 nums[i]，只有两种选择：
                    不选nums[i]：dp[i][j] = dp[i-1][j]
                                前i-1个数能凑出j就行

                    选nums[i]：  dp[i][j] = dp[i-1][j-num]
                                前i-1个数凑出j-num，再加上num就是j
                                前提：j >= num
                */
                if (j >= num) {
                    dp[i][j] = dp[i - 1][j] || dp[i - 1][j - num];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n - 1][target];
    }
};