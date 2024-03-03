
#include <string>
#include <vector>

/**
 * @brief build Partial Match Table
 * @return Partial Match Value for First i letters
 */
std::vector<int> buildPmt(std::string &&pattern) {
    std::vector<int> pmt;
    for (int i = 0; i < pattern.size(); ++i) {
        std::vector<std::string> prefix, surfix;
        for (int j = 1; j <= i; ++j) {
            prefix.push_back(pattern.substr(0, j));
        }
        for (int j = i; j > 0; --j) {
            surfix.push_back(pattern.substr(j, i - j + 1));
        }
        int pmv= 0;
        for (int j = i - 1; j >= 0; --j) {
            if (prefix[j] == surfix[j]) {
                pmv = prefix[j].size();
                break;
            }
        }
        pmt.push_back(pmv);
    }
    return pmt;
}

int main(int argc, const char** argv) {
    buildPmt("abcdabd");
}