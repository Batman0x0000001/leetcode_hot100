/*
给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。
单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。

示例 1：
    输入：board = [['A','B','C','E'],['S','F','C','S'],['A','D','E','E']], word = "ABCCED"
    输出：true
示例 2：
    输入：board = [['A','B','C','E'],['S','F','C','S'],['A','D','E','E']], word = "SEE"
    输出：true
示例 3：
    输入：board = [['A','B','C','E'],['S','F','C','S'],['A','D','E','E']], word = "ABCB"
    输出：false

提示：
    m == board.length
    n = board[i].length
    1 <= m, n <= 6
    1 <= word.length <= 15
    board 和 word 仅由大小写英文字母组成

进阶：
    你可以使用搜索剪枝的技术来优化解决方案，使其在 board 更大的情况下可以更快解决问题？
*/

#include<vector>
#include<string>
using std::vector;
using std::string;

class Solution {
public:
    void dfs(vector<vector<char>>& board,string& word,vector<vector<int>>& visited,int x,int y,int index,bool& flag){
        if(index == word.size()){
            flag = true;
            return;
        }
        visited[x][y] = 1;
        if(x-1 >= 0 && visited[x-1][y]!= 1 && board[x-1][y] == word[index]){
            dfs(board,word,visited,x-1,y,index+1,flag);
            //visited[x][y] = 0;    不能写在这里，这会导致父节点被归零！
            //回溯法：做出标记-->在谁的作用域就在谁里面回溯-->清除标记
        }
        if(y-1 >= 0 && visited[x][y-1]!= 1 && board[x][y-1] == word[index]){
            dfs(board,word,visited,x,y-1,index+1,flag);
        }
        if(x+1 < board.size() && visited[x+1][y]!= 1 && board[x+1][y] == word[index]){
            dfs(board,word,visited,x+1,y,index+1,flag);
        }
        if(y+1 < board[0].size() && visited[x][y+1]!= 1 && board[x][y+1] == word[index]){
            dfs(board,word,visited,x,y+1,index+1,flag);
        }
        visited[x][y] = 0;
    }
    bool exist(vector<vector<char>>& board, string word) {
        vector<vector<int>> visited(board.size(),vector<int>(board[0].size(),0));
        bool flag = false;
        for(int i = 0;i < board.size();i++){
            for(int j = 0;j < board[0].size();j++){
                if(board[i][j] == word[0]){
                    dfs(board,word,visited,i,j,1,flag);
                    if(flag == true){
                        return true;
                    }
                }
            }
        }
        return flag;
    }
};


//稍微优化
class Solution {
    /*
    static
        不加static：每个Solution对象都有一份dx,dy
        加static：所有Solution对象共享同一份dx,dy
    方向数组对所有实例都一样，没必要每个对象都存一份，static 让它只存一份。
    constexpr
        表示编译时常量，编译器直接把值嵌入代码
        比const更强，const只保证不被修改，constexpr保证编译时就确定值
    方向数组的值永远不变，用 constexpr 让编译器在编译时就处理好，运行时不需要额外计算。
    */
    static constexpr int dx[4] = {0,0,1,-1};
    static constexpr int dy[4] = {1,-1,0,0};
public:
    void dfs(vector<vector<char>>& board, string& word, int x, int y, int index, bool& flag){
        if(flag) return;  // 已找到，提前退出
        if(index == word.size()){
            flag = true;
            return;
        }
        char temp = board[x][y];
        board[x][y] = '#';
        for(int i = 0; i < 4; i++){
            int nx = x+dx[i], ny = y+dy[i];
            if(nx>=0 && nx<board.size() && ny>=0 && ny<board[0].size()
               && board[nx][ny] == word[index]){
                dfs(board, word, nx, ny, index+1, flag);
            }
        }
        board[x][y] = temp;
    }

    bool exist(vector<vector<char>>& board, string word) {
        for(int i = 0; i < board.size(); i++)
            for(int j = 0; j < board[0].size(); j++)
                if(board[i][j] == word[0]){
                    bool flag = false;
                    dfs(board, word, i, j, 1, flag);
                    if(flag) return true;
                }
        return false;
    }
};