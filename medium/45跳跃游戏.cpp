/*
给定一个长度为 n 的 0 索引整数数组 nums。初始位置在下标 0。
每个元素 nums[i] 表示从索引 i 向后跳转的最大长度。换句话说，如果你在索引 i 处，你可以跳转到任意 (i + j) 处：
0 <= j <= nums[i] 且 i + j < n
返回到达 n - 1 的最小跳跃次数。测试用例保证可以到达 n - 1。

示例 1:
    输入: nums = [2,3,1,1,4]
    输出: 2
    解释: 跳到最后一个位置的最小跳跃数是 2。
        从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
示例 2:
    输入: nums = [2,3,0,1,4]
    输出: 2

提示:
    1 <= nums.length <= 104
    0 <= nums[i] <= 1000
    题目保证可以到达 n - 1
*/

//官解解释版
#include<vector>
#include<algorithm>

class Solution {
public:
    int jump(std::vector<int>& nums) {
        int n = nums.size();

        int steps = 0;               // 已经使用的跳跃次数
        int currentRangeEnd = 0;     // 当前这一步最远能覆盖到的位置
        int nextRangeEnd = 0;        // 在当前范围内扫描后，下一步最远能到的位置

        for (int i = 0; i < n - 1; ++i) {
            // 在当前这一层的所有点中，持续更新“下一层最远边界”
            nextRangeEnd = std::max(nextRangeEnd, i + nums[i]);

            // 当前层扫描完毕，必须跳一次，进入下一层
            if (i == currentRangeEnd) {
                ++steps;
                currentRangeEnd = nextRangeEnd;
            }
        }

        return steps;
    }
};