/**
 * 
给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。

k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。

你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。



来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/reverse-nodes-in-k-group
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 
 */

#include <vector>
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *pNewHead = nullptr;
        ListNode *pPrev = nullptr;
        ListNode *pCur = head;
        while(pCur != nullptr) {
            int i = 1;
            ListNode *pGroupHead = pCur;
            ListNode *pGroupTail = pCur;
            for (; i < k; ++i) {
                if (pGroupTail != nullptr) {
                    pGroupTail = pGroupTail->next;
                }
            }
            if (i < k || pGroupTail == nullptr) {
                if (pNewHead == nullptr) {
                    pNewHead = pGroupHead;
                }
                if (pPrev != nullptr) {
                    pPrev->next = pGroupHead;
                }

                break;
            }

            pCur = pGroupTail->next;

            ListNode *pGroupCurrent = pGroupHead;
            ListNode *pGroupNext = pGroupHead->next;
            while (pGroupCurrent != pGroupTail) {
                ListNode *pNewGroupNext = pGroupNext->next;
                pGroupNext->next = pGroupCurrent;
                pGroupCurrent = pGroupNext;
                pGroupNext = pNewGroupNext;
            }

            if (pNewHead == nullptr) {
                pNewHead = pGroupCurrent;
            }
            if (pPrev != nullptr) {
                pPrev->next = pGroupCurrent;
            }
            pPrev = pGroupHead;
            pGroupHead->next = nullptr;
        }

        if (pNewHead == nullptr) {
            return head;
        }
        return pNewHead;
    }
};



void printLink(ListNode *pHead) {
    std::cout << "[";
    for (ListNode *pNode = pHead; pNode != nullptr; pNode = pNode->next) {
        std::cout << pNode->val << ", "; 
    }

    std::cout << "]" << std::endl;
}

void test1(std::vector<int> &&ary, int k) {
    ListNode *pHead = new ListNode(ary.front());
    ListNode *pNode = pHead;
    for (auto it = ary.begin() + 1; it != ary.end(); ++it) {
        pNode = pNode ->addNode(*it);
    }
    printLink(pHead);
    Solution sol;
    printLink(sol.reverseKGroup(pHead, k));
    
}

int main(int argc, const char ** argv) {
    // test1({1,2,3,4,5}, 2);
    // test1({1,2,3,4,5}, 3);
    test1({1,2}, 2);
    return 0;
} 