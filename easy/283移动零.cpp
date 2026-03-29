/*
给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

请注意 ，必须在不复制数组的情况下原地对数组进行操作。

示例 1:
    输入: nums = [0,1,0,3,12]
    输出: [1,3,12,0,0]
示例 2:
    输入: nums = [0]
    输出: [0]

提示:
    1 <= nums.length <= 104
    -231 <= nums[i] <= 231 - 1
 
进阶：你能尽量减少完成的操作次数吗？
*/

void moveZeroes(int* nums, int numsSize) {
    int pZero=0,pNZero=0;
    for(;pZero<numsSize&&nums[pZero]!=0;pZero++);
    pNZero=pZero;
    while(pNZero!=numsSize){
        if(nums[pNZero]==0){
            pNZero++;
        }else{
            nums[pZero++]=nums[pNZero];
            nums[pNZero++]=0;
        }
    }
}
/*
注意：pZero<numsSize && nums[pZero]!=0
是否溢出需要放在左边，因为先判断nums[pZero]!=0时，可能会溢出
*/


//代码优化
#include<vector>
#include<algorithm>
using std::vector;
using std::swap;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size(), left = 0, right = 0;
        while (right < n) {
            if (nums[right]) {
                swap(nums[left], nums[right]);
                left++;
            }
            right++;
        }
    }
};
/*
<algorithm> 或 <utility> 都提供了 swap：
    #include <algorithm>  // C++11之前
    #include <utility>    // C++11之后，swap移到这里了
实际上包含任何STL头文件基本都会间接包含它，所以通常不用显式写。
*/