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
#include <iostream>

class Solution {
public:
    int threeSumClosest(std::vector<int>& nums, int target) {

        if (nums.size() < 3) {
            return -1;
        }

        if (nums.size() == 3) {
            return nums[0] + nums[1] + nums[2];
        }

        std::sort(nums.begin(), nums.end());

        long closest = 2147483647;
        auto cur = nums.begin();
        
        for (; cur != nums.end() - 2; cur++) {
            auto left = cur + 1;
            auto right = nums.end() - 1;
            int leftNumbers = right - left - 1;
            int sum = *cur + *left + *right;
            int closestForCurrent = sum;

            // std::cout << "===begin for "  << *cur << std::endl;
            // std::cout << "update: " << *cur << " + " << *left << " + " << *right << " = " << closestForCurrent << std::endl;

            if (sum == target) {
                return sum;
            } else {
                while (leftNumbers > 0) {
                    if (sum == target) {
                        return sum;
                    }
                    int sum2;
                    if (sum < target) {
                        left = left + 1;
                        leftNumbers --;
                        sum2 = *cur + *left + *right;
                    } else if (sum > target) {
                        right = right - 1;
                        leftNumbers --;
                        sum2 = *cur + *left + *right;
                    }

                    if (std::abs(sum2 - target) < std::abs(closestForCurrent - target)) {
                        closestForCurrent = sum2;
                        // std::cout << "update: " << *cur << " + " << *left << " + " << *right << " = " << closestForCurrent << std::endl;
                    }
                    sum = sum2;
                }
            }
            if (std::abs(closestForCurrent - target) < std::abs(closest - target)) {
                // std::cout << "update: "  << closest << " -> " << closestForCurrent << std::endl;
                closest = closestForCurrent;
            }

            // std::cout << "===end for "  << *cur << std::endl;

        }
        return closest;
    }
};

void test1(){
    Solution sol;
    std::vector<int> nums = {-1,2,1,-4};
    const int target = 1;
    int res = sol.threeSumClosest(nums, 1);
    std::cout << "assume: " << 2 << ", actual: " << res << std::endl;
}

void test2(){
    Solution sol;
    std::vector<int> nums = {0,2,1,-3};
    const int target = 1;
    int res = sol.threeSumClosest(nums, target);
    std::cout << "assume: " << 0 << ", actual: " << res << std::endl;
}

void test3() {
    Solution sol;
    std::vector<int> nums = {1,1,1,1};
    const int target = -100;
    int res = sol.threeSumClosest(nums, target);
    std::cout << "assume: " << 3 << ", actual: " << res << std::endl;
}
void test4() {
    Solution sol;
    std::vector<int> nums = {1,2,4,8,16,32,64,128};
    const int target = 82;
    int res = sol.threeSumClosest(nums, target);
    std::cout << "assume: " << 82 << ", actual: " << res << std::endl;
}
void test5() {
    Solution sol;
    std::vector<int> nums = {1,6,9,14,16,70};
    const int target = 81;
    int res = sol.threeSumClosest(nums, target);
    std::cout << "assume: " << 80 << ", actual: " << res << std::endl;
}

void test6() {
    Solution sol;
    std::vector<int> nums = {4,0,5,-5,3,3,0,-4,-5};
    const int target = -2;
    int res = sol.threeSumClosest(nums, target);
    std::cout << "assume: " << 0 << ", actual: " << res << std::endl;
}

void test7() {
    Solution sol;
    std::vector<int> nums = {87,6,-100,-19,10,-8,-58,56,14,-1,-42,-45,-17,10,20,-4,13,-17,0,11,-44,65,74,-48,30,-91,13,-53,76,-69,-19,-69,16,78,-56,27,41,67,-79,-2,30,-13,-60,39,95,64,-12,45,-52,45,-44,73,97,100,-19,-16,-26,58,-61,53,70,1,-83,11,-35,-7,61,30,17,98,29,52,75,-73,-73,-23,-75,91,3,-57,91,50,42,74,-7,62,17,-91,55,94,-21,-36,73,19,-61,-82,73,1,-10,-40,11,54,-81,20,40,-29,96,89,57,10,-16,-34,-56,69,76,49,76,82,80,58,-47,12,17,77,-75,-24,11,-45,60,65,55,-89,49,-19,4};
    const int target = -275;
    int res = sol.threeSumClosest(nums, target);
    std::cout << "assume: " << -274 << ", actual: " << res << std::endl;
}

