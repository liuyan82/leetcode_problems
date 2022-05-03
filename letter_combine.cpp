/**
给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
示例 1：

输入：digits = "23"
输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
示例 2：

输入：digits = ""
输出：[]
示例 3：

输入：digits = "2"
输出：["a","b","c"]
 

提示：

0 <= digits.length <= 4
digits[i] 是范围 ['2', '9'] 的一个数字。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 */

#include <vector>
#include <string>
#include <iostream>

class Solution {
private:
    static constexpr char const * const sLetters [] = {nullptr, nullptr, "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

public:
    std::vector<std::string> letterCombinations(const std::string &digits) {
        std::vector<std::string> res;
        for (auto it = digits.begin(); it != digits.end(); ++it) {
            int digit = *it - '0';
            std::vector<std::string> currentLayer;
            if (res.empty()) {
                currentLayer = traverse("", digit);
            } else {
                for (auto prefixIt = res.begin(); prefixIt != res.end(); ++prefixIt) {
                    std::vector<std::string> x = traverse(*prefixIt, digit);
                    currentLayer.insert(currentLayer.end(), x.begin(), x.end());
                } 
            }
            res = currentLayer;
        }
        return res;
    }

private:
    std::vector<std::string> traverse(const std::string &prefix, int num) {
        const char* letters = sLetters[num];
        std::vector<std::string> res;
        if (letters == nullptr ) {
            if (!prefix.empty()) {
                res.push_back(prefix);
            }
            return res;
        }
        
        for (const char *pch = letters; *pch != '\0'; ++pch) {
            res.push_back(prefix + *pch);
        }
        return res;
    }
};

void test(const std::string &input) {
    Solution sol;
    std::vector<std::string> res = sol.letterCombinations(input);
    std::cout << "[";
    for (auto it = res.begin(); it != res.end(); ++it) {
        std::cout << *it << ", ";
    }
    std::cout << "]" << std::endl;
}

int main(int argc, const char** argv) {
    test("23");
    test("");
    test("2");

    return 0;
}