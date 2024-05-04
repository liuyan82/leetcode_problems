#include <vector>

using namespace std;

/**
 * @file find_all_sum_combine.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-03
 * 
 * @copyright Copyright (c) 2024
 * 39. 组合总和
已解答
中等
相关标签
相关企业
给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target ，找出 candidates 中可以使数字和为目标数 target 的 所有 不同组合 ，并以列表形式返回。你可以按 任意顺序 返回这些组合。

candidates 中的 同一个 数字可以 无限制重复被选取 。如果至少一个数字的被选数量不同，则两种组合是不同的。 

对于给定的输入，保证和为 target 的不同组合数少于 150 个。

 

示例 1：

输入：candidates = [2,3,6,7], target = 7
输出：[[2,2,3],[7]]
解释：
2 和 3 可以形成一组候选，2 + 2 + 3 = 7 。注意 2 可以使用多次。
7 也是一个候选， 7 = 7 。
仅有这两种组合。
示例 2：

输入: candidates = [2,3,5], target = 8
输出: [[2,2,2,2],[2,3,3],[3,5]]
示例 3：

输入: candidates = [2], target = 1
输出: []
 

提示：

1 <= candidates.length <= 30
2 <= candidates[i] <= 40
candidates 的所有元素 互不相同
1 <= target <= 40
 */

class Solution {
public:
    vector<vector<int> > combinationSum(vector<int>& candidates, int start, int target) {
        std::vector<vector<int> > res;
        int max_count = target / candidates[start];
        if (target % candidates[start] == 0) {
            res.push_back(std::vector(max_count, candidates[start]));
        }
        
        if (start == candidates.size() - 1) {
            // 最后一个数了
            return res;
        }

        for (int count = max_count; count >= 0; --count) {
            int current_sum = candidates[start] * count;
            if (target - current_sum < candidates[start + 1]) {
                continue;
            }
            vector<vector<int> > sub_res = combinationSum(candidates, start + 1, target - current_sum);
            for (vector<int>& x : sub_res) {
                for (int i = 0; i < count; ++i) {
                    x.push_back(candidates[start]);
                }
                res.push_back(x);
            }
        }

        return res;
    }

    vector<vector<int> > combinationSum(vector<int>& candidates, int target) {
        std::sort(candidates.begin(), candidates.end());
        return combinationSum(candidates, 0, target);
    }
};

/**
 * @brief 
 *40. 组合总和 II
中等
相关标签
相关企业
给定一个候选人编号的集合 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的每个数字在每个组合中只能使用 一次 。

注意：解集不能包含重复的组合。 

 

示例 1:

输入: candidates = [10,1,2,7,6,1,5], target = 8,
输出:
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]
示例 2:

输入: candidates = [2,5,2,1,2], target = 5,
输出:
[
[1,2,2],
[5]
]
 

提示:

1 <= candidates.length <= 100
1 <= candidates[i] <= 50
1 <= target <= 30 
 */
class Solution2 {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int start, int target) {
        int same_count = 0;
        for (int i = start; i < candidates.size(); ++i) {
            if (candidates[start] == candidates[i]) {
                ++same_count;
            }
        }

        std::vector<vector<int> > res;
        int max_count = target / candidates[start];
        
        if (target % candidates[start] == 0 && max_count <= same_count) {
            res.push_back(std::vector(max_count, candidates[start]));
        }
        
        if (start == candidates.size() - same_count) {
            // 最后一个数了
            return res;
        }

        max_count = std::min(max_count, same_count);

        for (int count = max_count; count >= 0; --count) {
            int current_sum = candidates[start] * count;
            if (target - current_sum < candidates[start + 1]) {
                continue;
            }
            vector<vector<int> > sub_res = combinationSum2(candidates, start + same_count, target - current_sum);
            for (vector<int>& x : sub_res) {
                for (int i = 0; i < count; ++i) {
                    x.push_back(candidates[start]);
                }
                res.push_back(x);
            }
        }

        return res;
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        std::sort(candidates.begin(), candidates.end());
        return combinationSum2(candidates, 0, target);
    }
};


int main(int argc, const char** argv) {
  Solution2 sol;
  std::vector<int> candidates = {1, 1};
  int target = 1;
  sol.combinationSum2(candidates, target);
}
