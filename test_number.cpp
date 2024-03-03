
#include <stdio.h>
#include <utility>

void printHex(int number) {
    printf("%d : 0x%08X\n", number, number);
}

int complement(int number) {
    return (~number + 1);
}

void testInteger() {
    printHex(-1000);
    printHex(1000 << 1);
}
/**
 * @brief 
 * multiply of a and b, params must be positive numbers
 * @param a 
 * @param b 
 * @return int 
 */
int mul(int a, int b) {
    int res = 0;
    for (int i = 0; i < 31; ++i) {
        if ((b & (1 << i)) != 0) {
            res += (a << i);
        }
    }
    return res;
}

void testMultiply(int a, int b) {
    printf("%d x %d = %d (%d)\n", a, b, a * b, mul(a, b));
}

/**
 * @brief 
 * division of a and b, params must be positive numbers
 * @param a 
 * @param b 
 * @return int 
 */
std::pair<int, int> div(int a, int b) {
    int res = 0, left = 0;
    for (int i = 30; i >= 0; --i) {
        left = (left << 1) + ((a >> i) & 1);
        res = res << 1;
        if (left >= b) {
            res += 1;
            left = left - b;
        } 
    }
    return std::make_pair(res, left);
}

void testDiv(int a, int b) {
    std::pair<int, int> res = div(a, b);
    printf("%d / %d = %d ... %d (%d ... %d)\n", a, b, a / b, a%b, res.first, res.second);
}

int main(int argc, const char **argv) {
    testMultiply(5, 10);
    testMultiply(12, 5);
    testMultiply(15, 15);

    testDiv(10, 5);
    testDiv(15, 4);
    
    return 0;
}