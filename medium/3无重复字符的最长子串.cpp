/*
给定一个字符串 s ，请你找出其中不含有重复字符的 最长 子串 的长度。

示例 1:
    输入: s = "abcabcbb"
    输出: 3 
    解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。注意 "bca" 和 "cab" 也是正确答案。
示例 2:
    输入: s = "bbbbb"
    输出: 1
    解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:
    输入: s = "pwwkew"
    输出: 3
    解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
        请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。

提示：
    0 <= s.length <= 5 * 104
    s 由英文字母、数字、符号和空格组成
*/
#include<string>
#include<unordered_set>
#include<deque>
using std::unordered_set;
using std::deque;
using std::string;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> window;
        deque<char> queue;
        int max = 0;
        for(char c : s){
            if(window.find(c) != window.end()){
                while(queue.front() != c){
                    window.erase(queue.front());
                    queue.pop_front();
                }
                if(!queue.empty()){
                    window.erase(queue.front());
                    queue.pop_front();
                }
            }
            window.insert(c);
            queue.push_back(c);
            max = window.size() > max ? window.size() : max;
            
        }
        return max;
    }
};


//滑动窗口模板
#include<vector>
void window(std::vector<int>& nums){
    int left = 0;
    bool condition;
    // 窗口内的状态变量，根据题目定义
    // int sum = 0;
    // unordered_map<char,int> count;

    for(int right = 0; right < nums.size(); right++){
        // 1. 扩大窗口，加入right元素
        // sum += nums[right];
        // count[s[right]]++;

        // 2. 判断是否需要缩小窗口
        while(condition){
            // 缩小窗口，移出left元素
            // sum -= nums[left];
            // count[s[left]]--;
            left++;
        }

        // 3. 此时窗口满足条件，更新答案
        // ans = max(ans, right - left + 1);
    }
}


#include<unordered_map>
#include<algorithm>
using std::unordered_map;
using std::max;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char,int> hashmap;
        int left = 0;
        int maxLength = 0;
        for(int right = 0;right < s.size();right++){
            hashmap[s[right]]++;
            if(hashmap[s[right]] > 1){
                while(s[left] != s[right]){
                    hashmap[s[left]]--;
                    left++;
                }
                hashmap[s[left]]--;
                left++;
            }
            maxLength = max(maxLength,right-left+1);
        }
        return maxLength;
    }
};


//优化
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
    unordered_map<char,int> pos;  // 记录字符最后出现的位置
    int left = 0, maxLength = 0;
    for(int right = 0; right < s.size(); right++){
        if(pos.count(s[right]) && pos[s[right]] >= left){
            left = pos[s[right]] + 1;  // 直接跳到重复字符的下一位
        }
        pos[s[right]] = right;  // 更新位置
        maxLength = max(maxLength, right - left + 1);
    }
    return maxLength;
    }
};