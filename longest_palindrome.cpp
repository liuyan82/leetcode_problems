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
        return dpAlgorithm(s);
    }
private:
    string wildSolution(const string &s) const {
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
    inline string dpAlgorithm(const string &str) const {
        unsigned char *dp = new unsigned char[str.size() * str.size()];
        int currentLongestStart = 0;
        int currentLongestLen = 0;
        for (int len = 1; len <= str.size(); ++len) {
            for (int s = 0; s <= str.size() - len; ++s) {
                int e = s + len - 1;
                cout << "calc dp[" << s <<"][" << e << "]" << endl;
                if (len == 1) {
                    // 一个字符的子串肯定是回文
                    dp[s * str.size() + e] = 1;
                    cout << "dp[" << s <<"][" << e << "] = 1" << endl;
                    if (currentLongestLen < len) {
                        currentLongestStart = s;
                        currentLongestLen = len;
                    }
                } else if (len == 2){
                    if (str[s] == str[e]) {
                        if (currentLongestLen < len) {
                            currentLongestStart = s;
                            currentLongestLen = len;
                        }
                        dp[s * str.size() + e] = 1;
                        cout << "dp[" << s <<"][" << e << "] = 1" << endl;
                    } else {
                        dp[s * str.size() + e] = 0;
                        cout << "dp[" << s <<"][" << e << "] = 0" << endl;
                    }

                } else {
                    cout << "dp[" << s + 1 << "][" << e - 1 << "] = " << (int)(dp[(s + 1) * str.size() + e - 1]) << endl;
                    cout << "str[" << s << "]=" << str[s] << ", str[" << e << "]=" << str[e] << endl;
                    if (dp[(s + 1) * str.size() + e - 1] == 1 && str[s] == str[e]) {
                        dp[s * str.size() + e] = 1;
                        cout << "dp[" << s <<"][" << e << "] = 1" << endl;
                        if (currentLongestLen < len) {
                            currentLongestStart = s;
                            currentLongestLen = len;
                        }
                    } else {
                        dp[s * str.size() + e] = 0;
                        cout << "dp[" << s <<"][" << e << "] = 0" << endl;
                    }
                }
            }
        }
        return str.substr(currentLongestStart, currentLongestLen);
    }
};

int main(int argc, const char** argv) {
    string testCase = "a";
    Solution sol;
    cout << sol.longestPalindrome(testCase) << endl;
    return 0;
}
