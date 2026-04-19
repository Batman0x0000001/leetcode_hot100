/*
给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。

示例 1：
    输入：head = [4,2,1,3]
    输出：[1,2,3,4]
示例 2：
    输入：head = [-1,5,3,4,0]
    输出：[-1,0,3,4,5]
示例 3：
    输入：head = []
    输出：[]

提示：
    链表中节点的数目在范围 [0, 5 * 104] 内
    -105 <= Node.val <= 105

进阶：
    你可以在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序吗？
*/


//不会
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    // 合并两个有序链表
    ListNode* merge(ListNode* l1, ListNode* l2){
        ListNode dummy;
        ListNode* curr = &dummy;
        while(l1 && l2){
            if(l1->val <= l2->val){
                curr->next = l1;
                l1 = l1->next;
            }else{
                curr->next = l2;
                l2 = l2->next;
            }
            curr = curr->next;
        }
        curr->next = l1 ? l1 : l2;
        return dummy.next;
    }

    // 从head切出size个节点，返回剩余部分
    ListNode* cut(ListNode* head, int size){
        while(--size && head) head = head->next;
        if(!head) return nullptr;
        ListNode* rest = head->next;
        head->next = nullptr;
        return rest;
    }

    ListNode* sortList(ListNode* head) {
        // 求链表长度
        int n = 0;
        ListNode* node = head;
        while(node) { n++; node = node->next; }

        ListNode dummy;
        dummy.next = head;

        // 步长从1开始倍增
        for(int size = 1; size < n; size *= 2){
            ListNode* curr = dummy.next;
            ListNode* tail = &dummy;

            while(curr){
                // 切出左半段
                ListNode* left = curr;
                ListNode* right = cut(left, size);  // right是剩余部分
                curr = cut(right, size);             // curr是下一轮起点

                tail->next = merge(left, right);
                while(tail->next) tail = tail->next;
            }
        }
        return dummy.next;
    }
};

/*
    ListNode dummy;       栈上分配，内存已经存在，可以直接用
    dummy.next = head;    ✅

    ListNode* dummy;      只是一个指针，没有分配任何内存
    dummy->next = head;   ❌ dummy指向随机地址，解引用崩溃

    指针要可以使用必须分配内存或者指向已有对象
*/