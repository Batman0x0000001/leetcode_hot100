/*
数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

示例 1：
    输入：n = 3
    输出：["((()))","(()())","(())()","()(())","()()()"]
示例 2：
    输入：n = 1
    输出：["()"]

提示：
    1 <= n <= 8
*/

#include<vector>
#include<string>
using std::vector;
using std::string;

class Solution {
public:
    void back_tracking(vector<string>& ret,string& s,int l,int r,int n){
        if(l == r && r == n){
            ret.emplace_back(s);
            return;
        }
        if(r > l){
            return;
        }
        if(l > n){
            return;
        }
        s.push_back('(');
        back_tracking(ret,s,l+1,r,n);
        s.pop_back();
        s.push_back(')');
        back_tracking(ret,s,l,r+1,n);
        s.pop_back();
    }
    vector<string> generateParenthesis(int n) {
        vector<string> ret;
        string s = "";
        back_tracking(ret,s,0,0,n);
        return ret;
    }
};