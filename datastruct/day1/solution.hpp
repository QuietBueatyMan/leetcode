#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <algorithm>
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

static std::vector<std::vector<int>> threeSum(std::vector<int>& sums){

    std::vector<std::vector<int>> result;
    std::sort(sums.begin(),sums.end());
    for (auto &&i : sums)
    {
            std::cout<<i<<"  ";

    }
    int lo=0;
    int ho=sums.size();
    std::cout<<"==============="<<std::endl;
    for(int lo=0;lo<ho;lo++){
        if (lo==0 || (sums[lo]!=sums[lo-1]))
        {        
            int lothird=ho-1; 
            for(int losecond=lo+1;losecond<ho;losecond++){
                if (losecond==lo+1||sums[losecond]!=sums[losecond-1]){

                    while (losecond<lothird &&sums[lo]+ sums[losecond]+sums[lothird]>0)
                    {
                        lothird--;
                    }

                    if (losecond==lothird)
                    {
                        break;
                    }
                    
                    if(sums[lo]+ sums[losecond]+sums[lothird]==0){
                       result.push_back({sums[lo],sums[losecond],sums[lothird]});
                    }
                }

            }
        }
    }

    return result; 
}

};