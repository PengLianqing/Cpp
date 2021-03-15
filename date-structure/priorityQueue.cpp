/**
  ****************************(C) COPYRIGHT 2021 Peng****************************
  * @file       algorithm-sort.cpp
  * @brief      
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Jan-1-2021      Peng            1. 完成
  *
  @verbatim
  ==============================================================================
  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2021 Peng****************************
  */
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
    static bool cmp( pair<int,int> a , pair<int,int> b){
        return a.second<b.second;
    }
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int ,int> m;
        for(int num:nums){ //统计元素出现次数
            ++m[num];
        }
        //for(auto elem:m) cout<<elem.first<<","<<elem.second<<endl;
        //建立小顶堆，指定排序算法cmp
        priority_queue<pair<int,int>,vector<pair<int,int>>,decltype(&cmp)> pq;
        for(auto elem:m){ //顶端元素始终为最小值
            int num=elem.first;
            int count=elem.second;
            if(pq.size()<k) pq.push( pair<int,int>(num,count) );
            else{
                if(count>pq.top().second){
                    pq.pop();
                    pq.push( pair<int,int>(num,count) );
                    //pq.emplace(num,count);
                }
            }
        }
        vector<int> ans;
        while(!pq.empty()){
            ans.push_back(pq.top().first);
            pq.pop();
        }
        return ans;
    }
};

int main(){
    return 0;
}