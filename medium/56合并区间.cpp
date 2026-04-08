/*
以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。

示例 1：
    输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
    输出：[[1,6],[8,10],[15,18]]
    解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
示例 2：
    输入：intervals = [[1,4],[4,5]]
    输出：[[1,5]]
    解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。
示例 3：
    输入：intervals = [[4,7],[1,4]]
    输出：[[1,7]]
    解释：区间 [1,4] 和 [4,7] 可被视为重叠区间。

提示：
    1 <= intervals.length <= 104
    intervals[i].length == 2
    0 <= starti <= endi <= 104
*/

#include<vector>
#include<algorithm>
using std::vector;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(),intervals.end(),[](const vector<int>& a,const vector<int>& b){
            return a[0]<b[0];
        });
        vector<vector<int>> ret;
        ret.emplace_back(intervals[0]);
        for(int i = 1;i< intervals.size();i++){
            int j = ret.size()-1;
            if(intervals[i][0] <= ret[j][1]){
                ret[j][1] = std::max(intervals[i][1],ret[j][1]);
            }else{
                ret.emplace_back(intervals[i]);
            }
        }
        return ret;
    }
};


/*
排序后只需要和 ret 的最后一个区间比较，不需要遍历整个 ret：
for(int i = 1;i< intervals.size();i++){
    for(int j = 0;j < ret.size();j++){
        if(intervals[i][0] <= ret[j][1]){
            ret[j][1] = max(intervals[i][1],ret[j][1]);
        }else{
            ret.emplace_back(intervals[i]);
        }
    }
}
不满足就插入了，但后面的区间可能满足条件，导致既插入了又合并了，产生重复。
*/