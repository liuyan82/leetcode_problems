/**
 * 罗马数字包含以下七种字符： I， V， X， L，C，D 和 M。

字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
例如， 罗马数字 2 写做 II ，即为两个并列的 1。12 写做 XII ，即为 X + II 。 27 写做  XXVII, 即为 XX + V + II 。

通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：

I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。 
C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
给你一个整数，将其转为罗马数字。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/integer-to-roman
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <string>

void addNumbers(std::string &roman, int n, char ten, char fifty, char one) {
    if (n < 4) {
        for (int i = 0; i < n; ++i) {
            roman.push_back(one);
        }
    } else if (n == 4) {
        roman.push_back(one);
        roman.push_back(fifty);
    } else if (n < 9) {
        roman.push_back(fifty);
        for (int i = 0; i < n - 5; ++i) {
            roman.push_back(one);
        }
    } else {
        roman.push_back(one);
        roman.push_back(ten);
    }
}

std::string toRomanNumber(int num) {
    int iThousands = num / 1000;
    int iHandreds = (num % 1000) / 100;
    int iTens = (num % 100) / 10;
    int i = (num % 10);

    std::string romanNumber;
    for (int i = 0; i < iThousands; ++i) {
        romanNumber.push_back('M');
    }


    addNumbers(romanNumber, iHandreds, 'M', 'D', 'C');
    addNumbers(romanNumber, iTens, 'C', 'L', 'X');
    addNumbers(romanNumber, i, 'X', 'V', 'I');
    
    return romanNumber;
    
}

    int getNumber(char ch) {
        switch(ch) {
            case 'I':return 1;
            case 'V':return 5;
            case 'X':return 10;
            case 'L':return 50;
            case 'C':return 100;
            case 'D':return 500;
            case 'M':return 1000;
            default: return -1;
        }
    }

    int romanToInt(std::string s) {
        int total = 0;
        int last = -1;
        for (char ch : s) {
            int n = getNumber(ch);
            if (last > 0 && last < n) {
                total += (n - last - last);
                last = -1;
            } else {
                total += n;
                last = n;
            }
        }
        return total;
    }

int main(int argc, const char ** argv) {
    std::cout << 3 << " : " << toRomanNumber(3) << " : " << romanToInt(toRomanNumber(3)) << std::endl;
    std::cout << 4 << " : " << toRomanNumber(4)  << " : " << romanToInt(toRomanNumber(4)) << std::endl;
    std::cout << 9 << " : " << toRomanNumber(9)  << " : " << romanToInt(toRomanNumber(9)) << std::endl;
    std::cout << 58 << " : " << toRomanNumber(58)  << " : " << romanToInt(toRomanNumber(58)) << std::endl;
    std::cout << 1994 << " : " << toRomanNumber(1994)  << " : " << romanToInt(toRomanNumber(1994)) << std::endl;


    return 0;
}
