/*
给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回 null 。

题目数据 保证 整个链式结构中不存在环。

注意，函数返回结果后，链表必须 保持其原始结构 。

自定义评测：

评测系统 的输入如下（你设计的程序 不适用 此输入）：

intersectVal - 相交的起始节点的值。如果不存在相交节点，这一值为 0
listA - 第一个链表
listB - 第二个链表
skipA - 在 listA 中（从头节点开始）跳到交叉节点的节点数
skipB - 在 listB 中（从头节点开始）跳到交叉节点的节点数
评测系统将根据这些输入创建链式数据结构，并将两个头节点 headA 和 headB 传递给你的程序。如果程序能够正确返回相交节点，那么你的解决方案将被 视作正确答案 。

进阶：你能否设计一个时间复杂度 O(m + n) 、仅用 O(1) 内存的解决方案？
*/

#include<stdio.h>
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    struct ListNode *listA =headA;
    struct ListNode *listB =headB;
    int lengthA=0,lengthB=0;
    while(listA!=NULL){
        listA=listA->next;
        lengthA++;
    }
    while(listB!=NULL){
        listB=listB->next;
        lengthB++;
    }
    if(lengthA>=lengthB){
        for(;lengthA>lengthB;lengthA--){
            headA=headA->next;
        }
    }else{
        for(;lengthA<lengthB;lengthB--){
            headB=headB->next;
        }
    }
    while(headA!=NULL){
        if(headA==headB){
            return headA;
        }
        headA=headA->next;
        headB=headB->next;
    }

    return NULL;
}

/*
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* curr = head;
    struct ListNode* next = NULL;
    while (curr != NULL) {
        next = curr->next;                  // 保存下一个
        curr->next = prev;                  // 反转指针
        prev = curr;                        // prev 前进
        curr = next;                        // curr 前进
    }
    return prev; // prev 最终指向新头节点
}

注意：
翻转后再还原，结构已经被破坏了，无法正确还原。
翻转 A 时，如果 A 和 B 共享尾部节点（这正是本题的前提），翻转 A 会把共享段的指针也一并改掉，导致 B 的结构也被破坏。
翻转前：
    A: a1 -> a2 -> c1 -> c2 -> c3
    B:             b1 -> c1 -> c2 -> c3
                            ↑共享

翻转A后：
    c3 -> c2 -> c1 -> a2 -> a1 -> NULL
                                B的链表已经断掉了！
*/


//代码优化
//1.hash
#include"uthash.h"
typedef struct HashNode{
    struct ListNode *key;
    UT_hash_handle hh;// 必须有这个字段
}HashNode;

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB){
    HashNode *hashmap = NULL;
    struct ListNode *temp = headA;
    while(temp != NULL){
        HashNode *node;
        HASH_FIND(hh,hashmap,&temp,sizeof(struct ListNode *),node);
        if(node == NULL){
            node == (HashNode *)malloc(sizeof(HashNode));
            node->key = temp;
            HASH_ADD(hh,hashmap,key,sizeof(struct ListNode *),node);
        }
        temp = temp->next;
    }
    temp = headB;
    while (temp != NULL)
    {
        HashNode *node;
        HASH_FIND(hh,hashmap,&temp,sizeof(struct ListNode *),node);
        if(node != NULL){
            return node;
        }
        temp = temp->next;
    }
    
    return NULL;
}
//2.双指针
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB){
    if(headA == NULL || headB == NULL){
        return NULL;
    }
    struct ListNode *pA = headA;
    struct ListNode *pB = headB;
    while (pA != pB)
    {
        pA = (pA == NULL) ? headA : pA->next;
        pB = (pB == NULL) ? headB : pB->next;
    }

    return pA;
}