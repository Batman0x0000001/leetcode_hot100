/*
给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

示例 1：
    输入：digits = "23"
    输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
示例 2：
    输入：digits = "2"
    输出：["a","b","c"]

提示：
    1 <= digits.length <= 4
    digits[i] 是范围 ['2', '9'] 的一个数字。
*/

#include<vector>
#include<string>
using std::vector;
using std::string;

class Solution {
public:
    void back_tracking(vector<string>& map,vector<string>& ret,string& str,string& digits,int i){
        if(str.size() == digits.size()){
            ret.emplace_back(str);
        }else{
            int idx = digits[i]-'0';//将字符转成数字
            for(char& it : map[idx]){
                str.push_back(it);
                back_tracking(map,ret,str,digits,i+1);
                str.pop_back();
            }
        }
    }
    vector<string> letterCombinations(string digits) {
        if(digits.size() == 0){
            return {};
        }
        vector<string> map{{""},{""},{"abc"},{"def"},{"ghi"},{"jkl"},{"mno"},{"pqrs"},{"tuv"},{"wxyz"}};
        vector<string> ret;
        string str;
        back_tracking(map,ret,str,digits,0);
        return ret;
    }
};

/*
emplace_back 只存在于序列容器中

emplace_back 的意义是在容器内直接构造对象，对于 string 来说追加字符没有构造过程，push_back 已经足够高效，所以标准库没有为 string 提供 emplace_back
*/