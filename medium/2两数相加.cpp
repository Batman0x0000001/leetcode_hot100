/*
给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
请你将两个数相加，并以相同形式返回一个表示和的链表。
你可以假设除了数字 0 之外，这两个数都不会以 0 开头。

示例 1：
    输入：l1 = [2,4,3], l2 = [5,6,4]
    输出：[7,0,8]
    解释：342 + 465 = 807.
示例 2：
    输入：l1 = [0], l2 = [0]
    输出：[0]
示例 3：
    输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
    输出：[8,9,9,9,0,0,0,1]

提示：
    每个链表中的节点数在范围 [1, 100] 内
    0 <= Node.val <= 9
    题目数据保证列表表示的数字不含前导零
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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* ret = new ListNode();
        ListNode* curr = ret;
        int carry = 0;
        while(l1 != nullptr && l2 != nullptr){
            int twoSum = l1->val + l2->val + carry;
            carry = twoSum >= 10 ? 1 : 0;
            ListNode* node = new ListNode(twoSum >= 10 ? twoSum-10 : twoSum);
            curr->next = node;
            curr = curr->next;
            l1 = l1->next;
            l2 = l2->next;
        }
        curr->next = l1 == nullptr ? l2 : l1;
        while(carry != 0){
            if(curr->next == nullptr){
                ListNode* node = new ListNode(carry);
                curr->next = node;
                carry = 0;//没有break或者让carry=0，死循环
            }else{
                curr = curr->next;
                int twoSum = curr->val + carry;
                carry = twoSum >= 10 ? 1 : 0;
                curr->val = twoSum >= 10 ? twoSum-10 : twoSum;
            }
        }
        return ret->next;
    }
};

//任意X进制两数之和  最大进位为1
//任意X进制两数之积  最大进位为X-2(X>=2)


//代码优化：如果两个链表的长度不同，则可以认为长度短的链表的后面有若干个 0 
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *head = nullptr, *tail = nullptr;
        int carry = 0;
        while (l1 || l2) {
            int n1 = l1 ? l1->val: 0;
            int n2 = l2 ? l2->val: 0;
            int sum = n1 + n2 + carry;
            if (!head) {
                head = tail = new ListNode(sum % 10);
            } else {
                tail->next = new ListNode(sum % 10);
                tail = tail->next;
            }
            carry = sum / 10;
            if (l1) {
                l1 = l1->next;
            }
            if (l2) {
                l2 = l2->next;
            }
        }
        if (carry > 0) {
            tail->next = new ListNode(carry);
        }
        return head;
    }
};