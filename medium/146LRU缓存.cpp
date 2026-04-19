/*
请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
实现 LRUCache 类：
LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。

示例：
输入
    ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
    [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
输出
    [null, null, null, 1, null, -1, null, -1, 3, 4]
解释
    LRUCache lRUCache = new LRUCache(2);
    lRUCache.put(1, 1); // 缓存是 {1=1}
    lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
    lRUCache.get(1);    // 返回 1
    lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
    lRUCache.get(2);    // 返回 -1 (未找到)
    lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
    lRUCache.get(1);    // 返回 -1 (未找到)
    lRUCache.get(3);    // 返回 3
    lRUCache.get(4);    // 返回 4

提示：
1 <= capacity <= 3000
0 <= key <= 10000
0 <= value <= 105
最多调用 2 * 105 次 get 和 put
*/


//链表题却想不到链表
#include<unordered_map>

class LRUCache {
    struct Node {
        int key, val;
        Node *prev, *next;
        Node(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr){}
    };

    int capacity;
    std::unordered_map<int, Node*> mp;  // key → 节点
    Node *head, *tail;             // 哑节点，头尾哨兵

    void moveToHead(Node* node){
        remove(node);
        insertHead(node);
    }

    void remove(Node* node){
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void insertHead(Node* node){
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

public:
    LRUCache(int capacity) : capacity(capacity) {
        head = new Node(0,0);
        tail = new Node(0,0);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if(!mp.count(key)) return -1;
        moveToHead(mp[key]);
        return mp[key]->val;
    }

    void put(int key, int value) {
        if(mp.count(key)){
            mp[key]->val = value;
            moveToHead(mp[key]);
        }else{
            Node* node = new Node(key, value);
            mp[key] = node;
            insertHead(node);
            if(mp.size() > capacity){
                Node* last = tail->prev;
                remove(last);
                mp.erase(last->key);
                delete last;
            }
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */