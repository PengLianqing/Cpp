#include <iostream>

/*

    生成窗口最大值数组：
    输入8，3，[4,3,5,4,3,3,6,7]
    输出5,5,5,4,6,7

*/

#include <vector>
#include <queue>

using namespace std;

void test(){
    
    int nsize = 8;
    int wsize = 3;
    vector<int> nums{ 4,3,5,4,3,3,6,7 };

    priority_queue<int> pq;
    vector<int> ans(nsize-wsize,0);

    // wsize 窗口内的最大值
    int nmax = nums[0];
    for( int i=0;i<wsize;i++){
        pq.push(nums[i]);
    }
    ans[0] = pq.top();

    // 滑动窗口
    for( int i=wsize;i<nsize;i++){
        int top = pq.top();
        while( !pq.empty() && nums[i]>top ){ // 将小于等于nums[i]的数弹出
            pq.pop();
            top = pq.top();
        }
        if(nums[i-wsize]==top){ //最大值不在滑动窗口了
            pq.pop();
        }
        pq.push(nums[i]);
        ans[i-wsize] = pq.top();
    }

    for(int elem:ans) cout << elem << ",";
    cout << endl;
}

int main()
{
    test();
    std::cout << "all done." << std::endl;
    return 0;
}

