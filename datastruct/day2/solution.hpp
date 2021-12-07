#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <algorithm>

namespace Day2
{
    class Solution
    {
    public:
        static std::vector<int> sortColors(std::vector<int> &nums)
        {
            // std::vector<int>::iterator ptr = nums.begin();
            // for (std::vector<int>::iterator it = nums.begin(); it != nums.end(); it++)
            // {
            //     if (*it == 0)
            //     {
            //         /* code */
            //         std::swap(*it, *ptr);
            //         ptr++;
            //     }
            // }

            // for (std::vector<int>::iterator it = ptr + 1; it != nums.end(); it++)
            // {
            //     if (*it == 1)
            //     {
            //         /* code */
            //         std::swap(*it, *ptr);
            //         ptr++;
            //     }
            // }
            // return nums;
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

        static std::vector<std::vector<int>> merge(std::vector<std::vector<int>> &intervals)
        {
            //sort end
            std::sort(intervals.begin(), intervals.end());
            std::vector<std::vector<int>> merge;
            for (std::vector<std::vector<int>>::iterator it = intervals.begin(); it != intervals.end(); it++)
            {
                int L=it->data()[0],R=it->data()[1];
                
                if (!merge.size()||merge.back()[1]<L)
                {
                    /* code */
                    merge.push_back({L,R});
                }else
                {
                    merge.back()[1]=std::max(R,merge.back()[1]);
                }
            }

            return merge;
        }
    };
} // namespace Day2