void test8() {
    Solution sol;
    std::vector<int> nums = {-1000,-999,-998,-997,-996,-995,-994,-993,-992,-991,-990,-989,-988,-987,-986,-985,-984,-983,-982,-981,-980,-979,-978,-977,-976,-975,-974,-973,-972,-971,-970,-969,-968,-967,-966,-965,-964,-963,-962,-961,-960,-959,-958,-957,-956,-955,-954,-953,-952,-951,-950,-949,-948,-947,-946,-945,-944,-943,-942,-941,-940,-939,-938,-937,-936,-935,-934,-933,-932,-931,-930,-929,-928,-927,-926,-925,-924,-923,-922,-921,-920,-919,-918,-917,-916,-915,-914,-913,-912,-911,-910,-909,-908,-907,-906,-905,-904,-903,-902,-901,-900,-899,-898,-897,-896,-895,-894,-893,-892,-891,-890,-889,-888,-887,-886,-885,-884,-883,-882,-881,-880,-879,-878,-877,-876,-875,-874,-873,-872,-871,-870,-869,-868,-867,-866,-865,-864,-863,-862,-861,-860,-859,-858,-857,-856,-855,-854,-853,-852,-851,-850,-849,-848,-847,-846,-845,-844,-843,-842,-841,-840,-839,-838,-837,-836,-835,-834,-833,-832,-831,-830,-829,-828,-827,-826,-825,-824,-823,-822,-821,-820,-819,-818,-817,-816,-815,-814,-813,-812,-811,-810,-809,-808,-807,-806,-805,-804,-803,-802,-801,-800,-799,-798,-797,-796,-795,-794,-793,-792,-791,-790,-789,-788,-787,-786,-785,-784,-783,-782,-781,-780,-779,-778,-777,-776,-775,-774,-773,-772,-771,-770,-769,-768,-767,-766,-765,-764,-763,-762,-761,-760,-759,-758,-757,-756,-755,-754,-753,-752,-751,-750,-749,-748,-747,-746,-745,-744,-743,-742,-741,-740,-739,-738,-737,-736,-735,-734,-733,-732,-731,-730,-729,-728,-727,-726,-725,-724,-723,-722,-721,-720,-719,-718,-717,-716,-715,-714,-713,-712,-711,-710,-709,-708,-707,-706,-705,-704,-703,-702,-701,-700,-699,-698,-697,-696,-695,-694,-693,-692,-691,-690,-689,-688,-687,-686,-685,-684,-683,-682,-681,-680,-679,-678,-677,-676,-675,-674,-673,-672,-671,-670,-669,-668,-667,-666,-665,-664,-663,-662,-661,-660,-659,-658,-657,-656,-655,-654,-653,-652,-651,-650,-649,-648,-647,-646,-645,-644,-643,-642,-641,-640,-639,-638,-637,-636,-635,-634,-633,-632,-631,-630,-629,-628,-627,-626,-625,-624,-623,-622,-621,-620,-619,-618,-617,-616,-615,-614,-613,-612,-611,-610,-609,-608,-607,-606,-605,-604,-603,-602,-601,-600,-599,-598,-597,-596,-595,-594,-593,-592,-591,-590,-589,-588,-587,-586,-585,-584,-583,-582,-581,-580,-579,-578,-577,-576,-575,-574,-573,-572,-571,-570,-569,-568,-567,-566,-565,-564,-563,-562,-561,-560,-559,-558,-557,-556,-555,-554,-553,-552,-551,-550,-549,-548,-547,-546,-545,-544,-543,-542,-541,-540,-539,-538,-537,-536,-535,-534,-533,-532,-531,-530,-529,-528,-527,-526,-525,-524,-523,-522,-521,-520,-519,-518,-517,-516,-515,-514,-513,-512,-511,-510,-509,-508,-507,-506,-505,-504,-503,-502,-501,-500,501,502,503,504,505,506,507,508,509,510,511,512,513,514,515,516,517,518,519,520,521,522,523,524,525,526,527,528,529,530,531,532,533,534,535,536,537,538,539,540,541,542,543,544,545,546,547,548,549,550,551,552,553,554,555,556,557,558,559,560,561,562,563,564,565,566,567,568,569,570,571,572,573,574,575,576,577,578,579,580,581,582,583,584,585,586,587,588,589,590,591,592,593,594,595,596,597,598,599,600,601,602,603,604,605,606,607,608,609,610,611,612,613,614,615,616,617,618,619,620,621,622,623,624,625,626,627,628,629,630,631,632,633,634,635,636,637,638,639,640,641,642,643,644,645,646,647,648,649,650,651,652,653,654,655,656,657,658,659,660,661,662,663,664,665,666,667,668,669,670,671,672,673,674,675,676,677,678,679,680,681,682,683,684,685,686,687,688,689,690,691,692,693,694,695,696,697,698,699,700,701,702,703,704,705,706,707,708,709,710,711,712,713,714,715,716,717,718,719,720,721,722,723,724,725,726,727,728,729,730,731,732,733,734,735,736,737,738,739,740,741,742,743,744,745,746,747,748,749,750,751,752,753,754,755,756,757,758,759,760,761,762,763,764,765,766,767,768,769,770,771,772,773,774,775,776,777,778,779,780,781,782,783,784,785,786,787,788,789,790,791,792,793,794,795,796,797,798,799,800,801,802,803,804,805,806,807,808,809,810,811,812,813,814,815,816,817,818,819,820,821,822,823,824,825,826,827,828,829,830,831,832,833,834,835,836,837,838,839,840,841,842,843,844,845,846,847,848,849,850,851,852,853,854,855,856,857,858,859,860,861,862,863,864,865,866,867,868,869,870,871,872,873,874,875,876,877,878,879,880,881,882,883,884,885,886,887,888,889,890,891,892,893,894,895,896,897,898,899,900,901,902,903,904,905,906,907,908,909,910,911,912,913,914,915,916,917,918,919,920,921,922,923,924,925,926,927,928,929,930,931,932,933,934,935,936,937,938,939,940,941,942,943,944,945,946,947,948,949,950,951,952,953,954,955,956,957,958,959,960,961,962,963,964,965,966,967,968,969,970,971,972,973,974,975,976,977,978,979,980,981,982,983,984,985,986,987,988,989,990,991,992,993,994,995,996,997,998,999};
    const int target = 2994;
    int res = sol.threeSumClosest(nums, target);
    std::cout << "assume: " << 2994 << ", actual: " << res << std::endl;
}

int main(int argc, const char ** argv) {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    return 0;
}

