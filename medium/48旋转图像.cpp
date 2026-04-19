/*
给定一个 n × n 的二维矩阵 matrix 表示一个图像。请你将图像顺时针旋转 90 度。
你必须在 原地 旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要 使用另一个矩阵来旋转图像。

示例 1：
    输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
    输出：[[7,4,1],[8,5,2],[9,6,3]]
示例 2：
    输入：matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
    输出：[[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]

提示：
    n == matrix.length == matrix[i].length
    1 <= n <= 20
    -1000 <= matrix[i][j] <= 1000
*/


//转置+翻转
#include<vector>
#include<algorithm>
using std::vector;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        for(int i = 0;i < matrix.size();i++){
            for(int j = i+1;j < matrix.size();j++){
                std::swap(matrix[i][j],matrix[j][i]);
            }
        }
        for(int i = 0;i < matrix.size();i++){
            reverse(matrix[i].begin(),matrix[i].end());
        }
    }
};

/*
因为是正方形，以左上，右上，左下，右下为四个点，每次将四个点按顺时针旋转，
下一次就+1偏移量取四个点旋转一遍，外层旋转完，然后往里进一层，就是上下左右往里面缩一层循环即可
*/
class Solution {
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int top = 0, bottom = n-1, left = 0, right = n-1;
        while(top < bottom && left < right) {
            for(int i = 0; i < right - left; i++) {
                int tmp = matrix[top][left + i];
                matrix[top][left + i] = matrix[bottom - i][left];
                matrix[bottom - i][left] = matrix[bottom][right - i];
                matrix[bottom][right - i] = matrix[top + i][right];
                matrix[top + i][right] = tmp;
            }
            top++;
            bottom--;
            left++;
            right--;
        }
    }
};