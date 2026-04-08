/*
给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。请你找出给定目标值在数组中的开始位置和结束位置。
如果数组中不存在目标值 target，返回 [-1, -1]。
你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。

示例 1：
    输入：nums = [5,7,7,8,8,10], target = 8
    输出：[3,4]
示例 2：
    输入：nums = [5,7,7,8,8,10], target = 6
    输出：[-1,-1]
示例 3：
    输入：nums = [], target = 0
    输出：[-1,-1]

提示：
    0 <= nums.length <= 105
    -109 <= nums[i] <= 109
    nums 是一个非递减数组
    -109 <= target <= 109
*/

#include<vector>
using std::vector;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size()-1;
        int index = -1;
        while(left <= right){
            int mid = (left + right) / 2;
            if(nums[mid] > target){
                right = mid - 1;
            }else if(nums[mid] < target){
                left = mid + 1;
            }else{
                index = mid;
                break;
            }
        }
        if(index == -1){
            return {-1,-1};
        }
        left = index;
        right = index;
        //判断边界的条件一定要放在左边，防止溢出
        while(left >= 0 && nums[left] == target){
            left--;
        }
        while(right < nums.size() && nums[right] == target){
            right++;
        }
        return {left+1,right-1};
    }
};


//代码优化
/*
上面的代码在最坏情况时间复杂度为O(n)
改为两次二分查找边界
*/
class Solution { 
public:
    int binarySearch(vector<int>& nums, int target, bool lower) {
        int left = 0, right = (int)nums.size() - 1, ans = (int)nums.size();
        while (left <= right) {
            int mid = (left + right) / 2;
            if (nums[mid] > target || (lower && nums[mid] >= target)) {
                right = mid - 1;
                ans = mid;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        int leftIdx = binarySearch(nums, target, true);
        int rightIdx = binarySearch(nums, target, false) - 1;
        if (leftIdx <= rightIdx && rightIdx < nums.size() && nums[leftIdx] == target && nums[rightIdx] == target) {
            return vector<int>{leftIdx, rightIdx};
        } 
        return vector<int>{-1, -1};
    }
};
