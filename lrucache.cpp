#include <iostream>

class LRUCache {
private:
    typedef struct _Node {
        int iKey;
        int iValue;
        int iSlot;

        struct _Node *pNext;
        struct _Node *pPrev;
    } Node;
public:
    LRUCache(int capacity)
    : miCapacity(capacity), pIndex(new Node*[capacity]), pHead(nullptr), pTail(nullptr) {
        miSize = 0;
        for (int i = 0; i < capacity; ++i) {
            pIndex[i] = nullptr;
        }
    }

    int get(int key) {
        Node* pResult = findNode(key);
        if (pResult != nullptr) {
            moveToTail(pResult);
            //std::cout << "get:" << key << "->" << pResult->iValue << std::endl;
            dump();
            return pResult->iValue;
        } else {
            //std::cout << "get:" << key << "->" << -1 << std::endl;
            dump();
            return -1;
        }
    }

    void put(int key, int value) {
        //std::cout << "put:" << key << "->" << value << std::endl;

        Node *pResult = findNode(key);
        if (pResult != nullptr) {
            pResult->iValue = value;
            moveToTail(pResult);
            dump();
            return;
        }

        if (miSize >= miCapacity) {
            if (pHead->iSlot >= 0) {
                pIndex[pHead->iSlot] = nullptr;
            }
            pHead = pHead->pNext;
            if (pHead != nullptr) {
                pHead->pPrev = nullptr;
            }
        } else {
            miSize++;
        }

        Node *newNode = new Node;
        newNode->iKey = key;
        newNode->iValue = value;

        int iSlot = key % miCapacity;
        if (pIndex[iSlot] == nullptr) {
            pIndex[iSlot] = newNode;
            newNode->iSlot = iSlot;
        } else {
            newNode->iSlot = -1;
        }

        if (pHead == nullptr) {
            newNode->pPrev = newNode->pNext = nullptr;
            pHead = pTail = newNode;
        } else {
            newNode->pPrev = pTail;
            newNode->pNext = nullptr;
            pTail->pNext = newNode;
            pTail = newNode;
        }
        dump();
    }

private:
    Node* findNode(int key) {
        Node* guess = pIndex[key % miCapacity];
        if (guess == nullptr || guess->iKey != key) {
            for(guess = pHead; guess != nullptr; guess = guess->pNext) {
                if (guess->iKey == key) {
                    break;
                }
            }
        }

        if (guess != nullptr && guess->iKey == key) {
            return guess;
        }

        return nullptr;
    }

    void moveToTail(Node* pNode) {
        if (pTail != pNode) {
            //std::cout << "move to tail:" << pNode->iKey << "->" << pNode->iValue << std::endl;
                if (pNode->pPrev != nullptr) {
                    pNode->pPrev->pNext = pNode->pNext;
                    if (pNode->pNext != nullptr) {
                        pNode->pNext->pPrev = pNode->pPrev;
                    }
                } else if (pNode->pNext != nullptr) {
                    pNode->pNext->pPrev = nullptr;
                    pHead = pNode->pNext;
                }
                pTail->pNext = pNode;
                pNode->pPrev = pTail;
                pNode->pNext = nullptr;
                pTail = pNode;
            }
    }

    void dump(){
        //for (Node *pNode = pHead; pNode != nullptr; pNode = pNode->pNext) {
        //    std::cout << pNode->iKey << "->" << pNode->iValue << " : ";
        //}
        //std::cout << std::endl;
    }

private:

    Node *pHead;
    Node *pTail;

    int miCapacity;
    int miSize;

    Node **pIndex;
};

int main(int argc, const char ** argv) {
    return 0;
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
