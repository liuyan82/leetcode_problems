#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:

    /**
     * in_front: true front part, false: back part
     */
    int FindIn(vector<int>& nums, int target, int start, int end, bool target_in_front) {
        if (end < start) {
            return -1;
        }

        int mid = (start + end) / 2;
        int val = nums.at(mid);
        if (val == target) {
            return mid;
        }

        if (start == end) {
            return -1;
        }

        if (val > nums.back() || nums.front() <= nums.back()) {
            // mid 在前半段
            if (target_in_front) {
                if (target < val) {
                    return FindIn(nums, target, start, mid - 1, target_in_front);
                } else {
                    return FindIn(nums, target, mid + 1, end, target_in_front);
                }
            } else {
                return FindIn(nums, target, mid + 1, end, target_in_front);
            }
        } else {
            // mid 在后半段
            if (target_in_front) {
                return FindIn(nums, target, start, mid - 1, target_in_front);
            } else {
                if (target < val) {
                    return FindIn(nums, target, start, mid - 1, target_in_front);
                } else {
                    return FindIn(nums, target, mid + 1, end, target_in_front);
                }
            }
        }
        
    }

    int search(vector<int>& nums, int target) {
        int start = 0, end = nums.size() - 1;
        bool in_front = false;
        if (nums.front() < nums.back()) {
            // 没旋转
            in_front = true;
        } else if (target <= nums.back()) {
            in_front = false;
        } else if (target >= nums.front()) {
            in_front = true;
        } else {
            return -1;
        }
        return FindIn(nums, target, start, end, in_front);
    }
};

int main(int argc, const char ** argv) {

    vector<int> nums = {1, 3};
    int target = 3;
    Solution sol;
    std::cout << sol.search(nums, target) << std::endl;

    return 0;

}
