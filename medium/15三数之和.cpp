/*
给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。请你返回所有和为 0 且不重复的三元组。
注意：答案中不可以包含重复的三元组。

示例 1：
    输入：nums = [-1,0,1,2,-1,-4]
    输出：[[-1,-1,2],[-1,0,1]]
    解释：
    nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 。
    nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 。
    nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 。
    不同的三元组是 [-1,0,1] 和 [-1,-1,2] 。
    注意，输出的顺序和三元组的顺序并不重要。
示例 2：
    输入：nums = [0,1,1]
    输出：[]
    解释：唯一可能的三元组和不为 0 。
示例 3：
    输入：nums = [0,0,0]
    输出：[[0,0,0]]
    解释：唯一可能的三元组和为 0 。

提示：
    3 <= nums.length <= 3000
    -105 <= nums[i] <= 105
*/


/*
思路:
    排序后：[-4,-1,-1,0,1,2]

    固定i，left=i+1，right=末尾
    sum < 0 → left右移（增大sum）
    sum > 0 → right左移（减小sum）
    sum == 0 → 记录，跳过重复
去重的三个位置：
    i：与上一个相同跳过
    left：找到答案后跳过连续相同
    right：找到答案后跳过连续相同
*/

#include<vector>
#include<algorithm>
using std::vector;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ret;
        sort(nums.begin(), nums.end());
        
        for(int i = 0; i < nums.size() - 2; i++){
            // 跳过重复的i
            if(i > 0 && nums[i] == nums[i-1]) continue;
            // 最小三数之和已经大于0，后面不可能有解
            if(nums[i] > 0) break;
            
            int left = i + 1, right = nums.size() - 1;
            while(left < right){
                int sum = nums[i] + nums[left] + nums[right];
                if(sum == 0){
                    ret.push_back({nums[i], nums[left], nums[right]});
                    // 跳过重复的left和right
                    while(left < right && nums[left] == nums[left+1]) left++;
                    while(left < right && nums[right] == nums[right-1]) right--;
                    left++;
                    right--;
                }else if(sum < 0){
                    left++;
                }else{
                    right--;
                }
            }
        }
        return ret;
    }
};