/*
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

示例 1：
    输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
    输出：6
    解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 
示例 2：
    输入：height = [4,2,0,3,2,5]
    输出：9

提示：
    n == height.length
    1 <= n <= 2 * 104
    0 <= height[i] <= 105
*/

#include<vector>
#include<algorithm>
using std::vector;
using std::max;

class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0,right = height.size()-1;
        int leftMax = height[left],rightMax = height[right];
        int ret = 0;
        left++;
        right--;
        while(left <= right){
            leftMax = max(height[left],leftMax);
            rightMax = max(height[right],rightMax);
            if(leftMax < rightMax){
                // 左指针的leftMax比右指针的rightMax矮
                // 说明：左指针的右边至少有一个板子 > 左指针左边所有板子
                // 根据水桶效应，保证了左指针当前列的水量决定权在左边
                // 那么可以计算左指针当前列的水量：左边最大高度-当前列高度
                ret += leftMax - height[left];
                left++;
            }else{
                ret += rightMax - height[right];
                right--;
            }
        }
        return ret;
    }
};