/*
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
此外，你可以假设该网格的四条边均被水包围。

示例 1：
    输入：grid = [
        ['1','1','1','1','0'],
        ['1','1','0','1','0'],
        ['1','1','0','0','0'],
        ['0','0','0','0','0']
    ]
    输出：1
示例 2：
    输入：grid = [
        ['1','1','0','0','0'],
        ['1','1','0','0','0'],
        ['0','0','1','0','0'],
        ['0','0','0','1','1']
    ]
    输出：3

提示：
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 300
    grid[i][j] 的值为 '0' 或 '1'
*/

//学习DFS与BFS模板
#include<vector>
using std::vector;

class Solution {
public:
    void dfs(vector<vector<char>>& grid,const int& row,const int& col,vector<vector<char>>& visited,int x,int y){
        visited[x][y] = '1';
        if(x-1 >= 0 && grid[x-1][y] == '1' && visited[x-1][y] != '1')
            dfs(grid,row,col,visited,x-1,y);
        if(x+1 < row && grid[x+1][y] == '1' && visited[x+1][y] != '1')
            dfs(grid,row,col,visited,x+1,y);
        if(y-1 >= 0 && grid[x][y-1] == '1' && visited[x][y-1] != '1')
            dfs(grid,row,col,visited,x,y-1);
        if(y+1 < col && grid[x][y+1] == '1' && visited[x][y+1] != '1')
            dfs(grid,row,col,visited,x,y+1);
    }
    int numIslands(vector<vector<char>>& grid) {
        int row = grid.size();
        int col = grid[0].size();
        int ret = 0;
        vector<vector<char>> visited(row,vector<char>(col,'0'));
        for(int i = 0;i < row;i++){
            for(int j = 0;j < col;j++){
                if(grid[i][j] == '1' && visited[i][j] != '1'){
                    ret++;
                    dfs(grid,row,col,visited,i,j);
                }
            }
        }
        return ret;
    }
};