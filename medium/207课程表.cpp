/*
你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。
在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。
例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。

示例 1：
    输入：numCourses = 2, prerequisites = [[1,0]]
    输出：true
    解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。
示例 2：
    输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
    输出：false
    解释：总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0 ；并且学习课程 0 之前，你还应先完成课程 1 。这是不可能的。

提示：
    1 <= numCourses <= 2000
    0 <= prerequisites.length <= 5000
    prerequisites[i].length == 2
    0 <= ai, bi < numCourses
    prerequisites[i] 中的所有课程对 互不相同
*/

#include<vector>
using std::vector;

class Solution {
public:
    void dfs(vector<vector<int>>& matrix,int x,int y,bool& conflict){
        if(matrix[x][y] == 2){
            conflict = true;
            return;
        }
        matrix[x][y] = 2;
        for(int i = 0;i < matrix.size();i++){
            if(matrix[y][i] != 0){
                dfs(matrix,y,i,conflict);
                matrix[y][i] = 0;
            }
        }
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> matrix(numCourses,vector<int>(numCourses,0));
        for(vector<int>& pre : prerequisites){
            int x = pre[0];
            int y = pre[1];
            matrix[x][y] = 1;
        }
        bool conflict = false;
        for(int i = 0;i < numCourses;i++){
            for(int j = 0;j < numCourses;j++){
                if(matrix[i][j] == 1){
                    dfs(matrix,i,j,conflict);
                    matrix[i][j] = 0;
                }
                if(conflict){
                    return false;
                }
            }
        }
        return true;
    }
};


//代码优化：使用邻接表
class Solution {
public:
    // 0=未访问 1=访问中 2=已完成
    bool dfs(vector<vector<int>>& graph, vector<int>& visited, int node){
        if(visited[node] == 1) return false;  // 有环
        if(visited[node] == 2) return true;   // 已确认无环

        visited[node] = 1;  // 标记访问中
        for(int next : graph[node]){
            if(!dfs(graph, visited, next)) return false;
        }
        visited[node] = 2;  // 标记已完成
        return true;
    }

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        for(auto& pre : prerequisites){
            graph[pre[0]].emplace_back(pre[1]);  // 邻接表
        }

        vector<int> visited(numCourses, 0);
        for(int i = 0; i < numCourses; i++){
            if(!dfs(graph, visited, i)) return false;
        }
        return true;
    }
};