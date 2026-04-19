/*
给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。

示例 1:
    输入: temperatures = [73,74,75,71,69,72,76,73]
    输出: [1,1,4,2,1,1,0,0]
示例 2:
    输入: temperatures = [30,40,50,60]
    输出: [1,1,1,0]
示例 3:
    输入: temperatures = [30,60,90]
    输出: [1,1,0]

提示：
    1 <= temperatures.length <= 105
    30 <= temperatures[i] <= 100
*/


//想不出，单调栈
#include<vector>
#include<stack>
using std::vector;
using std::stack;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans(n);
        stack<int> s;
        for (int i = 0; i < n; ++i) {
            while (!s.empty() && temperatures[i] > temperatures[s.top()]) {
                int previousIndex = s.top();
                ans[previousIndex] = i - previousIndex;
                s.pop();
            }
            s.push(i);
        }
        return ans;
    }
};

//next数组法
#include<climits>
#include<algorithm>

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        //next[t] = 温度t最近出现的下标
        vector<int> ans(n), next(101, INT_MAX);
        for (int i = n - 1; i >= 0; --i) {
            int warmerIndex = INT_MAX;
            for (int t = temperatures[i] + 1; t <= 100; ++t) {
                warmerIndex = std::min(warmerIndex, next[t]);
            }
            //从后找到更高温度
            if (warmerIndex != INT_MAX) {
                ans[i] = warmerIndex - i;
            }
            //没找到ans[i]仍为初始化的值

            next[temperatures[i]] = i;
        }
        return ans;
    }
};


/*
场景                    默认值
全局/static数组             0
局部数组                 随机值
= {}初始化                  0
vector                     0

{}初始化对任何类型都是零值初始化，指针是nullptr，数值是0，bool是false，char是'\0'。
*/