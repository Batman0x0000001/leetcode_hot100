/*
给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的子数组的个数 。
子数组是数组中元素的连续非空序列。

示例 1：
    输入：nums = [1,1,1], k = 2
    输出：2
示例 2：
    输入：nums = [1,2,3], k = 3
    输出：2

提示：
    1 <= nums.length <= 2 * 104
    -1000 <= nums[i] <= 1000
    -107 <= k <= 107
*/

//妙啊 妙啊
/*
前缀和的概念
    首先，我们使用一个叫做“前缀和”的概念。对于数组中的任何位置 j，前缀和 pre[j] 是数组中从第一个元素到第 j 个元素的总和。
    这意味着如果你想知道从元素 i+1 到 j 的子数组的和，你可以用 pre[j] - pre[i] 来计算。

使用 Map 来存储前缀和
    在代码中，我们用一个 Map（哈希表）来存储每个前缀和出现的次数。这是为了快速检查某个特定的前缀和是否已经存在，以及它出现了多少次。

核心逻辑解析
    当我们在数组中向前移动时，我们逐步增加 pre（当前的累积和）。对于每个新的 pre 值，我们检查 pre - k 是否在 Map 中：
    
pre - k 的意义：
    这个检查的意义在于，如果 pre - k 存在于 Map 中，说明之前在某个点的累积和是 pre - k。
    由于当前的累积和是 pre，这意味着从那个点到当前点的子数组之和恰好是 k（因为 pre - (pre - k) = k）。

如何使用这个信息：
    如果 pre - k 在 Map 中，那么 pre - k 出现的次数表示从不同的起始点到当前点的子数组和为 k 的不同情况。
    这是因为每一个 pre - k 都对应一个起点，使得从那个起点到当前点的子数组和为 k。
    因此，每当我们找到一个 pre - k 存在于 Map 中时，我们就把它的计数（即之前这种情况发生的次数）加到 count 上，
    因为这表示我们又找到了相应数量的以当前元素结束的子数组，其和为 k。
*/
#include<vector>
#include<unordered_map>
using std::vector;
using std::unordered_map;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        mp[0] = 1;
        int count = 0, pre = 0;
        for (auto& x:nums) {
            pre += x;
            if (mp.find(pre - k) != mp.end()) {
                count += mp[pre - k];
            }
            mp[pre]++;
            /*
            只有 map 和 unordered_map 有这种自动插入的 [] 运算符：
                mp[pre]++;
                等价于：
                cppif(mp.find(pre) == mp.end()){
                    mp[pre] = 0;  // key不存在时自动插入，默认值为0
                }
                mp[pre]++;        // 再自增
            */
        }
        return count;
    }
};