/*
给你一个未排序的整数数组 nums ，请你找出其中没有出现的最小的正整数。
请你实现时间复杂度为 O(n) 并且只使用常数级别额外空间的解决方案。

示例 1：
    输入：nums = [1,2,0]
    输出：3
    解释：范围 [1,2] 中的数字都在数组中。
示例 2：
    输入：nums = [3,4,-1,1]
    输出：2
    解释：1 在数组中，但 2 没有。
示例 3：
    输入：nums = [7,8,9,11,12]
    输出：1
    解释：最小的正数 1 没有出现。

提示：
    1 <= nums.length <= 105
    -231 <= nums[i] <= 231 - 1
*/


/*
神人：
想象有一间教室，座位从左到右编号为 1 到 n。
有 n 个学生坐在教室的座位上，把 nums[i] 当作坐在第 i 个座位上的学生的学号。
我们要做的事情，就是让学号在 1 到 n 中的学生，都坐到编号与自己学号相同的座位上（学号与座位编号匹配）。学号不在 [1,n] 中的学生可以忽略。
学生们交换座位后，从左往右看，第一个学号与座位编号不匹配的学生，其座位编号就是答案。
特别地，如果所有学生都坐在正确的座位上，那么答案是 n+1。
*/
#include<vector>
#include<algorithm>

class Solution {
public:
    int firstMissingPositive(std::vector<int>& nums) {
        for(int i = 0;i < nums.size();i++){
            //防止越界
            while(nums[i] != i+1 && nums[i] > 0 && nums[i] <= nums.size()){
                if(nums[nums[i]-1] != nums[i]){//排除影分身导致的死循环
                    std::swap(nums[i],nums[nums[i]-1]);
                }else{
                    break;
                }
            }
        }
        for(int i = 0;i < nums.size();i++){
            if(nums[i] != i+1){
                return i+1;
            }
        }
        return nums.size()+1;
    }
};