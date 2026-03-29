/*
设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。
实现 MinStack 类:
    MinStack() 初始化堆栈对象。
    void push(int val) 将元素val推入堆栈。
    void pop() 删除堆栈顶部的元素。
    int top() 获取堆栈顶部的元素。
    int getMin() 获取堆栈中的最小元素。

示例 1:
    输入：
    ["MinStack","push","push","push","getMin","pop","top","getMin"]
    [[],[-2],[0],[-3],[],[],[],[]]
    输出：
    [null,null,null,null,-3,null,0,-2]
    解释：
    MinStack minStack = new MinStack();
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    minStack.getMin();   --> 返回 -3.
    minStack.pop();
    minStack.top();      --> 返回 0.
    minStack.getMin();   --> 返回 -2.

提示：
    -231 <= val <= 231 - 1
    pop、top 和 getMin 操作总是在 非空栈 上调用
    push, pop, top, and getMin最多被调用 3 * 104 次
*/

#include<climits>

class MinStack {
public:
    int* m_stack;
    int m_count;
    int m_size;
    int m_min;

    MinStack() {
        m_stack = new int[1];
        m_count = 0;
        m_size = 1;
        m_min = INT_MAX;
    }
    
    void push(int val) {
        if(m_count < m_size){
            m_stack[m_count] = val;
            m_min = m_min < val ? m_min : val;
            m_count++;
        }else{
            int* temp = new int[m_size+1];
            for(int i = 0;i < m_size;i++){
                temp[i] = m_stack[i];
            }
            m_min = m_min < val ? m_min : val;
            temp[m_size] = val;
            m_size++;
            m_count++;
            delete[] m_stack;
            m_stack = temp;
        }

    }
    
    void pop() {
        if(m_count > 0){
                m_count--;
                if(m_stack[m_count] == m_min){
                    m_min = INT_MAX;
                    for(int i = 0; i < m_count; i++){
                        m_min = m_min < m_stack[i] ? m_min : m_stack[i];
                    }
                }
        }else{
            return;
        }
    }
    
    int top() {
        int ret = m_stack[m_count - 1];
        return ret;
    }
    
    int getMin() {
        return m_min;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */