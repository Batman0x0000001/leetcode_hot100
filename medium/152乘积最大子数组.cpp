/*
给你一个整数数组 nums ，请你找出数组中乘积最大的非空连续 子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。
测试用例的答案是一个 32-位 整数。
请注意，一个只包含一个元素的数组的乘积是这个元素的值。

示例 1:
    输入: nums = [2,3,-2,4]
    输出: 6
    解释: 子数组 [2,3] 有最大乘积 6。
示例 2:
    输入: nums = [-2,0,-1]
    输出: 0
    解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。

提示:
    1 <= nums.length <= 2 * 104
    -10 <= nums[i] <= 10
    nums 的任何子数组的乘积都 保证 是一个 32-位 整数
*/

//维护两个正负dp数组，开背
#include<vector>
#include<algorithm>
using std::vector;
using std::min;
using std::max;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        vector<int> numsMax(n);
        vector<int> numsMin(n);
        int ret = numsMax[0] = numsMin[0] = nums[0];
        for(int i = 1;i < n;i++){
            if(nums[i] > 0){
                numsMax[i] = max(numsMax[i-1]*nums[i],nums[i]);
                numsMin[i] = min(numsMin[i-1]*nums[i],nums[i]);
            }else{
                numsMax[i] = max(numsMin[i-1]*nums[i],nums[i]);
                numsMin[i] = min(numsMax[i-1]*nums[i],nums[i]);
            }
            ret = max(ret,numsMax[i]);
        }
        return ret;
    }
};


/*
数学思路：
对于最优区间 [l, r]：

左端点外侧不会有正数
    若 nums[l-1] > 0：
    区间扩展到[l-1, r]，乘积变大，矛盾
    所以 nums[l-1] <= 0，即为负数或0
右端点外侧不会有正数
    若 nums[r+1] > 0：
    区间扩展到[l, r+1]，乘积变大，矛盾
    所以 nums[r+1] <= 0，即为负数或0
两端不会同时有负数
    若 nums[l-1] < 0 且 nums[r+1] < 0：
    区间扩展到[l-1, r+1]，乘以两个负数乘积为正，变大，矛盾
    所以两端不能同时是负数

结论
    两端外侧只有这几种情况：
    左负右0，左0右负，左0右0，左负右数组边界，左数组边界右负...

无论哪种情况，端点一定是：
    1. 数组起止点
    2. 0的位置（遇0重新开始）
*/
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int ret = nums[0];
        int left = 1, right = 1;
        int n = nums.size();
        for(int i = 0; i < n; i++){
            left  *= nums[i];
            right *= nums[n-1-i];
            ret = max({ret,left, right});
            if(left  == 0) left  = 1;  // 遇0重新开始
            if(right == 0) right = 1;
        }
        return ret;
    }
};