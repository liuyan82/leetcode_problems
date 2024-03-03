class Solution {
public:
    /**
    * 2^31 = 2147483648
    *
    */
    int divide(int dividend, int divisor) {
        unsigned int a, b;
        bool negative = false;

        if (dividend < 0) {
            a = ~dividend;
            a += 1;
            negative = !negative;
        } else {
            a = dividend;
        }

        if (divisor < 0) {
            b = ~divisor;
            b += 1;
            negative = !negative;
        } else {
            b = divisor;
        }

        unsigned int res = 0, left = 0;
        for (int i = 31; i >= 0; --i) {
            left = (left << 1) + ((a >> i) & 1);
            res = res << 1;
            if (left >= b) {
                res += 1;
                left = left - b;
            } 
        }

        if (((res >> 31) & 1) != 0 && !negative) {
            return 0x7FFFFFFF;
        } else if (negative) {
            return (int)(~res + 1);
        } else {
            return res;
        }

    }
};