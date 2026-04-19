/*
将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

示例 1：
    输入：l1 = [1,2,4], l2 = [1,3,4]
    输出：[1,1,2,3,4,4]
示例 2：
    输入：l1 = [], l2 = []
    输出：[]
示例 3：
    输入：l1 = [], l2 = [0]
    输出：[0]
 
提示：
    两个链表的节点数目范围是 [0, 50]
    -100 <= Node.val <= 100
    l1 和 l2 均按 非递减顺序 排列
*/

#include<stdio.h>
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    if(list1 == NULL){
        return list2;
    }
    if(list2 == NULL){
        return list1;
    }
    struct ListNode* list3 = NULL;
    struct ListNode* listhead = NULL;
    while(list1 != NULL && list2 != NULL){
        if(list1->val <= list2->val){
            if(list3 == NULL){
                list3 = list1;
                listhead = list3;
                list1 = list1->next;
                list3->next = NULL;
            }else{
                list3->next = list1;
                list1 = list1->next;
                list3 = list3->next;
            }
        }else{
            if(list3 == NULL){
                list3 = list2;
                listhead = list3;
                list2 = list2->next;
                list3->next = NULL;
            }else{
                list3->next = list2;
                list2 = list2->next;
                list3 = list3->next;
            }
        }
    }
    if(list1 == NULL){
        list3->next = list2;
        return listhead;
    }
    if(list2 == NULL){
        list3->next = list1;
        return listhead;
    }
    return listhead;
}

/*
先移动指针再切断:
    list3 = list1;
    listhead = list3;
    list1 = list1->next;
    list3->next = NULL;
如果是这样：
    list3 = list1;
    list3->next = NULL;   // 先把 next 置 NULL
    listhead = list3;
    list1 = list1->next;  // 然后才移动 list1
list1会被改变

NULL 就是 0，没有地址，它不是一个真实存在的内存位置。
    struct ListNode* list3 = NULL;
    struct ListNode* listhead = list3;
这只是两个指针变量，各自存了一个值 0，互相独立，没有任何关联。

对比有意义的情况：
    struct ListNode node = {1, NULL};
    struct ListNode* list3 = &node;       // list3 存了 node 的地址，比如 0x1234
    struct ListNode* listhead = list3;    // listhead 也存了 0x1234
此时两个指针指向同一个节点，通过任意一个修改节点内容，另一个也能看到变化。
但如果让 list3 = list3->next，只是改了 list3 自己存的地址，listhead 仍然是 0x1234。
*/


//代码优化
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2){
    struct ListNode dummy = {0,NULL};
    struct ListNode *newList =  &dummy;
    struct ListNode *newHead = newList;
    while(list1 != NULL && list2 != NULL){
        if(list1->val < list2->val){
            newList->next = list1;
            list1 = list1->next;
        }else{
            newList->next = list2;
            list2 = list2->next;
        }
        newList = newList->next;
    }

    newList->next = list1 == NULL ? list2 : list1;

    return newHead->next;
}


//cpp
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *head = new ListNode(0,nullptr);
        ListNode *list3 = head;
        while(list1 != nullptr && list2 != nullptr){
            if(list1->val < list2->val){
                list3->next = list1;
                list1 = list1->next;
            }else{
                list3->next = list2;
                list2 = list2->next;
            }
            list3 = list3->next;
        }
        list3->next = list1 == nullptr ? list2 : list1;
        return head->next;
    }
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy;//栈上分配，性能更好
        ListNode *list3 = &dummy;
        while(list1 != nullptr && list2 != nullptr){
            if(list1->val < list2->val){
                list3->next = list1;
                list1 = list1->next;
            }else{
                list3->next = list2;
                list2 = list2->next;
            }
            list3 = list3->next;
        }
        list3->next = list1 == nullptr ? list2 : list1;
        return dummy.next;
    }
};