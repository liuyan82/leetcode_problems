/**
 给你一个由 n 个整数组成的数组 nums ，和一个目标值 target 。请你找出并返回满足下述全部条件且不重复的四元组 [nums[a], nums[b], nums[c], nums[d]] （若两个四元组元素一一对应，则认为两个四元组重复）：

0 <= a, b, c, d < n
a、b、c 和 d 互不相同
nums[a] + nums[b] + nums[c] + nums[d] == target
你可以按 任意顺序 返回答案 。

示例 1：

输入：nums = [1,0,-1,0,-2,2], target = 0
输出：[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
示例 2：

输入：nums = [2,2,2,2,2], target = 8
输出：[[2,2,2,2]]
 

提示：

1 <= nums.length <= 200
-109 <= nums[i] <= 109
-109 <= target <= 109

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/4sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 
 */

#include <vector>
#include <iostream>
#include <algorithm>

class Solution {
public:
    std::vector<std::vector<int> > fourSum(std::vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int> > res; 
        for (auto first = nums.begin(); first < nums.end(); first++) {
            for (auto second = first + 1; second < nums.end() - 2; second++) {
                auto left = second + 1;
                auto right = nums.end() - 1;
                int remaining = right - left - 1;
                while (remaining >= 0) {
                    long sum = (long)*first + *second + *left + *right;
                    if (sum == target) {
                        std::vector<int> tupple = {*first, *second, *left, *right};
                        if (res.empty()) {
                            res.push_back(std::move(tupple));
                        } else {
                            auto pos = std::upper_bound(res.begin(), res.end(), tupple, [](const std::vector<int> &l, const std::vector<int> &r) {
                                for (int i = 0; i < 3; ++i) {
                                    if (l[i] < r[i]) {
                                        return true;
                                    } else if (l[i] > r[i]) {
                                        return false;
                                    }
                                }
                                return false;
                            });
                            if (!((*(pos - 1))[0] == tupple[0] && (*(pos - 1))[1] == tupple[1] && (*(pos - 1))[2] == tupple[2] && (*(pos - 1))[3] == tupple[3])) {
                                res.insert(pos, std::move(tupple));
                            }
                        }
                    }

                    if (remaining > 0) {
                        if (sum <= target) {
                            left++;
                        } else {
                            right--;
                        }
                        remaining--;
                    } else {
                        break;
                    }
                }
                
            }
        }
        return res;
    }
};

void printRes(const std::vector<std::vector<int> > &res) {
    std::cout << "[";
    for (auto it = res.begin(); it != res.end(); ++it) {
        std::cout << "[";
        for (auto it2 = it->begin(); it2 != it->end(); ++it2) {
            std::cout << *it2 << ", ";
        }
        std::cout << "], ";
    }
    std::cout << "]" << std::endl;
}

void test1() {
    std::vector<int> nums = {1,0,-1,0,-2,2};
    int target = 0;
    Solution sol;
    std::vector<std::vector<int> > res = sol.fourSum(nums, target);
    printRes(res);
}

void test2() {
    std::vector<int> nums = {2,2,2,2,2};
    int target = 8;
    Solution sol;
    std::vector<std::vector<int> > res = sol.fourSum(nums, target);
    printRes(res);
}

int main(int argc, const char** argv) {
    test1();
    test2();
    return 0;
}