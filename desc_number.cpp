#include <string>

using namespace std;
class Solution {
public:
    
    string countAndSay(int n) {
        constexpr unsigned char kInvalid = (unsigned char) -1;
        int last_number = 1;
        for (int i = 2; i <= n; ++i) {
            unsigned char digit = kInvalid;
            unsigned char count = 0;
            int left_number = last_number;
            int desc_number = 0;
            int current_bitcount = 0;
            while (left_number > 0) {
                unsigned char current_digit = (left_number % 10);
                if (current_digit == digit) {
                    ++count;
                } else {
                    if (digit != kInvalid) {
                        int bit_count = 1;
                        while(count / (int)std::pow(10, bit_count) > 0) { ++bit_count; }
                        
                        if (desc_number == 0) {
                          desc_number = count * (int)std::pow(10, bit_count) + digit;
                          current_bitcount = bit_count + 1;
                        } else {
                          desc_number = (count * (int)std::pow(10, bit_count) + digit) * (int)std::pow(10, current_bitcount) + desc_number;
                          current_bitcount += bit_count + 1;
                        }
                    }
                    digit = current_digit;
                    count = 1;
                }
                left_number = left_number / 10;
            }

            if (digit != kInvalid) {
              int bit_count = 1;
              while(count / (int)std::pow(10, bit_count) > 0) { ++bit_count; }

              if (desc_number == 0) {
                desc_number = count * (int)std::pow(10, bit_count) + digit;
                current_bitcount = bit_count + 1;
              } else {
                desc_number = (count * (int)std::pow(10, bit_count) + digit) * (int)std::pow(10, current_bitcount) + desc_number;
                current_bitcount += bit_count + 1;
              }
            }

            last_number = desc_number;
        }
        return std::to_string(last_number);
    }
};


class Solution2 {
public:
    
    string countAndSay(int n) {
        constexpr char kInvalid = (char) -1;
        std::string last_number = "1";
        for (int i = 2; i <= n; ++i) {
            char digit = kInvalid;
            unsigned short count = 0;
            unsigned short pos = 0;
            std::string desc_number;
            while (pos < last_number.size()) {
                char current_digit = last_number.at(pos);
                if (current_digit == digit) {
                    ++count;
                } else {
                    if (digit != kInvalid) {
                        desc_number.append(std::to_string(count));
                        desc_number.append(1, digit);
                    }
                    digit = current_digit;
                    count = 1;
                }
                pos++;
            }

            if (digit != kInvalid) {
                desc_number.append(std::to_string(count));
                desc_number.append(1, digit);
            }

            last_number = desc_number;
        }
        return last_number;
    }
};

int main(int argc, const char** argv) {
  Solution2 sol;
  sol.countAndSay(21);
  return 0;
}