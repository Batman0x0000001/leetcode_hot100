/*
给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。

示例 1：
    输入：nums = [1,1,1,2,2,3], k = 2
    输出：[1,2]
示例 2：
    输入：nums = [1], k = 1
    输出：[1]
示例 3：
    输入：nums = [1,2,1,2,1,2,3,1,3,2], k = 2
    输出：[1,2]

提示：
    1 <= nums.length <= 105
    -104 <= nums[i] <= 104
    k 的取值范围是 [1, 数组中不相同的元素的个数]
    题目数据保证答案唯一，换句话说，数组中前 k 个高频元素的集合是唯一的

进阶：
    你所设计算法的时间复杂度 必须 优于 O(n log n) ，其中 n 是数组大小。
*/


//背堆排模板
#include<vector>
#include<utility>
#include<unordered_map>
#include<algorithm>
using std::vector;
using std::unordered_map;
using std::pair;
using std::swap;

class Solution {
public:
    void heapify(vector<pair<int,int>>& nums, int n, int i){
        int largest = i;
        int left = 2*i + 1;
        int right = 2*i + 2;
        
        if(left < n && nums[left].second > nums[largest].second) largest = left;
        if(right < n && nums[right].second > nums[largest].second) largest = right;
        
        if(largest != i){
            swap(nums[i], nums[largest]);
            heapify(nums, n, largest);  // 递归维护被交换的子树
        }
    }

    void buildHeap(vector<pair<int,int>>& nums){
        // 从最后一个非叶子节点开始，向上heapify
        for(int i = nums.size()/2 - 1; i >= 0; i--){
            heapify(nums, nums.size(), i);
        }
    }
    
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> hashmap;
        for(int& num:nums){
            hashmap[num]++;
        }
        vector<pair<int,int>> heap;
        for(auto& [a,b]:hashmap){
            heap.emplace_back(a,b);
        }
        buildHeap(heap);
        vector<int> ret;
        int n = heap.size();
        for(int i = 0; i < k; i++){
            ret.emplace_back(heap[0].first);  // 取堆顶
            swap(heap[0], heap[n-1]);         // 堆顶换到末尾
            n--;
            heapify(heap, n, 0);              // 重新维护堆
        }
        return ret;
    }
};


//优先队列：priority_queue 默认是一个最大堆
#include<queue>
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int,int> hashmap;
    for(int& num : nums) hashmap[num]++;

    // 小根堆，按频次排序
    std::priority_queue<pair<int,int>, vector<pair<int,int>>, std::greater<pair<int,int>>> minHeap;

    for(auto& [val, freq] : hashmap){
        minHeap.emplace(freq, val);
        if(minHeap.size() > k) minHeap.pop();  // 保持堆大小为k，堆顶是最小频次
    }

    vector<int> ret;
    while(!minHeap.empty()){
        ret.emplace_back(minHeap.top().second);
        minHeap.pop();
    }
    return ret;
}