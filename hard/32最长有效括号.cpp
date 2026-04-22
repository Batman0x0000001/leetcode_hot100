/*
给你一个只包含 '(' 和 ')' 的字符串，找出最长有效（格式正确且连续）括号 子串 的长度。
左右括号匹配，即每个左括号都有对应的右括号将其闭合的字符串是格式正确的，比如 "(()())"。

示例 1：
    输入：s = "(()"
    输出：2
    解释：最长有效括号子串是 "()"
示例 2：
    输入：s = ")()())"
    输出：4
    解释：最长有效括号子串是 "()()"
示例 3：
    输入：s = ""
    输出：0

提示：
    0 <= s.length <= 3 * 104
    s[i] 为 '(' 或 ')' 
*/

#include<string>
#include<vector>
#include<stack>
#include<algorithm>
using std::string;
using std::vector;
using std::stack;
using std::max;
using std::min;


//dp[i] = 以s[i]结尾的最长有效括号子串长度
class Solution {
public:
    int longestValidParentheses(string s) {
        if (s.size() == 0) return 0;
        vector<int> dp(s.size());
        stack<int> st;
        for (int i = 0; i < s.size(); i++) {
            if(s[i] == '('){
                st.push(i);  // 左括号，压入下标等待匹配
            }else if(!st.empty()){
                int top = st.top();
                st.pop();  // 找到匹配的左括号，下标为top
                dp[i] = i - top + 1                          // 当前匹配的括号对长度
                    + (top-1 >= 0 ? dp[top-1] : 0);       // 加上左括号左边的有效长度
            }
        } 
        return *max_element(dp.begin(), dp.end());
    }
};

//可以降低空间复杂度，用左右两次遍历计数，O(1)空间：
class Solution {
public:
    int longestValidParentheses(string s) {
        int left = 0, right = 0, ans = 0;
        
        // 从左到右
        for(char c : s){
            if(c == '(') left++;
            else right++;
            if(left == right) ans = max(ans, 2*right);
            else if(right > left) left = right = 0;  // 右括号多了，重置
        }
        
        left = right = 0;
        // 从右到左
        for(int i = s.size()-1; i >= 0; i--){
            if(s[i] == '(') left++;
            else right++;
            if(left == right) ans = max(ans, 2*left);
            else if(left > right) left = right = 0;  // 左括号多了，重置
        }
        return ans;
    }
};