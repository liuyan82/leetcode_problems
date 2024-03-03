/**
 给你一个 升序排列 的数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。元素的 相对顺序 应该保持 一致 。

由于在某些语言中不能改变数组的长度，所以必须将结果放在数组nums的第一部分。更规范地说，如果在删除重复项之后有 k 个元素，那么 nums 的前 k 个元素应该保存最终结果。

将最终结果插入 nums 的前 k 个位置后返回 k 。

不要使用额外的空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/remove-duplicates-from-sorted-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。* 
 */
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        auto it = nums.begin();
        auto itEnd = nums.end();
        while (it < itEnd) {
            auto it2 = it;
            for (; it2 < itEnd && *it2 == *it; ++it2);
            if (it2 != it) {
                for (auto it3 = it + 1, it4 = it2; it4 < itEnd; ++it3, ++it4) {
                    *it3 = *it4;
                }
                itEnd -= (it2 - it - 1);
            }
            ++it;
        }

        return itEnd - nums.begin();
    }
};

void test(vector<int> && nums) {
    Solution sol;
    vector<int> data(nums);
    int k = sol.removeDuplicates(data);
    for (int i = 0; i < k; i++) {
        std::cout << data[i] << std::endl;
    }
}

int main(int argc, const char** argv) {
    test({0,0,1,1,1,2,2,3,3,4});
    return 0;
}