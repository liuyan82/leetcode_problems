/*****
6. Z 字形变换
将一个给定字符串根据给定的行数，以从上往下、从左到右进行 Z 字形排列。

大概像下图这样
        
        |      |     |
        |    / |   / | 
        .....................................
        | /    | /   |
        |      |     |



比如输入字符串为 "LEETCODEISHIRING" 行数为 3 时，排列如下：

L   C   I   R
E T O E S I I G
E   D   H   N
之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："LCIRETOESIIGEDHN"。

请你实现这个将字符串进行指定行数变换的函数：

string convert(string s, int numRows);
示例 1:

输入: s = "LEETCODEISHIRING", numRows = 3
输出: "LCIRETOESIIGEDHN"
示例 2:

输入: s = "LEETCODEISHIRING", numRows = 4
输出: "LDREOEIIECIHNTSG"
解释:

L     D     R
E   O E   I I
E C   I H   N
T     S     G
********/

#include <string>
#include<iostream>

using namespace std;

class Solution {
public:
    string convert(const string& s, int numRows) {
        int sections= s.size() / (numRows + numRows - 2);
        int leftOver = s.size() % (numRows + numRows - 2);
        int cols = sections * (numRows - 1) + (leftOver < numRows ? 1 : leftOver - (numRows - 1) + 1);
        string result;
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int index = getLinearIndexOfZigzag(i, j, numRows);
                cout << "(" << i << ", " << j << ") => " << index << endl;
                if (index >= 0 && index < s.size()) {
                    result.push_back(s[index]);
                }
            }
        }
        return result;
    }
private:
    inline std::pair<int, int> getZigzagIndex(int linearIndex, int trow) {
        int row = 0, col = 0;
        int section = linearIndex / (trow + trow - 2);
        int posInSection = linearIndex % (trow + trow - 2);
        if (posInSection < trow - 1) {
            row = posInSection;
            col = section * (trow - 1);
        } else {
            row = trow - 1 - (posInSection - (trow - 1));
            col = section * (trow - 1) + (posInSection - (trow - 1));
        }
        return std::pair<int, int>(row, col);
    }
    inline int getLinearIndexOfZigzag(int row, int col, int trows) {
        int section = col / (trows - 1);
        int colOffset = col - (trows - 1) * section;
        cout << "(" << row << ", " << col << ") : section: " << section << ", col offset: " << colOffset << std::endl;
        if (colOffset == 0) {
            return (trows + trows - 2) * section + row;
        } else {
            if (row !=  (trows - 1 - colOffset)) {
                return -1;
            }
            int posInSection = (colOffset == 0 ? row : trows - 1 + colOffset);
           return (trows + trows - 2) * section + posInSection;
        }
    }
};

int main(int argc, const char ** argv) {
    //string s = "LEETCODEISHIRING";
    string s = "PAYPALISHIRING";
    int  numRows = 3;
    Solution sol;
    std::cout << sol.convert(s, numRows) << endl;
    return 0;
}
