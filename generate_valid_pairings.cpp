/**
 * @file generate_valid_pairings.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-19
 * 
 * @copyright Copyright (c) 2022
 
 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。


示例 1：

输入：n = 3
输出：["((()))","(()())","(())()","()(())","()()()"]
示例 2：

输入：n = 1
输出：["()"]
 

提示：

1 <= n <= 8


来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/generate-parentheses
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*
 *  
 */

#include <string>
#include <vector>
#include <deque>
#include <iostream>

class Solution {
public:
    std::vector<std::string> generateParenthesis(int n) {
        // n-th layer has 2^n nodes
        // start from zero, even nodes is left parenthese, odd node is right parenthese
        // if nlefts == nrights, no right parenthese allowed
        // use Deep-First-Search
        std::vector<std::string> results;
        traverseNode(2 * n, 0, 0, 0, 0, "", results);
        return results;
    }

private:
    /**
     * @brief 
     * 
     * @param maxLayer 
     * @param layer 
     * @param node 
     * @param nLefts 
     * @param nRights 
     * @param str 
     * @return int   -1 中断； 0 ： 继续； 1: 结束
     */
    int traverseNode(const int maxLayer, const int layer, const int node, 
                const int nLefts, const int nRights, const std::string &str, std::vector<std::string> &results) {
        char ch = node % 2 == 0 ? '(' : ')';
        if (nLefts <= nRights && ch == ')') {
            return -1;
        } 
        if (nLefts > maxLayer / 2) {
            return -1;
        }
         
        if (layer == maxLayer) {
            results.push_back(str);
            return 1;
        }

        std::string newstr = str + ch;
        
        int nextNLefts = (ch == '(' ? nLefts + 1 : nLefts);
        int nextNRights =  (ch == ')' ? nRights + 1 : nRights);
        // 上层的节点n，在下层的子节点为2 * n 和 2 * n + 1
        traverseNode(maxLayer, layer + 1, 2 * node, nextNLefts, nextNRights, newstr, results);
        traverseNode(maxLayer, layer + 1, 2 * node + 1, nextNLefts, nextNRights, newstr, results);
        return 0;
    }

    bool validParenthese(std::string s) {
        if (s.size() % 2 != 0) {
            return false;
        }

        std::deque<char> mStack;
        for (size_t i = 0; i < s.size(); ++i) {
            char ch = s[i];
            if (ch == ')' || ch == ']' || ch == '}') {
                if (mStack.empty()) {
                    return false;
                } else {
                    char prev = mStack.front();
                    mStack.pop_front();
                    if (!(ch == ')' && prev == '('
                        || ch == ']' && prev == '['
                        || ch == '}' && prev == '{')) {
                        return false;
                    }
                }
            } else {
                mStack.push_front(ch);
            }
        }

        return mStack.empty();
    }
};

int main(int argc, const char** argv) {
    Solution sol;
    std::vector<std::string> res = sol.generateParenthesis(3);
    for (std::string str : res) {
        std::cout << str << std::endl;
    }
    return 0;
}

