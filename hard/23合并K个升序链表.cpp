/*
给你一个链表数组，每个链表都已经按升序排列。
请你将所有链表合并到一个升序链表中，返回合并后的链表。

示例 1：
    输入：lists = [[1,4,5],[1,3,4],[2,6]]
    输出：[1,1,2,3,4,4,5,6]
    解释：链表数组如下：
    [
    1->4->5,
    1->3->4,
    2->6
    ]
    将它们合并到一个有序链表中得到。
    1->1->2->3->4->4->5->6
示例 2：
    输入：lists = []
    输出：[]
示例 3：
    输入：lists = [[]]
    输出：[]

提示：
    k == lists.length
    0 <= k <= 10^4
    0 <= lists[i].length <= 500
    -10^4 <= lists[i][j] <= 10^4
    lists[i] 按 升序 排列
    lists[i].length 的总和不超过 10^4
*/

#include<vector>
using std::vector;

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
        ListNode dummy;
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

    ListNode* merge(vector<ListNode*>& lists,int l,int r){
        if(l == r){
            return lists[l];
        }
        if(l > r){
            return nullptr;
        }
        int mid = (l + r)/2;
        return mergeTwoLists(merge(lists,l,mid),merge(lists,mid+1,r));
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return merge(lists,0,lists.size()-1);
    }
};