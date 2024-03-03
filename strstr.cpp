#include <vector>
#include <string>
#include <iostream>

using namespace std;
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty() || haystack == needle) {
            return 0;
        }
        std::vector<int> pmt = buildPmt(needle);
        for (auto it = haystack.begin(); it <= haystack.end() - needle.size();) {
            int matchCount = -1;
            auto it3 = it;
            for (auto it2 = needle.begin(); it2 != needle.end(); ++it2, ++it3) {
                if (*it3 == *it2) {
                    matchCount++;
                } else {
                    break;
                }
            }
            if (matchCount == needle.size()  - 1) {
                return it - haystack.begin();
            } else if (matchCount >= 0) {
                it += (matchCount + 1 - pmt[matchCount]);
            } else {
                it++;
            }
        }
        return -1;
    }
private:
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

void test(string haystack, string needle) {
    Solution sol;
    std::cout << sol.strStr(haystack, needle) << std::endl;
}

int main(int argc, const char** argv) {
    // string haystack = "hello", needle = "ll";
    // string haystack = "aaaaa", needle = "bba";
    // string haystack = "abc", needle = "c";
    string haystack = "aabaaabaaac", needle = "aabaaac";
    test(haystack, needle);
}