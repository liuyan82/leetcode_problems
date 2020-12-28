/**
* 5. 最长回文子串
* 给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。
* 
* 示例 1：
* 
* 输入: "babad"
* 输出: "bab"
* 注意: "aba" 也是一个有效答案。
* 示例 2：
* 
* 输入: "cbbd"
* 输出: "bb"
**/ 

#include <string>
#include <iostream>

using namespace std;

class Solution {
public:
    string longestPalindrome(const string &s) const {
        int longestStart = -1, longestEnd = -1;
        for (int end = s.size() - 1; end >= 0; --end) {
            if (longestEnd - longestStart + 1 > end + 1) {
                break;
            }
            int currentEnd = end;
            int matchStart = -1;
            int start = 0;
            while(start <= currentEnd){
                if (s[start] != s[currentEnd]) {
                    cout << "s[" << start << "] != s[" << currentEnd << "]" << endl;
                    if (matchStart >= 0) {
                        start = matchStart + 1;
                        currentEnd = end;
                        matchStart = -1;
                    } else {
                        start++;
                    }
                    continue;
                } else {
                    if (matchStart < 0) {
                        matchStart = start;
                    } 
                    cout << "s[" << start << "] == s[" << currentEnd << "]" << endl;
                    cout << "matchstart: " << matchStart << endl;

                    if (start == currentEnd || currentEnd - start == 1) {
                        if (end - matchStart  > longestEnd - longestStart || longestStart < 0) {
                            longestEnd = end;
                            longestStart = matchStart;
                            cout << "find : " << longestStart << " ~ " << longestEnd << endl;
                        }
                        break;
                    }
                    start++;
                    currentEnd--;
                }
            }
        }

        if (longestEnd >= 0 && longestStart >= 0 && longestEnd >= longestStart) {
            return s.substr(longestStart, longestEnd - longestStart + 1);
        } else {
            return "";
        }
    }
private:
};

int main(int argc, const char** argv) {
    string testCase = "a";
    Solution sol;
    cout << sol.longestPalindrome(testCase) << endl;
    return 0;
}
