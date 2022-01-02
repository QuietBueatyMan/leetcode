#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <algorithm>
#include <unordered_set>

namespace Solutions
{
    class Solution
    {
    public:
        /*
        给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
        你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
        你可以按任意顺序返回答案。
        */
        static std::vector<int> twoSum(std::vector<int> &nums, int target)
        {
            std::map<int, int> hashSet;

            for (int i = 0; i < nums.size(); i++)
            {
                /* code */
                auto lit = hashSet.find(target - nums[i]);
                if (lit == hashSet.end())
                {
                    hashSet[nums[i]] = i;
                }
                else
                {
                    return {lit->second, i};
                }
            }

            return {-1, -1};
        }
        /*
        给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
        请你将两个数相加，并以相同形式返回一个表示和的链表。
        你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
        */
        struct ListNode
        {
            int val;
            ListNode *next;
            ListNode() : val(0), next(nullptr) {}
            ListNode(int x) : val(x), next(nullptr) {}
            ListNode(int x, ListNode *next) : val(x), next(next) {}
        };
        static ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
        {
            if (l2 && l1)
            {
                int addResult = l1->val + l2->val;
                if (addResult >= 10)
                {
                    addResult -= 10;
                    if (l1->next)
                    {
                        l1->next->val = l1->next->val + 1;
                    }
                    else
                    {
                        l1->next = new ListNode(1);
                    }
                }

                l1->val = addResult;

                if (l1->next || l2->next)
                {
                    l1->next = l1->next ? l1->next : new ListNode(0);
                    l2->next = l2->next ? l2->next : new ListNode(0);
                    addTwoNumbers(l1->next, l2->next);
                }
            }
            return l1;
        }
        /*给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。*/
        static int lengthOfLongestSubstring(std::string s)
        {
            int startindex = 0;
            auto nextindex = 0;
            int maxlength = 0;
            std::unordered_set<char> hashSet;
            for (; startindex < s.length(); startindex++)
            {

                while (nextindex < s.length() && (hashSet.find(s[nextindex]) == hashSet.end()))
                {
                    hashSet.insert(s[nextindex]);
                    nextindex++;
                }
                maxlength = std::max(maxlength, nextindex - startindex);

                if (nextindex >= s.length())
                {
                    break;
                }
                hashSet.erase(s[startindex]);
                maxlength = std::max(maxlength, nextindex - startindex);
            }

            return maxlength;
        }
        /*
        给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。
        算法的时间复杂度应该为 O(log (m+n)) 。
        */
        static int GetNum(std::vector<int> &nums1, std::vector<int> &nums2, int target)
        {
            int index1 = 0, index2 = 0;
            int length1 = nums1.size(), length2 = nums2.size();

            while (true)
            {
                if (index1 == length1)
                    return nums2[index2 + target - 1];
                if (index2 == length2)
                    return nums1[index1 + target - 1];
                if (target == 1)
                    return std::min<int>(nums1[index1], nums2[index2]);

                int newIndex1 = std::min<int>(index1 + target / 2 - 1, length1 - 1);
                int newIndex2 = std::min<int>(index2 + target / 2 - 1, length2 - 1);
                if (nums2[newIndex2] >= nums1[newIndex1])
                {
                    target -= newIndex1 - index1 + 1;
                    index1 = newIndex1 + 1;
                }
                else
                {
                    target -= newIndex2 - index2 + 1;

                    index2 = newIndex2 + 1;
                }
            }
        }
        static double findMedianSortedArrays(std::vector<int> &nums1, std::vector<int> &nums2)
        {
            int length = nums1.size() + nums2.size();

            if (length % 2 == 1)
            {
                return GetNum(nums1, nums2, length / 2 + 1);
            }
            else
            {
                return (GetNum(nums1, nums2, length / 2) + GetNum(nums1, nums2, length / 2 + 1)) / 2.0;
            }
        }
        /*给你一个字符串 s，找到 s 中最长的回文子串。*/
        static std::string longestPalindrome(std::string s)
        {
            if (s.length() < 2)
                return s;

            std::vector<std::vector<bool>> res(s.length());

            int maxlength = 1;
            int result_index = 0;

            for (int i = 0; i < s.length(); i++)
            {
                res[i].resize(s.length());
            }

            for (int i = 0; i < s.length(); i++)
            {
                res[i][i] = true;
            }

            for (int len = 2; len <= s.length(); len++)
            {
                for (int start_index = 0, end_index = start_index + len - 1; end_index < s.length(); start_index++, end_index++)
                {
                    if (s[start_index] != s[end_index])
                    {
                        res[start_index][end_index] = false;
                    }
                    else
                    {
                        if (len > 2)
                        {
                            res[start_index][end_index] = res[start_index + 1][end_index - 1];
                        }
                        else
                        {
                            res[start_index][end_index] = true;
                        }
                    }

                    if (res[start_index][end_index] && len > maxlength)
                    {
                        maxlength = len;
                        result_index = start_index;
                    }
                }
            }

            return s.substr(result_index, maxlength);
            // return s.substr(maxlength_start, maxlength);
        }
        /*将一个给定字符串 s 根据给定的行数 numRows ，以从上往下、从左到右进行 Z 字形排列*/
        enum class UpOrDown
        {
            down = 0,
            up = 1
        };
        std::string convert(std::string s, int numRows)
        {
            int rownum = 0;
            UpOrDown dirct = UpOrDown::down;
            std::vector<std::string> rowarray(numRows);
            if (numRows == 1)
            {
                return s;
            }
            for (auto &&i : s)
            {
                rowarray[rownum].push_back(i);
                switch (dirct)
                {
                case UpOrDown::down:
                    if (rownum == numRows - 1)
                    {
                        dirct = UpOrDown::up;
                        rownum--;
                    }
                    else
                    {
                        rownum++;
                    }

                    break;
                case UpOrDown::up:
                    if (rownum == 0)
                    {
                        dirct = UpOrDown::down;
                        rownum++;
                    }
                    else
                    {
                        rownum--;
                    }
                    break;
                }
            }
            std::string result;
            for (auto &&i : rowarray)
            {
                result += i;
            }

            return result;
        }
        /*给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有和为 0 且不重复的三元组。*/
        static std::vector<std::vector<int>> threeSum(std::vector<int> &nums)
        {

            std::vector<std::vector<int>> result;
            std::sort(nums.begin(), nums.end());
            for (auto &&i : nums)
            {
                std::cout << i << "  ";
            }
            int lo = 0;
            int ho = nums.size();
            for (int lo = 0; lo < ho; lo++)
            {
                if (lo == 0 || (nums[lo] != nums[lo - 1]))
                {
                    int lothird = ho - 1;
                    for (int losecond = lo + 1; losecond < ho; losecond++)
                    {
                        if (losecond == lo + 1 || nums[losecond] != nums[losecond - 1])
                        {

                            while (losecond < lothird && nums[lo] + nums[losecond] + nums[lothird] > 0)
                            {
                                lothird--;
                            }

                            if (losecond == lothird)
                            {
                                break;
                            }

                            if (nums[lo] + nums[losecond] + nums[lothird] == 0)
                            {
                                result.push_back({nums[lo], nums[losecond], nums[lothird]});
                            }
                        }
                    }
                }
            }

            return result;
        }
        /*
        以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。
        请你合并所有重叠的区间，并返回一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间。
        */
        static std::vector<std::vector<int>> merge(std::vector<std::vector<int>> &intervals)
        {
            //sort end
            std::sort(intervals.begin(), intervals.end());
            std::vector<std::vector<int>> merge;
            for (std::vector<std::vector<int>>::iterator it = intervals.begin(); it != intervals.end(); it++)
            {
                int L = it->data()[0], R = it->data()[1];

                if (!merge.size() || merge.back()[1] < L)
                {
                    /* code */
                    merge.push_back({L, R});
                }
                else
                {
                    merge.back()[1] = std::max(R, merge.back()[1]);
                }
            }

            return merge;
        }
        /*
        给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
        此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。
        */
        static std::vector<int> sortColors(std::vector<int> &nums)
        {
            std::vector<int>::iterator ptr_zero = nums.begin();
            std::vector<int>::iterator ptr_one = nums.begin();
            for (std::vector<int>::iterator it = nums.begin(); it != nums.end(); it++)
            {
                switch (*it)
                {
                case 0:
                    std::swap(*it, *ptr_zero);
                    if (ptr_zero < ptr_one)
                    {
                        std::swap(*it, *ptr_one);
                    }
                    ptr_zero++;
                    ptr_one++;
                    break;
                case 1:
                    std::swap(*it, *ptr_one);
                    ptr_one++;
                    break;
                default:
                    break;
                }
            }

            return nums;
        }
        /*给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。*/
        static int singleNumber(std::vector<int> &nums)
        {
            int result = 0;
            for (auto e : nums)
            {
                result ^= e;
            }

            return result;
        }
        /*
        给定一个大小为 n 的数组，找到其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。
        你可以假设数组是非空的，并且给定的数组总是存在多数元素。
        */
        static int majorityElement(std::vector<int> &nums)
        {
            std::map<int, float> numMap;

            for (auto &&i : nums)
            {
                auto iter = numMap.find(i);
                if (iter == numMap.end())
                    numMap.insert(std::pair<int, float>(i, 1.0));
                else
                {
                    numMap[i] = iter->second + 1;
                }
            }

            float majorityNum = float(nums.size()) / 2.0;

            for (auto item : numMap)
            {
                std::cout << "key:" << item.first << "value:" << item.second << std::endl;
                if (item.second > majorityNum)
                    return item.first;
            }

            return 0;
        }
        };
} // namespace Solutions