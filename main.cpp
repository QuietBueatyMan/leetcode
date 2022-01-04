
#include "solution.hpp"
#include <vector>
#include <iostream>

int main()
{
    //1
    // std::vector<int> tmp={4,1,2,1,2};
    // auto result=Solution::singleNumber(tmp);
    // std::vector<int> tmp={3,2,3};
    // auto result=Solution::majorityElement(tmp);
    // std::vector<int> tmp={-1,0,1,2,-1,-4};
    // auto result=Day1::Solution::threeSum(tmp);
    // std::vector<std::vector<int>> tmp = {{1,4},{3,5},{3,7},{9,10},{15,18},{16,20}};
    // std::vector<std::vector<int>> tmp = {{1,4},{2,3}};
    auto result = Solutions::Solution::myAtoi("");
    std::cout << result << std::endl;
    // for (auto item : result)
    // {
    //     std::cout << "["<<item[0]<<","<<item[1]<<"]" << "  ";
    // }
}