/*
给你一个满足下述两条属性的 m x n 整数矩阵：
每行中的整数从左到右按非严格递增顺序排列。
每行的第一个整数大于前一行的最后一个整数。
给你一个整数 target ，如果 target 在矩阵中，返回 true ；否则，返回 false 。

示例 1：
    输入：matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
    输出：true
示例 2：
    输入：matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
    输出：false

提示：
    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 100
    -104 <= matrix[i][j], target <= 104
*/

#include<vector>
using std::vector;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int rowTop = 0,rowBottom = matrix.size()-1;
        int colLeft = 0,colRight = matrix[0].size()-1;
        int row = 0,col = 0;
        while(rowTop <= rowBottom){
            row = (rowBottom + rowTop) / 2;
            if(matrix[row][0] > target){
                rowBottom = row - 1;
            }else if(matrix[row][0] < target){
                rowTop = row + 1;
            }else{
                return true;
            }
        }
        row = rowBottom;
        if(row < 0){
            return false;
        }
        while(colLeft <= colRight){
            col = (colRight + colLeft) / 2;
            if(matrix[row][col] > target){
                colRight = col -1;
            }else if(matrix[row][col] < target){
                colLeft = col + 1;
            }else{
                return true;
            }
        }
        return false;
    }
};


//另一种方法
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int row = 0, col = matrix[0].size() - 1;
    while(row < matrix.size() && col >= 0){
        if(matrix[row][col] == target) return true;
        else if(matrix[row][col] > target) col--;  // 当前值太大，左移
        else row++;                                  // 当前值太小，下移
    }
    return false;
}
/*
原理：从右上角出发，每次比较可以排除一整行或一整列：
    比target大 → 向左移，排除当前列
    比target小 → 向下移，排除当前行

                    两次二分        右上角
搜索时间复杂度      O(logm + logn)  O(m+n)
代码复杂度              高              低
*/
