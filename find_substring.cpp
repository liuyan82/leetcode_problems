/**
30. 串联所有单词的子串
给定一个字符串 s 和一些 长度相同 的单词 words 。找出 s 中恰好可以由 words 中所有单词串联形成的子串的起始位置。

注意子串要与 words 中的单词完全匹配，中间不能有其他字符 ，但不需要考虑 words 中单词串联的顺序。

示例 1：

输入：s = "barfoothefoobarman", words = ["foo","bar"]
输出：[0,9]
解释：
从索引 0 和 9 开始的子串分别是 "barfoo" 和 "foobar" 。
输出的顺序不重要, [9,0] 也是有效答案。

示例 2：

输入：s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
输出：[]

示例 3：

输入：s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
输出：[6,9,12]

 */

#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <map>

class Solution {
public:
    std::vector<int> findSubstring(std::string s, std::vector<std::string>& words) {
        // the index is token number, which is the index of a single word in 'words'
        // the value (std::vector<int>) is the start indeices where the word appear in s
        std::vector<int> *pTokenAppear = new std::vector<int>[words.size()];
        std::map<int, std::vector<int> > matchedToken;
        bool hasEmptyMatch = false;
        for (size_t k = 0; k < words.size(); ++k) {
            const std::string &pattern = words[k];
            std::vector<int> pmt = buildPmt(pattern);

            int matchLength = -1;
            for (size_t i = 0; i <= s.length() - pattern.length(); ) {
                for (size_t j = 0; j < pattern.length(); ++j, ++i) {
                    if (s[i] == pattern[j]) {
                        matchLength = j;
                    }
                    else {
                        break;
                    }
                }

                // full match
                if (matchLength == pattern.length() - 1) {
                    int matchPos = i - pattern.length();
                    pTokenAppear[k].push_back(matchPos);
                    matchedToken[matchPos].push_back(k);
                }
                i = matchLength >= 0 ? (i - pmt[matchLength]) : i + 1;
                matchLength = -1;
            }
            if (pTokenAppear[k].empty()) {
                hasEmptyMatch = true;
                break;
            }
        }

        printMatchResult(pTokenAppear, words, matchedToken);
        std::vector<int> res;

        return res;
    }

private:

    /**
     * @brief 
     * matches的key就是在字符串中匹配的位置，并且是已经排好序的了
     * @param matches 
     * @param tokenLen 
     */
    void searchForResult(std::map<int, std::vector<int> > &matches, int tokenLen) {
        int lastIndex = -1;
        for (auto it = matches.begin(); it != matches.end(); ++it) {
            auto startIt = it;
            
        }
    }

    void traverseSolutions(std::vector<int> *pTokenAppear, size_t tokenCount, size_t tokenLength, size_t strLen) {
        for (int i = 0; i < tokenCount; ++i) {
            for (int j = 0; j < pTokenAppear[i][0]; ++j) {
                int index = pTokenAppear[i][j];
                if (index + tokenLength * tokenCount > strLen) {
                    break;
                }
            }
        }
    }

    void traverseSolutions(std::vector<int> *pTokenAppear, size_t tokenCount, size_t tokenLength, size_t strLen, int iCurToken, int iCurIndex) {
    }

    void printMatchResult(std::vector<int> *pTokenAppear, const std::vector<std::string> &words, std::map<int, std::vector<int> > &matchedToken) {
        for (int i = 0; i < words.size(); ++i) {
            std::cout << "Matching for : [" << words[i] << "]: [";
            for (auto it = pTokenAppear[i].begin(); it != pTokenAppear[i].end(); ++it) {
                std::cout << *it << ',';
            }
            std::cout << ']' << std::endl;
        }

        for (auto it = matchedToken.begin(); it != matchedToken.end(); ++it) {
            std::cout << "Start at : [" << it->first << "]: [";
            for (int tokenId : it->second) {
                std::cout << tokenId << ", ";
            }
            std::cout << ']' << std::endl;
        }
    }

    std::vector<int> buildPmt(const std::string &pattern) {
        std::vector<int> pmt;
        for (int i = 0; i < pattern.size(); ++i) {
            std::vector<std::string> prefix, surfix;
            for (int j = 1; j <= i; ++j) {
                prefix.push_back(pattern.substr(0, j));
            }
            for (int j = i; j > 0; --j) {
                surfix.push_back(pattern.substr(j, i - j + 1));
            }
            int pmv= 0;
            for (int j = i - 1; j >= 0; --j) {
                if (prefix[j] == surfix[j]) {
                    pmv = prefix[j].size();
                    break;
                }
            }
            pmt.push_back(pmv);
        }
        return pmt;
    }
};

void test(std::string && str, std::vector<std::string> && words) {
    Solution sol;
    sol.findSubstring(str, words);
}

int main(int argc, const char ** argv) {
    test("barfoothefoobarman", {"foo","bar"});
    std::cout << "------------" << std::endl;
    test("wordgoodgoodgoodbestword", {"word","good","best","word"});
    std::cout << "------------" << std::endl;
    test("barfoofoobarthefoobarman", {"bar","foo","the"});
    return 0;
}
