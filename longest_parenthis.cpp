#include <deque>
#include <string>
#include <iostream>

/**
给你一个只包含 '(' 和 ')' 的字符串，找出最长有效（格式正确且连续）括号
子串
的长度。

 

示例 1：

输入：s = "(()"
输出：2
解释：最长有效括号子串是 "()"
示例 2：

输入：s = ")()())"
输出：4
解释：最长有效括号子串是 "()()"
示例 3：

输入：s = ""
输出：0
 

提示：

0 <= s.length <= 3 * 104
s[i] 为 '(' 或 ')'
**/

using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        /**
         *An Example:
            index:  0  1  2   3  4  5  6  7  8  9 10  11
            string: (  (  )   )  (  (  (  )  (  (  )  )
        trace back: -1 -1 1   0  -1 -1 -1 6  -1 -1 9  8
         */

        // 当前最长的合法括号串
        int max_length = 0;
        
        // 记录每个右括号对应左括号的位置，以便回溯
        std::vector<int> matched_left_pos;

        // 左括号位置
        std::deque<int> unmatched_left_pos; 

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == ')') {
                if (unmatched_left_pos.size() == 0) {
                    // 无论如何都连不上了
                    matched_left_pos.push_back(-2);
                    continue;
                } else {
                    int left_pos = unmatched_left_pos.front();
                    std::cout << i << " match " << left_pos << std::endl;
                    unmatched_left_pos.pop_front();
                    matched_left_pos.push_back(left_pos);

                    // 回溯
                    for (;left_pos > 0;) {
                        int next_left_pos = matched_left_pos.at(left_pos - 1);
                        if (next_left_pos >= 0) {
                            left_pos = next_left_pos;
                        }

                        if (next_left_pos <= 0) {
                            break;
                        }
                    }
                    if (i - left_pos + 1 > max_length) {
                        max_length = i - left_pos + 1;
                    }
                }
            }

            if (s[i] == '(') {
                std::cout << "push " << i << std::endl;
                unmatched_left_pos.push_front(i);
                matched_left_pos.push_back(-1);
            }
        }
        return max_length;
    }

};



int main(int argc, const char** argv) {
    Solution sol;
    std::cout << sol.longestValidParentheses("(()") << std::endl;
    return 0;
}
