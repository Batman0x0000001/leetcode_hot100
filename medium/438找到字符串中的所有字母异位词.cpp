/*
给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。

示例 1:
    输入: s = "cbaebabacd", p = "abc"
    输出: [0,6]
    解释:
    起始索引等于 0 的子串是 "cba", 它是 "abc" 的异位词。
    起始索引等于 6 的子串是 "bac", 它是 "abc" 的异位词。

示例 2:
    输入: s = "abab", p = "ab"
    输出: [0,1,2]
    解释:
    起始索引等于 0 的子串是 "ab", 它是 "ab" 的异位词。
    起始索引等于 1 的子串是 "ba", 它是 "ab" 的异位词。
    起始索引等于 2 的子串是 "ab", 它是 "ab" 的异位词。

提示:
    1 <= s.length, p.length <= 3 * 104
    s 和 p 仅包含小写字母
*/

//笨办法
#include<unordered_map>
#include<vector>
#include<string>
#include<algorithm>
using std::vector;
using std::unordered_map;
using std::string;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> ret;
        unordered_map<char,int> target;
        for(char& c : p){
            target[c]++;
        }
        int left = 0;
        for(int right = left + p.size()-1;right < s.size();right++){
            unordered_map<char,int> source;
            for(int i = left;i <= right;i++){
                source[s[i]]++;
            }
            if(source == target){
                ret.emplace_back(left);
            }
            left++;
        }
        return ret;
    }
};

//超时：
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> ret;
        if(s.size() < p.size()){
            return ret;
        }
        sort(p.begin(),p.end());
        for(int i = 0;i<= s.size()-p.size();i++){
            string subS = s.substr(i,p.size());
            sort(subS.begin(),subS.end());
            if(subS == p){
                ret.emplace_back(i);
            }
        }
        return ret;
    }
};


//代码优化：官解滑动窗口
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int sLen = s.size(), pLen = p.size();

        if (sLen < pLen) {
            return vector<int>();
        }

        vector<int> ans;
        vector<int> sCount(26);
        vector<int> pCount(26);
        for (int i = 0; i < pLen; ++i) {
            ++sCount[s[i] - 'a'];
            ++pCount[p[i] - 'a'];
        }

        if (sCount == pCount) {
            ans.emplace_back(0);
        }

        for (int i = 0; i < sLen - pLen; ++i) {
            --sCount[s[i] - 'a'];
            ++sCount[s[i + pLen] - 'a'];

            if (sCount == pCount) {
                ans.emplace_back(i + 1);
            }
        }

        return ans;
    }
};