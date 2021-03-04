#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include<numeric>

using namespace std;

/**
  * @brief          内建函数
  * @retval         none
  */
void functionalTest(){
    //算数仿函数
    negate<int> n;
    cout<<n(50)<<endl; //取反仿函数 一元谓词

    plus<int>p;
    cout<<p(10,20)<<endl; //加法仿函数 二元谓词

    //关系仿函数
    vector<int> nums(10);
    for(int i=0;i<10;i++) nums[i]=rand()%32;
    sort(nums.begin(),nums.end(),greater<int>()); //大于仿函数 二元谓词
    for(int num:nums) cout<<num<<",";
    cout<<endl;

    //逻辑仿函数
    vector<bool> v1(10);
    for(int i=0;i<10;i++) v1[i]=rand()%2?true:false;
    for(bool v:v1) cout<<v<<",";
    cout<<endl;
    vector<bool> v2;
    v2.resize(v1.size());
    transform(v1.begin(),v1.end(),v2.begin(),logical_not<bool>()); //逻辑非仿函数 一元谓词
    for(bool v:v2) cout<<v<<",";
    cout<<endl;

}

/**
  * @brief          算法
  * @retval         none
  */
void printnums1(int num){ //普通函数
    cout<<num<<",";
}

class printNums2{ 
    public:
        void operator()(int num){
            cout<<num<<",";
        }
};

void printset3(int num){
    cout<<num<<",";
}

printNums2 printnums2;//函数对象
void algorithmTest(){
    //遍历
    vector<int> nums(10);
    for(int i=0;i<10;i++) nums[i]=rand()%8;
    for_each(nums.begin(), nums.end(), printnums1); //for_each 普通函数实现
    cout<<endl;

    for_each(nums.begin(), nums.end(), printnums2); //for_each 仿函数实现
    cout<<endl;

    vector<int> numsNew(nums.size());
    transform(nums.begin(),nums.end(),numsNew.begin(),bind2nd(plus<int>(),1)); //transform
    //通过函数适配器bind2nd(plus<int>(),1)绑定二元谓词
    for(int num:numsNew) cout<<num<<",";
    cout<<endl;

    //查找
    vector<int>::iterator it=find(nums.begin(),nums.end(),5); //find
    if(it==nums.end()) cout<<"not found."<<endl;
    else cout<<"num:"<<*it<<endl;

    it=find_if(nums.begin(),nums.end(),bind2nd(greater<int>(),5)); //find_if
    if(it==nums.end()) cout<<"not found."<<endl;
    else cout<<"num:"<<*it<<endl;

    it=adjacent_find(nums.begin(),nums.end()); //adjacent_find查找相邻重复元素
    if(it==nums.end()) cout<<"not found."<<endl;
    else cout<<"num:"<<*it<<endl;

    cout<<count(nums.begin(),nums.end(),5)<<endl; //count统计出现次数

    cout<<count_if(nums.begin(),nums.end(),bind2nd(greater<int>(),5))<<endl; //count_if统计满足条件次数

    vector<int> ordernums(10);
    for(int i=0;i<10;i++) ordernums[i]=i;
    bool ans=binary_search(ordernums.begin(),ordernums.end(),5); //bool binary_serach()二分查找
    cout<<(ans?"true":"false")<<endl;

    //排序
    sort(nums.begin(),nums.end()); //sort 排序

    random_shuffle(nums.begin(),nums.end()); //random_shuffle 随机乱序

    vector<int> sq1,sq2;
    for(int i=0;i<5;i++){
        sq1.push_back(i);
        sq2.push_back(i+1);
    }
    vector<int> sq3(sq1.size()+sq2.size());
    merge(sq1.begin(),sq1.end(),sq2.begin(),sq2.end(),sq3.begin()); //merge 和并有序序列
    for(int num:sq3) cout<<num<<",";
    cout<<endl;

    reverse(sq3.begin(),sq3.end()); //reverse 翻转容器元素
    for(int num:sq3) cout<<num<<",";
    cout<<endl;

    //拷贝、替换
    copy(sq1.begin(),sq1.end(),sq2.begin()); //copy

    replace(nums.begin(),nums.end(),5,128); //replace
    for(int num:nums) cout<<num<<",";
    cout<<endl;

    replace_if(nums.begin(),nums.end(),bind2nd(greater<int>(),5),128); //replace_if
    for(int num:nums) cout<<num<<",";
    cout<<endl;

    swap(sq1,sq2); //swap

    //算数生成算法 #include<numeric>
    int total=accumulate(nums.begin(),nums.end(),0); //accumulate返回"起始值+求和值"
    cout<<total<<endl;

    fill(nums.begin(),nums.end(),0); //fill
    for(int num:nums) cout<<num<<",";
    cout<<endl;

    //集合算法 要求有序
    vector<int> set1,set2;
    for(int i=0;i<5;i++){
        set1.push_back(i);
        set2.push_back(i+1);
    }
    vector<int> set3(set1.size()+set2.size());
    vector<int>::iterator itset3 = set_difference(set1.begin(),set1.end(),set2.begin(),set2.end(),set3.begin()); 
    //set_difference 两个有序集合的差集，返回差集的最后一个元素迭代器地址
    for_each(set3.begin(),itset3,printset3);
    cout<<endl;

    itset3 = set_intersection(set1.begin(),set1.end(),set2.begin(),set2.end(),set3.begin()); 
    //set_intersection 两个有序集合的交集，返回交集的最后一个元素迭代器地址
    for_each(set3.begin(),itset3,printset3);
    cout<<endl;

    itset3 = set_union(set1.begin(),set1.end(),set2.begin(),set2.end(),set3.begin()); 
    //set_union 两个有序集合的交集，返回交集的最后一个元素迭代器地址
    for_each(set3.begin(),itset3,printset3);
    cout<<endl;
}

int main(){
    srand(time(NULL));
    functionalTest();
    algorithmTest();
    cout<<"all done."<<endl;
}