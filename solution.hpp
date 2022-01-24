#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <math.h>
#include <string>
#include <stack>

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

        /*
        给你一个 32 位的有符号整数 x ，返回将 x 中的数字部分反转后的结果。
        如果反转后整数超过 32 位的有符号整数的范围 [−231,  231 − 1] ，就返回 0。
        */
        static int32_t reverse(int32_t x)
        {
            // std::string maxValue = "2147483648";

            // std::stringstream stream;
            // std::string value_str;
            // int32_t result;
            // stream << x;
            // stream >> value_str;
            // stream.clear();

            // if (x < 0)
            //     value_str = value_str.substr(1);

            // for (size_t index = 0; index <= (value_str.size() - 1) / 2; index++)
            // {
            //     char tmp = value_str[index];
            //     size_t target_index = value_str.size() - 1 - index;

            //     value_str[index] = value_str[target_index];
            //     value_str[target_index] = tmp;
            // }
            // if (value_str.length() == 10)
            // {
            //     for (size_t index = 0; index < value_str.size(); index++)
            //     {
            //         if (value_str[index] > maxValue[index])
            //         {
            //             return 0;
            //         }
            //         else if (value_str[index] < maxValue[index])
            //             break;
            //     }
            // }

            // stream << value_str;
            // stream >> result;
            // if (x < 0)
            //     result = -result;

            // return result;

            int32_t rev = 0;

            while (x != 0)
            {
                int32_t digit = x % 10;
                x = x / 10;

                if (x == 0 && (rev > 214748364 || rev < -214748364))
                {
                    return 0;
                }
                rev = rev * 10 + digit;
            }

            return rev;
        }

        /*
        请你来实现一个 myAtoi(string s) 函数，使其能将字符串转换成一个 32 位有符号整数（类似 C/C++ 中的 atoi 函数）。
        函数 myAtoi(string s) 的算法如下：
        读入字符串并丢弃无用的前导空格
        检查下一个字符（假设还未到字符末尾）为正还是负号，读取该字符（如果有）。 确定最终结果是负数还是正数。 如果两者都不存在，则假定结果为正。
        读入下一个字符，直到到达下一个非数字字符或到达输入的结尾。字符串的其余部分将被忽略。
        将前面步骤读入的这些数字转换为整数（即，"123" -> 123， "0032" -> 32）。如果没有读入数字，则整数为 0 。必要时更改符号（从步骤 2 开始）。
        如果整数数超过 32 位有符号整数范围 [−231,  231 − 1] ，需要截断这个整数，使其保持在这个范围内。具体来说，小于 −231 的整数应该被固定为 −231 ，大于 231 − 1 的整数应该被固定为 231 − 1 。
        返回整数作为最终结果。
        注意：
        本题中的空白字符只包括空格字符 ' ' 。
        除前导空格或数字后的其余字符串外，请勿忽略 任何其他字符。
        */
        static int32_t myAtoi(std::string s)
        {
            if (s.length() == 0)
                return 0;
            if (s.find_first_not_of(' ') == std::string::npos)
                return 0;

            std::string trmedstr = s.substr(s.find_first_not_of(' '));

            int32_t max_value = 2147483647;
            int32_t min_value = -2147483648;

            int result = 0;
            int negtive = 1;

            for (int i = 0; i < trmedstr.length(); i++)
            {
                if (i == 0)
                {
                    if (trmedstr[0] == '+')
                    {
                        negtive = 1;
                        continue;
                    }
                    else if (trmedstr[0] == '-')
                    {
                        negtive = -1;
                        continue;
                    }
                }

                if (trmedstr[i] >= 48 && trmedstr[i] <= 57)
                {

                    int digit = trmedstr[i] - '0';

                    if (result > max_value / 10)
                        return max_value;
                    else if (result == max_value / 10 && digit > 7)
                        return max_value;
                    else if (result < min_value / 10)
                        return min_value;
                    else if (result == min_value / 10 && digit > 8)
                        return min_value;

                    result = result * 10 + digit * negtive;
                }
                else
                {
                    break;
                }
            }

            return result;
        }

        /*
        给你一个整数 x ，如果 x 是一个回文整数，返回 true ；否则，返回 false .
        */
        static bool isPalindrome(int x)
        {
            if (x < 0)
                return false;
            if (x == 0)
                return true;
            if (x % 10 == 0)
                return false;

            int reverse_value = 0;

            while (x > reverse_value)
            {
                /* code */
                int dight = x % 10;
                reverse_value = reverse_value * 10 + dight;
                x = x / 10;
            }

            return reverse_value == x || reverse_value / 10 == x;
        }

        /*
        给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。
        '.' 匹配任意单个字符
        '*' 匹配零个或多个前面的那一个元素
        所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。
        */
        static bool isMatch(std::string s, std::string p)
        {
            std::vector<std::vector<int>> status = {s.length() + 1, std::vector<int>(p.length() + 1, 0)};

            status[0][0] = true;

            auto matchs = [&](int i, int j) {
                if (i == 0)
                    return false;
                if (p[j - 1] == '.')
                    return true;
                return (s[i - 1] == p[j - 1]);
            };

            for (int index_s = 0; index_s < s.length() + 1; index_s++)
            {
                for (int index_p = 1; index_p < p.length() + 1; index_p++)
                {
                    if (p[index_p - 1] != '*')
                    {
                        if (matchs(index_s, index_p))
                            status[index_s][index_p] |= status[index_s - 1][index_p - 1];
                    }
                    else
                    {
                        status[index_s][index_p] |= status[index_s][index_p - 2];
                        if (matchs(index_s, index_p - 1))
                            status[index_s][index_p] |= status[index_s - 1][index_p];
                    }
                }
            }

            return status[s.length()][p.length()];
        }

        /*
        给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。
        在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0) 。
        找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
        */
        static int maxArea(std::vector<int> &height)
        {
            // int start_index = 0;
            // int end_index = height.size() - 1;
            // int result = 0;

            // for (int index = 0; index < height.size(); index++)
            // {
            //     if (index != 0 && height[index] <= height[start_index])
            //         continue;
            //     for (int tmp_index = end_index; tmp_index > index; tmp_index--)
            //     {
            //         int tmpresult = std::min(height[index], height[tmp_index]) * (tmp_index - index);
            //         if (tmpresult > result)
            //         {
            //             start_index = index;
            //             end_index = tmp_index;
            //             result = tmpresult;
            //         }
            //     }
            // }

            // return result;
            int result = 0;
            std::vector<int>::iterator start_index = height.begin();
            std::vector<int>::iterator end_index = height.end() - 1;
            while (start_index != end_index)
            {
                /* code */
                result = std::max<int>(result, std::min(*start_index, *end_index) * (end_index - start_index));

                if (*start_index < *end_index)
                {
                    start_index++;
                }
                else
                {
                    end_index--;
                }
            }

            return result;
        }

        /*
        罗马数字包含以下七种字符： I， V， X， L，C，D 和 M。
        例如， 罗马数字 2 写做 II ，即为两个并列的 1。12 写做 XII ，即为 X + II 。 27 写做  XXVII, 即为 XX + V + II 。
        通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：
        I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
        X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。 
        C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
        给你一个整数，将其转为罗马数字
        */
        static std::string intToRoman(int num)
        {

            std::map<int, std::string, std::greater<int>> symbolsmap = {
                {1000, "M"},
                {900, "CM"},
                {500, "D"},
                {400, "CD"},
                {100, "C"},
                {90, "XC"},
                {50, "L"},
                {40, "XL"},
                {10, "X"},
                {9, "IX"},
                {5, "V"},
                {4, "IV"},
                {1, "I"}};

            std::string result = "";

            for (auto &&i : symbolsmap)
            {
                while (!(i.first > num))
                {
                    /* code */
                    num -= i.first;
                    result += i.second;
                }
            }

            return result;
        }

        /*
        例如， 罗马数字 2 写做 II ，即为两个并列的 1 。12 写做 XII ，即为 X + II 。 27 写做  XXVII, 即为 XX + V + II 。

        通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：

        I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
        X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。 
        C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
        给定一个罗马数字，将其转换成整数。
        */
        static int romanToInt(std::string s)
        {
            std::map<char, int> symbolsmap = {
                {'M', 1000},
                // {"CM", 900},
                {'D', 500},
                // {"CD", 400},
                {'C', 100},
                // {"XC", 90},
                {'L', 50},
                // {"XL", 40},
                {'X', 10},
                // {"IX", 9},
                {'V', 5},
                // {"IV", 4},
                {'I', 1}};
            int startindex = 0;
            int result = 0;
            while (startindex < s.length())
            {
                /* code */
                char start_char = s[startindex];
                if (startindex + 1 < s.length())
                {
                    char end_char = s[startindex + 1];
                    if (symbolsmap[start_char] < symbolsmap[end_char])
                    {
                        result += (symbolsmap[end_char] - symbolsmap[start_char]);
                        startindex += 2;
                        continue;
                    }
                }
                result += symbolsmap[start_char];
                startindex++;
            }

            return result;
        }

        /*
        编写一个函数来查找字符串数组中的最长公共前缀。
        如果不存在公共前缀，返回空字符串 ""。
        */
        static std::string longestCommonPrefix(std::vector<std::string> &strs)
        {
            std::string commonPrefix = "";
            std::string result = "";

            for (int start_index = 0; start_index < strs.size(); start_index++)
            {
                if (start_index == 0)
                {
                    commonPrefix = strs[start_index];
                    continue;
                }

                int tmp_index = 0;
                int length = 0;

                std::string str = strs[start_index];

                while (commonPrefix[tmp_index] && str[tmp_index] && commonPrefix[tmp_index] == str[tmp_index])
                {
                    /* code */
                    tmp_index++;
                    length++;
                }
                commonPrefix = length > 0 ? commonPrefix.substr(0, length) : "";
            }

            return commonPrefix;
        }

        /*
        给你一个长度为 n 的整数数组 nums 和 一个目标值 target。请你从 nums 中选出三个整数，使它们的和与 target 最接近。
        返回这三个数的和。
        假定每组输入只存在恰好一个解。
        */
        static int threeSumClosest(std::vector<int> &nums, int target)
        {
            std::sort(nums.begin(), nums.end());
            size_t index_p3 = nums.size() - 1;

            int closeestvalue = closeestvalue = nums[index_p3] + nums[1] + nums[0];

            for (size_t index_p1 = 0; index_p1 < nums.size(); index_p1++)
            {

                /* code */
                for (size_t index_p2 = index_p1 + 1; index_p2 < index_p3; index_p2++)
                {
                    /* code */
                    int temp_index = index_p3;
                    while (temp_index > index_p2)
                    {
                        int sumvalue = nums[temp_index] + nums[index_p2] + nums[index_p1];

                        if (sumvalue == target)
                        {
                            return target;
                        }
                        else if (sumvalue < target)
                        {
                            if (std::abs(sumvalue - target) < std::abs(closeestvalue - target))
                            {
                                closeestvalue = sumvalue;
                                index_p3 = temp_index;
                            }
                            break;
                        }
                        else
                        {
                            if (std::abs(sumvalue - target) < std::abs(closeestvalue - target))
                            {
                                closeestvalue = sumvalue;
                            }
                            temp_index--;
                        }
                    }
                }
            }
            return closeestvalue;
        }

        /*
        给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
        给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
        */
        static std::vector<std::string> letterCombinations(std::string digits)
        {
            std::map<char, std::vector<char>> digitmap = {{'2', std::vector<char>{'a', 'b', 'c'}}, {'3', std::vector<char>{'d', 'e', 'f'}}, {'4', std::vector<char>{'g', 'h', 'i'}}, {'5', std::vector<char>{'j', 'k', 'l'}}, {'6', std::vector<char>{'m', 'n', 'o'}}, {'7', std::vector<char>{'p', 'q', 'r', 's'}}, {'8', std::vector<char>{'t', 'u', 'v'}}, {'9', std::vector<char>{'w', 'x', 'y', 'z'}}};
            std::vector<std::string> result;

            for (auto &&digit : digits)
            {
                auto array_chars = digitmap[digit];
                if (result.size() == 0)
                {
                    for (auto item : array_chars)
                    {
                        std::string tmpstr;
                        tmpstr.push_back(item);
                        result.push_back(tmpstr);
                    }
                }
                else
                {
                    std::vector<std::string> tmp_result;
                    for (auto &&str_item : result)
                    {
                        for (auto &&item : array_chars)
                        {

                            std::string tmpstr = str_item;
                            tmpstr.push_back(item);
                            tmp_result.push_back(tmpstr);
                        }
                    }

                    result = tmp_result;
                }
            }

            return result;
        }

        /*
        给你一个由 n 个整数组成的数组 nums ，和一个目标值 target 。
        请你找出并返回满足下述全部条件且不重复的四元组 [nums[a], nums[b], nums[c], nums[d]] 
        （若两个四元组元素一一对应，则认为两个四元组重复）a b c d 不重复
        */
        static std::vector<std::vector<int>> fourSum(std::vector<int> &nums, int target)
        {
            std::vector<std::vector<int>> result;
            if (nums.size() < 4)
                return result;

            std::sort(nums.begin(), nums.end());

            int index_4 = nums.size() - 1;

            for (size_t index_1 = 0; index_1 < nums.size() - 3; index_1++)
            {
                if (index_1 > 0 && nums[index_1] == nums[index_1 - 1])
                {
                    continue;
                }

                for (size_t index_2 = index_1 + 1; index_2 < nums.size() - 2; index_2++)
                {
                    if (index_2 > index_1 + 1 && nums[index_2] == nums[index_2 - 1])
                    {
                        continue;
                    }

                    int start_index = index_2 + 1;
                    int end_index = nums.size() - 1;

                    while (start_index < end_index)
                    {
                        long sumvalue = (long)nums[index_1] + nums[index_2] + nums[start_index] + nums[end_index];

                        if (sumvalue < target)
                        {
                            start_index++;
                        }
                        else if (sumvalue == target)
                        {
                            /* code */
                            result.push_back({nums[index_1], nums[index_2], nums[start_index], nums[end_index]});
                            while (start_index < end_index && nums[end_index - 1] == nums[end_index])
                            {
                                /* code */
                                end_index--;
                            }
                            end_index--;
                            while (start_index < end_index && nums[start_index + 1] == nums[start_index])
                            {
                                /* code */
                                start_index++;
                            }
                            start_index++;
                        }
                        else
                        {
                            end_index--;
                        }
                    }
                }
            }
            return result;
        }

        /*
        给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。
        */
        static ListNode *removeNthFromEnd(ListNode *head, int n)
        {
            std::unordered_map<int, ListNode *> listmap;
            ListNode *nownode = head;
            int index = 0;
            int count = 0;
            while (nownode)
            {
                listmap[index] = nownode;
                count++;
                nownode = nownode->next;
                index++;
            }
            if (count < n)
                return head;
            else
            {
                /* code */
                ListNode *targetNode = listmap[count - n];
                if (targetNode != head)
                {
                    ListNode *frontNode = listmap[count - n - 1];
                    frontNode->next = targetNode->next;
                }
                else
                {
                    head = head->next;
                }
                delete targetNode;
            }
            return head;
        }

        /*
        给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。
        */
        static bool isValid(std::string s)
        {
            std::stack<char> stackcontainer;
            for (auto &&c : s)
            {
                switch (c)
                {
                case '(':
                case '{':
                case '[':
                    stackcontainer.push(c);
                    continue;
                case ')':
                case '}':
                case ']':
                    if (stackcontainer.size() == 0)
                        return false;
                    char target = stackcontainer.top();
                    if (target == '(' && c != ')')
                    {
                        return false;
                    }
                    else if (target == '{' && c != '}')
                    {
                        return false;
                    }
                    else if (target == '[' && c != ']')
                    {
                        return false;
                    }
                    stackcontainer.pop();
                    continue;
                }
            }

            if (stackcontainer.size() == 0)
                return true;
            else
                return false;
        }

        static ListNode *createList(std::vector<int> aray)
        {
            ListNode *dumpHead = new ListNode();
            ListNode *nownode = dumpHead;
            for (auto &&i : aray)
            {
                nownode->next = new ListNode(i);
                nownode = nownode->next;
            }
            auto result = dumpHead->next;
            delete dumpHead;
            return result;
        }

        static void showList(ListNode *head)
        {
            while (head)
            {
                std::cout << head->val << " ";
                head = head->next;
            }
            std::cout << std::endl;
        }

        /*
        将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 
        */
        static ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
        {
            ListNode *dumpend = new ListNode(101);
            ListNode *dumphead = new ListNode(-101, list1);
            ListNode *tmpnode = dumphead;

            while (tmpnode)
            {
                if (!tmpnode->next)
                {
                    tmpnode->next = dumpend;
                    break;
                }
                tmpnode = tmpnode->next;
            }

            ListNode *nownode = dumphead;

            while (list2)
            {

                if (nownode && list2->val >= nownode->next->val)
                {
                    nownode = nownode->next;
                }
                else if (nownode && list2->val < nownode->next->val)
                {
                    ListNode *takenode = list2;
                    list2 = list2->next;
                    takenode->next = nownode->next;
                    nownode->next = takenode;
                    nownode = takenode;
                }
            }

            tmpnode = dumphead;

            while (tmpnode)
            {
                if (tmpnode->next == dumpend)
                {
                    tmpnode->next = nullptr;
                    break;
                }
                tmpnode = tmpnode->next;
            }
            ListNode *result = dumphead->next;

            delete dumphead;
            return result;
        }

        /*
        
        数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
        
        */
        static void dfs(std::string curstr, int open, int close, std::vector<std::string> &res)
        {
            if (open == 0 && close == 0)
            {
                res.push_back(curstr);
                return;
            }

            if (open > close)
                return;

            if (open > 0)
            {
                curstr.push_back('(');
                dfs(curstr, open - 1, close, res);
                curstr.pop_back(); //hui shuo
            }

            if (close > 0)
            {
                curstr.push_back(')');
                dfs(curstr, open, close - 1, res);
            }
        }

        static std::vector<std::string> generateParenthesis(int n)
        {
            std::vector<std::string> result;

            dfs("", n, n, result);

            return result;
        }
        static bool place_valid(size_t row, size_t column, std::vector<std::vector<size_t>> &chessbord)
        {
            size_t row_index = row - 1;
            size_t column_index = column - 1;
            for (size_t i = 0; i < row_index; i++)
            {
                /* code */
                if (chessbord[i][column_index] == 1 || chessbord[row_index-1][column_index-1]==1 || chessbord[row_index-1][column_index+1]==1)
                {
                    return false;
                }
            }

            return true;
        }

        static void brtarce(size_t row, const size_t &rows, std::vector<std::vector<size_t>> &chessbord)
        {
            int colums = rows;
            if (row == rows+1)
            {
                for (size_t tmprow = 0; tmprow < rows; tmprow++)
                {
                    for (size_t tmpcolumn = 0; tmpcolumn < colums; tmpcolumn++)
                    {
                        if (chessbord[tmprow][tmpcolumn] != 0)
                        {
                            std::cout << "x:" << tmprow << ","
                                      << "y:" << tmpcolumn << "  ";
                        }
                    }
                }

                std::cout<<std::endl;
                return;
            }

            for (size_t column = 1; column <= colums; column++)
            {
                if (place_valid(row, column, chessbord))
                {
                    chessbord[row-1][column-1] = 1;
                    brtarce(row + 1, rows, chessbord);
                    chessbord[row-1][column-1] = 0;
                }
            }
        }
        static void queeQuestion(const size_t &n)
        {
            std::vector<std::vector<size_t>> chessbord{n, std::vector<size_t>(n, 0)};
            brtarce(1, n, chessbord);
        }
    };
} // namespace Solutions
