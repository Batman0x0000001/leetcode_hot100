/*
按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。
n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

示例 1：
    输入：n = 4
    输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
示例 2：
    输入：n = 1
    输出：[["Q"]]

提示：
    1 <= n <= 9

*/


//丑陋解法
#include<vector>
#include<string>
using std::vector;
using std::string;

class Solution {
public:
    bool isValid(vector<vector<int>>& matrix,int x,int y,int n){
        for(int i = 0;i < n;i++){
            if(matrix[i][y] == 1){
                return false;
            }
            if(x+i < n && y-i >= 0 && matrix[x+i][y-i] == 1){
                return false;
            }
            if(x+i < n && y+i < n && matrix[x+i][y+i] == 1){
                return false;
            }
            if(x-i >= 0 && y-i >= 0 && matrix[x-i][y-i] == 1){
                return false;
            }
            if(x-i >= 0 && y+i < n && matrix[x-i][y+i] == 1){
                return false;
            }
        }
        return true;
    }
    void backTracking(vector<vector<string>>& ret,vector<string>& path,vector<vector<int>>& matrix,int index,int n){
        if(index == n){
            ret.emplace_back(path);
            return;
        }
        string s = "";
        for(int i = 0;i < n;i++){
            if(isValid(matrix,index,i,n)){
                matrix[index][i] = 1;
                s.push_back('Q');
                for(int j = i+1;j < n;j++){
                    s.push_back('.');  
                }
                path.emplace_back(s);
                backTracking(ret,path,matrix,index+1,n);
                matrix[index][i] = 0;
                path.pop_back();
                while(s.back()!='Q'){
                    s.pop_back();
                }
                s.pop_back();
                s.push_back('.');
            }else{
                s.push_back('.');
            }
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ret;
        vector<string> path;
        vector<vector<int>> matrix(n,vector<int>(n,0));
        backTracking(ret,path,matrix,0,n);
        return ret;
    }
};


//代码优化

class Solution {
public:
    void backTracking(vector<vector<string>>& ret, vector<string>& path,
                      vector<bool>& col, vector<bool>& diag1, vector<bool>& diag2,
                      int row, int n){
        if(row == n){
            ret.emplace_back(path);
            return;
        }
        for(int i = 0; i < n; i++){
            // 列、左对角线、右对角线是否冲突
            if(col[i] || diag1[row-i+n] || diag2[row+i]) continue;
            
            // 构建这一行的字符串
            string s(n, '.');
            s[i] = 'Q';
            
            col[i] = diag1[row-i+n] = diag2[row+i] = true;
            path.emplace_back(s);
            backTracking(ret, path, col, diag1, diag2, row+1, n);
            path.pop_back();
            col[i] = diag1[row-i+n] = diag2[row+i] = false;
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ret;
        vector<string> path;
        vector<bool> col(n, false);
        /*
        左对角线：同一条对角线上 row-col 相同
        右对角线：同一条对角线上 row+col 相同

        row-col 范围是 -(n-1) 到 n-1，加n偏移变成 1 到 2n-1
        row+col 范围是 0 到 2n-2
        */
        vector<bool> diag1(2*n, false);  // 左对角线，row-col相同
        vector<bool> diag2(2*n, false);  // 右对角线，row+col相同
        backTracking(ret, path, col, diag1, diag2, 0, n);
        return ret;
    }
};