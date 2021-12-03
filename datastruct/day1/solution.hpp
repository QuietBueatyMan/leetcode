#include <vector>
#include <map>
#include <iostream>
class Solution
{
public:
//a^a=0 a^0=a a^b^c=b^a^c
static int singleNumber(std::vector<int>& nums){
    int result=0;
    for (auto e : nums)
    {
        result^=e;
    }
    
    return result;
}
//
static int majorityElement(std::vector<int>& nums){
    std::map<int,float> numMap;

    for (auto &&i : nums)
    {
       auto iter =numMap.find(i);
       if (iter==numMap.end())
         numMap.insert(std::pair<int,float>(i,1.0));
       else
       {
         numMap[i]=iter->second+1;
       }
    }

    float majorityNum=float(nums.size())/2.0;

    for (auto item :numMap){
        std::cout<<"key:"<<item.first<<"value:"<<item.second<<std::endl;
        if(item.second>majorityNum)
            return item.first;
    }

    return 0;
}
};