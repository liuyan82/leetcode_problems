/**
给你一个长度为 n 的整数数组 nums 和 一个目标值 target。请你从 nums 中选出三个整数，使它们的和与 target 最接近。

返回这三个数的和。

假定每组输入只存在恰好一个解。

 

示例 1：

输入：nums = [-1,2,1,-4], target = 1
输出：2
解释：与 target 最接近的和是 2 (-1 + 2 + 1 = 2) 。
示例 2：

输入：nums = [0,0,0], target = 1
输出：0
 

提示：

3 <= nums.length <= 1000
-1000 <= nums[i] <= 1000
-104 <= target <= 104

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/3sum-closest
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 
 */

#include <vector>
#include <algorithm>

class Solution {
public:
    int threeSumClosest(std::vector<int>& nums, int target) {
        for (auto it = nums.begin(); it != nums.end(); ++it) {
            *it = *it - target;
        }
        std::sort(nums.begin(), nums.end());

        int sum = target * 3;
        if (nums.front() >= 0) {
            return sum + nums[0] + nums[1] + nums[2];
        } else if (nums.back() <= 0) {
            int i = 0;
            for (auto it = nums.rbegin(); it != nums.rend(), i < 3; ++it, ++i) {
                sum += *it;
            }
            return sum;
        } else {
            int closest = 2147483647;
            auto it1 = nums.begin();
            auto it2 = nums.rbegin();
            for (; *it1 < 0, *it2 > 0; ) {
                if (*it1 < -*it2) {
                }
            }
        }

    }
};

int main(int argc, const char ** argv) {
    return 0;
}
