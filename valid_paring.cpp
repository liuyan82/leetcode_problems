#include <iostream>
#include <string>
#include <deque>

using namespace std;

class Solution2 {
public:
    bool isValid(string s) {
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

class SolutionWrong {
public:
    bool isValid(string s) {
        if (s.size() % 2 != 0) {
            return false;
        }
        size_t iBase = 0;
        int iLefts = 0;
        for (size_t i = 0; i < s.size(); ++i) {
            char ch = s[i];
            if (ch == ')' || ch == ']' || ch == '}') {
                iLefts --;
                if (iLefts  >= 0) {
                    char chPreviousHalf = s[iLefts + iBase];
                    if (!(ch == ')' && chPreviousHalf == '('
                        || ch == ']' && chPreviousHalf == '['
                        || ch == '}' && chPreviousHalf == '{')) {
                        return false;
                    }
                } else {
                    return false;
                }

                if (iLefts == 0) {
                    iBase = i + 1;
                }

            } else {
                iLefts += 1;
            }
        }

        return iLefts == 0;
    }
};

int main(int argc, const char ** argv) {
    Solution sol;
    sol.isValid("(([]){})");
}