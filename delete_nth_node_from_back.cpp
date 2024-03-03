/**
 * 给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。@brief 
 * 
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 * 
 *输入：head = [1,2,3,4,5], n = 2
输出：[1,2,3,5]
示例 2：

输入：head = [1], n = 1
输出：[]
示例 3：

输入：head = [1,2], n = 1
输出：[1]

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/remove-nth-node-from-end-of-list
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 
 */

#include <iostream>


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
        ListNode* removeNthFromEnd(ListNode* head, int n) {
            m_pBufferQueue = new ListNode*[n + 1];
            start = 0;
            end = 0;
            num = n + 1;
            full = false;

            for (ListNode *pNode = head; pNode != nullptr; pNode = pNode->next) {
                push(pNode);
            }

            if (full) {
                ListNode* pReverseNthNodeParent = m_pBufferQueue[start % num];
                ListNode* pReverseNthNode = m_pBufferQueue[(start + 1) % num];
                pReverseNthNodeParent->next = pReverseNthNode->next;
                return head;
            } else if (end - start == n) {
                ListNode* pReverseNthNode= m_pBufferQueue[start % num];
                return pReverseNthNode->next;
            } else {
                return nullptr;
            }
        }

    private:
        void push(ListNode *pNode) {
            if (full) {
                start++;
            }
            int index = end++ % num;
            if (!full && end - start >= num) {
                full = true;
            }
            
            m_pBufferQueue[index] = pNode;
            std::cout << "Put " << pNode->val << " at " << end - 1 << "(" << index << "), queue is from " <<  start << " to " << end << std::endl;
        }

    private:
        int start;
        int end;
        int num;
        bool full;
        
        ListNode **m_pBufferQueue;

};

void printLink(ListNode *pHead) {
    std::cout << "[";
    for (ListNode *pNode = pHead; pNode != nullptr; pNode = pNode->next) {
        std::cout << pNode->val << ", "; 
    }

    std::cout << "]" << std::endl;
}

void testCase1() {
    ListNode *pHead = new ListNode();
    pHead->val = 1;
    pHead->addNode(2)->addNode(3)->addNode(4)->addNode(5);
    // printLink(pHead);
    Solution sol;
    ListNode *pNewHead = sol.removeNthFromEnd(pHead, 2);
    printLink(pNewHead);
}

void testCase2() {
    ListNode *pHead = new ListNode();
    pHead->val = 1;
    // printLink(pHead);
    Solution sol;
    ListNode *pNewHead = sol.removeNthFromEnd(pHead, 1);
    printLink(pNewHead);
}

void testCase3() {
    ListNode *pHead = new ListNode();
    pHead->val = 1;
    pHead->addNode(2);
    // printLink(pHead);
    Solution sol;
    ListNode *pNewHead = sol.removeNthFromEnd(pHead, 2);
    printLink(pNewHead);
}

int main(int argc, const char** argv) {
    // testCase1();
    // testCase2();
    testCase3();
    return 0;
}