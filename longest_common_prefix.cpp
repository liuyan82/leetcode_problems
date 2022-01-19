/**
 *
编写一个函数来查找字符串数组中的最长公共前缀。
如果不存在公共前缀，返回空字符串 ""。
 

示例 1：

输入：strs = ["flower","flow","flight"]
输出："fl"
示例 2：

输入：strs = ["dog","racecar","car"]
输出：""
解释：输入不存在公共前缀。
 

提示：

1 <= strs.length <= 200
0 <= strs[i].length <= 200
strs[i] 仅由小写英文字母组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-common-prefix
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

#include <iostream>
#include <vector>
#include <string>

class Solution {
public:
    std::string longestCommonPrefix(std::vector<std::string>&& strs) {
        auto it = strs.begin();
        std::string commonPrefix = *it;
        for (it++; it != strs.end(); ++it) {
            int i = 0;
            for (; i < commonPrefix.size() && i < it->size(); ++i) {
                if (commonPrefix[i] != (*it)[i]) {
                    break;
                }
            }
            commonPrefix.resize(i);
            if (i == 0) {
                break;
            }
        }

        return commonPrefix;
    }
};

int main(int argc, const char ** argv) {
    Solution sol;
    std::cout << "flower, flow, flight" << sol.longestCommonPrefix(std::vector<std::string>({"flower","flow","flight"})) << std::endl;
    std::cout << "flower, flow, flight" << sol.longestCommonPrefix(std::vector<std::string>({"dog","racecar","car"})) << std::endl;
    return 0;
}
