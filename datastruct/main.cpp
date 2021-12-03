
#include "day1/solution.hpp"
#include <vector>
#include <iostream>

int main(){
    //1
    // std::vector<int> tmp={4,1,2,1,2};
    // auto result=Solution::singleNumber(tmp);
    std::vector<int> tmp={3,2,3};
    auto result=Solution::majorityElement(tmp);
    std::cout<<result<<std::endl;
}