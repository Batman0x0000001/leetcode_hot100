/*
给定一个包含红色、白色和蓝色、共 n 个元素的数组 nums ，原地 对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。
必须在不使用库内置的 sort 函数的情况下解决这个问题。

示例 1：
    输入：nums = [2,0,2,1,1,0]
    输出：[0,0,1,1,2,2]
示例 2：
    输入：nums = [2,0,1]
    输出：[0,1,2]

提示：
    n == nums.length
    1 <= n <= 300
    nums[i] 为 0、1 或 2

进阶：
    你能想出一个仅使用常数空间的一趟扫描算法吗？
*/

#include<vector>
#include<algorithm>
using std::vector;
using std::fill;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int count0 = 0,count1 = 0,count2 = 0;
        for(int& it:nums){
            if(it == 0) count0++;
            else if(it == 1) count1++;
            else count2++;
        }
        fill(nums.begin(),nums.begin()+count0,0);
        fill(nums.begin()+count0,nums.begin()+count0+count1,1);
        fill(nums.begin()+count0+count1,nums.end(),2);
    }
};

/*
将下标a到b的元素全部改为val
fill(nums.begin() + a, nums.begin() + b + 1, val);

将下标a到b的元素全部乘以2
transform(nums.begin() + a, nums.begin() + b + 1, 
          nums.begin() + a, 
          [](int x){ return x * 2; });
*/


//新方法：双指针一次遍历
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        int p0 = 0, p2 = n - 1;
        for (int i = 0; i <= p2; ++i) {
            while (i <= p2 && nums[i] == 2) {
                std::swap(nums[i], nums[p2]);
                --p2;
            }
            if (nums[i] == 0) {
                std::swap(nums[i], nums[p0]);
                ++p0;
            }
        }
    }
};