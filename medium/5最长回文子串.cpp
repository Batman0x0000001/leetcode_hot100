/*
给你一个字符串 s，找到 s 中最长的 回文 子串。

示例 1：
    输入：s = "babad"
    输出："bab"
    解释："aba" 同样是符合题意的答案。
示例 2：
    输入：s = "cbbd"
    输出："bb"

提示：
    1 <= s.length <= 1000
    s 仅由数字和英文字母组成
*/

#include<string>
#include<vector>
using std::string;
using std::vector;


//错误
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        if(n == 1){
            return s;
        }
        vector<vector<bool>> dp(n,vector<bool>(n,false));
        for(int i = 0;i < n;i++){
            dp[i][i] = true;
        }
        int start = 0;
        int maxlength = 1;
        for(int i = 0;i < n;i++){
            for(int j = i+1;j < n;j++){
                if(s[i] == s[j]){
                    if(i+1 <= j-1){
                        dp[i][j] = dp[i+1][j-1];//会访问到仅仅被初始化，而被没有设定的dp元素。错误！
                    }else{
                        dp[i][j] = true;
                    }
                }else{
                    dp[i][j] = false;
                }
                if(dp[i][j] == true){
                    if(maxlength < j-i){
                        maxlength = j-i;
                        start = i;
                    }
                }
            }
        }
        return s.substr(start,maxlength+1);
    }
};

//按长度遍历
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        for(int i = 0; i < n; i++) dp[i][i] = true;
        int start = 0, maxlength = 1;

        // 按长度从小到大遍历，保证dp[i+1][j-1]已经计算过
        for(int len = 2; len <= n; len++){
            for(int i = 0; i+len-1 < n; i++){
                int j = i+len-1;
                if(s[i] == s[j]){
                    if(len == 2){
                        dp[i][j] = true;  // 长度为2时中间没有元素
                    }else{
                        dp[i][j] = dp[i+1][j-1];  // 此时dp[i+1][j-1]已经计算过
                    }
                }
                if(dp[i][j] && len > maxlength){
                    maxlength = len;
                    start = i;
                }
            }
        }
        return s.substr(start, maxlength);
    }
};