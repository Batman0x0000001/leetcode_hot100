/*
给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。

示例 1：
    输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
    输出：[1,2,3,6,9,8,7,4,5]
示例 2：
    输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
    输出：[1,2,3,4,8,12,11,10,9,5,6,7]

提示：
    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 10
    -100 <= matrix[i][j] <= 100
*/

#include<vector>
using std::vector;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ret;
        int mRow = matrix.size();
        int mCol = matrix[0].size();
        int mSize = mRow * mCol;
        int row = 0,col = 0,i = 0;
        while(ret.size() < mSize){
            while(col < mCol-i && row == i && ret.size() < mSize){
                ret.emplace_back(matrix[row][col]);
                col++;
            }
            col--;
            row++;
            while(row < mRow-i && col == mCol-i-1 && ret.size() < mSize){
                ret.emplace_back(matrix[row][col]);
                row++;                
            }
            row--;
            col--;
            while(col > i-1 && row == mRow-i-1 && ret.size() < mSize){
                ret.emplace_back(matrix[row][col]);
                col--;                
            }
            col++;
            row--;
            while(row > i && col == i && ret.size() < mSize){
                ret.emplace_back(matrix[row][col]);
                row--;                
            }
            row++;
            col++;
            i++;
        }
        return ret;
    }
};


//优化代码
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) {
            return {};
        }

        int rows = matrix.size(), columns = matrix[0].size();
        vector<int> order;
        int left = 0, right = columns - 1, top = 0, bottom = rows - 1;
        while (left <= right && top <= bottom) {
            for (int column = left; column <= right; column++) {
                order.push_back(matrix[top][column]);
            }
            for (int row = top + 1; row <= bottom; row++) {
                order.push_back(matrix[row][right]);
            }
            if (left < right && top < bottom) {//防止单行或单列时重复添加元素
                for (int column = right - 1; column > left; column--) {
                    order.push_back(matrix[bottom][column]);
                }
                for (int row = bottom; row > top; row--) {
                    order.push_back(matrix[row][left]);
                }
            }
            left++;
            right--;
            top++;
            bottom--;
        }
        return order;
    }
};