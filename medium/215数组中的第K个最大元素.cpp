/*
给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。

示例 1:
    输入: [3,2,1,5,6,4], k = 2
    输出: 5
示例 2:
    输入: [3,2,3,1,2,4,5,5,6], k = 4
    输出: 4

提示：
    1 <= k <= nums.length <= 105
    -104 <= nums[i] <= 104
*/
#include<vector>
#include<algorithm>
using std::vector;
using std::sort;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end(),[](int a,int b){return a>b;});
        return nums[k-1];
    }
};


//快排
class Solution {
public:
    int partition(vector<int>& nums, int left, int right){
        int pivot = nums[right];
        int i = left;
        for(int j = left; j < right; j++){
            if(nums[j] >= pivot){  // 降序，大的放前面
                swap(nums[i], nums[j]);
                i++;
            }
        }
        swap(nums[i], nums[right]);
        return i;  // pivot最终位置
    }

    int quickSelect(vector<int>& nums, int left, int right, int k){
        int pos = partition(nums, left, right);
        if(pos == k - 1){
            return nums[pos];  // 找到第k大
        }else if(pos < k - 1){
            return quickSelect(nums, pos + 1, right, k);  // 去右边找
        }else{
            return quickSelect(nums, left, pos - 1, k);   // 去左边找
        }
    }

    int findKthLargest(vector<int>& nums, int k) {
        return quickSelect(nums, 0, nums.size() - 1, k);
    }
};


class Solution {
public:
    int quickselect(vector<int> &nums, int l, int r, int k) {
        if (l == r)
            return nums[k];
        int partition = nums[l], i = l - 1, j = r + 1;
        while (i < j) {
            do i++; while (nums[i] < partition);
            do j--; while (nums[j] > partition);
            if (i < j)
                swap(nums[i], nums[j]);
        }
        if (k <= j)return quickselect(nums, l, j, k);
        else return quickselect(nums, j + 1, r, k);
    }

    int findKthLargest(vector<int> &nums, int k) {
        int n = nums.size();
        return quickselect(nums, 0, n - 1, n - k);
    }
};

//堆排
#include<algorithm>
using std::swap;

class Solution {
public:
    void heapify(vector<int>& nums, int n, int i){
        int largest = i;
        int left = 2*i + 1;
        int right = 2*i + 2;
        
        if(left < n && nums[left] > nums[largest]) largest = left;
        if(right < n && nums[right] > nums[largest]) largest = right;
        
        if(largest != i){
            swap(nums[i], nums[largest]);
            heapify(nums, n, largest);  // 递归维护被交换的子树
        }
    }

    void buildHeap(vector<int>& nums){
        // 从最后一个非叶子节点开始，向上heapify
        for(int i = nums.size()/2 - 1; i >= 0; i--){
            heapify(nums, nums.size(), i);
        }
    }

    int findKthLargest(vector<int>& nums, int k) {
        buildHeap(nums);  // 建立大根堆
        
        int n = nums.size();
        for(int i = 0; i < k-1; i++){
            swap(nums[0], nums[n-1]);  // 堆顶（最大值）换到末尾
            n--;                        // 缩小堆范围
            heapify(nums, n, 0);       // 重新维护堆
        }
        return nums[0];  // 第k次操作前的堆顶就是第k大
    }
};