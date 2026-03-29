/*
给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
 
示例 1：
    输入：head = [1,2,3,4,5]
    输出：[5,4,3,2,1]
示例 2：
    输入：head = [1,2]
    输出：[2,1]
示例 3：
    输入：head = []
    输出：[]

提示：
    链表中节点的数目范围是 [0, 5000]
    -5000 <= Node.val <= 5000
 
进阶：链表可以选用迭代或递归方式完成反转。你能否用两种方法解决这道题？
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* next = nullptr;
        while(head != nullptr){
            next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }
        return prev;
    }
};

/*
prev 这个指针变量销毁了，但 prev 指向的堆上节点没有销毁 
return prev 是把 prev 存储的地址值复制给调用方，调用方拿到这个地址后仍然能访问堆上的节点。

int* func() {
    int* p = new int(5);  // 5在堆上
    return p;             // 把地址复制出去，p销毁但5还在
}
*/