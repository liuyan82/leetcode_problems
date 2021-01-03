/**
 7. 整数反转
给出一个 32 位的有符号整数，你需要将这个整数中每位上的数字进行反转。

示例 1:

输入: 123
输出: 321
 示例 2:

输入: -123
输出: -321
示例 3:

输入: 120
输出: 21
注意:

假设我们的环境只能存储得下 32 位的有符号整数，则其数值范围为 [−2^31,  2^31 − 1]。请根据这个假设，如果反转后整数溢出那么就返回 0。*
 */

#include <iostream>
#include <math.h>
class Solution {
public:
    int reverse(int x) {
        int max = pow(2, 30);
        max += max - 1;
        int min = -max - 1;
         
        int result = 0;
        int base0 = 10;
        for (int i = 1; ;i++) {
            // 当达到最高位时，pow(10, i )超过max int，所以先除以一个10
            int base = (int)pow(10, i - 1); 
            int left = (x / base) % base0 ;
            bool finished = (x / base / base0) == 0;
            if (x > 0 && max / base / base0 == 0 || x < 0 && min / base / base0 == 0) {
                // 超过了最大值或最小值了
                if (!finished) {
                    return 0;
                } else {
                    if (x > 0) {
                        int temp = max / 10;
                        if (result > temp || result == temp && left > max % 10) {
                            return 0;
                        } 
                    } else if (x < 0) {
                        int temp = min / 10;
                        if (result < temp || result == temp && left < min % 10) {
                            return 0;
                        }
                    }
                }
            }

            result = result * 10 + left;
            if (finished) {
                break;
            }
            
        }
        return result;
    }
};

#include <limits>

int main(int argc, const char ** argv) {
    Solution sol;
    int num = 1534236469;
    int res = sol.reverse(num);
    std::cout << num << " => "  << res << std::endl;;
}
