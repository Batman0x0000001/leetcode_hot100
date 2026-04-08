/*
给你一个整数 n ，返回 和为 n 的完全平方数的最少数量 。
完全平方数 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。

示例 1：
    输入：n = 12
    输出：3 
    解释：12 = 4 + 4 + 4
示例 2：
    输入：n = 13
    输出：2
    解释：13 = 4 + 9

提示：
    1 <= n <= 104
*/

#include<vector>
#include<algorithm>
#include<climits>

class Solution {
public:
    int numSquares(int n) {
        std::vector<int> dp(n+1,INT_MAX);
        dp[0] = 0;
        for(int i = 1;i < n+1;i++){
            for (int j = 1; j * j <= i; j++) {
                dp[i] = std::min(dp[i], dp[i - j * j] + 1);
            }
        }
        return dp[n];
    }
};

/*
这只比较了两种情况：
    用一个 1^2，也就是 dp[i-1] + 1
    用一个不超过 i 的最大平方数，也就是 dp[i-k^2] + 1
但正确思路应该是：
    枚举所有平方数 j*j <= i，取最小值

反例：
    n = 12
    最优解是：12 = 4 + 4 + 4
class Solution { 
public: 
    int numSquares(int n) {
        vector<int> dp(n+1,0); 
        dp[0] = 0; 
        dp[1] = 1; 
        for(int i = 2;i < n+1;i++){ 
            dp[i] = min(1+dp[i-1],1+dp[i-int(sqrt(i)*int(sqrt(i)))]); 
            } 
        return dp[n]; 
        }
    };
*/