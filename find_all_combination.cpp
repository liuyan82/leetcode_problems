#include <string.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    void ResetBit(int *p_bit_map, int p_index) {
        int num = p_index / sizeof(int);
        int offset = p_index % sizeof(int);
        int mask = 1;
        mask = ~(mask << (offset));
        p_bit_map[num] &= mask;
    }

    void SetBit(int *p_bit_map, int p_index) {
        int num = p_index / sizeof(int);
        int offset = p_index % sizeof(int);
        int mask = 1;
        mask = mask << (offset);
        p_bit_map[num] |= mask;
    }

    bool GetBit(int *p_bit_map, int p_index) {
        int num = p_index / sizeof(int);
        int offset = p_index % sizeof(int);
        int mask = 1;
        mask = mask << (offset);
        return (p_bit_map[num] & mask) != 0;
    }

    /**
     * 判断是否是一个全拼接串
     **/
     vector<int> findSubstring(string s, vector<string>& words) {
        int kLen = words.size() * words[0].size();
        int bit_map_count = words.size() / sizeof(int) + 1;
        int *bit_map = new int[bit_map_count];
        
        std::vector<int> res;

        if (s.size() < kLen || words.empty()) {
            delete[] bit_map;
            bit_map = nullptr;
            return res;
        }

        for (int i = 0; i <= s.size() - kLen; ++i) {
            std::cout << "begin from " << i << std::endl;
            memset(bit_map, 0, bit_map_count * sizeof(int));
            bool found_match = false;

            for (int current_word = i; current_word < i + kLen; current_word += words[0].size()) {
                for (int j = 0; j < words.size(); ++j) {
                    if (GetBit(bit_map, j)) {
                        std::cout << "used: " << j << std::endl;
                        continue;
                    }

                    if (s.substr(current_word, words[j].size()) == words[j]) {
                        SetBit(bit_map, j);
                        found_match = true;
                        std::cout << "match " << words[j] << " from " << i << " : " << current_word << std::endl;
                        break;
                    } else {
                        std::cout << "not match " << words[j] << " from " << i << " : " << current_word << std::endl;
                        found_match = false;
                    }
                }

                if (!found_match) {
                    break;
                }
            }

            if (found_match) {
                res.push_back(i);
            }

        }

        delete[] bit_map;
        bit_map = nullptr;
        return res;
    }

};

int main(int argc, const char** argv) {
    Solution sol;
    std::vector<std::string> words = {"foo","bar"};
    std::string s = "barfoothefoobarman";
    std::vector<int> res = sol.findSubstring(s, words);
    std::cout << "res: [";
    for (int pos : res) {
        std::cout << pos << ", ";
    }
    std::cout << "]" << std::endl;
    return 0;
}



