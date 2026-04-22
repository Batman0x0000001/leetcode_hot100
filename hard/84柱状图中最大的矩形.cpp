#include<vector>
#include<stack>
#include<algorithm>

class Solution {
public:
    int largestRectangleArea(std::vector<int>& heights) {
        std::stack<int> st;
        int ret = 0;
        heights.insert(heights.begin(),0);
        heights.push_back(0);
        for(int i = 0;i < heights.size();i++){
            while(!st.empty() && heights[i] < heights[st.top()]){
                int height = heights[st.top()];
                st.pop();
                //弹出栈顶后，左边界应该是新的栈顶，不是弹出前的栈顶：
                int width = i-st.top()-1;
                ret = std::max(ret,height*width);
            }
            st.push(i);
        }
        return ret;
    }
};