
#include<utility>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    // 翻转[head, tail]这一段，返回新头
    std::pair<ListNode*, ListNode*> reverse(ListNode* head, ListNode* tail){
        ListNode* prev = tail->next;  // tail->next是下一组的起点，作为终止条件
        ListNode* curr = head;
        while(prev != tail){
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return {tail, head};  // 翻转后tail是新头，head是新尾
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy;
        dummy.next = head;
        ListNode* pre = &dummy;

        while(head != nullptr){
            // 找到第k个节点
            ListNode* tail = pre;
            for(int i = 0; i < k; i++){
                tail = tail->next;
                if(tail == nullptr) return dummy.next;  // 不足k个，直接返回
            }

            ListNode* next = tail->next;  // 保存下一组起点
            auto [newHead, newTail] = reverse(head, tail);

            // 连接
            pre->next = newHead;
            newTail->next = next;

            // 移动到下一组
            pre = newTail;
            head = next;
        }
        return dummy.next;
    }
};