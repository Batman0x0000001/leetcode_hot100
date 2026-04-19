/*
给你一个字符串 s，请你将 s 分割成一些 子串，使每个子串都是 回文串 。返回 s 所有可能的分割方案。

示例 1：
    输入：s = "aab"
    输出：[["a","a","b"],["aa","b"]]
示例 2：
    输入：s = "a"
    输出：[["a"]]

提示：
    1 <= s.length <= 16
    s 仅由小写英文字母组成
*/



#include<string>
#include<vector>
using std::string;
using std::vector;

class Solution {
public:
    bool isPalindrome(string& s){
        int left = 0,right = s.size()-1;
        while(left < right){
            if(s[left] != s[right]){
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
    void backTracking(vector<vector<string>>& ret,vector<string>& path,string& fullStr,int index){
        if(index == fullStr.size()){
            ret.emplace_back(path);
            return;
        }
        //注意细节(边界、条件)
        for(int i = index;i < fullStr.size();i++){
            string sub = fullStr.substr(index,i-index+1);
            if(isPalindrome(sub)){
                path.emplace_back(sub);
                backTracking(ret,path,fullStr,i+1);
                path.pop_back();
            }
        }
    }
    vector<vector<string>> partition(string s) {
        vector<vector<string>> ret;
        vector<string> path;
        backTracking(ret,path,s,0);
        return ret;
    }
};