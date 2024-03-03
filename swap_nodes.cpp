/**
 24. 两两交换链表中的节点
给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。

 

示例 1：


输入：head = [1,2,3,4]
输出：[2,1,4,3]
示例 2：

输入：head = []
输出：[]
示例 3：

输入：head = [1]
输出：[1]

 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}

    ListNode* addNode(int val) {
        this->next = new ListNode();
        this->next->val = val;
        this->next->next = nullptr;
        return this->next;
    }
};



class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode *pNewHead = head->next;
        ListNode *pCur = head;
        ListNode *pPrev= nullptr;
        while (pCur != nullptr) {
            ListNode *pNext = pCur->next;
            if (pNext == nullptr) {
                break;
            }
            if (pPrev != nullptr) {
                pPrev->next = pNext;
            }
            ListNode *pNewNext = pNext ->next;
            pNext->next = pCur;
            pCur->next = pNewNext;
            pPrev = pCur;
            pCur = pNewNext;
        }

        return pNewHead;
        
    }
};

