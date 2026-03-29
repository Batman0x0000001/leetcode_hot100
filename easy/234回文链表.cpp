/*
给你一个单链表的头节点 head ，请你判断该链表是否为回文链表。如果是，返回 true ；否则，返回 false 。

示例 1：
    输入：head = [1,2,2,1]
    输出：true
示例 2：
    输入：head = [1,2]
    输出：false

提示：
    链表中节点数目在范围[1, 105] 内
    0 <= Node.val <= 9
 
进阶：你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？
*/

#include<stdio.h>
#include<stdbool.h> 
struct ListNode {
    int val;
    struct ListNode *next;
};

bool isPalindrome(struct ListNode* head) {
    struct ListNode *list = head;
    struct ListNode *curr = head;
    int length = 0;
    while(list != NULL){
        list = list->next;
        length++;
    }
    length = (length + 1) / 2;
    while(length != 0){
        curr = curr->next;
        length --;
    }
    struct ListNode *prev = NULL;
    struct ListNode *next = NULL;
    while(curr != NULL){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    while(prev != NULL){
        if(head->val != prev->val){
            return false;
        }
        head = head->next;
        prev = prev->next;
    }

    return true;
}
/*
length = (length + 1) / 2;
*/


//代码优化
//慢指针一次走一步，快指针一次走两步，快慢指针同时出发。当快指针移动到链表的末尾时，慢指针恰好到链表的中间。通过慢指针将链表分为两部分。
struct ListNode* endOfFirstHalf(struct ListNode* head) {
    struct ListNode* fast = head;
    struct ListNode* slow = head;
    while (fast->next != NULL && fast->next->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* endOfFirstHalf(ListNode* head){
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast->next != nullptr && fast->next->next != nullptr){
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow->next;
    }

    ListNode* reversal(ListNode* root){
        ListNode* prev = nullptr;
        ListNode* next = nullptr;
        ListNode* curr = root;
        while(curr != nullptr){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
    bool isPalindrome(ListNode* head) {
        ListNode* half = endOfFirstHalf(head);
        half = reversal(half);
        while(head != nullptr && half != nullptr){
            if(head->val != half->val){
                return false;
            }
            head = head->next;
            half = half->next;
        }
        return true;
    }
};
