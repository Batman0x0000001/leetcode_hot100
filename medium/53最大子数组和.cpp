/*
给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
子数组是数组中的一个连续部分。

示例 1：
    输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
    输出：6
    解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。
示例 2：
    输入：nums = [1]
    输出：1
示例 3：
    输入：nums = [5,4,-1,7,8]
    输出：23

提示：
    1 <= nums.length <= 105
    -104 <= nums[i] <= 104

进阶：如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的 分治法 求解。
*/

//看不懂
#include<vector>
using std::vector;
using std::max;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int pre = 0, maxAns = nums[0];
        for (const auto &x: nums) {
            pre = max(pre + x, x);
            maxAns = max(maxAns, pre);
        }
        return maxAns;
    }
};


//学习560题，使用前缀和解决
#include<algorithm>
using std::min;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int pre = 0;
        int preMax = nums[0];
        int preMin = 0;
        for(int& it:nums){
            pre += it;
            preMax = max(preMax,pre-preMin);
            preMin = min(pre,preMin);
        }
        return preMax;
    }    
};