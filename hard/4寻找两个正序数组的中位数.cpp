/*
给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。
算法的时间复杂度应该为 O(log (m+n)) 。

示例 1：
    输入：nums1 = [1,3], nums2 = [2]
    输出：2.00000
    解释：合并数组 = [1,2,3] ，中位数 2
示例 2：
    输入：nums1 = [1,2], nums2 = [3,4]
    输出：2.50000
    解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5

提示：
    nums1.length == m
    nums2.length == n
    0 <= m <= 1000
    0 <= n <= 1000
    1 <= m + n <= 2000
    -106 <= nums1[i], nums2[i] <= 106
*/

#include<vector>
#include<climits>
#include<algorithm>
using std::vector;
using std::max;
using std::min;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // 保证nums1是较短的数组，减少二分范围
        if(nums1.size() > nums2.size()) swap(nums1, nums2);
        
        int m = nums1.size(), n = nums2.size();
        int left = 0, right = m;
        
        while(left <= right){
            int i = (left + right) / 2;      // nums1的分割位置
            int j = (m + n + 1) / 2 - i;    // nums2的分割位置
            
            // 分割线左边最大值，右边最小值
            int nums1Left  = (i == 0) ? INT_MIN : nums1[i-1];
            int nums1Right = (i == m) ? INT_MAX : nums1[i];
            int nums2Left  = (j == 0) ? INT_MIN : nums2[j-1];
            int nums2Right = (j == n) ? INT_MAX : nums2[j];
            
            if(nums1Left <= nums2Right && nums2Left <= nums1Right){
                // 找到正确分割线
                if((m+n) % 2 == 1){
                    return max(nums1Left, nums2Left);  // 奇数，左边最大值就是中位数
                }else{
                    return (max(nums1Left, nums2Left) + min(nums1Right, nums2Right)) / 2.0;
                }
            }else if(nums1Left > nums2Right){
                right = i - 1;  // nums1分割线左移
            }else{
                left = i + 1;   // nums1分割线右移
            }
        }
        return 0.0;
    }
};