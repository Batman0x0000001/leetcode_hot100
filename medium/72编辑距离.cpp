/*
给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数  。
你可以对一个单词进行如下三种操作：
插入一个字符
删除一个字符
替换一个字符

示例 1：
    输入：word1 = "horse", word2 = "ros"
    输出：3
    解释：
    horse -> rorse (将 'h' 替换为 'r')
    rorse -> rose (删除 'r')
    rose -> ros (删除 'e')
示例 2：
    输入：word1 = "intention", word2 = "execution"
    输出：5
    解释：
    intention -> inention (删除 't')
    inention -> enention (将 'i' 替换为 'e')
    enention -> exention (将 'n' 替换为 'x')
    exention -> exection (将 'n' 替换为 'c')
    exection -> execution (插入 'u')

提示：
    0 <= word1.length, word2.length <= 500
    word1 和 word2 由小写英文字母组成
*/


//看到题目立即cv，太哈人了
#include<vector>
#include<string>
#include<algorithm>
using std::vector;
using std::string;
using std::min;

class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));

        for (int i = 0; i < dp.size(); i++) {
            dp[i][0] = i;
        }
        for (int j = 0; j < dp[0].size(); j++) {
            dp[0][j] = j;
        }

        //dp[i][j] = word1前i个字符转换为word2前j个字符的最少操作数
        for (int i = 1; i < dp.size(); i++) {
            for (int j = 1; j < dp[i].size(); j++) {
                /*
                如果是增操作，即是word1要增加一个字符才跟word2一样， 说明word1的[0..i]跟word2的[0..j-1]是一样的 ， dp[i][j] = dp[i][j-1] + 1
                如果是删操作，也是word1要删除一个字符才跟word2一样，说明word1的[0..i-1]跟word2的[0..j]是一样的， dp[i][j] = dp[i-1][j] + 1
                替换的话就也好理解，说明word1的[0..i-1]跟word2的[0..j-1]是一样的
                */
                if (word1[i-1] == word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];//没有变化
                }else{
                    dp[i][j] = min({dp[i-1][j-1],dp[i-1][j],dp[i][j-1]}) + 1;//对应增删改
                }
            }
        }
        return dp.back().back();
    }
};

//dp[i][j] 只依赖上一行，可以压缩到一维
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<int> dp(n+1);
        for(int j = 0; j <= n; j++) dp[j] = j;

        for(int i = 1; i <= m; i++){
            int prev = dp[0];  // 保存dp[i-1][j-1]
            dp[0] = i;
            for(int j = 1; j <= n; j++){
                int temp = dp[j];  // 保存当前dp[j]，下一轮作为prev
                if(word1[i-1] == word2[j-1]){
                    dp[j] = prev;
                }else{
                    dp[j] = min({prev, dp[j], dp[j-1]}) + 1;
                }
                prev = temp;
            }
        }
        return dp[n];
    }
};