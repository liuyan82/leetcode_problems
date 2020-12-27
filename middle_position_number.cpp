/**
 *4. 寻找两个正序数组的中位数
给定两个大小为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的中位数。

进阶：你能设计一个时间复杂度为 O(log (m+n)) 的算法解决此问题吗？

 

示例 1：

输入：nums1 = [1,3], nums2 = [2]
输出：2.00000
解释：合并数组 = [1,2,3] ，中位数 2
示例 2：

输入：nums1 = [1,2], nums2 = [3,4]
输出：2.50000
解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5
示例 3：

输入：nums1 = [0,0], nums2 = [0,0]
输出：0.00000
示例 4：

输入：nums1 = [], nums2 = [1]
输出：1.00000
示例 5：

输入：nums1 = [2], nums2 = []
输出：2.00000
 

提示：

nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-106 <= nums1[i], nums2[i] <= 106
 */

#include <vector>
#include <iostream>

using namespace std;
class Solution {
public:
    // solution function
    double findMedianSortedArrays(const vector<int>& nums1, const vector<int>& nums2) const {
        return findMedianSortedArrays_Logn_algorithm(nums1, nums2);
    }

private:    
    inline double findMedianSortedArrays_On_algorithm(const vector<int>& nums1, const vector<int>& nums2) const {

        size_t m = nums1.size();
        size_t n = nums2.size();
        size_t mid = (m + n) / 2;
        //cout << "mid : " << mid << endl;
        int i = 0, j = 0, k = 0;
        int midValue1, midValue2;
        for (; i <= m && j <= n && k <= mid; ++k) {
            //cout << "i: " << i << ", j: " << j << endl;
            if (i < m && (j >= n  || nums1[i] < nums2[j])) {
                if (k == mid - 1) {
                    midValue1 = nums1[i];
                } else if (k == mid) {
                    midValue2 = nums1[i];
                }
                //cout << "num " << k << ": " << nums1[i] << endl;
                ++i;
            } else if (j <n && (i >= m || nums1[i] >= nums2[j])) {
                if (k == mid - 1) {
                    midValue1 = nums2[j];
                } else if (k == mid) {
                    midValue2 = nums2[j];
                }
                //cout << "num " << k << ": " << nums2[j] << endl;
                ++j;
            }
        }

        if ((m + n) % 2 == 0) {
            return (midValue1 + midValue2) / 2.0;
        } else {
            return midValue2;
        }
    }

    
private:
    inline double findMedianSortedArrays_Logn_algorithm(const vector<int>& nums1, const vector<int>& nums2) const {
        size_t m = nums1.size();
        size_t n = nums2.size();
        if ((m + n) % 2 == 0) {
            int k1 = (m + n) / 2;
            int v1 = findKthNumber(nums1, nums2, k1);
            int k2 = (m + n) / 2 + 1;
            int v2 = findKthNumber(nums1, nums2, k2);
            std::cout << k1 << "th number is: " << v1 << ", " << k2 << "th number is: " << v2 << std::endl;
            return (v1 + v2) / 2.0;
        } else {
            int k = (m + n) / 2 + 1;
            int v = findKthNumber(nums1, nums2, k);
            std::cout << k << "th number is: " << v << std::endl;
            return v;
        }
    }

    inline int findKthNumber(const vector<int>& nums1, const vector<int>& nums2, size_t k) const {
        return findKthNumber(nums1, nums2, k, 0, 0);
    }

    // 求第k小的数， k = 1, 2, ..., nums1.size() + nums2.size()
    inline int findKthNumber(const vector<int>& nums1, const vector<int>& nums2, size_t k, size_t start1, size_t start2) const {
        std::cout << "find " << k << "th start from "<< start1 << ", " << start2 << std::endl;
        if (start1 >= nums1.size()) {
            return nums2[start2 + k - 1];
        } else if (start2 >= nums2.size()) {
            return nums1[start1 + k - 1];
        }
        
        if (k == 1) {
            int candidate1, candidate2, flag = 0;
            if (start1 < nums1.size()) {
                candidate1 = nums1[start1];
                flag |= 0x1;

            }
            if (start2 < nums2.size()) {
                candidate2 = nums2[start2];
                flag |= 0x2;
            }
            
            switch (flag) {
                case 1:
                    return candidate1;
                case 2:
                    return candidate2;
                case 3:
                    return candidate1 <= candidate2 ? candidate1 : candidate2;
            }
        } else {
            int split = k / 2 - 1;
            if (split + start1 >= nums1.size()) {
                split = nums1.size() - start1 - 1;
            }
            if (split + start2 >= nums2.size()) {
                split = nums2.size() - start2 - 1;
            }

            int v1 = nums1[split + start1];
            int v2 = nums2[split + start2];

            std::cout << "num1[" <<  split << " + " << start1 << "] = " << v1 << std::endl;
            std::cout << "num2[" <<  split << " + " << start2 << "] = " << v2 << std::endl;

            if (v1 < v2) {
                return findKthNumber(nums1, nums2, k - split - 1, start1 + split + 1, start2);
            } else {
                return findKthNumber(nums1, nums2, k - split - 1, start1, start2 + split + 1);
            }
        }

        return 0;
    }
};

int main(int argc, const char** argv) {
    vector<int> a{1, 3, 5, 6, 7, 8, 9, 15};
    vector<int> b{2, 3, 4, 5, 6};
    //vector<int> a{1, 2};
    //vector<int> b{3, 4};
    Solution sol;
    auto x = sol.findMedianSortedArrays(a, b);
    cout << x << endl;
    return 0;
}
