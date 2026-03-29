/*
在给定的 m x n 网格 grid 中，每个单元格可以有以下三个值之一：
值 0 代表空单元格；
值 1 代表新鲜橘子；
值 2 代表腐烂的橘子。
每分钟，腐烂的橘子 周围 4 个方向上相邻 的新鲜橘子都会腐烂。
返回 直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1 。

示例 1：
    输入：grid = [[2,1,1],[1,1,0],[0,1,1]]
    输出：4
示例 2：
    输入：grid = [[2,1,1],[0,1,1],[1,0,1]]
    输出：-1
    解释：左下角的橘子（第 2 行， 第 0 列）永远不会腐烂，因为腐烂只会发生在 4 个方向上。
示例 3：
    输入：grid = [[0,2]]
    输出：0
    解释：因为 0 分钟时已经没有新鲜橘子了，所以答案就是 0 。

提示：
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 10
    grid[i][j] 仅为 0、1 或 2
*/

#include<vector>
#include<queue>
#include <utility>   // pair
#include <tuple>     // tuple, tie
using std::vector;
using std::queue;
using std::pair;
using std::tie;

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        queue<pair<int,int>> queue;
        int row = grid.size();
        int col = grid[0].size();
        int count = 0;
        for(int i = 0;i < row;i++){
            for(int j = 0;j < col;j++){
                if(grid[i][j] == 2){
                    queue.push({i,j});
                }
                if(grid[i][j] == 1){
                    count++;
                }
            }
        }
        if(count == 0){
            return 0;
        }
        int minute = -1;
        while(!queue.empty()){
            int qSize = queue.size();
            for(int i = 0;i < qSize;i++){
                int x,y;
                tie(x,y) = queue.front();
                queue.pop();
                if(x-1 >= 0 && grid[x-1][y] == 1){
                    grid[x-1][y] = 2;
                    queue.push({x-1,y});
                    count--;
                }
                if(x+1 < row && grid[x+1][y] == 1){
                    grid[x+1][y] = 2;
                    queue.push({x+1,y});
                    count--;
                }
                if(y-1 >= 0 && grid[x][y-1] == 1){
                    grid[x][y-1] = 2;
                    queue.push({x,y-1});
                    count--;
                }
                if(y+1 < col && grid[x][y+1] == 1){
                    grid[x][y+1] = 2;
                    queue.push({x,y+1});
                    count--;
                }
            }
            minute++;
        }
        if(count != 0){
            return -1;
        }
        return minute;
    }
};


//代码缩减
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        queue<pair<int,int>> q;
        int row = grid.size(), col = grid[0].size();
        int count = 0;

        for(int i = 0; i < row; i++)
            for(int j = 0; j < col; j++){
                if(grid[i][j] == 2) q.push({i,j});
                if(grid[i][j] == 1) count++;
            }

        if(count == 0) return 0;

        int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
        int minute = -1;

        while(!q.empty()){
            int qSize = q.size();
            minute++;
            for(int i = 0; i < qSize; i++){
                auto [x, y] = q.front();
                q.pop();
                for(auto& d : dirs){
                    int nx = x + d[0], ny = y + d[1];
                    if(nx >= 0 && nx < row && ny >= 0 && ny < col && grid[nx][ny] == 1){
                        grid[nx][ny] = 2;
                        q.push({nx, ny});
                        count--;
                    }
                }
            }
        }

        return count != 0 ? -1 : minute;
    }
};


/*
结构化绑定 auto [a,b] 是C++17的特性。
    C++11中最简洁的写法是 tie：
    include <tuple>

    int a, b;
    tie(a, b) = q.front();  // 解包pair

    tuple也可以：
    cppint a, b, c;
    tie(a, b, c) = q.front();  // 解包tuple

对比三种写法：
    // C++11 - tie
    int a, b;
    tie(a, b) = q.front();

    // C++11 - first/second
    auto p = q.front();
    int a = p.first;
    int b = p.second;

    // C++17 - 结构化绑定
    auto [a, b] = q.front();
*/