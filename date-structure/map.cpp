#include <iostream>

#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        map<int ,int> s;
        for(int i=0;i<nums.size()-1;i++){
            if ( s.find(nums[i])!=s.end() ) s[nums[i]]++;
            else s.insert( pair<int,int>(s[nums[i]],1) );
        }
        for(auto elem:s){
            cout<<elem.first<<elem.second<<endl;
        }
        vector<int> res;
        return res;
    }
};

int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}


