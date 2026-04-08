/*
给定一个经过编码的字符串，返回它解码后的字符串。
编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。
你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。
此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。
测试用例保证输出的长度不会超过 105。

示例 1：
    输入：s = "3[a]2[bc]"
    输出："aaabcbc"
示例 2：
    输入：s = "3[a2[c]]"
    输出："accaccacc"
示例 3：
    输入：s = "2[abc]3[cd]ef"
    输出："abcabccdcdcdef"
示例 4：
    输入：s = "abc3[cd]xyz"
    输出："abccdcdcdxyz"

提示：
    1 <= s.length <= 30
    s 由小写英文字母、数字和方括号 '[]' 组成
    s 保证是一个 有效 的输入。
    s 中所有整数的取值范围为 [1, 300] 
*/


//丑陋解法
#include<stack>
#include<string>
#include<algorithm>
using std::stack;
using std::string;

class Solution {
public:
    string decodeString(string s) {
        stack<char> strStack;
        for(char& str:s){
            strStack.push(str);
            if(strStack.top() == ']'){
                strStack.pop();
                string temp = "";
                while(strStack.top() != '['){
                    temp += strStack.top();
                    strStack.pop();
                }
                reverse(temp.begin(),temp.end());
                strStack.pop();
                string numStr = "";
                while(!strStack.empty() && isdigit(strStack.top())){
                    numStr += strStack.top();
                    strStack.pop();
                }
                reverse(numStr.begin(), numStr.end());
                int i = stoi(numStr);
                string full = "";
                while(i != 0){
                    full += temp;
                    i--;
                }
                for(char& it:full){
                    strStack.push(it);
                }
            }
        }
        string ret = "";
        while(!strStack.empty()){
            ret += strStack.top();
            strStack.pop();
        }
        reverse(ret.begin(),ret.end());
        return ret;
    }
};


//代码优化：更加直观
class Solution {
public:
    string decodeString(string s) {
        stack<int> numStack;    // 存储重复次数
        stack<string> strStack; // 存储待拼接的前缀字符串
        string current = "";    // 当前正在构建的字符串
        int num = 0;            // 当前解析的数字
        
        for (char c : s) {
            if (isdigit(c)) {
                // 构建多位数
                num = num * 10 + (c - '0');
            } else if (c == '[') {
                // 遇到左括号，保存当前状态到栈中
                numStack.push(num);      // 保存重复次数
                strStack.push(current);  // 保存当前已构建的字符串
                num = 0;                 // 重置数字
                current = "";            // 重置当前字符串
            } else if (c == ']') {
                // 遇到右括号，进行字符串重复拼接
                int repeat = numStack.top();
                numStack.pop();
                string temp = current;   // 括号内的字符串
                current = strStack.top(); // 取出之前保存的前缀
                strStack.pop();
                // 重复拼接括号内的字符串
                while (repeat-- > 0) {
                    current += temp;
                }
            } else {
                // 普通字母，直接添加到当前字符串
                current += c;
            }
        }
        return current;
    }
};