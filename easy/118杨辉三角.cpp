/*
给定一个非负整数 numRows，生成「杨辉三角」的前 numRows 行。
在「杨辉三角」中，每个数是它左上方和右上方的数的和。

示例 1:
    输入: numRows = 5
    输出: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
示例 2:
    输入: numRows = 1
    输出: [[1]]

提示:
    1 <= numRows <= 30
*/

#include<vector>
using std::vector;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ret(numRows,vector<int>());
        ret[0].emplace_back(1);
        for(int i = 1;i < numRows;i++){
            ret[i].emplace_back(1);
            for(int j = 1;j < i;j++){
                ret[i].emplace_back(ret[i-1][j-1] + ret[i-1][j]);
            }
            ret[i].emplace_back(1);
        }
        return ret;
    }
};